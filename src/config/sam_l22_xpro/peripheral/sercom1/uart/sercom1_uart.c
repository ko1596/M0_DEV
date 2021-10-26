

//******************************************************************************
//  sercom1_uart.c
//    20200827
//******************************************************************************
//==============================================================================
//------------------------------------------------------------------------------
//..............................................................................
//______________________________________________________________________________


//********************************************************************
//  Connect to i.MX8MM M4      UART
//********************************************************************                       
//  I/O Multiplexing and Considerations ::    31 / 1092
//  PA18/S12- TXD     C-SERCOM1-PAD[2] / D-SERCOM1-PAD[2]
//  PA19/S13- RXD     C-SERCOM1-PAD[3] / D-SERCOM1-PAD[3]


#include "All_Header.h"






//******************************************************************************
//  Global
UART_INTERFACE    uartM4_BUFF;

/*
UINT32    uartM4_rx_Qbuf[SERCOM1_USART_RX_BUFFER_SIZE/4];
UINT32    uartM4_tx_Qbuf[SERCOM1_USART_TX_BUFFER_SIZE/4];
UINT32    uartM4_RXbuf[UARTM4_CMD_BUFFFER_SIZE/4];
UINT32    uartM4_TXbuf[UARTM4_CMD_BUFFFER_SIZE/4];
*/
UINT8 		uartM4_rx_Qbuf[SERCOM1_USART_RX_BUFFER_SIZE];
UINT8 		uartM4_tx_Qbuf[SERCOM1_USART_TX_BUFFER_SIZE];
UINT8 		uartM4_RXbuf[UARTM4_CMD_BUFFFER_SIZE];
//UINT8 		uartM4_TXbuf[UARTM4_CMD_BUFFFER_SIZE];

UINT8*    uartM4_rx_buffer;
UINT8*    uartM4_tx_buffer;
UINT8*    uartM4_buffer;




//******************************************************************************
//
//******************************************************************************
//	UART SERCOM1 C
//		PA18 	TXD 	SERCOM1-PAD[2]
//		PA19 	RXD 	SERCOM1-PAD[3]
void SERCOM1_USART_Initialize( void )
{
	//  PA18/S12- TXD     C-SERCOM1-PAD[2] / D-SERCOM1-PAD[2]
	//  PA19/S13- RXD     C-SERCOM1-PAD[3] / D-SERCOM1-PAD[3]
  PORT_REGS->GROUP[0].PORT_PINCFG[18] = 0x1;    //  The peripheral multiplexer selection is enabled
  PORT_REGS->GROUP[0].PORT_PINCFG[19] = 0x1;    //  The peripheral multiplexer selection is enabled
  //  19/2=9.5; 18/2=9;
  PORT_REGS->GROUP[0].PORT_PMUX[9] = 0x22;
  
  
  SERCOM1_REGS->USART_INT.SERCOM_CTRLA = 
            SERCOM_USART_INT_CTRLA_MODE_USART_INT_CLK | 
            SERCOM_USART_INT_CTRLA_RXPO(0x3) | 
            SERCOM_USART_INT_CTRLA_TXPO(0x1) | 
            SERCOM_USART_INT_CTRLA_DORD_Msk | 
            SERCOM_USART_INT_CTRLA_IBON_Msk | 
            SERCOM_USART_INT_CTRLA_FORM(0x0) | 
            SERCOM_USART_INT_CTRLA_SAMPR(0) ;

  SERCOM1_REGS->USART_INT.SERCOM_BAUD = SERCOM_USART_INT_BAUD_BAUD(SERCOM1_USART_INT_BAUD_VALUE_115200);
	//SERCOM1_REGS->USART_INT.SERCOM_BAUD = SERCOM_USART_INT_BAUD_BAUD(SERCOM1_USART_INT_BAUD_VALUE_115200_4);

  SERCOM1_REGS->USART_INT.SERCOM_CTRLB = SERCOM_USART_INT_CTRLB_CHSIZE_8_BIT | SERCOM_USART_INT_CTRLB_SBMODE_1_BIT | SERCOM_USART_INT_CTRLB_RXEN_Msk | SERCOM_USART_INT_CTRLB_TXEN_Msk;
  
  while(SERCOM1_REGS->USART_INT.SERCOM_SYNCBUSY);     // Wait for sync

  // Enable the UART after the configurations
  SERCOM1_REGS->USART_INT.SERCOM_CTRLA |= SERCOM_USART_INT_CTRLA_ENABLE_Msk;

  while(SERCOM1_REGS->USART_INT.SERCOM_SYNCBUSY);     // Wait for sync


  //----------------------------------------------------------------------------
  // Bit 7 – ERROR: Error Interrupt Enable
  //SERCOM1_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_ERROR_Msk;

  // Bit 2 – RXC: Receive Complete Interrupt Enable
  SERCOM1_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_RXC_Msk;
  // Bit 0 – DRE: Data Register Empty Interrupt Enable
  //SERCOM1_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_DRE_Msk;

  NOP( );


  // ***************************************************************************
  //  GitNet Commands buffer
  // ***************************************************************************
  uartM4_BUFF.rx.buffer = (UINT8*)uartM4_rx_Qbuf;
  uartM4_BUFF.tx.buffer = (UINT8*)uartM4_tx_Qbuf;
  uartM4_BUFF.TrData = (UINT8*)uartM4_RXbuf;
  
  uartM4_BUFF.rx.front = uartM4_BUFF.rx.tail = uartM4_BUFF.rx.buffull = 0;
  uartM4_Clear_State( ); 
  NOP( );
}     //void SERCOM1_USART_Initialize( void )












//******************************************************************************
//
//******************************************************************************
UINT8   uartM4_DataGet( UINT8 *rx_data )
{

  if( (uartM4_BUFF.rx.tail==uartM4_BUFF.rx.front) && (!uartM4_BUFF.rx.buffull) ) {
    NOP( );
    return  FAILURE;
  }
  
  //======================================================================================
  //  Disable RDAINT
  SERCOM1_USART_RX_INT_DISABLE( );
  NOP( );
  
  *rx_data = uartM4_BUFF.rx.buffer[ uartM4_BUFF.rx.front ];
  uartM4_BUFF.rx.front = (uartM4_BUFF.rx.front + 1) & (SERCOM1_USART_RX_BUFFER_SIZE - 1);
  
  if( (uartM4_BUFF.rx.buffull) && (uartM4_BUFF.rx.tail!=uartM4_BUFF.rx.front) )    {
    uartM4_BUFF.rx.buffull = 0;
  }
  
  //  Enable RDAINT
  SERCOM1_USART_RX_INT_ENABLE( );

  return  SUCCESS;
}   //UINT8   void  uartM4_DataGet( UINT8* rx_data )


//******************************************************************************
//
//******************************************************************************
UINT8   uartM4_DataPut( UINT8 tx_data )
{
  NOP( );
  if( uartM4_BUFF.tx.buffull ) {
  	if( wakeupA53_flg == 0 ) 	{
    	SERCOM1_USART_TX_INT_ENABLE( );
    }
    else 	{
    	return FAILURE;
    }
    NOP( );
    while( uartM4_BUFF.tx.buffull ) {
      NOP( );
    }
  }

  //============================================================================
	if( wakeupA53_flg == 0 ) 	{
  	SERCOM1_USART_TX_INT_ENABLE( );
  }

  uartM4_BUFF.tx.buffer[ uartM4_BUFF.tx.tail ] = tx_data;
  uartM4_BUFF.tx.tail = (uartM4_BUFF.tx.tail + 1) & (SERCOM1_USART_TX_BUFFER_SIZE - 1);
  
  if( uartM4_BUFF.tx.tail == uartM4_BUFF.tx.front ) {
      uartM4_BUFF.tx.buffull = 1;
  }
  
  //  Enabae TXENDIF
	if( wakeupA53_flg == 0 ) 	{
  	SERCOM1_USART_TX_INT_ENABLE( );
  }
  
  return SUCCESS;
}   //UINT8   void  uartM4_DataPut( UINT8* tx_data )


//******************************************************************************
//
//******************************************************************************
UINT8   uartM4_StringPut( UINT8* w_buf, UINT16 length  )
{
  int i;  

  for( i=0 ; i<length ; i++ )   {
    //WaitMS( 1 );
    if( uartM4_DataPut( w_buf[i] ) != SUCCESS )   {
      NOP( );
      return FAILURE;
    }
  }   //for( i=0 ; i<length ; i++ )   {

  return SUCCESS;
}     //UINT8   uartM4_StringPut( UINT8* w_buf, UINT16 length  )













//******************************************************************************
//
//******************************************************************************
void  SERCOM1_Handler_RX( void )
{
  UINT8     uart_data;
  UART_FIFO *fifo = &(uartM4_BUFF.rx);


  uart_data = SERCOM1_REGS->USART_INT.SERCOM_DATA;
  
  //----------------------------------------------------------------------------------
  if( fifo->buffull ) {               
    NOP( );
    //  Disable RDAINT
    SERCOM1_USART_RX_INT_DISABLE( );
    NOP( );    
    return;
  }   //  if( fifo->buffull ) {
  
  //----------------------------------------------------------------------------------
  fifo->buffer[ fifo->tail ] = uart_data;
  fifo->tail = (fifo->tail + 1) & (SERCOM1_USART_RX_BUFFER_SIZE - 1);
  if( fifo->tail == fifo->front ) {
    fifo->buffull = 1;    //  buffer full
    NOP( );
  }   //  if( fifo->tail == fifo->front ) {
  NOP( );

}   //void  SERCOM1_Handler_RX( void )


//******************************************************************************
//
//******************************************************************************
void  SERCOM1_Handler_TX( void )
{
  UINT8     uart_data;
  UART_FIFO *fifo = &(uartM4_BUFF.tx);


  if( (fifo->tail == fifo->front) && (!fifo->buffull))  {
    SERCOM1_USART_TX_INT_DISABLE( );
    NOP( );
    return;
  }   //if( (fifo->tail == fifo->front) && (!fifo->buffull))  {

  else  {
    uart_data = fifo->buffer[ fifo->front ];
    SERCOM1_REGS->USART_INT.SERCOM_DATA = uart_data;

    fifo->front = (fifo->front + 1) & (SERCOM1_USART_TX_BUFFER_SIZE - 1);
    fifo->buffull = 0;

    if( fifo->tail != fifo->front ) {
    	if( wakeupA53_flg == 0 ) 	{
      	//  Enabae TXENDIF
      	SERCOM1_USART_TX_INT_ENABLE( );
    	}
    }   //  if( fifo->tail != fifo->front ) {

  }    //if( (fifo->tail == fifo->front) && (!fifo->buffull))  {    else

}   //void  SERCOM1_Handler_TX( void )




//******************************************************************************
//
//******************************************************************************
void  SERCOM1_Handler( void )
{
  NOP( );
  if(SERCOM1_REGS->USART_INT.SERCOM_INTENSET != 0)    {
    NOP( );

    // Checks for data register empty flag
    if((SERCOM1_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_DRE_Msk) 
        && (SERCOM1_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_DRE_Msk))   {
      NOP( );
      SERCOM1_Handler_TX( );
      NOP( );
    }

    // Checks for receive complete empty flag
    if((SERCOM1_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_RXC_Msk) 
        && (SERCOM1_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_RXC_Msk))   {
      NOP( );
      SERCOM1_Handler_RX( );
      NOP( );
    }

    // Checks for receive complete empty flag
    if((SERCOM1_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_TXC_Msk) 
        && (SERCOM1_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_TXC_Msk))   {
      NOP( );
      NOP( );
    }    

    // Checks for error flag
    if((SERCOM1_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_ERROR_Msk) 
        && (SERCOM1_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_ERROR_Msk))   {
      NOP( );
      NOP( );
    }
  }   //if(SERCOM1_REGS->USART_INT.SERCOM_INTENSET != 0)    {

  NOP( );
}   //void SERCOM1_Handler( void )

