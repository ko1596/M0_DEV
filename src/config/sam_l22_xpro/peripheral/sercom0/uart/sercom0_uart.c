

//******************************************************************************
//  sercom1_uart.c
//    20200827
//******************************************************************************
//==============================================================================
//------------------------------------------------------------------------------
//..............................................................................
//______________________________________________________________________________


//********************************************************************
//  Connect to RHMe      UART
//********************************************************************                       
//  I/O Multiplexing and Considerations ::    31 / 1092
//  32.8 Register Description
//  SERCOM USART - Register Description ::  532 / 1092

//	UART sercom0 C
//		PB24 	TXD 	SERCOM0-PAD[0]
//		PB25 	RXD 	SERCOM0-PAD[1]
//		PB22- GPIO
//		PB23- GPIO


#include "All_Header.h"


#if   SERCOM0_ENABLE




//******************************************************************************
//  Global
UART_INTERFACE    uartChili2S_BUFF;

UINT8 		uartChili2S_rx_Qbuf[SERCOM0_USART_RX_BUFFER_SIZE];
UINT8 		uartChili2S_tx_Qbuf[SERCOM0_USART_TX_BUFFER_SIZE];
UINT8 		uartChili2S_RXbuf[UARTCHILI2S_CMD_BUFFFER_SIZE];
UINT8 		uartChili2S_TXbuf[UARTCHILI2S_CMD_BUFFFER_SIZE];

UINT8*    uartChili2S_rx_buffer;
UINT8*    uartChili2S_tx_buffer;
UINT8*    uartChili2S_buffer;


//CHILI2S_INFO_FRAME  	Chili2S_info;


//==============================================================================
//	TEST
#if  	Tst_Chili2S_UART
	UINT8  	Tst_Buf[1024];
	UINT8  	Tst_Buf2[1024];
	int  		Tst_index;
	TIMER*  tm_Chili2S_UART;
#endif 		//#if  	Tst_Chili2S_UART

	int  Tst_length;




//******************************************************************************
//
//******************************************************************************
static void  uartChili2S_Clear_State( void )
{
  uartChili2S_BUFF.CMD = uartChili2S_BUFF.PTR = uartChili2S_BUFF.STATE = uartChili2S_BUFF.LENGTH = 0;
}   //void  uartChili2S_Clear_State( void )






//******************************************************************************
//
//******************************************************************************
//	UART SERCOM0 C
//		PC24 	TXD 	SERCOM0-PAD[2]
//		PC25 	RXD 	SERCOM0-PAD[3]
void SERCOM0_USART_Initialize( void )
{
  PORT_REGS->GROUP[2].PORT_PINCFG[24] = 0x1;    //  The peripheral multiplexer selection is enabled
  PORT_REGS->GROUP[2].PORT_PINCFG[25] = 0x1;    //  The peripheral multiplexer selection is enabled
  //  24/2=12; 25/2=12.5;
  PORT_REGS->GROUP[2].PORT_PMUX[12] = 0x22; 			//	Peripheral function C selected

  //	32. SERCOM USART – SERCOM Universal Synchronous and  		p514/1092
  //			32.7 Register Summary 															p531/1092
  SERCOM0_REGS->USART_INT.SERCOM_CTRLA = 
            SERCOM_USART_INT_CTRLA_MODE_USART_INT_CLK | 
            SERCOM_USART_INT_CTRLA_RXPO(0x3) |  		//	PAD[3]
            SERCOM_USART_INT_CTRLA_TXPO(0x1) |  		//	SERCOM PAD[2]
            SERCOM_USART_INT_CTRLA_DORD_Msk | 
            SERCOM_USART_INT_CTRLA_IBON_Msk | 
            SERCOM_USART_INT_CTRLA_FORM(0x0) | 
            SERCOM_USART_INT_CTRLA_SAMPR(0) ;

  SERCOM0_REGS->USART_INT.SERCOM_BAUD = SERCOM_USART_INT_BAUD_BAUD(SERCOM0_USART_INT_BAUD_VALUE_115200);

  SERCOM0_REGS->USART_INT.SERCOM_CTRLB = SERCOM_USART_INT_CTRLB_CHSIZE_8_BIT | SERCOM_USART_INT_CTRLB_SBMODE_1_BIT | SERCOM_USART_INT_CTRLB_RXEN_Msk | SERCOM_USART_INT_CTRLB_TXEN_Msk;
  
  while(SERCOM0_REGS->USART_INT.SERCOM_SYNCBUSY);     // Wait for sync

  // Enable the UART after the configurations
  SERCOM0_REGS->USART_INT.SERCOM_CTRLA |= SERCOM_USART_INT_CTRLA_ENABLE_Msk;

  while(SERCOM0_REGS->USART_INT.SERCOM_SYNCBUSY);     // Wait for sync


  //----------------------------------------------------------------------------
  // Bit 7 – ERROR: Error Interrupt Enable
  //SERCOM0_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_ERROR_Msk;

  // Bit 2 – RXC: Receive Complete Interrupt Enable
  SERCOM0_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_RXC_Msk;
  // Bit 0 – DRE: Data Register Empty Interrupt Enable
  //SERCOM0_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_DRE_Msk;

  NOP( );

  // ***************************************************************************
  //  Device Commands buffer
  // ***************************************************************************
  uartChili2S_BUFF.rx.buffer = (UINT8*)uartChili2S_rx_Qbuf;
  uartChili2S_BUFF.tx.buffer = (UINT8*)uartChili2S_tx_Qbuf;
  uartChili2S_BUFF.TrData = (UINT8*)uartChili2S_RXbuf;
  
  uartChili2S_BUFF.rx.front = uartChili2S_BUFF.rx.tail = uartChili2S_BUFF.rx.buffull = 0;
  uartChili2S_Clear_State( ); 
  NOP( );

	#if  	Tst_Chili2S_UART
  	Tst_index = 0;
  #endif  	//#if  	Tst_Chili2S_UART
}     //void SERCOM0_USART_Initialize( void )











//******************************************************************************
//
//******************************************************************************
void  SERCOM0_Handler_RX( void )
{
  UINT8     uart_data;
  UART_FIFO *fifo = &(uartChili2S_BUFF.rx);


  uart_data = SERCOM0_REGS->USART_INT.SERCOM_DATA;

  #if  	Tst_Chili2S_UART
	  Tst_Buf[ Tst_index ] = uart_data;
	  Tst_index++;
	  if( Tst_index >= 1024 )		{
	  	Tst_index = 0;
	  }
	  NOP( );
  #endif  	//#if  	Tst_Chili2S_UART
  
  //----------------------------------------------------------------------------------
  if( fifo->buffull ) {               
    NOP( );
    //  Disable RDAINT
    SERCOM0_USART_RX_INT_DISABLE( );
    NOP( );    
    return;
  }   //  if( fifo->buffull ) {
  
  //----------------------------------------------------------------------------------
  fifo->buffer[ fifo->tail ] = uart_data;
  fifo->tail = (fifo->tail + 1) & (SERCOM0_USART_RX_BUFFER_SIZE - 1);
  if( fifo->tail == fifo->front ) {
    fifo->buffull = 1;    //  buffer full
    NOP( );
  }   //  if( fifo->tail == fifo->front ) {
  NOP( );

}   //void  SERCOM0_Handler_RX( void )


//******************************************************************************
//
//******************************************************************************
void  SERCOM0_Handler_TX( void )
{
  UINT8     uart_data;
  UART_FIFO *fifo = &(uartChili2S_BUFF.tx);


  if( (fifo->tail == fifo->front) && (!fifo->buffull))  {
    SERCOM0_USART_TX_INT_DISABLE( );
    NOP( );
    return;
  }   //if( (fifo->tail == fifo->front) && (!fifo->buffull))  {

  else  {
    uart_data = fifo->buffer[ fifo->front ];
    SERCOM0_REGS->USART_INT.SERCOM_DATA = uart_data;

    fifo->front = (fifo->front + 1) & (SERCOM0_USART_TX_BUFFER_SIZE - 1);
    fifo->buffull = 0;

    if( fifo->tail != fifo->front ) {
      //  Enabae TXENDIF
      SERCOM0_USART_TX_INT_ENABLE( );
    }   //  if( fifo->tail != fifo->front ) {

  }    //if( (fifo->tail == fifo->front) && (!fifo->buffull))  {    else

}   //void  SERCOM0_Handler_TX( void )




//******************************************************************************
//
//******************************************************************************
void  SERCOM0_Handler( void )
{
  NOP( );
  if(SERCOM0_REGS->USART_INT.SERCOM_INTENSET != 0)    {
    NOP( );

    // Checks for data register empty flag
    if((SERCOM0_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_DRE_Msk) 
        && (SERCOM0_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_DRE_Msk))   {
      NOP( );
      SERCOM0_Handler_TX( );
      NOP( );
    }

    // Checks for receive complete empty flag
    if((SERCOM0_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_RXC_Msk) 
        && (SERCOM0_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_RXC_Msk))   {
      NOP( );
      SERCOM0_Handler_RX( );
      NOP( );
    }

    // Checks for receive complete empty flag
    if((SERCOM0_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_TXC_Msk) 
        && (SERCOM0_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_TXC_Msk))   {
      NOP( );
      NOP( );
    }    

    // Checks for error flag
    if((SERCOM0_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_ERROR_Msk) 
        && (SERCOM0_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_ERROR_Msk))   {
      NOP( );
      NOP( );
    }
  }   //if(SERCOM0_REGS->USART_INT.SERCOM_INTENSET != 0)    {

  NOP( );
}   //void SERCOM0_Handler( void )












//******************************************************************************
//
//******************************************************************************
/*
	CC 08 77  0000  FD	2222		7856
	CC 08 77  0000  FD  2222		0000
*/
void  Chili2S_Set_PAN_ADD( UINT16 panid, UINT16 sAddr, UINT8 rf_channel )
{
	Chili2S_DataPut( 0xCC );

	Chili2S_DataPut( 0x09 );

	Chili2S_DataPut( 0x77 );

	Chili2S_DataPut( 0x00 );
	Chili2S_DataPut( 0x00 );

	Chili2S_DataPut( 0xFD );

	Chili2S_DataPut( panid & 0x00FF );
	Chili2S_DataPut( (panid >> 8) & 0x00FF );

	Chili2S_DataPut( sAddr & 0x00FF );
	Chili2S_DataPut( (sAddr >> 8) & 0x00FF );

	Chili2S_DataPut( rf_channel );

}  		//void  Chili2S_Set_PAN_ADD( UINT16 panid, UINT16 sAddr )


//******************************************************************************
//
//******************************************************************************
/*
	//	Set RTC  	--------------------------------------------------------
	//															Y		M		D 	nc 	h 	m 	s
	CC 0E 60  0000  00 00 00  F8  	15 	08	17	00	0B	09	0B
*/
void  Chili2S_Set_RTC( void )
{
	SysRTC_Get( &(sysInfo.mcu_RTC) );

	Chili2S_DataPut( 0xCC );

	Chili2S_DataPut( 0x0E );

	Chili2S_DataPut( 0x60 );

	Chili2S_DataPut( 0x00 );
	Chili2S_DataPut( 0x00 );

	Chili2S_DataPut( 0x00 );
	Chili2S_DataPut( 0x00 );
	Chili2S_DataPut( 0x00 );
	Chili2S_DataPut( 0xF8 );

	Chili2S_DataPut( sysInfo.mcu_RTC.Year );
	Chili2S_DataPut( sysInfo.mcu_RTC.Month );
	Chili2S_DataPut( sysInfo.mcu_RTC.Day );
	Chili2S_DataPut( 0x00 );
	Chili2S_DataPut( sysInfo.mcu_RTC.Hour );
	Chili2S_DataPut( sysInfo.mcu_RTC.Minute );
	Chili2S_DataPut( sysInfo.mcu_RTC.Second );
}  	//void  Chili2S_Set_RTC( void )














//******************************************************************************
//
//******************************************************************************
void 	Chili2S_Req_Info( void )
{
	//	Req  F/W Version  	------------------------------------------------------
	//	CC 03 2C  0000
	Chili2S_DataPut( 0xCC );

	Chili2S_DataPut( 0x03 );

	Chili2S_DataPut( 0x2C );

	Chili2S_DataPut( 0x00 );
	Chili2S_DataPut( 0x00 );


	//	Req  Net Info  	----------------------------------------------------------
	//	CC 03 2D  0000
	Chili2S_DataPut( 0xCC );

	Chili2S_DataPut( 0x03 );

	Chili2S_DataPut( 0x2D );

	Chili2S_DataPut( 0x00 );
	Chili2S_DataPut( 0x00 );

	//	Req  RTC  	--------------------------------------------------------------
	//	CC 07 60  0000  00 00 00  F9
	Chili2S_DataPut( 0xCC );

	Chili2S_DataPut( 0x07 );

	Chili2S_DataPut( 0x60 );

	Chili2S_DataPut( 0x00 );
	Chili2S_DataPut( 0x00 );

	Chili2S_DataPut( 0x00 );
	Chili2S_DataPut( 0x00 );
	Chili2S_DataPut( 0x00 );
	Chili2S_DataPut( 0xF9 );
}  	//void 	Chili2S_Req_Info( void )







#if  Tst_Chili2S_UART

//******************************************************************************
//
//******************************************************************************
void  TimerF_Tst_Chili2S_UART(void)
{
	reset_timer( tm_Chili2S_UART );  
	NOP( );

	Chili2S_Set_PAN_ADD( 0x2222, 0x0000 );
}  		//void  TimerF_Tst_Chili2S_UART(void)

#endif  	//#if  Tst_Chili2S_UART

















//******************************************************************************
//
//******************************************************************************
UINT8   Chili2S_DataGet( UINT8 *rx_data )
{

  if( (uartChili2S_BUFF.rx.tail==uartChili2S_BUFF.rx.front) && (!uartChili2S_BUFF.rx.buffull) ) {
    NOP( );
    return  FAILURE;
  }
  
  //======================================================================================
  //  Disable RDAINT
  SERCOM0_USART_RX_INT_DISABLE( );
  NOP( );
  
  *rx_data = uartChili2S_BUFF.rx.buffer[ uartChili2S_BUFF.rx.front ];
  uartChili2S_BUFF.rx.front = (uartChili2S_BUFF.rx.front + 1) & (SERCOM0_USART_RX_BUFFER_SIZE - 1);
  
  if( (uartChili2S_BUFF.rx.buffull) && (uartChili2S_BUFF.rx.tail!=uartChili2S_BUFF.rx.front) )    {
    uartChili2S_BUFF.rx.buffull = 0;
  }
  
  //  Enable RDAINT
  SERCOM0_USART_RX_INT_ENABLE( );

  return  SUCCESS;
}   //UINT8   void  Chili2S_DataGet( UINT8* rx_data )


//******************************************************************************
//
//******************************************************************************
UINT8   Chili2S_DataPut( UINT8 tx_data )
{
  NOP( );
  if( uartChili2S_BUFF.tx.buffull ) {
    SERCOM0_USART_TX_INT_ENABLE( );
    NOP( );
    while( uartChili2S_BUFF.tx.buffull ) {
      NOP( );
    }
  }

  //============================================================================
  SERCOM0_USART_TX_INT_ENABLE( );

  uartChili2S_BUFF.tx.buffer[ uartChili2S_BUFF.tx.tail ] = tx_data;
  uartChili2S_BUFF.tx.tail = (uartChili2S_BUFF.tx.tail + 1) & (SERCOM0_USART_TX_BUFFER_SIZE - 1);
  
  if( uartChili2S_BUFF.tx.tail == uartChili2S_BUFF.tx.front ) {
      uartChili2S_BUFF.tx.buffull = 1;
  }
  
  //  Enabae TXENDIF
  SERCOM0_USART_TX_INT_ENABLE( );
  
  return SUCCESS;
}   //UINT8   void  Chili2S_DataPut( UINT8* tx_data )


//******************************************************************************
//
//******************************************************************************
UINT8   Chili2S_StringPut( UINT8* w_buf, UINT16 length  )
{
  int i;

  for( i=0 ; i<length ; i++ )   {
    //WaitMS( 1 );
    if( Chili2S_DataPut( w_buf[i] ) != SUCCESS )   {
      NOP( );
      return FAILURE;
    }
  }   //for( i=0 ; i<length ; i++ )   {

  return SUCCESS;
}     //UINT8   Chili2S_StringPut( UINT8* w_buf, UINT16 length  )

















//******************************************************************************
//
//******************************************************************************
/*
typedef struct _uart_fifo {
    UINT8*  buffer; // used as a ring buffer
    UINT16  front;          // Head index of queue
    UINT16  tail;         // next new index of queue
    UINT8   buffull;        // =1, queue full
    UINT8   NC1;          // No used
    UINT8   NC2;          // No used
    UINT8   NC3;          // No used
}UART_FIFO;

typedef struct _uart_interface_{
  UART_FIFO rx;
  UART_FIFO tx;
  UINT16    PTR;
  UINT16    LENGTH;
  UINT8     STATE;
  UINT8     CMD;
  UINT16    CRC16;
  UINT8*    TrData;
}UART_INTERFACE;

*/
void 	UartDataRx_Chili2S( void )
{
	UINT8 	uart_data;


	while( Chili2S_DataGet( &uart_data ) )  {

		switch( uartChili2S_BUFF.STATE )  {
			//========================================================================
			//	header
			case 0:
				if(uart_data == 0xCC) {
					uartChili2S_BUFF.PTR = 0;
					uartChili2S_BUFF.LENGTH = 0xFF;
					uartChili2S_BUFF.STATE = 1;
				}
				break;

			//------------------------------------------------------------------------
			// 	the packet length
			case 1:
				if( uart_data > (UINT8)100 )	{
					uartChili2S_Clear_State( );
					break;
				}
				else	{
					if( uart_data > (UINT8)128 )	{
						uartChili2S_Clear_State( );
						break;
					}
					uartChili2S_BUFF.LENGTH = uart_data;
					uartChili2S_BUFF.STATE = 2;
				}
				break;

			//------------------------------------------------------------------------
			// 	the packet payload
			case 2:
				NOP( );
				if( (uartChili2S_BUFF.PTR < (UINT16)UARTCHILI2S_CMD_BUFFFER_SIZE) && (uartChili2S_BUFF.PTR <= uartChili2S_BUFF.LENGTH) )	{
					
					uartChili2S_BUFF.TrData[ uartChili2S_BUFF.PTR ] = uart_data;
					uartChili2S_BUFF.PTR++;
					
					if( uartChili2S_BUFF.PTR == uartChili2S_BUFF.LENGTH )	{
						NOP( );
						NOP( );
						NOP( );
						return;
					}
				}
				else 	{
					uartChili2S_Clear_State( );
				}
				break;

			//------------------------------------------------------------------------
			//------------------------------------------------------------------------
			default:
				uartChili2S_Clear_State( );
				break;
		}  		//switch( uartChili2S_BUFF.STATE )  {
	}  		//while( Chili2S_DataGet( &uart_data ) )  {

}  		//void 	UartDataRx_Chili2S( void )


//******************************************************************************
//
//******************************************************************************
void 	UartDataRx_Chili2S_CMD( void )
{
	int  i;
	UINT8 *ptr;


	#if  	Tst_Chili2S_UART
		//	UINT8  	Tst_Buf2[1024];
		memset( Tst_Buf2, 0x00, 1024 );
		memcpy( Tst_Buf2, uartChili2S_BUFF.TrData, uartChili2S_BUFF.LENGTH );
	#endif  	//#if  	Tst_Chili2S_UART

	if( uartChili2S_BUFF.PTR && (uartChili2S_BUFF.LENGTH==uartChili2S_BUFF.PTR ) )	{
		NOP( );

		switch( uartChili2S_BUFF.TrData[0] )
		{
			//	Chili2S F/W Version  	------------------------------------------------
			//	[Tx]: CC 03 2C 00 00
			//	[Rx]: CC 33 AC 78 56   43 68 69 6C 69 73 20 50 61 72 6B 4D 65 74 65 72 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 32 30 32 31 30 38 32 36 2D 32 30 31
			case 0x2C+0x80:
				if( uartChili2S_BUFF.LENGTH == 0x33 ) 	{
					for( i=0 ; i<48 ; i++ )		{
						sysInfo.Chili2S_info.fw_ver[i] = uartChili2S_BUFF.TrData[i+3];
					}
				}  	//if( uartChili2S_BUFF.LENGTH == 0x33 ) 	{
				NOP( );
				break;

			//	Chili2S PAN-ID Short-Address  	--------------------------------------
			//	[Tx]: CC 03 2D 00 00
			//	[Rx]: CC 0E AD 78 56 01 88 88 88 88 4E 62 7A 12 22 22
			case 0x2D+0x80:
				if( uartChili2S_BUFF.LENGTH == 0x0E ) 	{
					sysInfo.Chili2S_info.sAddr = uartChili2S_BUFF.TrData[1];
					sysInfo.Chili2S_info.sAddr |= (uartChili2S_BUFF.TrData[2] << 8);

					sysInfo.Chili2S_info.rf_channel = uartChili2S_BUFF.TrData[11];

					sysInfo.Chili2S_info.panid = uartChili2S_BUFF.TrData[12];
					sysInfo.Chili2S_info.panid |= (uartChili2S_BUFF.TrData[13] << 8);
				}  	//if( uartChili2S_BUFF.LENGTH == 0x0E ) 	{
				NOP( );
				break;

			//	RTC  	----------------------------------------------------------------
			//	[Tx]: CC 07 60 00 00 00 00 00 F9
			//	[Rx]: CC 10 E0 78 56 00 00 00 F9 08 00 15 09 01 00 0A 34 2F
			case 0x60+0x80:
				if( uartChili2S_BUFF.LENGTH == 0x10 ) 	{
					sysInfo.Chili2S_info.rtc.Year = uartChili2S_BUFF.TrData[9];
					sysInfo.Chili2S_info.rtc.Month = uartChili2S_BUFF.TrData[10];
					sysInfo.Chili2S_info.rtc.Day = uartChili2S_BUFF.TrData[11];
					sysInfo.Chili2S_info.rtc.Hour = uartChili2S_BUFF.TrData[13];
					sysInfo.Chili2S_info.rtc.Minute = uartChili2S_BUFF.TrData[14];
					sysInfo.Chili2S_info.rtc.Second = uartChili2S_BUFF.TrData[15];
				}  	//if( uartChili2S_BUFF.LENGTH == 0x10 ) 	{
				NOP( );
				break;

			//	VOS  	----------------------------------------------------------------
			case 0x77:
				NOP( );
				switch( uartChili2S_BUFF.TrData[3] )  	{
					//	Lidar Data from Chili2S 	----------------------------------------
					//	CC 0A 77 00 00 F0 95 00 6C 08 E0 08
					case 0xF0:
						NOP( );
						Tst_length = sizeof(PARKMETER_VOS_MSG_FRAME);
						if ( (uartChili2S_BUFF.LENGTH-4) == sizeof(PARKMETER_VOS_MSG_FRAME) )		{
							NOP( );
							ptr = (UINT8*)&M0_AllDevStatus.lidar;
							for( i=0 ; i<sizeof(PARKMETER_VOS_MSG_FRAME) ; i++ )	{
								*ptr = uartChili2S_BUFF.TrData[ i + 4];
								ptr++;
							}
							//SysRTC_Get( (M0_RTC_TIME_FRAME*)&(M0_AllDevStatus.lidar.mcu_RTC) );
							UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_LIDAR, (uint8_t*)&(M0_AllDevStatus.lidar), sizeof(PARKMETER_VOS_MSG_FRAME) );
							NOP( );
						}  	//if ( uartChili2S_BUFF.LENGTH == 0x0A )		{
						break;

					//--------------------------------------------------------------------
					case 0xF1:
						NOP( );
						break;

					default:
						NOP( );
						#if  Tst_Chili2S_LIDAR
							M0_AllDevStatus.lidar.Dist = 0x1234;
							M0_AllDevStatus.lidar.Strength = 0x5678;
							M0_AllDevStatus.lidar.Temp = 0x9ABC;

							SysRTC_Get( (M0_RTC_TIME_FRAME*)&(M0_AllDevStatus.lidar.mcu_RTC) );
							NOP( );
							UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_LIDAR, (uint8_t*)&(M0_AllDevStatus.lidar), sizeof(PARKMETER_VOS_MSG_FRAME) );
						#endif  	//#if  Tst_Chili2S_LIDAR
						break;

				}  	//switch( uartChili2S_BUFF.TrData[3] )  	{
				break;
		}

		uartChili2S_Clear_State( );
	}  		//if( uartChili2S_BUFF.PTR && (uartChili2S_BUFF.LENGTH==uartChili2S_BUFF.PTR ) && (uartChili2S_BUFF.LENGTH<=UART_CMD_PAYLOAD_LENGTH) )	{

}  		//void 	UartDataRx_Chili2S_CMD( void )


#endif 		//#if   SERCOM0_ENABLE


