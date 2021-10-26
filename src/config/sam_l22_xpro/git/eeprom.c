

// *****************************************************************************
//  eeprom.c
//    20210601
// *****************************************************************************
//==============================================================================
//------------------------------------------------------------------------------
//..............................................................................
//______________________________________________________________________________


#include "All_Header.h"




//******************************************************************************
//	Global
UINT16 		eepData_writeAddr;
UINT16 		eepData_writeByte;
UINT16 		eepData_writeLength;
UINT8*  	eepData_writeBuf;

TIMER 		*tm_eep_Active;


//******************************************************************************
//
//******************************************************************************
void 	eep24aa64_i2c_Init( void )
{
	NOP( );
} 		//void 	eep24aa64_i2c_Init( void )




//******************************************************************************
//
//******************************************************************************
void 	eep24aa64_i2c_Read( UINT16 Addr, UINT8* readBuf, UINT16 length )
{
	UINT8* dataPtr;


	if( i2c_interface.i2c_addr != 0 )		{
		return;
	}

	//==================================================================
	i2c_interface.i2c_addr = I2C_DEV_ADDR_LTC2944;
	i2c_interface.STATE = 0;
	i2c_interface.i2c_delay = I2CM_DELAY_200KHZ;

	dataPtr = readBuf;
	//memset( i2c_RxBuf, 0x00, I2CM_RX_BUF_SIZE );
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

				sercom5_i2cm_WData( (Addr >> 8) & 0x00FF );
				sercom5_i2cm_WData( Addr  & 0x00FF );
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
				sercom5_i2cm_RData( (UINT8*)dataPtr, 0 );
				dataPtr++;
				i2c_rxIndex++;

				if( i2c_rxIndex >= (length-1) )		{
					i2c_interface.STATE++;
				}
				break;

			case 3:
				sercom5_i2cm_RData( (UINT8*)dataPtr, 1 );
				sercom5_i2cm_End( );
				i2c_interface.STATE++;
				break;

			case 4:
				i2c_interface.i2c_addr = 0;
				i2c_interface.STATE = 0;
				return;
				break;
		} 		//switch( i2c_interface.STATE)	{
	} 		//while( 1 )		{

} 		//void 	eep24aa64_i2c_Read( UINT16 Addr, UINT8* readBuf, UINT16 length )


//******************************************************************************
//
//******************************************************************************
void 	TimerF_eep24aa64_i2c_Write( void )
{
	UINT16  	wByte;
	int  			i = 0;


	reset_timer( tm_eep_Active );

	//============================================================================
	if( i2c_interface.i2c_addr != 0 )		{
		return;
	}

	//==================================================================
	i2c_interface.i2c_addr = I2C_DEV_ADDR_LTC2944;
	i2c_interface.STATE = 0;
	i2c_interface.i2c_delay = I2CM_DELAY_200KHZ;

	//dataPtr = writeBuf;
	i2c_txIndex = 0;

	//============================================================================
	wByte = eepData_writeLength - eepData_writeByte;
	if( wByte > EEP_WRITE_PAGE_BYTE )	{
		wByte = EEP_WRITE_PAGE_BYTE;
	}
	eepData_writeByte += wByte;

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

				sercom5_i2cm_WData( (eepData_writeAddr >> 8) & 0x00FF );
				sercom5_i2cm_WData( eepData_writeAddr & 0x00FF );
				eepData_writeAddr += wByte;

				i2c_interface.STATE++;
				break;

				//	write data
				case 1:
					sercom5_i2cm_WData( *eepData_writeBuf );
					eepData_writeBuf++;
					i++;

					if( i>= wByte )		{
						i2c_interface.STATE++;
					}
					break;

				case 2:
					sercom5_i2cm_End( );
					i2c_interface.i2c_addr = 0;
					i2c_interface.STATE = 0;

					if( eepData_writeByte == eepData_writeLength )	{
						NOP( );
						close_timer( tm_eep_Active );
					}
					return;
					break;
		} 		//switch( i2c_interface.STATE)	{

	} 		//while( 1 )		{

} 		//void 	TimerF_eep24aa64_i2c_Write( void )


//******************************************************************************
//
//******************************************************************************
void 	eep24aa64_i2c_Write( void )
{
	tm_eep_Active = setup_timer( 7, 0, (void (*)())TimerF_eep24aa64_i2c_Write, NULL );
} 		//void 	eep24aa64_i2c_Write( void )








//******************************************************************************
//
//******************************************************************************
void 	TimerF_eep_Write( void )
{
	reset_timer( tm_eep_Active );
	//============================================================================
	
} 		//void 	TimerF_eep_Write( void )


//******************************************************************************
//
//******************************************************************************
void 	TimerF_eep_Read( void )
{
	reset_timer( tm_eep_Active );
	//============================================================================
	
} 		//void 	TimerF_eep_Read( void )

