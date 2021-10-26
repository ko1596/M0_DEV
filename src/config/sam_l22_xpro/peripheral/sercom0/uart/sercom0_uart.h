

#ifndef GIT_SERCOM0_UART_H
#define GIT_SERCOM0_UART_H


#if   SERCOM0_ENABLE


//******************************************************************************
//  Defined
#define SERCOM0_USART_INT_BAUD_VALUE_115200            (61775U)     //  115207

#define SERCOM0_USART_RX_BUFFER_SIZE      256
#define SERCOM0_USART_TX_BUFFER_SIZE      256
#define UARTCHILI2S_CMD_BUFFFER_SIZE      128


#define SERCOM0_USART_RX_INT_DISABLE()      SERCOM0_REGS->USART_INT.SERCOM_INTENCLR = SERCOM_USART_INT_INTENCLR_RXC_Msk
#define SERCOM0_USART_RX_INT_ENABLE()       SERCOM0_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_RXC_Msk

#define SERCOM0_USART_TX_INT_DISABLE()      SERCOM0_REGS->USART_INT.SERCOM_INTENCLR = SERCOM_USART_INT_INTENCLR_DRE_Msk
#define SERCOM0_USART_TX_INT_ENABLE()       SERCOM0_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_DRE_Msk



//******************************************************************************
//  Global
extern 	UART_INTERFACE    uartChili2S_BUFF;

extern 	UINT8     uartChili2S_rx_Qbuf[];
extern 	UINT8     uartChili2S_tx_Qbuf[];

extern 	UINT8     uartChili2S_RXbuf[];
extern 	UINT8     uartChili2S_TXbuf[];

extern 	UINT8*    uartChili2S_rx_buffer;
extern 	UINT8*    uartChili2S_tx_buffer;
extern 	UINT8*    uartChili2S_buffer;


//extern  CHILI2S_INFO_FRAME  	Chili2S_info;




#if  	Tst_Chili2S_UART
	UINT8  	Tst_Buf[1024];
	int  		Tst_index;
	TIMER*  tm_Chili2S_UART;
#endif 		//#if  	Tst_Chili2S_UART





//******************************************************************************
//  Function
void  SERCOM0_USART_Initialize( void );

UINT8   Chili2S_DataGet( UINT8 *rx_data );
UINT8   Chili2S_DataPut( UINT8 tx_data );
UINT8   Chili2S_StringPut( UINT8* w_buf, UINT16 length  );


void  Chili2S_Set_PAN_ADD( UINT16 panid, UINT16 sAddr, UINT8 rf_channel );
void  Chili2S_Set_RTC( void );

void 	Chili2S_Req_Info( void );


void 	UartDataRx_Chili2S( void );
void 	UartDataRx_Chili2S_CMD( void );




#if  Tst_Chili2S_UART
	void  TimerF_Tst_Chili2S_UART(void);
#endif  	//#if  Tst_Chili2S_UART


#endif 		//#if   SERCOM0_ENABLE

#endif // GIT_SERCOM0_UART_H

