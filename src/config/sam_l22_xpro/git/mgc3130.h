

// *****************************************************************************
//  mgc3130.h
//    20210322
// *****************************************************************************

#ifndef DEV_MGC3130_H
#define DEV_MGC3130_H



//******************************************************************************
//	i2c_RxBuf[0] = 0x1A			data length



//******************************************************************************
//  Defined
//==============================================================================
#define 	I2C_BAUDRATE_MGC3130        200000U
#define 	I2C_DEV_ADDR_MGC3130_IS20   0x42 			//	1101001


//	I2C 	SCL :	PB31- PAD[1]
//	I2C 	SDA :	PB30- PAD[0]
//				TS 		PC08- EIC/EXTIN[0]
//				MCLR 	PC28- GPIO

//	MCLR 	PC28- GPIO
#define 	MGC_MCLR_PORT_GROUP			2
#define 	MGC_MCLR_PORT_PIN				28
#define 	MGC_MCLR_PORT_DIR 				0x10000000 		//	PC28	10000000000000000000000000000
#define 	MGC_MCLR_PORT_OUT 				0x10000000 		//	PC28	10000000000000000000000000000

//	TS 		PC08- EIC/EXTIN[0]
#define 	MGC_TS_PORT_GROUP			2
#define 	MGC_TS_PORT_PIN				8
#define 	MGC_TS_PORT_DIR 				0x100 		//	PC08	100000000
#define 	MGC_TS_PORT_OUT 				0x100 		//	PC08	100000000

//------------------------------------------------------------------------------
#define 	MGC_MCLR_H( ) 				(PORT_REGS->GROUP[MGC_MCLR_PORT_GROUP].PORT_OUTSET = 1 << MGC_MCLR_PORT_PIN)
#define 	MGC_MCLR_L( ) 				(PORT_REGS->GROUP[MGC_MCLR_PORT_GROUP].PORT_OUTCLR = 1 << MGC_MCLR_PORT_PIN)

#define 	MGC_TS_H( ) 				(PORT_REGS->GROUP[MGC_TS_PORT_GROUP].PORT_OUTSET = 1 << MGC_TS_PORT_PIN)
#define 	MGC_TS_L( ) 				(PORT_REGS->GROUP[MGC_TS_PORT_GROUP].PORT_OUTCLR = 1 << MGC_TS_PORT_PIN)
//#define 	MGC_TS_Get( )					(((PORT_REGS->GROUP[MGC_TS_PORT_GROUP].PORT_IN >> MGC_TS_PORT_PIN)) & MGC_TS_PORT_DIR)
#define 	MGC_TS_Get( )					(((PORT_REGS->GROUP[MGC_TS_PORT_GROUP].PORT_IN >> MGC_TS_PORT_PIN)) & 0x0001)


//	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*
//	PC06 Test
#define 	TST_PC06_PORT_GROUP			2
#define 	TST_PC06_PORT_PIN				6
#define 	TST_PC06_PORT_DIR 				0x40 		//	PC06	1000000
#define 	TST_PC06_PORT_OUT 				0x40 		//	PC06	1000000

#define 	TST_PC06_H( ) 				(PORT_REGS->GROUP[TST_PC06_PORT_GROUP].PORT_OUTSET = 1 << TST_PC06_PORT_PIN)
#define 	TST_PC06_L( ) 				(PORT_REGS->GROUP[TST_PC06_PORT_GROUP].PORT_OUTCLR = 1 << TST_PC06_PORT_PIN)


#define 	TST_PC10_PORT_GROUP			2
#define 	TST_PC10_PORT_PIN				10
#define 	TST_PC10_PORT_DIR 				0x400 		//	PC10	10000000000
#define 	TST_PC10_PORT_OUT 				0x400 		//	PC10	10000000000

#define 	TST_PC10_H( ) 				(PORT_REGS->GROUP[TST_PC10_PORT_GROUP].PORT_OUTSET = 1 << TST_PC10_PORT_PIN)
#define 	TST_PC10_L( ) 				(PORT_REGS->GROUP[TST_PC10_PORT_GROUP].PORT_OUTCLR = 1 << TST_PC10_PORT_PIN)
*/
/*
#define 	TST_PA04_PORT_GROUP			0
#define 	TST_PA04_PORT_PIN				4
#define 	TST_PA04_PORT_DIR 				0x10 		//	PA04	10000
#define 	TST_PA04_PORT_OUT 				0x10 		//	PA04	10000

#define 	TST_PA04_H( ) 				(PORT_REGS->GROUP[TST_PA04_PORT_GROUP].PORT_OUTSET = 1 << TST_PA04_PORT_PIN)
#define 	TST_PA04_L( ) 				(PORT_REGS->GROUP[TST_PA04_PORT_GROUP].PORT_OUTCLR = 1 << TST_PA04_PORT_PIN)
*/


//******************************************************************************
//  Global
extern 	UINT8 	flg_mgc_ts;

extern	UINT8 	mgc_i2c_RxLength;


//******************************************************************************
//  Function
void 	mgc3130_i2c_Init( void );
void 	mgc3130_hw_Reset( void );

void 	mgc3130_GetData( void );


#endif // DEV_MGC3130_H

