

// *****************************************************************************
//  sercom5_i2cm.h
//    20210319
// *****************************************************************************

#ifndef SERCOM5_I2CM_H
#define SERCOM5_I2CM_H




//******************************************************************************
//  Defined
//==============================================================================
#define 	I2CM_READ_ACTIVE 					1
#define 	I2CM_WRITE_ACTIVE 				0

#define 	I2CM_RX_BUF_SIZE 					256
#define 	I2CM_TX_BUF_SIZE 					256

#define 	I2CM_DELAY_350KHZ 				1
#define 	I2CM_DELAY_200KHZ 				2
#define 	I2CM_DELAY_100KHZ 				3



//	I2C 	SCL :	PB31- PAD[1]
//	I2C 	SDA :	PB30- PAD[0]
#define 	I2CM_SCL_PORT_GROUP				1
#define 	I2CM_SCL_PORT_PIN					31
#define 	I2CM_SCL_PORT_DIR 				0x80000000 		//	PB31	10000000000000000000000000000000
#define 	I2CM_SCL_PORT_OUT 				0x80000000 		//	PB31	10000000000000000000000000000000
#define 	I2CM_SCL_H( ) 				(PORT_REGS->GROUP[I2CM_SCL_PORT_GROUP].PORT_OUTSET = 1 << I2CM_SCL_PORT_PIN)
#define 	I2CM_SCL_L( ) 				(PORT_REGS->GROUP[I2CM_SCL_PORT_GROUP].PORT_OUTCLR = 1 << I2CM_SCL_PORT_PIN)

#define 	I2CM_SDA_PORT_GROUP				1
#define 	I2CM_SDA_PORT_PIN					30
#define 	I2CM_SDA_PORT_DIR 				0x40000000 		//	PB30	1000000000000000000000000000000
#define 	I2CM_SDA_PORT_OUT 				0x40000000 		//	PB30	1000000000000000000000000000000
#define 	I2CM_SDA_H( ) 				(PORT_REGS->GROUP[I2CM_SDA_PORT_GROUP].PORT_OUTSET = 1 << I2CM_SDA_PORT_PIN)
#define 	I2CM_SDA_L( ) 				(PORT_REGS->GROUP[I2CM_SDA_PORT_GROUP].PORT_OUTCLR = 1 << I2CM_SDA_PORT_PIN)
#define 	I2CM_SDA_Get( )				(((PORT_REGS->GROUP[I2CM_SDA_PORT_GROUP].PORT_IN >> I2CM_SDA_PORT_PIN)) & 0x0001)


//******************************************************************************
//  Global
extern 	I2C_INTERFACE 	i2c_interface;

extern 	UINT8 	i2c_RxBuf[];
extern 	UINT8 	i2c_TxBuf[];

extern 	int 		i2c_rxIndex;
extern 	int 		i2c_txIndex;

extern 	UINT8 	i2c_ack;


//	TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!




//******************************************************************************
//  Function
void 	SERCOM5_I2C_Initialize( void );




void 		sercom5_i2cm_delay( void );
UINT8 	sercom5_i2cm_Start( UINT8 addr, int rw );
void 		sercom5_i2cm_End( void );
UINT8 	sercom5_i2cm_WData( UINT8 wData );
UINT8 	sercom5_i2cm_RData( UINT8* rDataPtr, int last_byte );



#endif // SERCOM5_I2CM_H

