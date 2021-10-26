

// *****************************************************************************
//  mgc3130.c
//    20210322
// *****************************************************************************
//==============================================================================
//------------------------------------------------------------------------------
//..............................................................................
//______________________________________________________________________________


#include "All_Header.h"




//******************************************************************************
//	Global
UINT8 	flg_mgc_ts;

UINT8 	mgc_i2c_RxLength;


//******************************************************************************
//
//******************************************************************************
void 	mgc3130_i2c_Init( void )
{
	//	MCLR 		MGC3130
	PORT_REGS->GROUP[MGC_MCLR_PORT_GROUP].PORT_DIR |= MGC_MCLR_PORT_DIR;
	PORT_REGS->GROUP[MGC_MCLR_PORT_GROUP].PORT_OUT |= MGC_MCLR_PORT_OUT;
	
	//	TS 			MGC3130
	PORT_REGS->GROUP[MGC_TS_PORT_GROUP].PORT_DIR &= ~MGC_TS_PORT_DIR;
  PORT_REGS->GROUP[MGC_TS_PORT_GROUP].PORT_OUT |= MGC_TS_PORT_OUT;	  
  PORT_REGS->GROUP[MGC_TS_PORT_GROUP].PORT_PINCFG[MGC_TS_PORT_PIN] = 0x7; 				//  0111


  //	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  /*
	PORT_REGS->GROUP[TST_PC06_PORT_GROUP].PORT_DIR |= TST_PC06_PORT_DIR;
	PORT_REGS->GROUP[TST_PC06_PORT_GROUP].PORT_OUT |= TST_PC06_PORT_OUT;

	PORT_REGS->GROUP[TST_PC10_PORT_GROUP].PORT_DIR |= TST_PC10_PORT_DIR;
	PORT_REGS->GROUP[TST_PC10_PORT_GROUP].PORT_OUT |= TST_PC10_PORT_OUT;
	*/
	/*
	PORT_REGS->GROUP[TST_PA04_PORT_GROUP].PORT_DIR |= TST_PA04_PORT_DIR;
	PORT_REGS->GROUP[TST_PA04_PORT_GROUP].PORT_OUT |= TST_PA04_PORT_OUT;
	*/


  //	Reset MGC3130   ..........................................................
  flg_mgc_ts = 0;
} 		//void 	mgc3130_i2c_Init( void )


//******************************************************************************
//
//******************************************************************************
void 	mgc3130_hw_Reset( void )
{
//	Reset MGC3130   ..........................................................
  flg_mgc_ts = 0;

  MGC_MCLR_H( );
  WaitMS( 50 );
  MGC_MCLR_L( );
  WaitMS( 50 );
  MGC_MCLR_H( );
  NOP( );  
}	//void 	mgc3130_hw_Reset( void )









//******************************************************************************
//
//******************************************************************************
void 	mgc3130_GetData( void )
{
	if( i2c_interface.i2c_addr != 0 )		{
		return;
	}

	//============================================================================
	if( MGC_TS_Get( ) == 1)		{
		NOP( );
		flg_mgc_ts = 0;
		i2c_interface.i2c_addr = 0;
		i2c_interface.STATE = 0;
		return;
	}
	else if( ((flg_mgc_ts==1)||(MGC_TS_Get( ) == 0)) && (i2c_interface.i2c_addr==0) )	{
		i2c_interface.i2c_addr = I2C_DEV_ADDR_MGC3130_IS20;
		i2c_interface.STATE = 0;
		i2c_interface.i2c_delay = I2CM_DELAY_350KHZ;

		memset( i2c_RxBuf, 0x00, I2CM_RX_BUF_SIZE );
		i2c_rxIndex = 0;
	} 		//if( (flg_mgc_ts==1) && (i2c_interface.i2c_addr==0) )	{

	else if( i2c_interface.i2c_addr == I2C_DEV_ADDR_MGC3130_IS20 )	{
		NOP( );
	}
	else	{
		NOP( );
		return;
	}

	//============================================================================
	NOP( );
	while( 1 )		{
		switch( i2c_interface.STATE)	{
			case 0:
				if( MGC_TS_Get( ) == 1)		{ 		//	CK TS   ............................
					NOP( );
					flg_mgc_ts = 0;
					i2c_interface.i2c_addr = 0;
					i2c_interface.STATE = 0;
					//sercom5_i2cm_End( );
					return;
				}



				i2c_ack = sercom5_i2cm_Start( i2c_interface.i2c_addr, I2CM_READ_ACTIVE );
				if( i2c_ack == 1 )	{
					flg_mgc_ts = 0;
					i2c_interface.i2c_addr=0;
					i2c_interface.STATE = 0;
					return;
				}
				i2c_interface.STATE++;

				if( MGC_TS_Get( ) == 1)		{ 		//	CK TS   ............................
					NOP( );
					flg_mgc_ts = 0;
					i2c_interface.i2c_addr = 0;
					i2c_interface.STATE = 0;
					//sercom5_i2cm_End( );
					return;
				}
				break;

			case 1:
				if( MGC_TS_Get( ) == 1)		{ 		//	CK TS   ............................
					NOP( );
					flg_mgc_ts = 0;
					i2c_interface.i2c_addr = 0;
					i2c_interface.STATE = 0;
					//sercom5_i2cm_End( );
					return;
				}
				//	send data length
				//sercom5_i2cm_WData( 0x1A );
				//sercom5_i2cm_RData( (UINT8*)&mgc_i2c_RxLength, 0 );
				sercom5_i2cm_RData( (UINT8*)&i2c_RxBuf[i2c_rxIndex], 0 );
				mgc_i2c_RxLength = i2c_RxBuf[ i2c_rxIndex ];
				i2c_rxIndex++;
				i2c_interface.STATE++;
				//return; 		//	Next while loop phase
				break;

			//	phase 	--------------------------------------------------------------
			case 2:
				NOP( );
				while( i2c_rxIndex < (mgc_i2c_RxLength-1) )	{
					if( MGC_TS_Get( ) == 1)		{ 		//	CK TS   ............................
						NOP( );
						flg_mgc_ts = 0;
						i2c_interface.i2c_addr = 0;
						i2c_interface.STATE = 0;
						//sercom5_i2cm_End( );
						return;
					}

					sercom5_i2cm_RData( (UINT8*)&i2c_RxBuf[i2c_rxIndex], 0 );
					i2c_rxIndex++;
				} 	//while( mgc_i2c_RxLength > i2c_rxIndex )	{
				i2c_interface.STATE++;
				break;

			case 3:
				if( MGC_TS_Get( ) == 1)		{ 		//	CK TS   ............................
					NOP( );
					flg_mgc_ts = 0;
					i2c_interface.i2c_addr = 0;
					i2c_interface.STATE = 0;
					//sercom5_i2cm_End( );
					return;
				}

				sercom5_i2cm_RData( (UINT8*)&i2c_RxBuf[i2c_rxIndex], 1 );
				sercom5_i2cm_End( );
				
				
				if( mgc_i2c_RxLength == 0x1A )	{
					NOP( );

					if( (i2c_RxBuf[0] == 0x1A) &&
							(i2c_RxBuf[3] == 0x91) &&
							(i2c_RxBuf[4] == 0x1F) &&
							(i2c_RxBuf[5] == 0x01) )	{

						switch( i2c_RxBuf[10] )	{
							//case 1:
							case 2:
							case 3:
							case 4:
							case 5:
								NOP( );
								M0_AllDevStatus.mgc.mgc = i2c_RxBuf[10];
								SysRTC_Get( (M0_RTC_TIME_FRAME*)&(M0_AllDevStatus.mgc.mcu_RTC) );
								//	Send to A53  -----------------------------------------------
								UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_MGC3130, (uint8_t*)&(M0_AllDevStatus.mgc), sizeof(M0_MGC_DATA_FRAME) );
								break;
						} 	//switch( i2c_RxBuf[10] )	{

					} 		//if( (i2c_RxBuf[0] == 0x1A)
				}


				i2c_interface.i2c_addr = 0;
				i2c_interface.STATE = 0;
				flg_mgc_ts = 0;
				return;
				
				/*
				i2c_interface.STATE = 0;
				if( MGC_TS_Get( ) == 1)		{ 		//	CK TS   ............................
					NOP( );
					flg_mgc_ts = 0;
					i2c_interface.i2c_addr = 0;
					i2c_interface.STATE = 0;
					//sercom5_i2cm_End( );
					return;
				}
				*/
				break;
		} 		//switch( i2c_interface.STATE)	{


	} 		//while( 1 )		{

} 		//void 	mgc3130_GetData( void )

