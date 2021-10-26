

#ifndef GIT_SERCOM4_UART_H
#define GIT_SERCOM4_UART_H


//******************************************************************************
//  Defined
//#define SERCOM4_USART_INT_BAUD_VALUE_115200            (61761U)   //  115740
#define SERCOM4_USART_INT_BAUD_VALUE_115200            (61775U)     //  115207

#define SERCOM4_USART_RX_BUFFER_SIZE      256
#define SERCOM4_USART_TX_BUFFER_SIZE      256
#define UARTRADARB_CMD_BUFFFER_SIZE       128


#define SERCOM4_USART_RX_INT_DISABLE()      SERCOM4_REGS->USART_INT.SERCOM_INTENCLR = SERCOM_USART_INT_INTENCLR_RXC_Msk
#define SERCOM4_USART_RX_INT_ENABLE()       SERCOM4_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_RXC_Msk

#define SERCOM4_USART_TX_INT_DISABLE()      SERCOM4_REGS->USART_INT.SERCOM_INTENCLR = SERCOM_USART_INT_INTENCLR_DRE_Msk
#define SERCOM4_USART_TX_INT_ENABLE()       SERCOM4_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_DRE_Msk




//******************************************************************************
//  Global
extern 	UART_INTERFACE    uartRadarB_BUFF;

extern 	UINT8 		uartRadarB_rx_Qbuf[];
extern 	UINT8 		uartRadarB_tx_Qbuf[];
extern 	UINT8 		uartRadarB_RXbuf[];
extern 	UINT8 		uartRadarB_TXbuf[];

extern 	UINT8*    uartRadarB_rx_buffer;
extern 	UINT8*    uartRadarB_tx_buffer;
extern 	UINT8*    uartRadarB_buffer;

extern	UINT8 		uartRadarB_Set_param[ sizeof(M0_RADAR_SET_FRAME) ];
extern	M0_RADAR_SET_FRAME  	RadarB_Set_Data;


//	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#if 	Tst_RADARB_01
	extern 	TIMER 	*tm_RadarB_Test;
	extern 	UINT8 	TstBuf_uartRadarB[];
#endif 	//#if 	Tst_RADARB_01




//******************************************************************************
//  Function
void  SERCOM4_USART_Initialize( void );

UINT8   RadarB_DataGet( UINT8 *rx_data );
UINT8   RadarB_DataPut( UINT8 tx_data );
UINT8   RadarB_StringPut( UINT8* w_buf, UINT16 length  );

void 	UartDataRx_RadarB( void );
void 	UartDataRx_RadarB_CMD( void );


//==============================================================================
void 		RadarB_Req_SWversion( void );




//	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#if 	Tst_RADARB_01
	void  TimerF_RadarB_Tst(void);	
#endif 	//#if 	Tst_RADARB_01


#endif // GIT_SERCOM4_UART_H

