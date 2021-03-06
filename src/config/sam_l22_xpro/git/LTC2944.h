

// *****************************************************************************
//  LTC2944.h
//    20210525
// *****************************************************************************

#ifndef DEV_LTC2944_H
#define DEV_LTC2944_H




//******************************************************************************
//  Defined
//==============================================================================
#define 	I2C_BAUDRATE_LTC2944        200000U
#define 	I2C_DEV_ADDR_LTC2944_IS20   0x64 			//	1100100


//	LTC2944 ALCC 		PC10- GPIO-I
#define 	LTC2944__ALCC_PORT_GROUP			2
#define 	LTC2944__ALCC_PORT_PIN				10
#define 	LTC2944__ALCC_PORT_DIR 				0x400 	//	PC10	10000000000

#define 	VOLT_NOUSED						99000




//	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



//******************************************************************************
//  Global
extern 	TIMER 	*tm_ltc2944_read;



//******************************************************************************
//  Function
void 	LTC2944_i2c_Init( void );

void 	LTC2944_Write_ControlReg( UINT8 wData );
void 	LTC2944_GetData( void );

void 	TimerF_LTC2944_Read( void );

#endif // DEV_LTC2944_H

