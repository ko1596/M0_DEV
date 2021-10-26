

// *******************************************************************
//  lm75.c
//    20210517
// *******************************************************************
//====================================================================
//--------------------------------------------------------------------
//....................................................................
//____________________________________________________________________


#include "All_Header.h"




//********************************************************************
//	Global
TIMER 	*tm_lm75_read;


#if 	Tst_LM75_01
	UINT32 	lm75_Data;
#endif 		//#if 	Tst_LM75_01




//********************************************************************
//
//********************************************************************
void 	lm75_i2c_Init( void )
{
	NOP( );
} 		//void 	lm75_i2c_Init( void )


//********************************************************************
//
//********************************************************************
void 	TimerF_LM75_Read( void )
{
	reset_timer( tm_lm75_read );
	//==================================================================

	lm75_GetData( );
} 		//void 	TimerF_LM75_Read( void )


//********************************************************************
//
//********************************************************************
void 	lm75_GetData( void )
{
	UINT8 	rData;
	UINT16 	tempData;

	if( i2c_interface.i2c_addr != 0 )		{
		return;
	}

	//==================================================================
	i2c_interface.i2c_addr = I2C_DEV_ADDR_LM75;
	i2c_interface.STATE = 0;
	i2c_interface.i2c_delay = I2CM_DELAY_200KHZ;

	memset( i2c_RxBuf, 0x00, I2CM_RX_BUF_SIZE );
	i2c_rxIndex = 0;


	//============================================================================
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

				sercom5_i2cm_WData( 0x00 );
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
				
				i2c_interface.STATE++;
				break;

			case 2:
				sercom5_i2cm_RData( (UINT8*)&rData, 0 );
				tempData = ((UINT32)rData<<8);
				sercom5_i2cm_RData( (UINT8*)&rData, 1 );
				tempData |= rData;



				tempData = (tempData >> 7);
				//	TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				//tempData = 0x1FF;		//	TEST
				//tempData = 0x1CE;		//	TEST
				//tempData = 0x192;		//	TEST

				if( (tempData & 0x100) == 0 )	{
					M0_AllDevStatus.temperature.temp0 = (tempData>>1)*100;
					if( tempData & 0x01 )	{
						M0_AllDevStatus.temperature.temp0 += 50;
					}
					NOP( );
				}
				else	{
					M0_AllDevStatus.temperature.temp0 = ((0x200-tempData)>>1)*100;
					if( tempData & 0x01 )	{
						M0_AllDevStatus.temperature.temp0 += 50;
					}
					M0_AllDevStatus.temperature.temp0 |= 0x80000000;
				}
				NOP( );
				i2c_interface.STATE++;
				break;

			case 3:
				sercom5_i2cm_End( );
				i2c_interface.STATE++;
				break;

			case 4:
				i2c_interface.i2c_addr = 0;
				i2c_interface.STATE = 0;

				#if !Tst_LM75_01
					//close_timer( tm_lm75_read );
				#endif 		//#if !Tst_LM75_01
				return;
				break;
		} 		//switch( i2c_interface.STATE)	{

	} 		//while( 1 )		{
} 		//void 	lm75_GetData( void )

