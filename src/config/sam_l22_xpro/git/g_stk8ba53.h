
// *****************************************************************************
// 	g_stk8ba53.h
// 			20210809
// *****************************************************************************


#ifndef DEV_STK8BA53_H
#define DEV_STK8BA53_H



//******************************************************************************
//  Defined
//==============================================================================
#define 	I2C_DEV_ADDR_STK8BA53 				0x18 			//	0011000
#define 	STK8BA53_CHIP_ID							0x87			//	10000111

//------------------------------------------------------------------------------
#define 	STK8BA53_INT_COUNT						100
#define 	STK8BA53_INT_READ_PERIOD			2

//#define 	STK8BA53_ACC_WOM_DEFAULT			50	//% 		Test
//#define 	STK8BA53_ACC_WOM_DEFAULT			80	//%

//------------------------------------------------------------------------------
#define 	STK8BA53_RANGE_2G							0x03
#define 	STK8BA53_RANGE_4G							0x05
#define 	STK8BA53_RANGE_8G							0x08

//#define 	STK8BA53_G_RANGE 			STK8BA53_RANGE_2G
#define 	STK8BA53_G_RANGE 			STK8BA53_RANGE_4G
//#define 	STK8BA53_G_RANGE 			STK8BA53_RANGE_8G




//------------------------------------------------------------------------------
//	INT 		PC09 EIC/EXTINT[1]
#define 	ICM_INT_PORT_GROUP			2
#define 	ICM_INT_PORT_PIN				9
#define 	ICM_INT_PORT_DIR 				0x200 		//	PC09	1000000000
#define 	ICM_INT_PORT_OUT 				0x200 		//	PC09	1000000000





//******************************************************************************
//  Global
extern 	UINT8  	flg_g_sensor_INT;
extern TIMER*	tm_STK8BA53_INT_start;


//	Test  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
extern 	TIMER*	tm_STK8BA53_Req;



//******************************************************************************
//  Function
void 	STK8BA53_i2c_Init( void );
UINT8 	STK8BA53_i2c_Read( UINT8  regAddr, UINT8* wBuf, UINT16 length );
UINT8 	STK8BA53_i2c_Write( UINT8  regAddr, UINT8* wBuf, UINT16 length );

UINT8 	STK8BA53_acc_Read( void );
void 	TimerF_STK8BA53_INT( void );


//	TEST  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void 	TimerF_STK8BA53_Normal_Read( void );

#endif // DEV_STK8BA53_H

