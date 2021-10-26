
#if   SERCOM2_ENABLE

#ifndef GIT_SERCOM2_UART_H
#define GIT_SERCOM2_UART_H


//******************************************************************************
//  Defined
//#define SERCOM2_USART_INT_BAUD_VALUE_115200            (61761U)   //  115740
#define SERCOM2_USART_INT_BAUD_VALUE_115200            (61775U)     //  115207


#if 	MCU_ATSAML22N18A
	#define SERCOM2_USART_RX_BUFFER_SIZE      2048
	#define SERCOM2_USART_TX_BUFFER_SIZE      2048
#elif 	MCU_ATSAML22N17A
	#define SERCOM2_USART_RX_BUFFER_SIZE      1024
	#define SERCOM2_USART_TX_BUFFER_SIZE      1024
#endif 		//#if 	MCU_ATSAML22N18A

#define UART_TLSAM_Tx_BUFFFER_SIZE        1024
#define UART_TLSAM_Rx_BUFFFER_SIZE        1600


#define SERCOM2_USART_RX_INT_DISABLE()      SERCOM2_REGS->USART_INT.SERCOM_INTENCLR = SERCOM_USART_INT_INTENCLR_RXC_Msk
#define SERCOM2_USART_RX_INT_ENABLE()       SERCOM2_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_RXC_Msk

#define SERCOM2_USART_TX_INT_DISABLE()      SERCOM2_REGS->USART_INT.SERCOM_INTENCLR = SERCOM_USART_INT_INTENCLR_DRE_Msk
#define SERCOM2_USART_TX_INT_ENABLE()       SERCOM2_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_DRE_Msk




//******************************************************************************
//  Global
extern 	UART_INTERFACE    uartTLSAM_BUFF;

extern 	UINT8 		uartTLSAM_rx_Qbuf[];
extern 	UINT8 		uartTLSAM_tx_Qbuf[];
extern 	UINT8 		uartTLSAM_RXbuf[];
extern 	UINT8 		uartTLSAM_TXbuf[];

extern 	UINT8*    uartTLSAM_rx_buffer;
extern 	UINT8*    uartTLSAM_tx_buffer;
extern 	UINT8*    uartTLSAM_buffer;

//==============================================================================
extern 	M0_TLSAM_FRAME 		TLSAM_Data;

extern 	TIMER 	*tm_TLSAM;


//	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#if 	Tst_TLSAM_01
	extern 	TIMER 	*tm_TLSAM_Test;
#endif 	//#if 	Tst_TLSAM_01







//******************************************************************************
//  Function
void  SERCOM2_USART_Initialize( void );

UINT8   TLSAM_DataGet( UINT8 *rx_data );
UINT8   TLSAM_DataPut( UINT8 tx_data );
UINT8   TLSAM_StringPut( UINT8* w_buf, UINT16 length  );

void 	UartDataRx_TLSAM( void );
void 	UartDataRx_TLSAM_CMD( void );

void 		TLSAM_Req_FWversion( void );
void 		TLSAM_Req_Encrypt( UINT8* dataPtr, UINT16 dataLength );


void 	TimerF_TLSAM_ReqFWversion( void );



#if 	Tst_TLSAM_01
	void 	TimerF_TLSAM_Test( void );
#endif 	//#if 	Tst_TLSAM_01



#endif // GIT_SERCOM2_UART_H

#endif  //#if   SERCOM2_ENABLE
