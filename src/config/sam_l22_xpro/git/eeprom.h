

// *****************************************************************************
//  eeprom.h
//    20210601
// *****************************************************************************

#ifndef DEV_EEPROM_H
#define DEV_EEPROM_H




//******************************************************************************
//  Defined
//==============================================================================
//	Microchip 		24AA64
#define 	I2C_BAUDRATE_LTC2944 			200000U
#define 	I2C_DEV_ADDR_LTC2944 			0x51 			//	1010001

#define 	EEP_WRITE_PAGE_BYTE 			16


//	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//******************************************************************************
//  Global
extern 	UINT16 		eepData_writeAddr;
extern 	UINT16 		eepData_writeByte;
extern 	UINT16 		eepData_writeLength;
extern 	UINT8*  	eepData_writeBuf;

extern 	TIMER 		*tm_eep_Active;


//******************************************************************************
//  Function
void 	eep24aa64_i2c_Init( void );


void 	eep24aa64_i2c_Read( UINT16 Addr, UINT8* readBuf, UINT16 length );
void 	eep24aa64_i2c_Write( void );


void 	TimerF_eep_Write( void );
void 	TimerF_eep_Read( void );


#endif // DEV_EEPROM_H

