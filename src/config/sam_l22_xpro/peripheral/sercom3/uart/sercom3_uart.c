

//******************************************************************************
//  SERCOM3_uart.c
//    20210106
//******************************************************************************
//==============================================================================
//------------------------------------------------------------------------------
//..............................................................................
//______________________________________________________________________________


//********************************************************************
//  Connect to Radar A      UART
//********************************************************************                       
//  I/O Multiplexing and Considerations ::    31 / 1092
//  32.8 Register Description
//  SERCOM USART - Register Description ::  532 / 1092

//	UART SERCOM3 D
//		PA12 	TXD 	SERCOM3-PAD[0]
//		PA13 	RXD 	SERCOM3-PAD[1]


#include "All_Header.h"




//******************************************************************************
//  Global
UART_INTERFACE    uartRadarA_BUFF;

UINT8 		uartRadarA_rx_Qbuf[SERCOM3_USART_RX_BUFFER_SIZE];
UINT8 		uartRadarA_tx_Qbuf[SERCOM3_USART_TX_BUFFER_SIZE];
UINT8 		uartRadarA_RXbuf[UARTRADARA_CMD_BUFFFER_SIZE];
UINT8 		uartRadarA_TXbuf[UARTRADARA_CMD_BUFFFER_SIZE];

UINT8*    uartRadarA_rx_buffer;
UINT8*    uartRadarA_tx_buffer;
UINT8*    uartRadarA_buffer;

UINT8 		uartRadarA_Set_param[ sizeof(M0_RADAR_SET_FRAME) ];
M0_RADAR_SET_FRAME  	RadarA_Set_Data;


UINT16 		ckSUM_RadarA;

static int  RadarA_car01_cnt;



//	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#if 	Tst_RADARA_01
	TIMER 	*tm_RadarA_Test;
	UINT8 	TstBuf_uartRadarA[1024];
#endif 	//#if 	Tst_RADARA_01









//==============================================================================
static void  uartRadarA_Clear_State( void );




//******************************************************************************
//
//******************************************************************************
//	UART SERCOM3 D
//		PA12 	TXD 	SERCOM3-PAD[0]
//		PA13 	RXD 	SERCOM3-PAD[1]
void SERCOM3_USART_Initialize( void )
{
	//		PA12 	TXD 	SERCOM3-PAD[0]
	//		PA13 	RXD 	SERCOM3-PAD[1]
	//	29. PORT - I/O Pin Controller 		p456/1092
	//		29.7 Register Summary 					p465/1092
  PORT_REGS->GROUP[0].PORT_PINCFG[12] = 0x1;    //  The peripheral multiplexer selection is enabled
  PORT_REGS->GROUP[0].PORT_PINCFG[13] = 0x1;    //  The peripheral multiplexer selection is enabled
  //  12/2=6; 13/2=6.5;
  PORT_REGS->GROUP[0].PORT_PMUX[6] = 0x33; 			//	Peripheral function D selected

  //	32. SERCOM USART – SERCOM Universal Synchronous and  		p514/1092
  //			32.7 Register Summary 															p531/1092
  SERCOM3_REGS->USART_INT.SERCOM_CTRLA = 
            SERCOM_USART_INT_CTRLA_MODE_USART_INT_CLK | 
            SERCOM_USART_INT_CTRLA_RXPO(0x1) | 
            SERCOM_USART_INT_CTRLA_TXPO(0x0) | 
            SERCOM_USART_INT_CTRLA_DORD_Msk | 
            SERCOM_USART_INT_CTRLA_IBON_Msk | 
            SERCOM_USART_INT_CTRLA_FORM(0x0) | 
            SERCOM_USART_INT_CTRLA_SAMPR(0) ;

  SERCOM3_REGS->USART_INT.SERCOM_BAUD = SERCOM_USART_INT_BAUD_BAUD(SERCOM3_USART_INT_BAUD_VALUE_115200);

  SERCOM3_REGS->USART_INT.SERCOM_CTRLB = SERCOM_USART_INT_CTRLB_CHSIZE_8_BIT | SERCOM_USART_INT_CTRLB_SBMODE_1_BIT | SERCOM_USART_INT_CTRLB_RXEN_Msk | SERCOM_USART_INT_CTRLB_TXEN_Msk;
  
  while(SERCOM3_REGS->USART_INT.SERCOM_SYNCBUSY);     // Wait for sync

  // Enable the UART after the configurations
  SERCOM3_REGS->USART_INT.SERCOM_CTRLA |= SERCOM_USART_INT_CTRLA_ENABLE_Msk;

  while(SERCOM3_REGS->USART_INT.SERCOM_SYNCBUSY);     // Wait for sync


  //----------------------------------------------------------------------------
  // Bit 7 – ERROR: Error Interrupt Enable
  //SERCOM3_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_ERROR_Msk;

  // Bit 2 – RXC: Receive Complete Interrupt Enable
  SERCOM3_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_RXC_Msk;
  // Bit 0 – DRE: Data Register Empty Interrupt Enable
  //SERCOM3_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_DRE_Msk;

  NOP( );

  // ***************************************************************************
  //  Device Commands buffer
  // ***************************************************************************
	//	20211014-031270
	RadarA_car01_cnt = 0;
	memset( ((UINT8*)&M0_AllDevStatus.radar_A), 0x00, sizeof(M0_RADAR_FRAME) );

	//----------------------------------------------------------------------------
	uartRadarA_BUFF.rx.buffer = (UINT8*)uartRadarA_rx_Qbuf;
	uartRadarA_BUFF.tx.buffer = (UINT8*)uartRadarA_tx_Qbuf;
	uartRadarA_BUFF.TrData = (UINT8*)uartRadarA_RXbuf;

	uartRadarA_BUFF.rx.front = uartRadarA_BUFF.rx.tail = uartRadarA_BUFF.rx.buffull = 0;
	uartRadarA_Clear_State( ); 
	NOP( );
}     //void SERCOM3_USART_Initialize( void )












//******************************************************************************
//
//******************************************************************************
void  SERCOM3_Handler_RX( void )
{
  UINT8     uart_data;
  UART_FIFO *fifo = &(uartRadarA_BUFF.rx);


  uart_data = SERCOM3_REGS->USART_INT.SERCOM_DATA;
  
  //----------------------------------------------------------------------------------
  if( fifo->buffull ) {               
    NOP( );
    //  Disable RDAINT
    SERCOM3_USART_RX_INT_DISABLE( );
    NOP( );    
    return;
  }   //  if( fifo->buffull ) {
  
  //----------------------------------------------------------------------------------
  fifo->buffer[ fifo->tail ] = uart_data;
  fifo->tail = (fifo->tail + 1) & (SERCOM3_USART_RX_BUFFER_SIZE - 1);
  if( fifo->tail == fifo->front ) {
    fifo->buffull = 1;    //  buffer full
    NOP( );
  }   //  if( fifo->tail == fifo->front ) {
  NOP( );

}   //void  SERCOM3_Handler_RX( void )


//******************************************************************************
//
//******************************************************************************
void  SERCOM3_Handler_TX( void )
{
  UINT8     uart_data;
  UART_FIFO *fifo = &(uartRadarA_BUFF.tx);


  if( (fifo->tail == fifo->front) && (!fifo->buffull))  {
    SERCOM3_USART_TX_INT_DISABLE( );
    NOP( );
    return;
  }   //if( (fifo->tail == fifo->front) && (!fifo->buffull))  {

  else  {
    uart_data = fifo->buffer[ fifo->front ];
    SERCOM3_REGS->USART_INT.SERCOM_DATA = uart_data;

    fifo->front = (fifo->front + 1) & (SERCOM3_USART_TX_BUFFER_SIZE - 1);
    fifo->buffull = 0;

    if( fifo->tail != fifo->front ) {
      //  Enabae TXENDIF
      SERCOM3_USART_TX_INT_ENABLE( );
    }   //  if( fifo->tail != fifo->front ) {

  }    //if( (fifo->tail == fifo->front) && (!fifo->buffull))  {    else

}   //void  SERCOM3_Handler_TX( void )




//******************************************************************************
//
//******************************************************************************
void  SERCOM3_Handler( void )
{
  NOP( );
  if(SERCOM3_REGS->USART_INT.SERCOM_INTENSET != 0)    {
    NOP( );

    // Checks for data register empty flag
    if((SERCOM3_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_DRE_Msk) 
        && (SERCOM3_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_DRE_Msk))   {
      NOP( );
      SERCOM3_Handler_TX( );
      NOP( );
    }

    // Checks for receive complete empty flag
    if((SERCOM3_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_RXC_Msk) 
        && (SERCOM3_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_RXC_Msk))   {
      NOP( );
      SERCOM3_Handler_RX( );
      NOP( );
    }

    // Checks for receive complete empty flag
    if((SERCOM3_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_TXC_Msk) 
        && (SERCOM3_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_TXC_Msk))   {
      NOP( );
      NOP( );
    }    

    // Checks for error flag
    if((SERCOM3_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_ERROR_Msk) 
        && (SERCOM3_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_ERROR_Msk))   {
      NOP( );
      NOP( );
    }
  }   //if(SERCOM3_REGS->USART_INT.SERCOM_INTENSET != 0)    {

  NOP( );
}   //void SERCOM3_Handler( void )

















//******************************************************************************
//
//******************************************************************************
static void  uartRadarA_Clear_State( void )
{
  uartRadarA_BUFF.CMD = uartRadarA_BUFF.PTR = uartRadarA_BUFF.STATE = uartRadarA_BUFF.LENGTH = 0;
}   //void  uartRadarA_Clear_State( void )


//******************************************************************************
//
//******************************************************************************
UINT8   RadarA_DataGet( UINT8 *rx_data )
{

  if( (uartRadarA_BUFF.rx.tail==uartRadarA_BUFF.rx.front) && (!uartRadarA_BUFF.rx.buffull) ) {
    NOP( );
    return  FAILURE;
  }
  
  //======================================================================================
  //  Disable RDAINT
  SERCOM3_USART_RX_INT_DISABLE( );
  NOP( );
  
  *rx_data = uartRadarA_BUFF.rx.buffer[ uartRadarA_BUFF.rx.front ];
  uartRadarA_BUFF.rx.front = (uartRadarA_BUFF.rx.front + 1) & (SERCOM3_USART_RX_BUFFER_SIZE - 1);
  
  if( (uartRadarA_BUFF.rx.buffull) && (uartRadarA_BUFF.rx.tail!=uartRadarA_BUFF.rx.front) )    {
    uartRadarA_BUFF.rx.buffull = 0;
  }
  
  //  Enable RDAINT
  SERCOM3_USART_RX_INT_ENABLE( );

  return  SUCCESS;
}   //UINT8   void  RadarA_DataGet( UINT8* rx_data )


//******************************************************************************
//
//******************************************************************************
UINT8   RadarA_DataPut( UINT8 tx_data )
{
  NOP( );
  if( uartRadarA_BUFF.tx.buffull ) {
    SERCOM3_USART_TX_INT_ENABLE( );
    NOP( );
    while( uartRadarA_BUFF.tx.buffull ) {
      NOP( );
    }
  }

  //============================================================================
  SERCOM3_USART_TX_INT_ENABLE( );

  uartRadarA_BUFF.tx.buffer[ uartRadarA_BUFF.tx.tail ] = tx_data;
  uartRadarA_BUFF.tx.tail = (uartRadarA_BUFF.tx.tail + 1) & (SERCOM3_USART_TX_BUFFER_SIZE - 1);
  
  if( uartRadarA_BUFF.tx.tail == uartRadarA_BUFF.tx.front ) {
      uartRadarA_BUFF.tx.buffull = 1;
  }
  
  //  Enabae TXENDIF
  SERCOM3_USART_TX_INT_ENABLE( );
  
  return SUCCESS;
}   //UINT8   void  RadarA_DataPut( UINT8* tx_data )


//******************************************************************************
//
//******************************************************************************
UINT8   RadarA_StringPut( UINT8* w_buf, UINT16 length  )
{
  int i;

  for( i=0 ; i<length ; i++ )   {
    //WaitMS( 1 );
    if( RadarA_DataPut( w_buf[i] ) != SUCCESS )   {
      NOP( );
      return FAILURE;
    }
  }   //for( i=0 ; i<length ; i++ )   {

  return SUCCESS;
}     //UINT8   RadarA_StringPut( UINT8* w_buf, UINT16 length  )














//******************************************************************************
//
//******************************************************************************
void 		RadarA_Req_SWversion( void )
{
	UINT8			*txPtr = uartRadarA_TXbuf;
	UINT16 		txLength;

	UINT16 		ckSUM = 0;
	int  i;

	#if 	M0_RADAR_VER_30_210930
		*txPtr = 0x7A;						txPtr++;
		*txPtr = 0xA7;						txPtr++;

		*txPtr = 0x00;						txPtr++;
		*txPtr = 0x09;						txPtr++;

		*txPtr = 0x00;						txPtr++; 				//		CMD


		*txPtr = 0x00;						txPtr++;
		*txPtr = 0x09;						txPtr++;
		*txPtr = 0xD3;						txPtr++;
		*txPtr = 0x3D;						txPtr++;
	#else  		//#if 	M0_RADAR_VER_30_210930
		*txPtr = 0x7A;						txPtr++;
		*txPtr = 0xA7;						txPtr++;

		*txPtr = 0x00;						txPtr++;
		*txPtr = 0x00;						txPtr++;

		*txPtr = 0x00;						txPtr++; 				//		CMD


		*txPtr = 0x00;						txPtr++;
		*txPtr = 0x00;						txPtr++;
		*txPtr = 0xD3;						txPtr++;
		*txPtr = 0x3D;						txPtr++;
	#endif  	//#if 	M0_RADAR_VER_30_210930

	//----------------------------------------------------------------------------
	txLength = txPtr - uartRadarA_TXbuf;
	uartRadarA_TXbuf[2] = (txLength>>8) & 0x00FF;
	uartRadarA_TXbuf[3] = (txLength) & 0x00FF;

	ckSUM = 0;
	for( i=0 ; i<(txLength-6) ; i++)		{
		ckSUM += uartRadarA_TXbuf[i+2];
	}
	uartRadarA_TXbuf[txLength-4] = (ckSUM>>8) & 0x00FF;
	uartRadarA_TXbuf[txLength-3] = (ckSUM) & 0x00FF;

	RadarA_StringPut( uartRadarA_TXbuf, txLength );
	NOP( );
} 				//void 		RadarA_Req_SWversion( void )

















//******************************************************************************
//
//******************************************************************************
void 	UartDataRx_RadarA( void )
{
	UINT8 	uart_data;


	while( RadarA_DataGet( &uart_data ) )  {

		switch( uartRadarA_BUFF.STATE )  {
			//========================================================================
			//	header
			case 0:
				if(uart_data == 0x7A) 	{
					uartRadarA_BUFF.STATE++;
				}
				break;

			case 1:
				if(uart_data == 0xA7) 	{
					uartRadarA_BUFF.CRC16 = 0;
					uartRadarA_BUFF.PTR = 0;
					uartRadarA_BUFF.STATE++;
				}
				else 	{
					uartRadarA_Clear_State( );
				}
				break;

			//========================================================================
			//	length
			case 2:
				uartRadarA_BUFF.LENGTH = ((UINT16)uart_data<<8) & 0xFF00;

				uartRadarA_RXbuf[uartRadarA_BUFF.PTR] = uart_data;
				uartRadarA_BUFF.PTR++;
				uartRadarA_BUFF.CRC16 += uart_data;
				uartRadarA_BUFF.STATE++;
				break;

			case 3:
				uartRadarA_BUFF.LENGTH |= uart_data;

				uartRadarA_RXbuf[uartRadarA_BUFF.PTR] = uart_data;
				uartRadarA_BUFF.PTR++;
				uartRadarA_BUFF.CRC16 += uart_data;
				uartRadarA_BUFF.STATE++;
				break;

			//========================================================================
			//	CMD
			case 4:
				uartRadarA_BUFF.CMD = uart_data;

				uartRadarA_RXbuf[uartRadarA_BUFF.PTR] = uart_data;
				uartRadarA_BUFF.PTR++;
				uartRadarA_BUFF.CRC16 += uart_data;
				uartRadarA_BUFF.STATE++;
				break;

			//========================================================================
			//	Data 			loop 			--------------------------------------------------
			case 5:
				uartRadarA_RXbuf[uartRadarA_BUFF.PTR] = uart_data;
				uartRadarA_BUFF.PTR++;
				uartRadarA_BUFF.CRC16 += uart_data;

				if( uartRadarA_BUFF.PTR >= (uartRadarA_BUFF.LENGTH-6) )		{
					uartRadarA_BUFF.STATE++;
				}				
				break;

			//========================================================================
			//	CK SUM
			case 6:
				ckSUM_RadarA = ((UINT16)uart_data<<8) & 0xFF00;
				uartRadarA_BUFF.STATE++;
				break;

			case 7:
				ckSUM_RadarA |= uart_data;
				uartRadarA_BUFF.STATE++;
				break;

			//========================================================================
			//	End
			case 8:
				if( uart_data == 0xD3 ) 	{
					uartRadarA_BUFF.STATE++;
				}
				else 	{
					uartRadarA_Clear_State( );
				}
				break;

			case 9:
				if( uart_data == 0x3D ) 	{
					if( ckSUM_RadarA == uartRadarA_BUFF.CRC16 )	{
						NOP( );
						uartRadarA_BUFF.STATE++;
						return;
					} 		//if( ckSUM_RadarA == uartRadarA_BUFF )	{
					else  	{
						uartRadarA_Clear_State( );
					}
				} 		//if( uart_data == 0x3D ) 	{
				else {
					uartRadarA_Clear_State( );
				}
				break;


			//========================================================================
			//========================================================================
			default:
				uartRadarA_Clear_State( );
				break;
		} 		//switch( uartRadarA_BUFF.STATE )  {
	} 		//while( RadarA_DataGet( &uart_data ) )  {

	NOP( );
} 		//void 	UartDataRx_RadarA( void )










//******************************************************************************
//
//******************************************************************************
//		M0_AllDevStatus.radar_A
//		uartRadarA_RXbuf[0] uartRadarA_RXbuf[1] = uartRadarA_BUFF.LENGTH
//		uartRadarA_RXbuf[2] 	uartRadarA_BUFF.CMD
void 	UartDataRx_RadarA_CMD( void )
{
	//UINT8 	radar_Rsp_Buf[1024];


	if( uartRadarA_BUFF.STATE == 10 ) 	{

		switch( uartRadarA_BUFF.CMD )		{

			//	GET_SW_VERSION 		----------------------------------------------------
			case 0x10:
				M0_AllDevStatus.radar_A.FW_version[0] = uartRadarA_RXbuf[3];
				M0_AllDevStatus.radar_A.FW_version[1] = uartRadarA_RXbuf[4];
				M0_AllDevStatus.radar_A.FW_version[2] = uartRadarA_RXbuf[5];
				M0_AllDevStatus.radar_A.FW_version[3] = uartRadarA_RXbuf[6];
				NOP( );
				break;

			//	GET_RADAR_RESULT_AND_SETTING 	----------------------------------------
			case 0x12:
				NOP( );
				#if 	M0_RADAR_VER_30_210930
					M0_AllDevStatus.radar_A.data.Result 						= uartRadarA_RXbuf[3];
					M0_AllDevStatus.radar_A.data.Current_status 		= uartRadarA_RXbuf[4];
					M0_AllDevStatus.radar_A.data.Object_type 				= uartRadarA_RXbuf[5];
					M0_AllDevStatus.radar_A.data.Current_amount 		= uartRadarA_RXbuf[6];

					M0_AllDevStatus.radar_A.data.radar_X					= (uartRadarA_RXbuf[7]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.radar_X					|= uartRadarA_RXbuf[8] & 0x00FF;
					M0_AllDevStatus.radar_A.data.radar_Y					= (uartRadarA_RXbuf[9]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.radar_Y					|= uartRadarA_RXbuf[10] & 0x00FF;
					M0_AllDevStatus.radar_A.data.radar_L					= (uartRadarA_RXbuf[11]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.radar_L					|= uartRadarA_RXbuf[12] & 0x00FF;
					M0_AllDevStatus.radar_A.data.radar_W					= (uartRadarA_RXbuf[13]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.radar_W					|= uartRadarA_RXbuf[14] & 0x00FF;
					M0_AllDevStatus.radar_A.data.radar_H					= (uartRadarA_RXbuf[15]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.radar_H					|= uartRadarA_RXbuf[16] & 0x00FF;

					M0_AllDevStatus.radar_A.data.Z_m 							= uartRadarA_RXbuf[17];
					M0_AllDevStatus.radar_A.data.Z_p 							= uartRadarA_RXbuf[18];
					M0_AllDevStatus.radar_A.data.DoA_E_m 					= uartRadarA_RXbuf[19];
					M0_AllDevStatus.radar_A.data.DoA_E_p 					= uartRadarA_RXbuf[20];
					M0_AllDevStatus.radar_A.data.DoA_H_m 					= uartRadarA_RXbuf[21];
					M0_AllDevStatus.radar_A.data.DoA_H_p 					= uartRadarA_RXbuf[22];
					M0_AllDevStatus.radar_A.data.Theta 						= uartRadarA_RXbuf[23];
					M0_AllDevStatus.radar_A.data.Phi 							= uartRadarA_RXbuf[24];
					M0_AllDevStatus.radar_A.data.L_R 							= uartRadarA_RXbuf[25];
					M0_AllDevStatus.radar_A.data.Threshold_Boundary 	= uartRadarA_RXbuf[26];

					M0_AllDevStatus.radar_A.data.Threshold_A			= (uartRadarA_RXbuf[27]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.Threshold_A			|= uartRadarA_RXbuf[28] & 0x00FF;
					M0_AllDevStatus.radar_A.data.Threshold_B			= (uartRadarA_RXbuf[29]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.Threshold_B			|= uartRadarA_RXbuf[30] & 0x00FF;

					M0_AllDevStatus.radar_A.data.Peak_amount 			= uartRadarA_RXbuf[31];
					M0_AllDevStatus.radar_A.data.Compare_car 			= uartRadarA_RXbuf[32];
					M0_AllDevStatus.radar_A.data.Compare_emp 			= uartRadarA_RXbuf[33];

					M0_AllDevStatus.radar_A.data.Block_lim				= (uartRadarA_RXbuf[34]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.Block_lim				|= uartRadarA_RXbuf[35] & 0x00FF;
					M0_AllDevStatus.radar_A.data.Block_index			= (uartRadarA_RXbuf[41]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.Block_index			|= uartRadarA_RXbuf[42] & 0x00FF;

					M0_AllDevStatus.radar_A.data.Range_Object1		= (uartRadarA_RXbuf[44]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.Range_Object1		|= uartRadarA_RXbuf[45] & 0x00FF;
					M0_AllDevStatus.radar_A.data.x_Object1				= (uartRadarA_RXbuf[46]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.x_Object1				|= uartRadarA_RXbuf[47] & 0x00FF;
					M0_AllDevStatus.radar_A.data.y_Object1				= (uartRadarA_RXbuf[48]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.y_Object1				|= uartRadarA_RXbuf[49] & 0x00FF;
					M0_AllDevStatus.radar_A.data.z_Object1				= (uartRadarA_RXbuf[50]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.z_Object1				|= uartRadarA_RXbuf[51] & 0x00FF;
					M0_AllDevStatus.radar_A.data.Power_Object1		= (uartRadarA_RXbuf[52]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.Power_Object1		|= uartRadarA_RXbuf[53] & 0x00FF;

					M0_AllDevStatus.radar_A.data.Range_Object2		= (uartRadarA_RXbuf[54]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.Range_Object2		|= uartRadarA_RXbuf[55] & 0x00FF;
					M0_AllDevStatus.radar_A.data.x_Object2				= (uartRadarA_RXbuf[56]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.x_Object2				|= uartRadarA_RXbuf[57] & 0x00FF;
					M0_AllDevStatus.radar_A.data.y_Object2				= (uartRadarA_RXbuf[58]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.y_Object2				|= uartRadarA_RXbuf[59] & 0x00FF;
					M0_AllDevStatus.radar_A.data.z_Object2				= (uartRadarA_RXbuf[60]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.z_Object2				|= uartRadarA_RXbuf[61] & 0x00FF;
					M0_AllDevStatus.radar_A.data.Power_Object2		= (uartRadarA_RXbuf[62]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.Power_Object2		|= uartRadarA_RXbuf[63] & 0x00FF;

					M0_AllDevStatus.radar_A.data.Range_Object3		= (uartRadarA_RXbuf[64]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.Range_Object3		|= uartRadarA_RXbuf[65] & 0x00FF;
					M0_AllDevStatus.radar_A.data.x_Object3				= (uartRadarA_RXbuf[66]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.x_Object3				|= uartRadarA_RXbuf[67] & 0x00FF;
					M0_AllDevStatus.radar_A.data.y_Object3				= (uartRadarA_RXbuf[68]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.y_Object3				|= uartRadarA_RXbuf[69] & 0x00FF;
					M0_AllDevStatus.radar_A.data.z_Object3				= (uartRadarA_RXbuf[70]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.z_Object3				|= uartRadarA_RXbuf[71] & 0x00FF;
					M0_AllDevStatus.radar_A.data.Power_Object3		= (uartRadarA_RXbuf[72]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.Power_Object3		|= uartRadarA_RXbuf[73] & 0x00FF;

				#else  	//#if 	M0_RADAR_VER_30_210930
					M0_AllDevStatus.radar_A.data.car_change 			= uartRadarA_RXbuf[3];
					M0_AllDevStatus.radar_A.data.parking_status		= uartRadarA_RXbuf[4];
					M0_AllDevStatus.radar_A.data.CarChange_status	= uartRadarA_RXbuf[5];
					M0_AllDevStatus.radar_A.data.obj_type					= uartRadarA_RXbuf[6];
					M0_AllDevStatus.radar_A.data.obj_position_X		= uartRadarA_RXbuf[7];
					M0_AllDevStatus.radar_A.data.obj_position_Y		= uartRadarA_RXbuf[8];
					M0_AllDevStatus.radar_A.data.obj_position_Z		= uartRadarA_RXbuf[9];
					M0_AllDevStatus.radar_A.data.obj_distance_R		= uartRadarA_RXbuf[10];

					M0_AllDevStatus.radar_A.data.radar_X					= (uartRadarA_RXbuf[11]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.radar_X					|= uartRadarA_RXbuf[12] & 0x00FF;

					M0_AllDevStatus.radar_A.data.radar_Y					= (uartRadarA_RXbuf[13]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.radar_Y					|= uartRadarA_RXbuf[14] & 0x00FF;

					M0_AllDevStatus.radar_A.data.radar_L					= (uartRadarA_RXbuf[15]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.radar_L					|= uartRadarA_RXbuf[16] & 0x00FF;

					M0_AllDevStatus.radar_A.data.radar_W					= (uartRadarA_RXbuf[17]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.radar_W					|= uartRadarA_RXbuf[18] & 0x00FF;

					M0_AllDevStatus.radar_A.data.radar_H					= (uartRadarA_RXbuf[19]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.radar_H					|= uartRadarA_RXbuf[20] & 0x00FF;

					M0_AllDevStatus.radar_A.data.Theta						= uartRadarA_RXbuf[21];
					M0_AllDevStatus.radar_A.data.Phi							= uartRadarA_RXbuf[22];
					M0_AllDevStatus.radar_A.data.L_R							= uartRadarA_RXbuf[23];

					//	RB-60P(台灣版) UART Portocol_210526  	------------------------------
					M0_AllDevStatus.radar_A.data.Reserved_01[0]		= uartRadarA_RXbuf[24];
					M0_AllDevStatus.radar_A.data.Reserved_01[1]		= uartRadarA_RXbuf[25];
					M0_AllDevStatus.radar_A.data.Reserved_01[2]		= uartRadarA_RXbuf[26];
					M0_AllDevStatus.radar_A.data.Reserved_01[3]		= uartRadarA_RXbuf[27];

					//	"210625-020D10"  ---------------------------------------------------
					M0_AllDevStatus.radar_A.data.power						= (uartRadarA_RXbuf[28]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.power						|= uartRadarA_RXbuf[29] & 0x00FF;

					M0_AllDevStatus.radar_A.data.recordPos_X			= uartRadarA_RXbuf[30];
					M0_AllDevStatus.radar_A.data.recordPos_Y			= uartRadarA_RXbuf[31];
					M0_AllDevStatus.radar_A.data.recordPos_Z			= uartRadarA_RXbuf[32];
					M0_AllDevStatus.radar_A.data.record_Distance	= uartRadarA_RXbuf[33];

					M0_AllDevStatus.radar_A.data.record_power			= (uartRadarA_RXbuf[34]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.record_power			|= uartRadarA_RXbuf[35] & 0x00FF;

					M0_AllDevStatus.radar_A.data.motion_index1		= (uartRadarA_RXbuf[36]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.motion_index1		|= uartRadarA_RXbuf[37] & 0x00FF;

					M0_AllDevStatus.radar_A.data.motion_index2		= (uartRadarA_RXbuf[38]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.motion_index2		|= uartRadarA_RXbuf[39] & 0x00FF;

					M0_AllDevStatus.radar_A.data.block_index			= (uartRadarA_RXbuf[40]<<8) & 0xFF00;
					M0_AllDevStatus.radar_A.data.block_index			|= uartRadarA_RXbuf[41] & 0x00FF;
				#endif  	//#if 	M0_RADAR_VER_30_210930

				NOP( );
				SysRTC_Get( (M0_RTC_TIME_FRAME*)&(M0_AllDevStatus.radar_A.mcu_RTC) );
				//	TEST 	//UartDataTx_M0toM4_Data( uart_RSP_DUMMY_TEST, (UINT8*)(&M0_AllDevStatus.radar_A.data), sizeof(M0_RADAR_DATA_FRAME) );
				
				#if  Tst_PRE_SHOOT_ENABLE

					//	PreShooting		==========================================
					if( IsCapture( (M0_RADAR_FRAME*)&M0_AllDevStatus.radar_A ) != 0 )	{
						UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_RADAR_A, (uint8_t*)&(M0_AllDevStatus.radar_A), sizeof(M0_RADAR_FRAME) );
					}  	//if( IsCapture(M0_AllDevStatus.radar_A.data) != 0 )	{

					if( IsDelete( (M0_RADAR_FRAME*)&M0_AllDevStatus.radar_A ) != 0 )	{
						UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_RADAR_A, (uint8_t*)&(M0_AllDevStatus.radar_A), sizeof(M0_RADAR_FRAME) );
					}  	//if( IsDelete( (M0_RADAR_FRAME*)&M0_AllDevStatus.radar_A ) != 0 )	{
    				
					UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_RADAR_A, (uint8_t*)&(M0_AllDevStatus.radar_A), sizeof(M0_RADAR_FRAME) );
					
					NOP( );

				#else  	//Tst_PRE_SHOOT_ENABLE
					//	20211014-031270  ---------------------------------------
					//M0_AllDevStatus.radar_A.pre_Result = M0_AllDevStatus.radar_A.data.Result;
                        
					if( M0_AllDevStatus.radar_A.data.Result == 0 )		{
						M0_AllDevStatus.radar_A.pre_car = M0_AllDevStatus.radar_A.car;
						M0_AllDevStatus.radar_A.car = 0;
						RadarA_car01_cnt = 0;
					}

					if( (M0_AllDevStatus.radar_A.data.Result == 1) && (M0_AllDevStatus.radar_A.pre_Result == 1) )  	{
						RadarA_car01_cnt++;

						if( RadarA_car01_cnt > 60 )	{
							M0_AllDevStatus.radar_A.pre_car = M0_AllDevStatus.radar_A.car;
							M0_AllDevStatus.radar_A.car = 1;
							RadarA_car01_cnt = 99;
						}
					}

					#if 	Tst_Radar_Send_AllData
						if( flg_Radar_Info_noSkip )		{
							UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_RADAR_A, (uint8_t*)&(M0_AllDevStatus.radar_A), sizeof(M0_RADAR_FRAME) );
						}
						

					#else  	//#if 	Tst_Radar_Send_AllData
						if( flg_Radar_Info_noSkip )		{
							#if 	M0_RADAR_VER_30_210930
								if( M0_AllDevStatus.radar_A.car != M0_AllDevStatus.radar_A.pre_car )  	{
									UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_RADAR_A, (uint8_t*)&(M0_AllDevStatus.radar_A), sizeof(M0_RADAR_FRAME) );
								}

							#else  	//#if 	M0_RADAR_VER_30_210930
								if( M0_AllDevStatus.radar_A.data.pre_car_change == 0xFF )	{
									M0_AllDevStatus.radar_A.data.pre_car_change = M0_AllDevStatus.radar_A.data.car_change;
								}
								else 	{
									if( M0_AllDevStatus.radar_A.data.car_change != M0_AllDevStatus.radar_A.data.pre_car_change )		{
										UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_RADAR_A, (uint8_t*)&(M0_AllDevStatus.radar_A), sizeof(M0_RADAR_FRAME) );
										M0_AllDevStatus.radar_A.data.pre_car_change = M0_AllDevStatus.radar_A.data.car_change;
									}
								} 		//if( M0_AllDevStatus.radar_A.data.pre_car_change == 0xFF )	{
							#endif  	//#if 	M0_RADAR_VER_30_210930

						} 		//if( flg_Radar_Info_noSkip )		{
					#endif 		//Tst_Radar_Send_AllData

				#endif  	//Tst_PRE_SHOOT_ENABLE

				M0_AllDevStatus.radar_A.pre_Result = M0_AllDevStatus.radar_A.data.Result;
				M0_AllDevStatus.radar_A.pre_Object_type = M0_AllDevStatus.radar_A.data.Object_type;
				NOP( );
				break;
		} 		//switch( uartRadarA_BUFF.CMD )		{
		uartRadarA_Clear_State( );
	} 		//if( uartRadarA_BUFF.STATE == 10 ) 	{
} 		//void 	UartDataRx_RadarA_CMD( void )

