

#ifndef GIT_UART_M4_H
#define GIT_UART_M4_H


//******************************************************************************
//  Defined
//==============================================================================
#define    uart_REQ_DUMMY_TEST 			0x00
#define    uart_RSP_DUMMY_TEST 			0x80

#define    uart_REQ_SYSTEM_INFO 		0x01
#define    uart_RSP_SYSTEM_INFO 		0x81

#define    uart_M0_WAKEUP_A53 			0x82

#define    uart_SET_DEV 						0x50
#define    uart_RSP_DEV 						0xD0

#define    uart_REQ_DEV_STATUS 			0x51
#define    uart_RSP_DEV_STATUS 			0xD1

#define    uart_REQ_SAVE_EEPROM 		0x5A
#define    uart_RSP_SAVE_EEPROM 		0xDA

#define    uart_REQ_READ_EEPROM 		0x5B
#define    uart_RSP_READ_EEPROM 		0xDB

#define    uart_REQ_DEV_RESTART			0x5F
#define    uart_RSP_DEV_RESTART			0xDF

#define    uart_REQ_ENC							0x68
#define    uart_RSP_ENC							0xE8

#define    uart_SET_RTC 						0x60
#define    uart_RSP_RTC 						0xE0

#define    uart_REQ_ALARM 					0x70
#define    uart_RSP_ALARM 					0xF0

//  Test  ----------------------------------------------------------------------
#define    uart_REQ_UART_TEST01 		0x7E
#define    uart_RSP_UART_TEST01 		0xFE

#define    uart_REQ_UART_TEST02 		0x7D
#define    uart_RSP_UART_TEST02 		0xFD

//==============================================================================
//	Alarm Sub-Type;			M0 alarm A53
//	#define    uart_REQ_ALARM 					0x70
//	#define    uart_RSP_ALARM 					0xF0
#define    uart_ALARM_TEMP 								0x10

#define    uart_ALARM_RADAR_PWOFF					0x70
#define    uart_ALARM_RADAR_PWON					0x71




//------------------------------------------------------------------------------




//******************************************************************************
//  Global


#if 	Tst_UART_A53M0_TxRx
	extern	UINT32 	tst_a53m0_Rx_Cnt;
	extern 	TIMER*  	tm_Tst01;
#endif 		//#if 	Tst_UART_A53M0_TxRx





//******************************************************************************
//  Function
void    uartM4_Clear_State( void );

void   UartDataTx_M0toM4_Data( UINT8 cmd, UINT8* DataPtr, UINT16 DataLength );
void   UartDataTx_M0toM4_DevData( UINT8 cmd, UINT8 dev_subType, UINT8* DataPtr, UINT16 DataLength );
void   UartDataTx_M0toM4_Data_NoWakeupA53( UINT8 cmd, UINT8* DataPtr, UINT16 DataLength );

UINT8   UartDataRx_M4_M0( void );
void    UartDataRx_M4_M0_Cmd( void );


//==============================================================================
void  uart_TEST01( void );
void  uart_DUMMY_TEST( void );


void  uart_Rsp_System_Info( void );
void  uart_Rsp_Devices_Status( void );

void 	uart_Set_Devices( void );
void 	uart_ReStart_Devices( void );


void  uart_Set_RTC( void );
void  uart_Req_RTC( void );

void 	uart_Write_EEP( void );
void 	uart_Read_EEP( void );




#if 	Tst_UART_A53M0_TxRx
	void 	TimerF_Tst_A53M0_TxRx01( void );
#endif 		//#if 	Tst_UART_A53M0_TxRx


#endif // GIT_UART_M4_H

