

// *****************************************************************************
// 	g_stk8ba53.c
// 			20210809
// *****************************************************************************
//==============================================================================
//------------------------------------------------------------------------------
//..............................................................................
//______________________________________________________________________________


#include "All_Header.h"



//******************************************************************************
//	Global
UINT8  	flg_g_sensor_INT;

TIMER*	tm_STK8BA53_INT_start;


//	Test  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
TIMER*	tm_STK8BA53_Req;
UINT8  	tstBuf[16];



//******************************************************************************
//
//******************************************************************************
void 	STK8BA53_i2c_Init( void )
{
	UINT8		 data;


	// 	CHIP_ID 		==============================================================
	data = 0xFF;
	STK8BA53_i2c_Read( 0x00, &data, 1 );
	if( data != (UINT8)STK8BA53_CHIP_ID ) 	{
		NOP( );
		return;
	}
	NOP( );


	//----------------------------------------------------------------------------
	//	SWRST  -------------------------------------------------------------------
	data = 0xB6;
	STK8BA53_i2c_Write( 0x14, &data, 1 );
	WaitMS( 5 );

	//	RANGESEL  ----------------------------------------------------------------
	/*
		b0011 ±2g 0.98 mg/LSB
		b0101 ±4g 1.95 mg/LSB
		b1000 ±8g 3.91 mg/LSB
	*/
	//data = 0x03; 				//	b0011 ±2g 0.98 mg/LSB
	//data = 0x05; 				//	b0101 ±4g 1.95 mg/LSB
	//data = 0x08; 				//	b1000 ±8g 3.91 mg/LSB
	data = STK8BA53_G_RANGE;
	STK8BA53_i2c_Write( 0x0F, &data, 1 );
	STK8BA53_i2c_Read( 0x0F, &data, 1 );
	NOP( );

	//	BWSEL  	------------------------------------------------------------------
	data = 0x0C; 				//	b01100 125Hz
	STK8BA53_i2c_Write( 0x10, &data, 1 );
	STK8BA53_i2c_Read( 0x10, &data, 1 );
	NOP( );

	
	//----------------------------------------------------------------------------
	//	DATASETUP 		PROTECT_DIS  DATA_SEL
	data = 0x00;
	//data |= 0x80; 		//	DATA_SEL,   =0 : Data output filtered; 
											//	DATA_SEL ‘1’: unfiltered data, ‘0’: filtered data, as the input of the slop detection
	data |= 0x40; 		//	PROTECT_DIS,  =1 : Disable the data protection function
	STK8BA53_i2c_Write( 0x13, &data, 1 );
	STK8BA53_i2c_Read( 0x13, &data, 1 );
	NOP( );

	// 	--------------------------------------------------------------------------
	//	INTEN2,		DATA_EN
	data = 0x00;
	//data |= 0x10; 		//	DATA_EN
	STK8BA53_i2c_Write( 0x17, &data, 1 );
	STK8BA53_i2c_Read( 0x17, &data, 1 );
	NOP( );


	//----------------------------------------------------------------------------
	// 	--------------------------------------------------------------------------
	//	INTCFG1, 	INT1_LV 	INT1_OD
	data = 0x00;  		// 	0 : Active low. + 0 : Push-pull output type.
	STK8BA53_i2c_Write( 0x20, &data, 1 );
	STK8BA53_i2c_Read( 0x20, &data, 1 );
	NOP( );

	// 	--------------------------------------------------------------------------
	//	SIGMOT1, SKIP_TIME[7:0]
	//data = 25; 		//	500ms / 20 = 25
	data = 1; 		//	20ms / 20 = 1
	STK8BA53_i2c_Write( 0x29, &data, 1 );
	STK8BA53_i2c_Read( 0x29, &data, 1 );
	NOP( );

	// 	--------------------------------------------------------------------------
	//	SIGMOT3, PROOF_TIME[7:0]
	//data = 5; 		//	100ms / 20 = 5 
	data = 10; 		//	200ms / 20 = 10 
	STK8BA53_i2c_Write( 0x2B, &data, 1 );
	STK8BA53_i2c_Read( 0x2B, &data, 1 );
	NOP( );

	// 	--------------------------------------------------------------------------
	//	SLOPEDLY
	data = 0x03;
	STK8BA53_i2c_Write( 0x27, &data, 1 );
	STK8BA53_i2c_Read( 0x27, &data, 1 );
	NOP( );

	// 	--------------------------------------------------------------------------
	//	SLOPETHD
	/*
		±2g SLP_THD[7:0] * 3.91
		±4g SLP_THD[7:0] * 7.81
		±8g SLP_THD[7:0] * 15.63
	*/
	//data = 0x64;  		//	±4g   500mg = 50000/781 = 64
	data = 0x25;  		//	±4g   200mg = 20000/781 = 25
	STK8BA53_i2c_Write( 0x28, &data, 1 );
	STK8BA53_i2c_Read( 0x28, &data, 1 );
	NOP( );

	// 	--------------------------------------------------------------------------
	//	INTEN1, 	
	//		SLP_EN_X
	//		SLP_EN_Y
	//		SLP_EN_Z
	data = 0x07;
	STK8BA53_i2c_Write( 0x16, &data, 1 );
	STK8BA53_i2c_Read( 0x16, &data, 1 );
	NOP( );

	// 	--------------------------------------------------------------------------
	//	INTMAP1
	data = 0x00;
	data |= 0x01; 		//	SIGMOT2INT1
	//data |= 0x04; 		//	ANYMOT2INT1
	STK8BA53_i2c_Write( 0x19, &data, 1 );
	STK8BA53_i2c_Read( 0x19, &data, 1 );
	NOP( );


	// 	--------------------------------------------------------------------------
	//	INTMAP2, 	DATA2INT1
	data = 0x00;
	STK8BA53_i2c_Write( 0x1A, &data, 1 );
	STK8BA53_i2c_Read( 0x1A, &data, 1 );
	NOP( );

	// 	--------------------------------------------------------------------------
	//	INTCFG2, 	INT_LATCH[3:0]
	data = 0x00;
	data |= 0x80;  		//	INT_RST
	STK8BA53_i2c_Write( 0x21, &data, 1 );
	STK8BA53_i2c_Read( 0x21, &data, 1 );
	NOP( );




	// 	--------------------------------------------------------------------------
	//	SIGMOT2, 	NY_MOT_EN 	SIG_MOT_EN 	SKIP_TIME[8]
	data = 0x00;
	data |= 0x02;  	//	SIG_MOT_EN
	//data |= 0x04;  	//	ANY_MOT_EN
	STK8BA53_i2c_Write( 0x2A, &data, 1 );
	STK8BA53_i2c_Read( 0x2A, &data, 1 );
	NOP( );




	//	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//============================================================================
	//	INT 		PC09 EIC/EXTINT[1]
	PORT_REGS->GROUP[ICM_INT_PORT_GROUP].PORT_DIR &= ~ICM_INT_PORT_DIR;
	PORT_REGS->GROUP[ICM_INT_PORT_GROUP].PORT_OUT |= ICM_INT_PORT_OUT;
	PORT_REGS->GROUP[ICM_INT_PORT_GROUP].PORT_PINCFG[ICM_INT_PORT_PIN] = 0x7; 				//  0111


}  	//void 	STK8BA53_i2c_Init( void )










//******************************************************************************
//
//******************************************************************************
UINT8 	STK8BA53_i2c_Read( UINT8  regAddr, UINT8* wBuf, UINT16 length )
{
	UINT8*	rxPtr = wBuf;
	UINT16  	rxCnt = 0;


	if( i2c_interface.i2c_addr != 0 )		{
		return FAILURE;
	}

	//============================================================================
	i2c_interface.i2c_addr = I2C_DEV_ADDR_STK8BA53;
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

	return SUCCESS;
}  	//UINT8 	STK8BA53_i2c_Read( UINT8  regAddr, UINT8* wBuf, UINT16 length )


//******************************************************************************
//
//******************************************************************************
UINT8 	STK8BA53_i2c_Write( UINT8  regAddr, UINT8* wBuf, UINT16 length )
{
	UINT8*  	txPtr = wBuf;
	UINT16  	txCnt = 0;


	if( i2c_interface.i2c_addr != 0 )		{
		return FAILURE;
	}

	//============================================================================
	i2c_interface.i2c_addr = I2C_DEV_ADDR_STK8BA53;
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

	return SUCCESS;
}  	//UINT8 	STK8BA53_i2c_Write( UINT8  regAddr, UINT8* wBuf, UINT16 length )











//	****************************************************************************
//
//	****************************************************************************
UINT32 	STK8BA53_get_value( UINT32 g_in )
{
	UINT32 	g_out = g_in >> 4;


	if( g_out & 0x800 )	{
		g_out = 0x1000 - g_out;
	}

	//g_out *=98;
	//g_out *=195;
	//g_out *=391;

	#if 	(STK8BA53_G_RANGE == STK8BA53_RANGE_2G)
		g_out *=98;
	#elif 	(STK8BA53_G_RANGE == STK8BA53_RANGE_4G)
		g_out *=195;
	#else
		g_out *=391;
	#endif

	g_out /= 100;

	return g_out;
}  		//UINT32 	STK8BA53_get_value( UINT32 g_in )


//	****************************************************************************
//
//	****************************************************************************
UINT8 	STK8BA53_acc_Read( void )
{
	int  i;

	// 	--------------------------------------------------------------------------
	for( i=0 ; i<16 ; i++ )		{
		tstBuf[i] = 0x00;
	}
	STK8BA53_i2c_Read( 0x02, tstBuf, 6 );
	NOP( );

	M0_AllDevStatus.g_sensor.stk8ba53.acc_X = STK8BA53_get_value( (tstBuf[0] | (tstBuf[1]<<8)) );
	M0_AllDevStatus.g_sensor.stk8ba53.acc_Y = STK8BA53_get_value( (tstBuf[2] | (tstBuf[3]<<8)) );
	M0_AllDevStatus.g_sensor.stk8ba53.acc_Z = STK8BA53_get_value( (tstBuf[4] | (tstBuf[5]<<8)) );
	NOP( );
	return SUCCESS;
}  	//	UINT8 	STK8BA53_acc_Read( void )


//	****************************************************************************
//
//	****************************************************************************
UINT8 	STK8BA53_acc_INT_Read( void )
{
	int  i;

	UINT32  acc_INT_X;
	UINT32  acc_INT_Y;
	UINT32  acc_INT_Z;

	// 	--------------------------------------------------------------------------
	for( i=0 ; i<16 ; i++ )		{
		tstBuf[i] = 0x00;
	}
	STK8BA53_i2c_Read( 0x02, tstBuf, 6 );
	NOP( );

	acc_INT_X = STK8BA53_get_value( (tstBuf[0] | (tstBuf[1]<<8)) );
	acc_INT_Y = STK8BA53_get_value( (tstBuf[2] | (tstBuf[3]<<8)) );
	acc_INT_Z = STK8BA53_get_value( (tstBuf[4] | (tstBuf[5]<<8)) );

	if( acc_INT_X > M0_AllDevStatus.g_sensor.stk8ba53.acc_INT_X )		{
		M0_AllDevStatus.g_sensor.stk8ba53.acc_INT_X = acc_INT_X;
	}
	if( acc_INT_Y > M0_AllDevStatus.g_sensor.stk8ba53.acc_INT_Y )		{
		M0_AllDevStatus.g_sensor.stk8ba53.acc_INT_Y = acc_INT_Y;
	}
	if( acc_INT_Z > M0_AllDevStatus.g_sensor.stk8ba53.acc_INT_Z )		{
		M0_AllDevStatus.g_sensor.stk8ba53.acc_INT_Z = acc_INT_Z;
	}
	NOP( );
	return SUCCESS;
}  	//	UINT8 	STK8BA53_acc_Read( void )





//********************************************************************
//
//********************************************************************
void 	TimerF_STK8BA53_INT( void )
{
	reset_timer( tm_STK8BA53_INT_start );

	reset_timer( tm_STK8BA53_Req );

	//==================================================================
	STK8BA53_acc_INT_Read( );
	NOP( );

	if( M0_AllDevStatus.g_sensor.stk8ba53.flg_INT > STK8BA53_INT_COUNT )	{
		close_timer( tm_STK8BA53_INT_start );
		M0_AllDevStatus.g_sensor.stk8ba53.flg_INT = 0;

		SysRTC_Get( (M0_RTC_TIME_FRAME*)&(M0_AllDevStatus.g_sensor.mcu_RTC) );
		UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_G_SENSOR, (uint8_t*)&(M0_AllDevStatus.g_sensor), sizeof(M0_G_SENSOR_FRAME) );
		return;
	}

	M0_AllDevStatus.g_sensor.stk8ba53.flg_INT++;
}  		//void 	TimerF_STK8BA53_INT( void )


//********************************************************************
//
//********************************************************************
void 	TimerF_STK8BA53_Normal_Read( void )
{

	reset_timer( tm_STK8BA53_Req );

	//==================================================================
	M0_AllDevStatus.g_sensor.stk8ba53.acc_INT_X = M0_AllDevStatus.g_sensor.stk8ba53.acc_INT_Y = M0_AllDevStatus.g_sensor.stk8ba53.acc_INT_Z = 0;
	STK8BA53_acc_Read( );
	SysRTC_Get( (M0_RTC_TIME_FRAME*)&(M0_AllDevStatus.g_sensor.mcu_RTC) );
	NOP( );

	#if 	Tst_STK8BA53_NORMAL_SHOW
		SysRTC_Get( (M0_RTC_TIME_FRAME*)&(M0_AllDevStatus.g_sensor.mcu_RTC) );
		UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_G_SENSOR, (uint8_t*)&(M0_AllDevStatus.g_sensor), sizeof(M0_G_SENSOR_FRAME) );
	#endif  	//#if 	Tst_STK8BA53_NORMAL_SHOW
	NOP( );
}  		//void 	TimerF_STK8BA53_Normal_Read( void )

