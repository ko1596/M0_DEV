

#ifndef GIT_SERCOM1_UART_H
#define GIT_SERCOM1_UART_H






//******************************************************************************
//  Defined
//		115200 :	8.68055us
//#define SERCOM1_USART_INT_BAUD_VALUE_115200            (61775U)     //  115207 		0.9424460431654676
//#define SERCOM1_USART_INT_BAUD_VALUE_115200            (61770U)     // 					0.9579207920792079
//#define SERCOM1_USART_INT_BAUD_VALUE_115200            (61765U)     // 	0.9703075291622481 	//2856:0.9677871148459384
//#define SERCOM1_USART_INT_BAUD_VALUE_115200            (61760U)     // 	7461:0.973596032703391;	8209:0.9699110732123279
#define SERCOM1_USART_INT_BAUD_VALUE_115200            (61755U)     //	8.69us, 114942
//#define SERCOM1_USART_INT_BAUD_VALUE_115200            (61750U)     //	8.69us, 115074
//#define SERCOM1_USART_INT_BAUD_VALUE_115200            (61740U)     //
//#define SERCOM1_USART_INT_BAUD_VALUE_115200            (61745U)     //
			// 	6493:0.9644232250115509
			// 	8616:0.9803853296193129
			// 	T128 	7106:	0.9878975513650436
			// 	T128 	8200:	0.9896341463414634
			//	T128	3157:	0.9896341463414634
			//	T128	10158:	0.9765701909824769 	50ms
			//	T128	10000:	0.9886 	-50ms
			//	T128	10000:	0.9929 	-200ms



#define SERCOM1_USART_INT_BAUD_VALUE_115200_4          (SERCOM1_USART_INT_BAUD_VALUE_115200*4) 		//	115200*4


#if 	MCU_ATSAML22N18A
	#define SERCOM1_USART_RX_BUFFER_SIZE      2048
	#define SERCOM1_USART_TX_BUFFER_SIZE      2048
#elif 	MCU_ATSAML22N17A
	#define SERCOM1_USART_RX_BUFFER_SIZE      1024
	#define SERCOM1_USART_TX_BUFFER_SIZE      1024
	//#define SERCOM1_USART_RX_BUFFER_SIZE      2048
	//#define SERCOM1_USART_TX_BUFFER_SIZE      2048
#endif 		//#if 	MCU_ATSAML22N18A

#define UARTM4_CMD_BUFFFER_SIZE           (1024+64)


#define SERCOM1_USART_RX_INT_DISABLE()      SERCOM1_REGS->USART_INT.SERCOM_INTENCLR = SERCOM_USART_INT_INTENCLR_RXC_Msk
#define SERCOM1_USART_RX_INT_ENABLE()       SERCOM1_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_RXC_Msk

#define SERCOM1_USART_TX_INT_DISABLE()      SERCOM1_REGS->USART_INT.SERCOM_INTENCLR = SERCOM_USART_INT_INTENCLR_DRE_Msk
#define SERCOM1_USART_TX_INT_ENABLE()       SERCOM1_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_DRE_Msk




//******************************************************************************
//  Global
extern  UART_INTERFACE    uartM4_BUFF;

/*
extern  UINT32    uartM4_rx_Qbuf[SERCOM1_USART_RX_BUFFER_SIZE/4];
extern  UINT32    uartM4_tx_Qbuf[SERCOM1_USART_TX_BUFFER_SIZE/4];
extern  UINT32    uartM4_RXbuf[UARTM4_CMD_BUFFFER_SIZE/4];
extern  UINT32    uartM4_TXbuf[UARTM4_CMD_BUFFFER_SIZE/4];
*/
extern	UINT8 		uartM4_rx_Qbuf[SERCOM1_USART_RX_BUFFER_SIZE];
extern	UINT8 		uartM4_tx_Qbuf[SERCOM1_USART_TX_BUFFER_SIZE];
extern	UINT8 		uartM4_RXbuf[UARTM4_CMD_BUFFFER_SIZE];
//extern	UINT8 		uartM4_TXbuf[UARTM4_CMD_BUFFFER_SIZE];

extern  UINT8*    uartM4_rx_buffer;
extern  UINT8*    uartM4_tx_buffer;
extern  UINT8*    uartM4_buffer;




//******************************************************************************
//  Function
void  SERCOM1_USART_Initialize( void );

UINT8   uartM4_DataGet( UINT8 *rx_data );
UINT8   uartM4_DataPut( UINT8 tx_data );
UINT8   uartM4_StringPut( UINT8* w_buf, UINT16 length  );


#endif // GIT_SERCOM1_UART_H

