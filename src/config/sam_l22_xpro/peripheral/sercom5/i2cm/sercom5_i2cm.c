

// *****************************************************************************
//  sercom5_i2cm.c
//    20210319
// *****************************************************************************
//==============================================================================
//------------------------------------------------------------------------------
//..............................................................................
//______________________________________________________________________________


#include "All_Header.h"


//	SDA			PB30- PAD[0]
//	SCL 		PB31- PAD[1]    



//******************************************************************************
//  Global
I2C_INTERFACE 	i2c_interface;

UINT8 	i2c_RxBuf[I2CM_RX_BUF_SIZE];
UINT8 	i2c_TxBuf[I2CM_TX_BUF_SIZE];

int 		i2c_rxIndex;
int 		i2c_txIndex;

UINT8 	i2c_ack;


//	TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!






//******************************************************************************
//
//******************************************************************************
void 	SERCOM5_I2C_SDA_OUT( void )
{
	//	TS : Output
	PORT_REGS->GROUP[I2CM_SDA_PORT_GROUP].PORT_DIR |= I2CM_SDA_PORT_DIR;
	PORT_REGS->GROUP[I2CM_SDA_PORT_GROUP].PORT_OUT |= I2CM_SDA_PORT_OUT;
	PORT_REGS->GROUP[I2CM_SDA_PORT_GROUP].PORT_PINCFG[I2CM_SDA_PORT_PIN] = 0x00; 				//  0000	
}


void 	SERCOM5_I2C_SDA_IN( void )
{
	//	TS : Input
	PORT_REGS->GROUP[I2CM_SDA_PORT_GROUP].PORT_DIR &= ~I2CM_SDA_PORT_DIR;
	PORT_REGS->GROUP[I2CM_SDA_PORT_GROUP].PORT_OUT |= I2CM_SDA_PORT_OUT;
	PORT_REGS->GROUP[I2CM_SDA_PORT_GROUP].PORT_PINCFG[I2CM_SDA_PORT_PIN] = 0x7; 				//  0111
}





//******************************************************************************
//
//******************************************************************************
void 	SERCOM5_I2C_Initialize( void )
{
	PORT_REGS->GROUP[I2CM_SCL_PORT_GROUP].PORT_DIR |= I2CM_SCL_PORT_DIR;
	PORT_REGS->GROUP[I2CM_SCL_PORT_GROUP].PORT_OUT |= I2CM_SCL_PORT_OUT;
	//PORT_REGS->GROUP[I2CM_SCL_PORT_GROUP].PORT_PINCFG[I2CM_SCL_PORT_PIN] = 0x7; 				//  0111

	SERCOM5_I2C_SDA_OUT( );
	I2CM_SCL_H( );
	I2CM_SDA_H( );
	
	memset( (UINT8*)&i2c_interface, 0x00, sizeof(I2C_INTERFACE) );
	i2c_interface.i2c_delay = I2CM_DELAY_100KHZ;
} 		//void 	SERCOM5_I2C_Initialize( void )





//******************************************************************************
//
//******************************************************************************
void 	sercom5_i2cm_delay( void )
{
	int i;
	for( i=0 ; i<i2c_interface.i2c_delay ; i++ )	{
		NOP( );
		
		NOP( );
		NOP( );
	}
} 		//void 	sercom5_i2cm_delay( void )




//******************************************************************************
//
//******************************************************************************
//	addr: 	7bit
//	rw:		=0, Write; 	=1, Read
void 	sercom5_i2cm_End( void )
{
	SERCOM5_I2C_SDA_OUT( );
	sercom5_i2cm_delay( );
	I2CM_SDA_L( );
	I2CM_SCL_L( );
	sercom5_i2cm_delay( );
	sercom5_i2cm_delay( );

	I2CM_SCL_H( );
	sercom5_i2cm_delay( );
	sercom5_i2cm_delay( );
	I2CM_SDA_H( );
	sercom5_i2cm_delay( );
	sercom5_i2cm_delay( );
} 	//void 	sercom5_i2cm_End( void )


//******************************************************************************
//
//******************************************************************************
//	addr: 	7bit
//	rw:		=0, Write; 	=1, Read
UINT8 	sercom5_i2cm_Start( UINT8 addr, int rw )
{
	int i;
	//UINT8 i2c_ack = 1;
	UINT8 devAddr = addr * 2;
	int cnt_bit = 8;


	//	I2C Stat  	--------------------------------------------------------------
	SERCOM5_I2C_SDA_OUT( );

	I2CM_SCL_H( );
	I2CM_SDA_H( );
	//WaitMS( 2 );
	for( i=0 ; i<30 ; i++)	{
		sercom5_i2cm_delay( );
	}

	I2CM_SDA_L( );
	sercom5_i2cm_delay( );
	I2CM_SCL_L( );
	sercom5_i2cm_delay( );
	sercom5_i2cm_delay( );


	//	I2C Address dat + RW 			-------------------------------------------------
	if( rw )	{
		devAddr |= 0x01;
	}
	else {
		devAddr &= 0xFE;
	}

	while( cnt_bit )		{
		if( devAddr & 0x80 )	{
			I2CM_SDA_H( );
		}
		else {
			I2CM_SDA_L( );
		}

		I2CM_SCL_H( );
		sercom5_i2cm_delay( );
		I2CM_SCL_L( );
		NOP( );
		NOP( );
		I2CM_SDA_L( );
		//sercom5_i2cm_delay( );
		NOP( );

		devAddr <<= 1;
		cnt_bit--;
	} 		//while( cnt_bit )		{
	
	NOP( );


	//	I2C ACK CK  	------------------------------------------------------------
	sercom5_i2cm_delay( );
	SERCOM5_I2C_SDA_IN( );

	I2CM_SCL_H( );
	sercom5_i2cm_delay( );
	i2c_ack = I2CM_SDA_Get( );
	I2CM_SCL_L( );
	sercom5_i2cm_delay( );
	NOP( );
	return i2c_ack;
} 	//UINT8 	sercom5_i2cm_Start( UINT8 addr, int rw )


//******************************************************************************
//
//******************************************************************************
//	addr: 	7bit
//	rw:		=0, Write; 	=1, Read
UINT8 	sercom5_i2cm_WData( UINT8 wData )
{
	int cnt_bit = 8;


	SERCOM5_I2C_SDA_OUT( );
	sercom5_i2cm_delay( );
	
	while( cnt_bit )		{
		if( wData & 0x80 )	{
			I2CM_SDA_H( );
		}
		else {
			I2CM_SDA_L( );
		}

		I2CM_SCL_H( );
		sercom5_i2cm_delay( );
		I2CM_SCL_L( );
		NOP( );
		NOP( );
		I2CM_SDA_L( );
		//sercom5_i2cm_delay( );
		NOP( );

		wData <<= 1;
		cnt_bit--;
	} 		//while( cnt_bit )		{	
	NOP( );

	//	I2C ACK CK  	------------------------------------------------------------
	sercom5_i2cm_delay( );
	SERCOM5_I2C_SDA_IN( );

	I2CM_SCL_H( );
	sercom5_i2cm_delay( );
	i2c_ack = I2CM_SDA_Get( );
	I2CM_SCL_L( );
	sercom5_i2cm_delay( );
	NOP( );
	return i2c_ack;
} 	//UINT8 	sercom5_i2cm_WData( UINT8 wData )


//******************************************************************************
//
//******************************************************************************
//	addr: 	7bit
//	rw:		=0, Write; 	=1, Read
UINT8 	sercom5_i2cm_RData( UINT8* rDataPtr, int last_byte )
{
	int cnt_bit = 8;
	UINT8 	sdaData;

	I2CM_SCL_L( );
	I2CM_SDA_L( );
	SERCOM5_I2C_SDA_IN( );
	sercom5_i2cm_delay( );
	sercom5_i2cm_delay( );

	*rDataPtr = 0;

	while( cnt_bit )		{
		*rDataPtr <<= 1;

		sercom5_i2cm_delay( );
		I2CM_SCL_H( );
		sercom5_i2cm_delay( );
		sdaData = I2CM_SDA_Get( );
		I2CM_SCL_L( );
		if( sdaData == 0 )	{
			*rDataPtr &= 0xFE;
		}
		else {
			*rDataPtr |= 0x01;
		}

		cnt_bit--;
		sercom5_i2cm_delay( );
	} 		//while( cnt_bit )		{


	//	I2C ACK CK  	------------------------------------------------------------
		sercom5_i2cm_delay( );
	if( last_byte == 1) 	{
		SERCOM5_I2C_SDA_IN( );

		I2CM_SCL_H( );
		sercom5_i2cm_delay( );
		i2c_ack = I2CM_SDA_Get( );
		I2CM_SCL_L( );
	}
	else 	{
		SERCOM5_I2C_SDA_OUT( );

		I2CM_SDA_L( );
		NOP( );
		NOP( );
		NOP( );
		NOP( );
		I2CM_SCL_H( );
		sercom5_i2cm_delay( );
		I2CM_SCL_L( );		
	}
	sercom5_i2cm_delay( );
	NOP( );
	return i2c_ack;
} 	//UINT8 	sercom5_i2cm_RData( UINT8* rDataPtr, int last_byte )

