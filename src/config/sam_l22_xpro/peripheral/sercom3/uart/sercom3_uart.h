

#ifndef GIT_SERCOM3_UART_H
#define GIT_SERCOM3_UART_H


//******************************************************************************
//  Defined
//#define SERCOM3_USART_INT_BAUD_VALUE_115200            (61761U)   //  115740
#define SERCOM3_USART_INT_BAUD_VALUE_115200            (61775U)     //  115207

#define SERCOM3_USART_RX_BUFFER_SIZE      256
#define SERCOM3_USART_TX_BUFFER_SIZE      256
#define UARTRADARA_CMD_BUFFFER_SIZE       128


#define SERCOM3_USART_RX_INT_DISABLE()      SERCOM3_REGS->USART_INT.SERCOM_INTENCLR = SERCOM_USART_INT_INTENCLR_RXC_Msk
#define SERCOM3_USART_RX_INT_ENABLE()       SERCOM3_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_RXC_Msk

#define SERCOM3_USART_TX_INT_DISABLE()      SERCOM3_REGS->USART_INT.SERCOM_INTENCLR = SERCOM_USART_INT_INTENCLR_DRE_Msk
#define SERCOM3_USART_TX_INT_ENABLE()       SERCOM3_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_DRE_Msk




//******************************************************************************
//  Global
extern 	UART_INTERFACE    uartRadarA_BUFF;

extern 	UINT8 		uartRadarA_rx_Qbuf[];
extern 	UINT8 		uartRadarA_tx_Qbuf[];
extern 	UINT8 		uartRadarA_RXbuf[];
extern 	UINT8 		uartRadarA_TXbuf[];

extern 	UINT8*    uartRadarA_rx_buffer;
extern 	UINT8*    uartRadarA_tx_buffer;
extern 	UINT8*    uartRadarA_buffer;

extern 	UINT8 		uartRadarA_Set_param[ sizeof(M0_RADAR_SET_FRAME) ];
extern 	M0_RADAR_SET_FRAME  	RadarA_Set_Data;


//	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#if 	Tst_RADARA_01
	extern 	TIMER 	*tm_RadarA_Test;
	extern 	UINT8 	TstBuf_uartRadarA[];
#endif 	//#if 	Tst_RADARA_01




//******************************************************************************
//  Function
void  SERCOM3_USART_Initialize( void );

UINT8   RadarA_DataGet( UINT8 *rx_data );
UINT8   RadarA_DataPut( UINT8 tx_data );
UINT8   RadarA_StringPut( UINT8* w_buf, UINT16 length  );

void 	UartDataRx_RadarA( void );
void 	UartDataRx_RadarA_CMD( void );


//==============================================================================
void 		RadarA_Req_SWversion( void );




//	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#if 	Tst_RADARA_01
	void  TimerF_RadarA_Tst(void);	
#endif 	//#if 	Tst_RADARA_01


#endif // GIT_SERCOM3_UART_H

