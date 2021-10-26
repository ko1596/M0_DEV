

// *****************************************************************************
//  LTC2944.c
//    20210525
// *****************************************************************************
//==============================================================================
//------------------------------------------------------------------------------
//..............................................................................
//______________________________________________________________________________


#include "All_Header.h"




//******************************************************************************
//	Global
TIMER 	*tm_ltc2944_read;



//******************************************************************************
//
//******************************************************************************
void 	LTC2944_i2c_Init( void )
{

	/*
//	LTC2944 ALCC 		PC10- GPIO-I
	#define 	LTC2944__ALCC_PORT_GROUP			2
	#define 	LTC2944__ALCC_PORT_PIN				10
	#define 	LTC2944__ALCC_PORT_DIR 				0x400 	//	PC10	10000000000
	*/
	PORT_REGS->GROUP[LTC2944__ALCC_PORT_GROUP].PORT_DIR &= ~LTC2944__ALCC_PORT_DIR;
  PORT_REGS->GROUP[LTC2944__ALCC_PORT_GROUP].PORT_PINCFG[LTC2944__ALCC_PORT_PIN] = 0x7; 				//  0111

} 		//void 	LTC2944_i2c_Init( void )








//******************************************************************************
//
//******************************************************************************
void 	LTC2944_Write_ControlReg( UINT8 wData )
{
	if( i2c_interface.i2c_addr != 0 )		{
		return;
	}

	//============================================================================
	i2c_interface.i2c_addr = I2C_DEV_ADDR_LTC2944_IS20;
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
					return;
				}

				sercom5_i2cm_WData( 0x01 );		//	Control Reg.

				sercom5_i2cm_WData( wData );
				i2c_interface.STATE++;
				break;

			case 1:
				sercom5_i2cm_End( );
				i2c_interface.STATE++;
				break;

			case 2:
				i2c_interface.i2c_addr = 0;
				i2c_interface.STATE = 0;
				return;
				break;
		} 		//switch( i2c_interface.STATE)	{

	} 		//while( 1 )		{

} 		//void 	LTC2944_Write_ControlReg( UINT8 wData )


//******************************************************************************
//
//******************************************************************************
void 	LTC2944_GetData( void )
{
	UINT8*	rxPtr;


	if( i2c_interface.i2c_addr != 0 )		{
		return;
	}

	//============================================================================
	i2c_interface.i2c_addr = I2C_DEV_ADDR_LTC2944_IS20;
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
					return;
				}

				sercom5_i2cm_WData( 0x00 );		//	Reg.
				i2c_interface.STATE++;
				break;

			case 1:
				i2c_ack = sercom5_i2cm_Start( i2c_interface.i2c_addr, I2CM_READ_ACTIVE );
				if( i2c_ack == 1 )	{
					flg_mgc_ts = 0;
					i2c_interface.i2c_addr=0;
					i2c_interface.STATE = 0;
					return;
				}
				
				i2c_rxIndex = 0;
				i2c_interface.STATE++;
				break;

			case 2:
				sercom5_i2cm_RData( (UINT8*)rxPtr, 0 );
				i2c_rxIndex++;
				rxPtr++;

				if( i2c_rxIndex > 0x15 )	{
					i2c_interface.STATE++;
				}
				break;

			case 3:
				sercom5_i2cm_End( );
				i2c_interface.STATE++;
				break;

			case 4:
				//	VSENSE– = 70.8V •RESULT(h)/FFFFh = 70.8V •RESULT(DEC)/65535
				M0_AllDevStatus.adc_pw.pw_meter.bat_v = i2c_RxBuf[0x09];
				M0_AllDevStatus.adc_pw.pw_meter.bat_v |= (i2c_RxBuf[0x08] << 8);				
				M0_AllDevStatus.adc_pw.pw_meter.bat_v *= 100;
				M0_AllDevStatus.adc_pw.pw_meter.bat_v *= 708;
				M0_AllDevStatus.adc_pw.pw_meter.bat_v /= 65535;

				//	R(sense) = 3mOHM
				M0_AllDevStatus.adc_pw.pw_meter.bat_i = i2c_RxBuf[0x0F];
				M0_AllDevStatus.adc_pw.pw_meter.bat_i |= (i2c_RxBuf[0x0E] << 8);
				M0_AllDevStatus.adc_pw.pw_meter.bat_i = ((((M0_AllDevStatus.adc_pw.pw_meter.bat_i-32767)*10000)/32767)*(6400/4)) / 100;
				if ( (M0_AllDevStatus.adc_pw.pw_meter.bat_i%10) >=5 )		{
					M0_AllDevStatus.adc_pw.pw_meter.bat_i += 10;
				}
				M0_AllDevStatus.adc_pw.pw_meter.bat_i /= 10;

				//
				M0_AllDevStatus.adc_pw.pw_meter.temp = i2c_RxBuf[0x15];
				M0_AllDevStatus.adc_pw.pw_meter.temp |= (i2c_RxBuf[0x14] << 8);
				M0_AllDevStatus.adc_pw.pw_meter.temp *= 5100;
				M0_AllDevStatus.adc_pw.pw_meter.temp /= 65535;


				i2c_interface.i2c_addr = 0;
				i2c_interface.STATE = 0;
				return;
				break;
		} 		//switch( i2c_interface.STATE)	{

	} 		//while( 1 )		{

} 		//void 	LTC2944_GetData( void )




//********************************************************************
//
//********************************************************************
void 	TimerF_LTC2944_Read( void )
{
	reset_timer( tm_ltc2944_read );
	//==================================================================

  //	LTV2944 Control: 	----------------------------------------------
  //LTC2944_Write_ControlReg( 0x80 | 0x3C );
  //LTC2944_Write_ControlReg( 0xC0 | 0x3C );  
  //LTC2944_Write_ControlReg( 0xF8  );		//	LTV2944 Control: 11 111 00 0
  //LTC2944_Write_ControlReg( 0xC0  );		//	LTV2944 Control: 11 000 00 0
  //LTC2944_Write_ControlReg( 0xE8  );		//	LTV2944 Control: 11 101 00 0
  //LTC2944_Write_ControlReg( 0xF0  );		//	LTV2944 Control: 11 110 00 0
  //LTC2944_Write_ControlReg( 0x70  );		//	LTV2944 Control: 01 110 00 0

	LTC2944_GetData( );
	//SysRTC_Get( (M0_RTC_TIME_FRAME*)&(M0_AllDevStatus.adc_pw.pw_meter.mcu_RTC) );

	//------------------------------------------------------------------
	M0_AllDevStatus.adc_pw.pw_EN = 0x00;
	if( PW_SOLAR_EN_Get() == 0 )	{
		M0_AllDevStatus.adc_pw.pw_EN |= PW_EN_SOLAR;

		M0_AllDevStatus.adc_pw.V_batA = M0_AllDevStatus.adc_pw.adc0 * ADC_BAT_A_FACTOR / 1000;
		M0_AllDevStatus.adc_pw.V_batB = M0_AllDevStatus.adc_pw.adc1 * ADC_BAT_B_FACTOR / 1000;
		M0_AllDevStatus.adc_pw.V_Solar = M0_AllDevStatus.adc_pw.pw_meter.bat_v;
		M0_AllDevStatus.adc_pw.V_DC = VOLT_NOUSED;
	}
	
	else if( PW_DC_EN_Get() == 0 )	{
		M0_AllDevStatus.adc_pw.pw_EN |= PW_EN_DC_IN;

		M0_AllDevStatus.adc_pw.V_batA = M0_AllDevStatus.adc_pw.adc0 * ADC_BAT_A_FACTOR / 1000;
		M0_AllDevStatus.adc_pw.V_batB = M0_AllDevStatus.adc_pw.adc1 * ADC_BAT_B_FACTOR / 1000;
		M0_AllDevStatus.adc_pw.V_Solar = VOLT_NOUSED;
		M0_AllDevStatus.adc_pw.V_DC = M0_AllDevStatus.adc_pw.pw_meter.bat_v;
		
	}

	else if( PW_BAT_A_EN_Get() == 0 )	{
		M0_AllDevStatus.adc_pw.pw_EN |= PW_EN_BAT_A;
		
		M0_AllDevStatus.adc_pw.V_batA = M0_AllDevStatus.adc_pw.pw_meter.bat_v;
		M0_AllDevStatus.adc_pw.V_batB = M0_AllDevStatus.adc_pw.adc1 * ADC_BAT_B_FACTOR / 1000;
		M0_AllDevStatus.adc_pw.V_Solar = VOLT_NOUSED;
		M0_AllDevStatus.adc_pw.V_DC = VOLT_NOUSED;
	}
	else if( PW_BAT_B_EN_Get() == 0 )	{
		M0_AllDevStatus.adc_pw.pw_EN |= PW_EN_BAT_B;

		M0_AllDevStatus.adc_pw.V_batB = M0_AllDevStatus.adc_pw.pw_meter.bat_v;
		M0_AllDevStatus.adc_pw.V_batA = M0_AllDevStatus.adc_pw.adc0 * ADC_BAT_A_FACTOR / 1000;
		M0_AllDevStatus.adc_pw.V_Solar = VOLT_NOUSED;
		M0_AllDevStatus.adc_pw.V_DC = VOLT_NOUSED;
	}
	NOP( );
} 		//void 	TimerF_LTC2944_Read( void )

