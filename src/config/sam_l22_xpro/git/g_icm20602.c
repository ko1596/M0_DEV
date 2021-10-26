

// *****************************************************************************
// 	g_icm20602.c
// 	20210603
// *****************************************************************************
//==============================================================================
//------------------------------------------------------------------------------
//..............................................................................
//______________________________________________________________________________


#include "All_Header.h"




//******************************************************************************
//	Global
UINT8  	ICM_who_am_i;

UINT8  	flg_g_sensor_INT;
TIMER*	tm_ICM20602_INT_start;


#if  	Tst_ICM_01
	TIMER*	tm_ICM20602_Req;

	UINT32	acc_X;
	UINT32	acc_Y;
	UINT32	acc_Z;
#endif  	//#if  	Tst_ICM_01



//******************************************************************************
//
//******************************************************************************
void 	ICM20602_i2c_Init( void )
{
	UINT8		 data;


	memset( (UINT8*)&(M0_AllDevStatus.g_sensor), 0x00, sizeof(M0_G_SENSOR_FRAME) );
	flg_g_sensor_INT = 0;
	tm_ICM20602_INT_start = NULL;

	//	INT 		PC09 EIC/EXTINT[1]
	PORT_REGS->GROUP[ICM_INT_PORT_GROUP].PORT_DIR &= ~ICM_INT_PORT_DIR;
	PORT_REGS->GROUP[ICM_INT_PORT_GROUP].PORT_OUT |= ICM_INT_PORT_OUT;
	PORT_REGS->GROUP[ICM_INT_PORT_GROUP].PORT_PINCFG[ICM_INT_PORT_PIN] = 0x7; 				//  0111

	// 	Who am I 		==============================================================
	data = 0xFF;
	ICM20602_i2c_Read( ICM20602REG_WHO_AM_I, &ICM_who_am_i, 1 );
	if( ICM_who_am_i != (UINT8)ICM20602_WHO_AM_I ) 		{
		NOP( );
		return;
	}
	NOP( );

	//============================================================================
	// full reset of chip
	data = 0x80;
	if( ICM20602_i2c_Write( ICM20602REG_PWR_MGMT_1, &data, 1 ) != SUCCESS )	{
		NOP( );
		return;
	}
	WaitMS( 1000 );

	//	CK ICM20602  		--------------------------------------------------------
	data = 0xFF;
	ICM20602_i2c_Read( ICM20602REG_CONFIG, &data, 1 );
	if( data != 0x80 )	{
		return;
	}

	data = 0xFF;
	ICM20602_i2c_Read( ICM20602REG_PWR_MGMT_1, &data, 1 );
	if( data != 0x41 )	{
		return;
	}


	//======================================================================================
	// set clock to internal PLL  ==========================================================
	data = 0x01;
	ICM20602_i2c_Write( ICM20602REG_PWR_MGMT_1, &data, 1 );
	
	// place accel and gyro on standby 	====================================================
	data = 0x3F;
	ICM20602_i2c_Write( ICM20602REG_PWR_MGMT_2, &data, 1 );
	
	// disable fifo 	======================================================================
	data = 0x00;
	ICM20602_i2c_Write( ICM20602REG_USER_CTRL, &data, 1 );


	// Step 2: Accelerometer Configuration 	================================================
	//ACCEL_FCHOICE_B = 1 and A_DLPF_CFG[2:0] = 1 (b001); 4KHz
	// 0001 1000 : Average 8 samples + 4KHz 
	//data = 0x18;
	// 	0001	:	Average 8 samples 
	//	0 110 : 1kHz
	//		0001 0110
	//data = 0x16;
	// 0011	3 = Average 32 samples		..........................................................
	// 0 111
 	//data = 0x37;
	// 0011	3 = Average 32 samples		..........................................................
	// 0 001
	data = 0x31;
	ICM20602_i2c_Write( ICM20602REG_ACCEL_CONFIG_2, &data, 1 );	
	

  // 111 11 000 : XYZ Accel self-test +-16g (11) 	========================================
	data = 0xF0;		//	+-8g  111 10 000	
	//data = 0xE8;		//	+-4g  111 01 000	
	//data = 0xE0;		//	+-2g  111 00 000	
	ICM20602_i2c_Write( ICM20602REG_ACCEL_CONFIG, &data, 1 );
	//M0_AllDevStatus.g_sensor.icm20602.g_fact = 2048;		//	+-16g
	M0_AllDevStatus.g_sensor.icm20602.g_fact = 4096;		//	+-8g
	//M0_AllDevStatus.g_sensor.icm20602.g_fact = 8192;		//	+-4g
	//M0_AllDevStatus.g_sensor.icm20602.g_fact = 16384;		//	+-2g


	// enable FIFO ; D88	==================================================================	//  0100 0100
  //data = 0x44;
	//ICM20602_i2c_Write( ICM20602REG_USER_CTRL, &data, 1 );	
	
	// enable FIFO if requested 	==========================================================
	//tmp = ((dev->use_accel) && (dev->accel_fifo)) ? 0x08 : 0x00;
	//tmp |= ((dev->use_gyro) && (dev->gyro_fifo)) ? 0x10 : 0x00;
	//data = 0x08;   //  ACCEL_FIFO_EN
	//ICM20602_i2c_Write( ICM20602REG_FIFO_EN, &data, 1 );
	
	//  00000111 = 0x07;  gyro:Disable; accelerometer On
	data = 0x07;
	ICM20602_i2c_Write( ICM20602REG_PWR_MGMT_2, &data, 1 );



	//======================================================================================
	//	INIT Init
	//======================================================================================
	//  1011 1000
	data = 0xB8;
	ICM20602_i2c_Write( ICM20602REG_INT_PIN_CFG, &data, 1 );
	
	//  Step 3: Enable Motion Interrupt 	==================================================
	//    In INT_ENABLE register (0x38) set WOM_X_INT_EN = WOM_Y_INT_EN = WOM_Z_INT_EN = 1 to enable motion interrupt for X, Y, and Z axis
	//data = 0xF0;   //  11110000
	data = 0xE0;   //  111 00000
	ICM20602_i2c_Write( ICM20602REG_INT_ENABLE, &data, 1 );
	
	
	//  Step 4: Set Motion Threshold 	======================================================
	//    Set the motion threshold for X-axis in ACCEL_WOM_X_THR register (0x20)
	//    Set the motion threshold for Y-axis in ACCEL_WOM_Y_THR register (0x21)
	//    Set the motion threshold for Z-axis in ACCEL_WOM_Z_THR register (0x22)
	M0_AllDevStatus.g_sensor.icm20602.acc_wom_X = M0_AllDevStatus.g_sensor.icm20602.acc_wom_Y = M0_AllDevStatus.g_sensor.icm20602.acc_wom_Z = (UINT8)(ICM20602_ACC_WOM_DEFAULT*256/100);
	
	data = M0_AllDevStatus.g_sensor.icm20602.acc_wom_X;
	ICM20602_i2c_Write( ICM20602REG_ACCEL_WOM_X_THR, &data, 1 );		

	data = M0_AllDevStatus.g_sensor.icm20602.acc_wom_Y;
	ICM20602_i2c_Write( ICM20602REG_ACCEL_WOM_Y_THR, &data, 1 );	

	data = M0_AllDevStatus.g_sensor.icm20602.acc_wom_Z;
	ICM20602_i2c_Write( ICM20602REG_ACCEL_WOM_Z_THR, &data, 1 );	
	
	
	//  Step 5: Set Interrupt Mode 	========================================================
	//    In ACCEL_INTEL_CTRL register (0x69) clear bit 0 (WOM_TH_MODE) to 
	//			select the motion interrupt as an OR of the enabled interrupts for X, Y, Z-axes 
	//			and set bit 0 to make the interrupt an AND of the enabled interrupts for X, Y, Z axes
	
	//  Step 6: Enable Accelerometer Hardware Intelligence	================================
	//    In ACCEL_INTEL_CTRL register (0x69) set ACCEL_INTEL_EN = ACCEL_INTEL_MODE = 1
	//	11 0000 1 0
	//data = 0xC2;
	data = 0x80;
	ICM20602_i2c_Write( ICM20602REG_ACCEL_INTEL_CTRL, &data, 1 );	
	
	//  Step 7: Set Frequency of Wake-Up 	==================================================
	//    In SMPLRT_DIV register (0x19) set SMPLRT_DIV[7:0] = 3.9Hz – 500Hz	
	data = 1;
	ICM20602_i2c_Write( ICM20602REG_SMPLRT_DIV, &data, 1 );
	

	//  Step 8: Enable Cycle Mode (Accelerometer Low-Power Mode) 	==========================
	//    In PWR_MGMT_1 register (0x6B) set CYCLE = 1
	//data = 0xFF;
	//ICM20602_i2c_Read( ICM20602REG_PWR_MGMT_1, &data, 1 );
	//data |= 0x20;		//	0010 0000
	//ICM20602_i2c_Write( ICM20602REG_PWR_MGMT_1, &data, 1 );
	NOP( );
	NOP( );
} 		//void 	ICM20602_i2c_Init( void )








//******************************************************************************
//
//******************************************************************************
UINT8 	ICM20602_i2c_Write( UINT8  regAddr, UINT8* wBuf, UINT16 length )
{
	UINT8*  	txPtr = wBuf;
	UINT16  	txCnt = 0;


	if( i2c_interface.i2c_addr != 0 )		{
		return FAILURE;
	}

	//============================================================================
	i2c_interface.i2c_addr = I2C_DEV_ADDR_ICM20602_SA1;
	i2c_interface.STATE = 0;
	i2c_interface.i2c_delay = I2CM_DELAY_350KHZ;

	//============================================================================
	//	I2C Start
	NOP( );
	while( 1 )		{

		switch( i2c_interface.STATE)	{
			case 0:
				i2c_ack = sercom5_i2cm_Start( i2c_interface.i2c_addr, I2CM_WRITE_ACTIVE );
				if( i2c_ack == 1 )	{
					flg_mgc_ts = 0;
					i2c_interface.i2c_addr=0;
					i2c_interface.STATE = 0;
					return FAILURE;
				}

				sercom5_i2cm_WData( regAddr );		//	Reg.
				txPtr = wBuf;
				txCnt = 0;

				i2c_interface.STATE++;
				break;

			case 1:
				if( txCnt >= length ) 		{
					i2c_interface.STATE++;
					break;
				}
				sercom5_i2cm_WData( *txPtr );
				txPtr ++;
				txCnt ++;
				break;

			case 2:
				sercom5_i2cm_End( );
				i2c_interface.i2c_addr = 0;
				i2c_interface.STATE = 0;
				return SUCCESS;
				break;
		} 		//switch( i2c_interface.STATE)	{
	} 		//while( 1 )		{

} 		//UINT8 	ICM20602_i2c_Write( UINT8  regAddr, UINT8* wBuf, UINT16 length )


//******************************************************************************
//
//******************************************************************************
UINT8 	ICM20602_i2c_Read( UINT8  regAddr, UINT8* wBuf, UINT16 length )
{
	UINT8*	rxPtr = wBuf;
	UINT16  	rxCnt = 0;


	if( i2c_interface.i2c_addr != 0 )		{
		return FAILURE;
	}

	//============================================================================
	i2c_interface.i2c_addr = I2C_DEV_ADDR_ICM20602_SA1;
	i2c_interface.STATE = 0;
	i2c_interface.i2c_delay = I2CM_DELAY_350KHZ;

	memset( i2c_RxBuf, 0x00, I2CM_RX_BUF_SIZE );
	rxPtr = i2c_RxBuf;
	i2c_rxIndex = 0;

	//============================================================================
	//	I2C Start
	NOP( );
	while( 1 )		{

		switch( i2c_interface.STATE)	{
			case 0:
				i2c_ack = sercom5_i2cm_Start( i2c_interface.i2c_addr, I2CM_WRITE_ACTIVE );
				if( i2c_ack == 1 )	{
					flg_mgc_ts = 0;
					i2c_interface.i2c_addr=0;
					i2c_interface.STATE = 0;
					return FAILURE;
				}

				sercom5_i2cm_WData( regAddr );		//	Reg.
				i2c_interface.STATE++;
				break;

			case 1:
				i2c_ack = sercom5_i2cm_Start( i2c_interface.i2c_addr, I2CM_READ_ACTIVE );
				if( i2c_ack == 1 )	{
					flg_mgc_ts = 0;
					i2c_interface.i2c_addr=0;
					i2c_interface.STATE = 0;
					return FAILURE;
				}

				rxPtr = wBuf;
				rxCnt = 0;
				
				i2c_rxIndex = 0;
				i2c_interface.STATE++;
				break;

			case 2:
				if( rxCnt >= (length - 1) )	{
					i2c_interface.STATE++;
					break;
				}
				sercom5_i2cm_RData( (UINT8*)rxPtr, 0 );
				rxPtr++;
				rxCnt++;
				break;

			case 3:
				sercom5_i2cm_RData( (UINT8*)rxPtr, 1 );
				sercom5_i2cm_End( );
				i2c_interface.i2c_addr = 0;
				i2c_interface.STATE = 0;
				return SUCCESS;
				break;
		} 		//switch( i2c_interface.STATE)	{
	} 		//while( 1 )		{

} 		//UINT8 	ICM20602_i2c_Read( UINT8  regAddr, UINT8* wBuf, UINT16 length )










//	**************************************************************************************
//
//	**************************************************************************************
static 	UINT32	 	ICM20602_get_gData( UINT16 data )
{
	UINT32 	G_value;
	int			flg_negative = 0;
	
	
	if( data & 0x8000 )	{
		G_value = 0xFFFF0000 | data;
		flg_negative = 1;
		NOP( );
		G_value = ~G_value;
		NOP( );
	}
	else	{
		flg_negative = 0;		
		G_value = (UINT32)data& 0x0000FFFF;
	}
	
	G_value *= 1000;
	G_value /= M0_AllDevStatus.g_sensor.icm20602.g_fact;
	
	if( flg_negative )	{
		G_value |= 0x80000000;
	}	
	return G_value;
}		//static 	UINT32	 	ICM20602_get_gData( UINT16 data )


//	**************************************************************************************
//
//	**************************************************************************************
UINT8 	ICM20602_acc_Read( void )
{
	UINT8		rBuf[6];

	NOP( );
	ICM20602_i2c_Read( ICM20602REG_ACCEL_XOUT_H, rBuf, 6 );

	NOP( );
	
	M0_AllDevStatus.g_sensor.icm20602.acc_X = ICM20602_get_gData( (rBuf[0]<<8)|rBuf[1] );
	M0_AllDevStatus.g_sensor.icm20602.acc_Y = ICM20602_get_gData( (rBuf[2]<<8)|rBuf[3] );
	M0_AllDevStatus.g_sensor.icm20602.acc_Z = ICM20602_get_gData( (rBuf[4]<<8)|rBuf[5] );
	NOP( );
	
	return SUCCESS;
}		//UINT8 	ICM20602_acc_Read( void )


//	**************************************************************************************
//
//	**************************************************************************************
UINT8	 	ICM20602_acc_Read_INT( void )
{
	UINT8		rBuf[6];
	UINT32 	tDataX;
	UINT32 	tDataY;
	UINT32 	tDataZ;

	NOP( );
	ICM20602_i2c_Read( ICM20602REG_ACCEL_XOUT_H, rBuf, 6 );
	NOP( );
	
	
	tDataX = ICM20602_get_gData( (rBuf[0]<<8)|rBuf[1] ) & 0x007FFF;
	tDataY = ICM20602_get_gData( (rBuf[2]<<8)|rBuf[3] ) & 0x007FFF;
	tDataZ = ICM20602_get_gData( (rBuf[4]<<8)|rBuf[5] ) & 0x007FFF;
	NOP( );


	if( tDataX > M0_AllDevStatus.g_sensor.icm20602.acc_X )	{
		M0_AllDevStatus.g_sensor.icm20602.acc_X = tDataX;
	}
	if( tDataY > M0_AllDevStatus.g_sensor.icm20602.acc_Y )	{
		M0_AllDevStatus.g_sensor.icm20602.acc_Y = tDataY;
	}
	if( tDataZ > M0_AllDevStatus.g_sensor.icm20602.acc_Z )	{
		M0_AllDevStatus.g_sensor.icm20602.acc_Z = tDataZ;
	}

	return SUCCESS;
}		//UINT8	 	ICM20602_acc_Read_INT( void )






//********************************************************************
//
//********************************************************************
void 	TimerF_ICM20602_INT_period( void )
{	
	if( (M0_AllDevStatus.g_sensor.icm20602.acc_X != 0) 
			&& (M0_AllDevStatus.g_sensor.icm20602.acc_Y != 0)
			&& (M0_AllDevStatus.g_sensor.icm20602.acc_Z != 0) )  	{

		if( (M0_AllDevStatus.g_sensor.icm20602.acc_X < 1000) 
				&& (M0_AllDevStatus.g_sensor.icm20602.acc_Y < 1000)
				&& (M0_AllDevStatus.g_sensor.icm20602.acc_Z < 1000) )  	{
			NOP( );
		}
		else 	{
			SysRTC_Get( (M0_RTC_TIME_FRAME*)&(M0_AllDevStatus.g_sensor.mcu_RTC) );
			UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_G_SENSOR, (uint8_t*)&(M0_AllDevStatus.g_sensor), sizeof(M0_G_SENSOR_FRAME) );		
		}
	}

	M0_AllDevStatus.g_sensor.icm20602.flg_INT = 0;

	//==================================================================
	close_timer( tm_ICM20602_INT_start );
} 		//void 	TimerF_ICM20602_INT_period( void )


//	****************************************************************************
//
//	****************************************************************************
void 	ICM20602_AlarmMsg( void )
{
	
	if( M0_AllDevStatus.g_sensor.icm20602.flg_INT )		{
		M0_AllDevStatus.g_sensor.icm20602.flg_INT = 0;

		//==========================================================================
		SysRTC_Get( (M0_RTC_TIME_FRAME*)&(M0_AllDevStatus.g_sensor.mcu_RTC) );
		UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_G_SENSOR, (uint8_t*)&(M0_AllDevStatus.g_sensor), sizeof(M0_G_SENSOR_FRAME) );
	} 		//if( M0_AllDevStatus.g_sensor.icm20602.flg_INT )		{
} 		//void	ICM20602_AlarmMsg( void )






#if  	Tst_ICM_01
//********************************************************************
//
//********************************************************************
void 	TimerF_ICM20602_Read( void )
{
	UINT8		rBuf[6];


	reset_timer( tm_ICM20602_Req );
	//==================================================================

	//ICM20602_acc_Read( );
	//NOP( );

	

	NOP( );
	ICM20602_i2c_Read( ICM20602REG_ACCEL_XOUT_H, rBuf, 6 );

	NOP( );	
	acc_X = ICM20602_get_gData( (rBuf[0]<<8)|rBuf[1] );
	acc_Y = ICM20602_get_gData( (rBuf[2]<<8)|rBuf[3] );
	acc_Z = ICM20602_get_gData( (rBuf[4]<<8)|rBuf[5] );
	NOP( );
}  	//void 	TimerF_ICM20602_Read( void )
#endif  	//#if  	Tst_ICM_01

