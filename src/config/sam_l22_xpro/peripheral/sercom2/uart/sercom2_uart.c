

//******************************************************************************
//  sercom_uart.c
//    20200818
//******************************************************************************
//==============================================================================
//------------------------------------------------------------------------------
//..............................................................................
//______________________________________________________________________________


//********************************************************************
//  Connect to i.MX8MM M4      UART
//********************************************************************                       
//  I/O Multiplexing and Considerations ::    31 / 1092
//  PA18/S12- TXD     C-SERCOM1-PAD[2] / D-SERCOM2-PAD[2]
//  PA19/S13- RXD     C-SERCOM1-PAD[3] / D-SERCOM2-PAD[3]


#include "All_Header.h"


#if   SERCOM2_ENABLE

//******************************************************************************
//  Global
UART_INTERFACE    uartTLSAM_BUFF;

UINT8 		uartTLSAM_rx_Qbuf[SERCOM2_USART_RX_BUFFER_SIZE];
UINT8 		uartTLSAM_tx_Qbuf[SERCOM2_USART_TX_BUFFER_SIZE];
UINT8 		uartTLSAM_RXbuf[UART_TLSAM_Rx_BUFFFER_SIZE];
UINT8 		uartTLSAM_TXbuf[UART_TLSAM_Tx_BUFFFER_SIZE];

UINT8*    uartTLSAM_rx_buffer;
UINT8*    uartTLSAM_tx_buffer;
UINT8*    uartTLSAM_buffer;

//==============================================================================
M0_TLSAM_FRAME 		TLSAM_Data;

TIMER 	*tm_TLSAM;


//	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#if 	Tst_TLSAM_01
	TIMER 	*tm_TLSAM_Test;
	UINT8     CHK1;
	UINT8     CHK2;	
#endif 	//#if 	Tst_TLSAM_01






//==============================================================================
static void  uartTLSAM_Clear_State( void );


//******************************************************************************
//
//******************************************************************************
void SERCOM2_USART_Initialize( void )
{
	//		PA22 	TXD 	SERCOM2D-PAD[0]
	//		PA23 	RXD 	SERCOM2D-PAD[1]
	//	29. PORT - I/O Pin Controller 		p456/1092
	//		29.7 Register Summary 					p465/1092
  PORT_REGS->GROUP[0].PORT_PINCFG[22] = 0x1;    //  The peripheral multiplexer selection is enabled
  PORT_REGS->GROUP[0].PORT_PINCFG[23] = 0x1;    //  The peripheral multiplexer selection is enabled
  //  12/2=6; 13/2=6.5;
  PORT_REGS->GROUP[0].PORT_PMUX[11] = 0x33; 			//	Peripheral function D selected

  //	32. SERCOM USART – SERCOM Universal Synchronous and  		p514/1092
  //			32.7 Register Summary 															p531/1092
  SERCOM2_REGS->USART_INT.SERCOM_CTRLA = 
            SERCOM_USART_INT_CTRLA_MODE_USART_INT_CLK | 
            SERCOM_USART_INT_CTRLA_RXPO(0x1) | 
            //SERCOM_USART_INT_CTRLA_TXPO(0x1) | 
            SERCOM_USART_INT_CTRLA_TXPO(0x0) | 
            SERCOM_USART_INT_CTRLA_DORD_Msk | 
            SERCOM_USART_INT_CTRLA_IBON_Msk | 
            SERCOM_USART_INT_CTRLA_FORM(0x0) | 
            SERCOM_USART_INT_CTRLA_SAMPR(0) ;

  SERCOM2_REGS->USART_INT.SERCOM_BAUD = SERCOM_USART_INT_BAUD_BAUD(SERCOM2_USART_INT_BAUD_VALUE_115200);

  SERCOM2_REGS->USART_INT.SERCOM_CTRLB = SERCOM_USART_INT_CTRLB_CHSIZE_8_BIT | SERCOM_USART_INT_CTRLB_SBMODE_1_BIT | SERCOM_USART_INT_CTRLB_RXEN_Msk | SERCOM_USART_INT_CTRLB_TXEN_Msk;
  
  while(SERCOM2_REGS->USART_INT.SERCOM_SYNCBUSY);     // Wait for sync

  // Enable the UART after the configurations
  SERCOM2_REGS->USART_INT.SERCOM_CTRLA |= SERCOM_USART_INT_CTRLA_ENABLE_Msk;

  while(SERCOM2_REGS->USART_INT.SERCOM_SYNCBUSY);     // Wait for sync


  //----------------------------------------------------------------------------
  // Bit 7 – ERROR: Error Interrupt Enable
  //SERCOM2_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_ERROR_Msk;

  // Bit 2 – RXC: Receive Complete Interrupt Enable
  SERCOM2_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_RXC_Msk;
  // Bit 0 – DRE: Data Register Empty Interrupt Enable
  //SERCOM2_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_DRE_Msk;

  NOP( );

  // ***************************************************************************
  //  Device Commands buffer
  // ***************************************************************************
  uartTLSAM_BUFF.rx.buffer = (UINT8*)uartTLSAM_rx_Qbuf;
  uartTLSAM_BUFF.tx.buffer = (UINT8*)uartTLSAM_tx_Qbuf;
  uartTLSAM_BUFF.TrData = (UINT8*)uartTLSAM_RXbuf;
  
  uartTLSAM_BUFF.rx.front = uartTLSAM_BUFF.rx.tail = uartTLSAM_BUFF.rx.buffull = 0;
  uartTLSAM_Clear_State( ); 
  NOP( );

  //============================================================================
  memset( (UINT8*)&TLSAM_Data, 0x00, sizeof(M0_TLSAM_FRAME) );

}     //void SERCOM2_USART_Initialize( void )












//******************************************************************************
//
//******************************************************************************
void  SERCOM2_Handler_RX( void )
{
  UINT8     uart_data;
  UART_FIFO *fifo = &(uartTLSAM_BUFF.rx);


  uart_data = SERCOM2_REGS->USART_INT.SERCOM_DATA;
  
  //----------------------------------------------------------------------------------
  if( fifo->buffull ) {               
    NOP( );
    //  Disable RDAINT
    SERCOM2_USART_RX_INT_DISABLE( );
    NOP( );    
    return;
  }   //  if( fifo->buffull ) {
  
  //----------------------------------------------------------------------------------
  fifo->buffer[ fifo->tail ] = uart_data;
  fifo->tail = (fifo->tail + 1) & (SERCOM2_USART_RX_BUFFER_SIZE - 1);
  if( fifo->tail == fifo->front ) {
    fifo->buffull = 1;    //  buffer full
    NOP( );
  }   //  if( fifo->tail == fifo->front ) {
  NOP( );

}   //void  SERCOM2_Handler_RX( void )


//******************************************************************************
//
//******************************************************************************
void  SERCOM2_Handler_TX( void )
{
  UINT8     uart_data;
  UART_FIFO *fifo = &(uartTLSAM_BUFF.tx);


  if( (fifo->tail == fifo->front) && (!fifo->buffull))  {
    SERCOM2_USART_TX_INT_DISABLE( );
    NOP( );
    return;
  }   //if( (fifo->tail == fifo->front) && (!fifo->buffull))  {

  else  {
    uart_data = fifo->buffer[ fifo->front ];
    SERCOM2_REGS->USART_INT.SERCOM_DATA = uart_data;

    fifo->front = (fifo->front + 1) & (SERCOM2_USART_TX_BUFFER_SIZE - 1);
    fifo->buffull = 0;

    if( fifo->tail != fifo->front ) {
      //  Enabae TXENDIF
      SERCOM2_USART_TX_INT_ENABLE( );
    }   //  if( fifo->tail != fifo->front ) {

  }    //if( (fifo->tail == fifo->front) && (!fifo->buffull))  {    else

}   //void  SERCOM2_Handler_TX( void )




//******************************************************************************
//
//******************************************************************************
void  SERCOM2_Handler( void )
{
  NOP( );
  if(SERCOM2_REGS->USART_INT.SERCOM_INTENSET != 0)    {
    NOP( );

    // Checks for data register empty flag
    if((SERCOM2_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_DRE_Msk) 
        && (SERCOM2_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_DRE_Msk))   {
      NOP( );
      SERCOM2_Handler_TX( );
      NOP( );
    }

    // Checks for receive complete empty flag
    if((SERCOM2_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_RXC_Msk) 
        && (SERCOM2_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_RXC_Msk))   {
      NOP( );
      SERCOM2_Handler_RX( );
      NOP( );
    }

    // Checks for receive complete empty flag
    if((SERCOM2_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_TXC_Msk) 
        && (SERCOM2_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_TXC_Msk))   {
      NOP( );
      NOP( );
    }    

    // Checks for error flag
    if((SERCOM2_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_ERROR_Msk) 
        && (SERCOM2_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_ERROR_Msk))   {
      NOP( );
      NOP( );
    }
  }   //if(SERCOM2_REGS->USART_INT.SERCOM_INTENSET != 0)    {

  NOP( );
}   //void SERCOM2_Handler( void )
















//******************************************************************************
//
//******************************************************************************
static void  uartTLSAM_Clear_State( void )
{
  uartTLSAM_BUFF.CMD = uartTLSAM_BUFF.PTR = uartTLSAM_BUFF.STATE = uartTLSAM_BUFF.LENGTH = 0;
}   //void  uartTLSAM_Clear_State( void )




//******************************************************************************
//
//******************************************************************************
UINT8   TLSAM_DataGet( UINT8 *rx_data )
{

  if( (uartTLSAM_BUFF.rx.tail==uartTLSAM_BUFF.rx.front) && (!uartTLSAM_BUFF.rx.buffull) ) {
    NOP( );
    return  FAILURE;
  }
  
  //======================================================================================
  //  Disable RDAINT
  SERCOM2_USART_RX_INT_DISABLE( );
  NOP( );
  
  *rx_data = uartTLSAM_BUFF.rx.buffer[ uartTLSAM_BUFF.rx.front ];
  uartTLSAM_BUFF.rx.front = (uartTLSAM_BUFF.rx.front + 1) & (SERCOM2_USART_RX_BUFFER_SIZE - 1);
  
  if( (uartTLSAM_BUFF.rx.buffull) && (uartTLSAM_BUFF.rx.tail!=uartTLSAM_BUFF.rx.front) )    {
    uartTLSAM_BUFF.rx.buffull = 0;
  }
  
  //  Enable RDAINT
  SERCOM2_USART_RX_INT_ENABLE( );

  return  SUCCESS;
}   //UINT8   void  TLSAM_DataGet( UINT8* rx_data )


//******************************************************************************
//
//******************************************************************************
UINT8   TLSAM_DataPut( UINT8 tx_data )
{
  NOP( );
  if( uartTLSAM_BUFF.tx.buffull ) {
    SERCOM2_USART_TX_INT_ENABLE( );
    NOP( );
    while( uartTLSAM_BUFF.tx.buffull ) {
      NOP( );
    }
  }

  //============================================================================
  SERCOM2_USART_TX_INT_ENABLE( );

  uartTLSAM_BUFF.tx.buffer[ uartTLSAM_BUFF.tx.tail ] = tx_data;
  uartTLSAM_BUFF.tx.tail = (uartTLSAM_BUFF.tx.tail + 1) & (SERCOM2_USART_TX_BUFFER_SIZE - 1);
  
  if( uartTLSAM_BUFF.tx.tail == uartTLSAM_BUFF.tx.front ) {
      uartTLSAM_BUFF.tx.buffull = 1;
  }
  
  //  Enabae TXENDIF
  SERCOM2_USART_TX_INT_ENABLE( );
  
  return SUCCESS;
}   //UINT8   void  TLSAM_DataPut( UINT8* tx_data )


//******************************************************************************
//
//******************************************************************************
UINT8   TLSAM_StringPut( UINT8* w_buf, UINT16 length  )
{
  int i;

  for( i=0 ; i<length ; i++ )   {
    //WaitMS( 1 );
    if( TLSAM_DataPut( w_buf[i] ) != SUCCESS )   {
      NOP( );
      return FAILURE;
    }
  }   //for( i=0 ; i<length ; i++ )   {

  return SUCCESS;
}     //UINT8   TLSAM_StringPut( UINT8* w_buf, UINT16 length  )














//******************************************************************************
//
//******************************************************************************
//	after 145ms response
void 		TLSAM_Req_FWversion( void )
{
	UINT8			*txPtr = uartTLSAM_TXbuf;
	UINT16 		txLength;

	int  i;


	*txPtr = 0x7E;						txPtr++;

	*txPtr = 0x00;						txPtr++; 				//	LEN; (00 03)
	*txPtr = 0x00;						txPtr++;

	*txPtr = 0xA1;						txPtr++; 				//	CMD, Read F/W version

	//		Data 		----------------------------------------------------------------
	*txPtr = 0x00;						txPtr++; 				//	data


	//----------------------------------------------------------------------------
	txLength = txPtr - uartTLSAM_TXbuf;
	uartTLSAM_TXbuf[1] = ((txLength-2)>>8) & 0x00FF;
	uartTLSAM_TXbuf[2] = (txLength-2) & 0x00FF;

	uartTLSAM_TXbuf[txLength] = 0;
	for( i=0 ; i<txLength ; i++)		{
		uartTLSAM_TXbuf[txLength] ^= uartTLSAM_TXbuf[i];
	}

	TLSAM_StringPut( uartTLSAM_TXbuf, (txLength+1) );
	NOP( );
} 	//void 		TLSAM_Req_FWversion( void )


//******************************************************************************
//
//******************************************************************************
//	after 145ms response
void 		TLSAM_Req_Encrypt( UINT8* dataPtr, UINT16 dataLength )
{
	UINT8			*txPtr = uartTLSAM_TXbuf;
	UINT16 		txLength;
	int  i;

	NOP( );
	*txPtr = 0x7E;						txPtr++;

	*txPtr = 0x00;						txPtr++; 				//	LEN; (00 03)
	*txPtr = 0x00;						txPtr++;

	*txPtr = 0xA2;						txPtr++; 				//	CMD, Read F/W version

	//		Data 		----------------------------------------------------------------
	for( i=0 ; i<dataLength ; i++ )		{
		*txPtr = *dataPtr;
		txPtr++;
		dataPtr++;
	}

	//----------------------------------------------------------------------------
	txLength = txPtr - uartTLSAM_TXbuf;
	uartTLSAM_TXbuf[1] = ((txLength-2)>>8) & 0x00FF;
	uartTLSAM_TXbuf[2] = (txLength-2) & 0x00FF;

	uartTLSAM_TXbuf[txLength] = 0;
	for( i=0 ; i<txLength ; i++)		{
		uartTLSAM_TXbuf[txLength] ^= uartTLSAM_TXbuf[i];
	}

	TLSAM_StringPut( uartTLSAM_TXbuf, (txLength+1) );
	NOP( );
} 		//void 		TLSAM_Req_Encrypt( UINT8* dataPtr, UINT16 dataLength )

















//******************************************************************************
//
//******************************************************************************
void 	UartDataRx_TLSAM( void )
{
	UINT8 	uart_data;
	UINT8 	ckSUM;
	int 		i;


	while( TLSAM_DataGet( &uart_data ) )  {
		NOP( );
		switch( uartTLSAM_BUFF.STATE )  {
			//========================================================================
			//	header
			case 0:
				if(uart_data == 0x7F) 	{
					uartTLSAM_RXbuf[0] = uart_data;
					uartTLSAM_BUFF.STATE = 1;
				}
				break;

			case 1:
				uartTLSAM_RXbuf[uartTLSAM_BUFF.STATE] = uart_data;
				uartTLSAM_BUFF.LENGTH = ((UINT16)uart_data<<8) & 0xFF00;
				uartTLSAM_BUFF.STATE++;
				break;

			case 2:
				uartTLSAM_RXbuf[uartTLSAM_BUFF.STATE] = uart_data;
				uartTLSAM_BUFF.LENGTH |= uart_data;
				uartTLSAM_BUFF.STATE++;
				uartTLSAM_BUFF.PTR = 0;
				break;

			//========================================================================
			case 3:
				uartTLSAM_BUFF.PTR++;
				uartTLSAM_RXbuf[uartTLSAM_BUFF.PTR+2] = uart_data;
				if( uartTLSAM_BUFF.PTR == uartTLSAM_BUFF.LENGTH )		{
					NOP( );
					ckSUM = 0;
					for( i=0 ; i<=(uartTLSAM_BUFF.PTR+1) ; i++ )	{
						ckSUM ^= uartTLSAM_RXbuf[i];
						NOP( );
					} 		//for( i=0 ; i<=(uartTLSAM_BUFF.PTR+1) ; i++ )	{

					if( ckSUM != uart_data )	{
						NOP( );
						uartTLSAM_Clear_State( );
					}
					NOP( );
					return;
				} 		//if( uartTLSAM_BUFF.PTR == uartTLSAM_BUFF.LENGTH )		{
				break;


			//========================================================================
			//========================================================================
			default:
				uartTLSAM_Clear_State( );
				break;
		} 		//switch( uartTLSAM_BUFF.STATE )  {

	} 		//while( TLSAM_DataGet( &uart_data ) )  {
} 	//void 	UartDataRx_TLSAM( void )


//******************************************************************************
//
//******************************************************************************
//		M0_AllDevStatus.radar_A
//		uartTLSAM_RXbuf[0] uartTLSAM_RXbuf[1] = uartTLSAM_BUFF.LENGTH
//		uartTLSAM_RXbuf[2] 	uartTLSAM_BUFF.CMD
//
//			加密16 bytes. 總回應bytes數是 256+(16+16）+256 = 544 bytes
//
/*
	typedef struct  {
		UINT8 								FW_version[2];
		UINT16 								status;
		UINT8 								name[64];
		UINT32 								dataLength;
		UINT8 								data[1600];
	}M0_TLSAM_FRAME;
*/
void 	UartDataRx_TLSAM_CMD( void )
{
	UINT16 		i;

	if( (uartTLSAM_BUFF.PTR>0) && (uartTLSAM_BUFF.PTR == uartTLSAM_BUFF.LENGTH) )		{
		NOP( );
		
		switch( uartTLSAM_RXbuf[3] )		{
			//	TL-SAM FW version 	--------------------------------------------------
			case 0xA1:
				NOP( );
				TLSAM_Data.status = uartTLSAM_RXbuf[4];
				TLSAM_Data.FW_version[0] = uartTLSAM_RXbuf[5];
				TLSAM_Data.FW_version[1] = uartTLSAM_RXbuf[6];

				close_timer( tm_TLSAM );
				NOP( );
				break;

			//	Encryption Data 	----------------------------------------------------
			case 0xA2:
				NOP( );
				TLSAM_Data.dataLength = uartTLSAM_BUFF.LENGTH - 2;
				for( i=0 ; i<TLSAM_Data.dataLength ; i++ )		{
					TLSAM_Data.data[i] = uartTLSAM_RXbuf[4+i];
				} 		//for( i=0 ; i<(uartTLSAM_BUFF.LENGTH-1) ; i++ )		{

				//UartDataTx_M0toM4_Data( uart_RSP_ENC, (UINT8*)&TLSAM_Data, sizeof(M0_TLSAM_FRAME) );
				UartDataTx_M0toM4_Data( uart_RSP_ENC, (UINT8*)&TLSAM_Data, (2+2+64+4+TLSAM_Data.dataLength) );
				break;
		} 		//switch( uartTLSAM_RXbuf[3] )		{
		uartTLSAM_Clear_State( );
	} 		//if( (uartTLSAM_BUFF.PTR>0) && (uartTLSAM_BUFF.PTR == uartTLSAM_BUFF.LENGTH) )		{
} 	//void 	UartDataRx_TLSAM_CMD( void )













//******************************************************************************
//
//******************************************************************************
void 	TimerF_TLSAM_ReqFWversion( void )
{
	reset_timer( tm_TLSAM );  
	NOP( );

	//============================================================================
	TLSAM_Req_FWversion( );
} 		//void 	TimerF_TLSAM_ReqFWversion( void )




#if 	Tst_TLSAM_01

//******************************************************************************
//
//******************************************************************************
void 	TimerF_TLSAM_Test( void )
{
	reset_timer( tm_TLSAM_Test );  
	NOP( );

	//============================================================================
	TLSAM_Req_FWversion( );
} 		//void 	TimerF_TLSAM_Test( void )

#endif 	//#if 	Tst_TLSAM_01


#endif //	#if   SERCOM2_ENABLE


