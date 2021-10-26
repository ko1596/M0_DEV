

//******************************************************************************
//  SERCOM4_uart.c
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

//	UART SERCOM4 C
//		PA14 	TXD 	SERCOM4-PAD[2]
//		PA15 	RXD 	SERCOM4-PAD[3]


#include "All_Header.h"




//******************************************************************************
//  Global
UART_INTERFACE    uartRadarB_BUFF;

UINT8 		uartRadarB_rx_Qbuf[SERCOM4_USART_RX_BUFFER_SIZE];
UINT8 		uartRadarB_tx_Qbuf[SERCOM4_USART_TX_BUFFER_SIZE];
UINT8 		uartRadarB_RXbuf[UARTRADARB_CMD_BUFFFER_SIZE];
UINT8 		uartRadarB_TXbuf[UARTRADARB_CMD_BUFFFER_SIZE];

UINT8*    uartRadarB_rx_buffer;
UINT8*    uartRadarB_tx_buffer;
UINT8*    uartRadarB_buffer;

UINT8 		uartRadarB_Set_param[ sizeof(M0_RADAR_SET_FRAME) ];
M0_RADAR_SET_FRAME  	RadarB_Set_Data;


UINT16 		ckSUM_RadarB;

static int  RadarB_car01_cnt;


//	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#if 	Tst_RADARB_01
	TIMER 	*tm_RadarB_Test;
	UINT8 	TstBuf_uartRadarB[1024];
#endif 	//#if 	Tst_RADARB_01






//==============================================================================
static void  uartRadarB_Clear_State( void );



//******************************************************************************
//
//******************************************************************************
//	UART SERCOM4 C
//		PA14 	TXD 	SERCOM4-PAD[2]
//		PA15 	RXD 	SERCOM4-PAD[3]
void SERCOM4_USART_Initialize( void )
{
	//		PA14 	TXD 	SERCOM4-PAD[2]
	//		PA15 	RXD 	SERCOM4-PAD[3]
	//	29. PORT - I/O Pin Controller 		p456/1092
	//		29.7 Register Summary 					p465/1092
  PORT_REGS->GROUP[0].PORT_PINCFG[14] = 0x1;    //  The peripheral multiplexer selection is enabled
  PORT_REGS->GROUP[0].PORT_PINCFG[15] = 0x1;    //  The peripheral multiplexer selection is enabled
  //  14/2=7; 15/2=7.5;
  PORT_REGS->GROUP[0].PORT_PMUX[7] = 0x22; 			//C Peripheral function C selected

  //	32. SERCOM USART – SERCOM Universal Synchronous and  		p514/1092
  //			32.7 Register Summary 															p531/1092
  SERCOM4_REGS->USART_INT.SERCOM_CTRLA = 
            SERCOM_USART_INT_CTRLA_MODE_USART_INT_CLK | 
            SERCOM_USART_INT_CTRLA_RXPO(0x3) | 
            SERCOM_USART_INT_CTRLA_TXPO(0x1) | 
            SERCOM_USART_INT_CTRLA_DORD_Msk | 
            SERCOM_USART_INT_CTRLA_IBON_Msk | 
            SERCOM_USART_INT_CTRLA_FORM(0x0) | 
            SERCOM_USART_INT_CTRLA_SAMPR(0) ;

  SERCOM4_REGS->USART_INT.SERCOM_BAUD = SERCOM_USART_INT_BAUD_BAUD(SERCOM4_USART_INT_BAUD_VALUE_115200);

  SERCOM4_REGS->USART_INT.SERCOM_CTRLB = SERCOM_USART_INT_CTRLB_CHSIZE_8_BIT | SERCOM_USART_INT_CTRLB_SBMODE_1_BIT | SERCOM_USART_INT_CTRLB_RXEN_Msk | SERCOM_USART_INT_CTRLB_TXEN_Msk;
  
  while(SERCOM4_REGS->USART_INT.SERCOM_SYNCBUSY);     // Wait for sync

  // Enable the UART after the configurations
  SERCOM4_REGS->USART_INT.SERCOM_CTRLA |= SERCOM_USART_INT_CTRLA_ENABLE_Msk;

  while(SERCOM4_REGS->USART_INT.SERCOM_SYNCBUSY);     // Wait for sync


  //----------------------------------------------------------------------------
  // Bit 7 – ERROR: Error Interrupt Enable
  //SERCOM4_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_ERROR_Msk;

  // Bit 2 – RXC: Receive Complete Interrupt Enable
  SERCOM4_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_RXC_Msk;
  // Bit 0 – DRE: Data Register Empty Interrupt Enable
  //SERCOM4_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_DRE_Msk;

  NOP( );

  // ***************************************************************************
  //  Device Commands buffer
  // ***************************************************************************
//	20211014-031270
	RadarB_car01_cnt = 0;
	memset( ((UINT8*)&M0_AllDevStatus.radar_B), 0x00, sizeof(M0_RADAR_FRAME) );

	//----------------------------------------------------------------------------
	uartRadarB_BUFF.rx.buffer = (UINT8*)uartRadarB_rx_Qbuf;
	uartRadarB_BUFF.tx.buffer = (UINT8*)uartRadarB_tx_Qbuf;
	uartRadarB_BUFF.TrData = (UINT8*)uartRadarB_RXbuf;

	uartRadarB_BUFF.rx.front = uartRadarB_BUFF.rx.tail = uartRadarB_BUFF.rx.buffull = 0;
	uartRadarB_Clear_State( ); 
	NOP( );
  
}     //void SERCOM4_USART_Initialize( void )












//******************************************************************************
//
//******************************************************************************
void  SERCOM4_Handler_RX( void )
{
  UINT8     uart_data;
  UART_FIFO *fifo = &(uartRadarB_BUFF.rx);


  uart_data = SERCOM4_REGS->USART_INT.SERCOM_DATA;
  
  //----------------------------------------------------------------------------------
  if( fifo->buffull ) {               
    NOP( );
    //  Disable RDAINT
    SERCOM4_USART_RX_INT_DISABLE( );
    NOP( );    
    return;
  }   //  if( fifo->buffull ) {
  
  //----------------------------------------------------------------------------------
  fifo->buffer[ fifo->tail ] = uart_data;
  fifo->tail = (fifo->tail + 1) & (SERCOM4_USART_RX_BUFFER_SIZE - 1);
  if( fifo->tail == fifo->front ) {
    fifo->buffull = 1;    //  buffer full
    NOP( );
  }   //  if( fifo->tail == fifo->front ) {
  NOP( );

}   //void  SERCOM4_Handler_RX( void )


//******************************************************************************
//
//******************************************************************************
void  SERCOM4_Handler_TX( void )
{
  UINT8     uart_data;
  UART_FIFO *fifo = &(uartRadarB_BUFF.tx);


  if( (fifo->tail == fifo->front) && (!fifo->buffull))  {
    SERCOM4_USART_TX_INT_DISABLE( );
    NOP( );
    return;
  }   //if( (fifo->tail == fifo->front) && (!fifo->buffull))  {

  else  {
    uart_data = fifo->buffer[ fifo->front ];
    SERCOM4_REGS->USART_INT.SERCOM_DATA = uart_data;

    fifo->front = (fifo->front + 1) & (SERCOM4_USART_TX_BUFFER_SIZE - 1);
    fifo->buffull = 0;

    if( fifo->tail != fifo->front ) {
      //  Enabae TXENDIF
      SERCOM4_USART_TX_INT_ENABLE( );
    }   //  if( fifo->tail != fifo->front ) {

  }    //if( (fifo->tail == fifo->front) && (!fifo->buffull))  {    else

}   //void  SERCOM4_Handler_TX( void )




//******************************************************************************
//
//******************************************************************************
void  SERCOM4_Handler( void )
{
  NOP( );
  if(SERCOM4_REGS->USART_INT.SERCOM_INTENSET != 0)    {
    NOP( );

    // Checks for data register empty flag
    if((SERCOM4_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_DRE_Msk) 
        && (SERCOM4_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_DRE_Msk))   {
      NOP( );
      SERCOM4_Handler_TX( );
      NOP( );
    }

    // Checks for receive complete empty flag
    if((SERCOM4_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_RXC_Msk) 
        && (SERCOM4_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_RXC_Msk))   {
      NOP( );
      SERCOM4_Handler_RX( );
      NOP( );
    }

    // Checks for receive complete empty flag
    if((SERCOM4_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_TXC_Msk) 
        && (SERCOM4_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_TXC_Msk))   {
      NOP( );
      NOP( );
    }    

    // Checks for error flag
    if((SERCOM4_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_ERROR_Msk) 
        && (SERCOM4_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_ERROR_Msk))   {
      NOP( );
      NOP( );
    }
  }   //if(SERCOM4_REGS->USART_INT.SERCOM_INTENSET != 0)    {

  NOP( );
}   //void SERCOM4_Handler( void )


















//******************************************************************************
//
//******************************************************************************
static void  uartRadarB_Clear_State( void )
{
  uartRadarB_BUFF.CMD = uartRadarB_BUFF.PTR = uartRadarB_BUFF.STATE = uartRadarB_BUFF.LENGTH = 0;
}   //void  uartRadarB_Clear_State( void )




//******************************************************************************
//
//******************************************************************************
UINT8   RadarB_DataGet( UINT8 *rx_data )
{

  if( (uartRadarB_BUFF.rx.tail==uartRadarB_BUFF.rx.front) && (!uartRadarB_BUFF.rx.buffull) ) {
    NOP( );
    return  FAILURE;
  }
  
  //======================================================================================
  //  Disable RDAINT
  SERCOM4_USART_RX_INT_DISABLE( );
  NOP( );
  
  *rx_data = uartRadarB_BUFF.rx.buffer[ uartRadarB_BUFF.rx.front ];
  uartRadarB_BUFF.rx.front = (uartRadarB_BUFF.rx.front + 1) & (SERCOM4_USART_RX_BUFFER_SIZE - 1);
  
  if( (uartRadarB_BUFF.rx.buffull) && (uartRadarB_BUFF.rx.tail!=uartRadarB_BUFF.rx.front) )    {
    uartRadarB_BUFF.rx.buffull = 0;
  }
  
  //  Enable RDAINT
  SERCOM4_USART_RX_INT_ENABLE( );

  return  SUCCESS;
}   //UINT8   void  RadarB_DataGet( UINT8* rx_data )


//******************************************************************************
//
//******************************************************************************
UINT8   RadarB_DataPut( UINT8 tx_data )
{
  NOP( );
  if( uartRadarB_BUFF.tx.buffull ) {
    SERCOM4_USART_TX_INT_ENABLE( );
    NOP( );
    while( uartRadarB_BUFF.tx.buffull ) {
      NOP( );
    }
  }

  //============================================================================
  SERCOM4_USART_TX_INT_ENABLE( );

  uartRadarB_BUFF.tx.buffer[ uartRadarB_BUFF.tx.tail ] = tx_data;
  uartRadarB_BUFF.tx.tail = (uartRadarB_BUFF.tx.tail + 1) & (SERCOM4_USART_TX_BUFFER_SIZE - 1);
  
  if( uartRadarB_BUFF.tx.tail == uartRadarB_BUFF.tx.front ) {
      uartRadarB_BUFF.tx.buffull = 1;
  }
  
  //  Enabae TXENDIF
  SERCOM4_USART_TX_INT_ENABLE( );
  
  return SUCCESS;
}   //UINT8   void  RadarB_DataPut( UINT8* tx_data )


//******************************************************************************
//
//******************************************************************************
UINT8   RadarB_StringPut( UINT8* w_buf, UINT16 length  )
{
  int i;

  for( i=0 ; i<length ; i++ )   {
    //WaitMS( 1 );
    if( RadarB_DataPut( w_buf[i] ) != SUCCESS )   {
      NOP( );
      return FAILURE;
    }
  }   //for( i=0 ; i<length ; i++ )   {

  return SUCCESS;
}     //UINT8   RadarB_StringPut( UINT8* w_buf, UINT16 length  )














//******************************************************************************
//
//******************************************************************************
void 		RadarB_Req_SWversion( void )
{
	UINT8			*txPtr = uartRadarB_TXbuf;
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
	txLength = txPtr - uartRadarB_TXbuf;
	uartRadarB_TXbuf[2] = (txLength>>8) & 0x00FF;
	uartRadarB_TXbuf[3] = (txLength) & 0x00FF;

	ckSUM = 0;
	for( i=0 ; i<(txLength-6) ; i++)		{
		ckSUM += uartRadarB_TXbuf[i+2];
	}
	uartRadarB_TXbuf[txLength-4] = (ckSUM>>8) & 0x00FF;
	uartRadarB_TXbuf[txLength-3] = (ckSUM) & 0x00FF;

	RadarB_StringPut( uartRadarB_TXbuf, txLength );
	NOP( );
} 				//void 		RadarB_Req_SWversion( void )


//******************************************************************************
//
//******************************************************************************


















//******************************************************************************
//
//******************************************************************************
void 	UartDataRx_RadarB( void )
{
	UINT8 	uart_data;


	while( RadarB_DataGet( &uart_data ) )  {

		switch( uartRadarB_BUFF.STATE )  {
			//========================================================================
			//	header
			case 0:
				if(uart_data == 0x7A) 	{
					uartRadarB_BUFF.STATE++;
				}
				break;

			case 1:
				if(uart_data == 0xA7) 	{
					uartRadarB_BUFF.CRC16 = 0;
					uartRadarB_BUFF.PTR = 0;
					uartRadarB_BUFF.STATE++;
				}
				else 	{
					uartRadarB_Clear_State( );
				}
				break;

			//========================================================================
			//	length
			case 2:
				uartRadarB_BUFF.LENGTH = ((UINT16)uart_data<<8) & 0xFF00;

				uartRadarB_RXbuf[uartRadarB_BUFF.PTR] = uart_data;
				uartRadarB_BUFF.PTR++;
				uartRadarB_BUFF.CRC16 += uart_data;
				uartRadarB_BUFF.STATE++;
				break;

			case 3:
				uartRadarB_BUFF.LENGTH |= uart_data;

				uartRadarB_RXbuf[uartRadarB_BUFF.PTR] = uart_data;
				uartRadarB_BUFF.PTR++;
				uartRadarB_BUFF.CRC16 += uart_data;
				uartRadarB_BUFF.STATE++;
				break;

			//========================================================================
			//	CMD
			case 4:
				uartRadarB_BUFF.CMD = uart_data;

				uartRadarB_RXbuf[uartRadarB_BUFF.PTR] = uart_data;
				uartRadarB_BUFF.PTR++;
				uartRadarB_BUFF.CRC16 += uart_data;
				uartRadarB_BUFF.STATE++;
				break;

			//========================================================================
			//	Data 			loop 			--------------------------------------------------
			case 5:
				uartRadarB_RXbuf[uartRadarB_BUFF.PTR] = uart_data;
				uartRadarB_BUFF.PTR++;
				uartRadarB_BUFF.CRC16 += uart_data;

				if( uartRadarB_BUFF.PTR >= (uartRadarB_BUFF.LENGTH-6) )		{
					uartRadarB_BUFF.STATE++;
				}				
				break;

			//========================================================================
			//	CK SUM
			case 6:
				ckSUM_RadarB = ((UINT16)uart_data<<8) & 0xFF00;
				uartRadarB_BUFF.STATE++;
				break;

			case 7:
				ckSUM_RadarB |= uart_data;
				uartRadarB_BUFF.STATE++;
				break;

			//========================================================================
			//	End
			case 8:
				if( uart_data == 0xD3 ) 	{
					uartRadarB_BUFF.STATE++;
				}
				else 	{
					uartRadarB_Clear_State( );
				}
				break;

			case 9:
				if( uart_data == 0x3D ) 	{
					if( ckSUM_RadarB == uartRadarB_BUFF.CRC16 )	{
						NOP( );
						uartRadarB_BUFF.STATE++;
						return;
					} 		//if( ckSUM_RadarB == uartRadarB_BUFF )	{
					else  	{
						uartRadarB_Clear_State( );
					}
				} 		//if( uart_data == 0x3D ) 	{
				else {
					uartRadarB_Clear_State( );
				}
				break;


			//========================================================================
			//========================================================================
			default:
				uartRadarB_Clear_State( );
				break;
		} 		//switch( uartRadarB_BUFF.STATE )  {
	} 		//while( RadarB_DataGet( &uart_data ) )  {

	NOP( );
} 		//void 	UartDataRx_RadarB( void )










//******************************************************************************
//
//******************************************************************************
//		M0_AllDevStatus.radar_B
//		uartRadarB_RXbuf[0] uartRadarB_RXbuf[1] = uartRadarB_BUFF.LENGTH
//		uartRadarB_RXbuf[2] 	uartRadarB_BUFF.CMD
void 	UartDataRx_RadarB_CMD( void )
{
	//UINT8 	radar_Rsp_Buf[1024];


	if( uartRadarB_BUFF.STATE == 10 ) 	{

		switch( uartRadarB_BUFF.CMD )		{

			//	GET_SW_VERSION 		----------------------------------------------------
			case 0x10:
				M0_AllDevStatus.radar_B.FW_version[0] = uartRadarB_RXbuf[3];
				M0_AllDevStatus.radar_B.FW_version[1] = uartRadarB_RXbuf[4];
				M0_AllDevStatus.radar_B.FW_version[2] = uartRadarB_RXbuf[5];
				M0_AllDevStatus.radar_B.FW_version[3] = uartRadarB_RXbuf[6];
				NOP( );
				break;

			//	GET_RADAR_RESULT_AND_SETTING 	----------------------------------------
			case 0x12:
				NOP( );
				#if 	M0_RADAR_VER_30_210930
					M0_AllDevStatus.radar_B.data.Result 						= uartRadarB_RXbuf[3];
					M0_AllDevStatus.radar_B.data.Current_status 		= uartRadarB_RXbuf[4];
					M0_AllDevStatus.radar_B.data.Object_type 				= uartRadarB_RXbuf[5];
					M0_AllDevStatus.radar_B.data.Current_amount 		= uartRadarB_RXbuf[6];

					M0_AllDevStatus.radar_B.data.radar_X					= (uartRadarB_RXbuf[7]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.radar_X					|= uartRadarB_RXbuf[8] & 0x00FF;
					M0_AllDevStatus.radar_B.data.radar_Y					= (uartRadarB_RXbuf[9]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.radar_Y					|= uartRadarB_RXbuf[10] & 0x00FF;
					M0_AllDevStatus.radar_B.data.radar_L					= (uartRadarB_RXbuf[11]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.radar_L					|= uartRadarB_RXbuf[12] & 0x00FF;
					M0_AllDevStatus.radar_B.data.radar_W					= (uartRadarB_RXbuf[13]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.radar_W					|= uartRadarB_RXbuf[14] & 0x00FF;
					M0_AllDevStatus.radar_B.data.radar_H					= (uartRadarB_RXbuf[15]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.radar_H					|= uartRadarB_RXbuf[16] & 0x00FF;

					M0_AllDevStatus.radar_B.data.Z_m 							= uartRadarB_RXbuf[17];
					M0_AllDevStatus.radar_B.data.Z_p 							= uartRadarB_RXbuf[18];
					M0_AllDevStatus.radar_B.data.DoA_E_m 					= uartRadarB_RXbuf[19];
					M0_AllDevStatus.radar_B.data.DoA_E_p 					= uartRadarB_RXbuf[20];
					M0_AllDevStatus.radar_B.data.DoA_H_m 					= uartRadarB_RXbuf[21];
					M0_AllDevStatus.radar_B.data.DoA_H_p 					= uartRadarB_RXbuf[22];
					M0_AllDevStatus.radar_B.data.Theta 						= uartRadarB_RXbuf[23];
					M0_AllDevStatus.radar_B.data.Phi 							= uartRadarB_RXbuf[24];
					M0_AllDevStatus.radar_B.data.L_R 							= uartRadarB_RXbuf[25];
					M0_AllDevStatus.radar_B.data.Threshold_Boundary 	= uartRadarB_RXbuf[26];

					M0_AllDevStatus.radar_B.data.Threshold_A			= (uartRadarB_RXbuf[27]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.Threshold_A			|= uartRadarB_RXbuf[28] & 0x00FF;
					M0_AllDevStatus.radar_B.data.Threshold_B			= (uartRadarB_RXbuf[29]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.Threshold_B			|= uartRadarB_RXbuf[30] & 0x00FF;

					M0_AllDevStatus.radar_B.data.Peak_amount 			= uartRadarB_RXbuf[31];
					M0_AllDevStatus.radar_B.data.Compare_car 			= uartRadarB_RXbuf[32];
					M0_AllDevStatus.radar_B.data.Compare_emp 			= uartRadarB_RXbuf[33];

					M0_AllDevStatus.radar_B.data.Block_lim				= (uartRadarB_RXbuf[34]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.Block_lim				|= uartRadarB_RXbuf[35] & 0x00FF;
					M0_AllDevStatus.radar_B.data.Block_index			= (uartRadarB_RXbuf[41]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.Block_index			|= uartRadarB_RXbuf[42] & 0x00FF;

					M0_AllDevStatus.radar_B.data.Range_Object1		= (uartRadarB_RXbuf[44]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.Range_Object1		|= uartRadarB_RXbuf[45] & 0x00FF;
					M0_AllDevStatus.radar_B.data.x_Object1				= (uartRadarB_RXbuf[46]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.x_Object1				|= uartRadarB_RXbuf[47] & 0x00FF;
					M0_AllDevStatus.radar_B.data.y_Object1				= (uartRadarB_RXbuf[48]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.y_Object1				|= uartRadarB_RXbuf[49] & 0x00FF;
					M0_AllDevStatus.radar_B.data.z_Object1				= (uartRadarB_RXbuf[50]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.z_Object1				|= uartRadarB_RXbuf[51] & 0x00FF;
					M0_AllDevStatus.radar_B.data.Power_Object1		= (uartRadarB_RXbuf[52]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.Power_Object1		|= uartRadarB_RXbuf[53] & 0x00FF;

					M0_AllDevStatus.radar_B.data.Range_Object2		= (uartRadarB_RXbuf[54]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.Range_Object2		|= uartRadarB_RXbuf[55] & 0x00FF;
					M0_AllDevStatus.radar_B.data.x_Object2				= (uartRadarB_RXbuf[56]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.x_Object2				|= uartRadarB_RXbuf[57] & 0x00FF;
					M0_AllDevStatus.radar_B.data.y_Object2				= (uartRadarB_RXbuf[58]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.y_Object2				|= uartRadarB_RXbuf[59] & 0x00FF;
					M0_AllDevStatus.radar_B.data.z_Object2				= (uartRadarB_RXbuf[60]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.z_Object2				|= uartRadarB_RXbuf[61] & 0x00FF;
					M0_AllDevStatus.radar_B.data.Power_Object2		= (uartRadarB_RXbuf[62]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.Power_Object2		|= uartRadarB_RXbuf[63] & 0x00FF;

					M0_AllDevStatus.radar_B.data.Range_Object3		= (uartRadarB_RXbuf[64]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.Range_Object3		|= uartRadarB_RXbuf[65] & 0x00FF;
					M0_AllDevStatus.radar_B.data.x_Object3				= (uartRadarB_RXbuf[66]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.x_Object3				|= uartRadarB_RXbuf[67] & 0x00FF;
					M0_AllDevStatus.radar_B.data.y_Object3				= (uartRadarB_RXbuf[68]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.y_Object3				|= uartRadarB_RXbuf[69] & 0x00FF;
					M0_AllDevStatus.radar_B.data.z_Object3				= (uartRadarB_RXbuf[70]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.z_Object3				|= uartRadarB_RXbuf[71] & 0x00FF;
					M0_AllDevStatus.radar_B.data.Power_Object3		= (uartRadarB_RXbuf[72]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.Power_Object3		|= uartRadarB_RXbuf[73] & 0x00FF;


				#else  	//#if 	M0_RADAR_VER_30_210930
					M0_AllDevStatus.radar_B.data.car_change 			= uartRadarB_RXbuf[3];
					M0_AllDevStatus.radar_B.data.parking_status		= uartRadarB_RXbuf[4];
					M0_AllDevStatus.radar_B.data.CarChange_status	= uartRadarB_RXbuf[5];
					M0_AllDevStatus.radar_B.data.obj_type					= uartRadarB_RXbuf[6];
					M0_AllDevStatus.radar_B.data.obj_position_X		= uartRadarB_RXbuf[7];
					M0_AllDevStatus.radar_B.data.obj_position_Y		= uartRadarB_RXbuf[8];
					M0_AllDevStatus.radar_B.data.obj_position_Z		= uartRadarB_RXbuf[9];
					M0_AllDevStatus.radar_B.data.obj_distance_R		= uartRadarB_RXbuf[10];

					M0_AllDevStatus.radar_B.data.radar_X					= (uartRadarB_RXbuf[11]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.radar_X					|= uartRadarB_RXbuf[12] & 0x00FF;

					M0_AllDevStatus.radar_B.data.radar_Y					= (uartRadarB_RXbuf[13]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.radar_Y					|= uartRadarB_RXbuf[14] & 0x00FF;

					M0_AllDevStatus.radar_B.data.radar_L					= (uartRadarB_RXbuf[15]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.radar_L					|= uartRadarB_RXbuf[16] & 0x00FF;

					M0_AllDevStatus.radar_B.data.radar_W					= (uartRadarB_RXbuf[17]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.radar_W					|= uartRadarB_RXbuf[18] & 0x00FF;

					M0_AllDevStatus.radar_B.data.radar_H					= (uartRadarB_RXbuf[19]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.radar_H					|= uartRadarB_RXbuf[20] & 0x00FF;

					M0_AllDevStatus.radar_B.data.Theta						= uartRadarB_RXbuf[21];
					M0_AllDevStatus.radar_B.data.Phi							= uartRadarB_RXbuf[22];
					M0_AllDevStatus.radar_B.data.L_R							= uartRadarB_RXbuf[23];

					//	RB-60P(台灣版) UART Portocol_210526  	------------------------------
					M0_AllDevStatus.radar_B.data.Reserved_01[0]		= uartRadarB_RXbuf[24];
					M0_AllDevStatus.radar_B.data.Reserved_01[1]		= uartRadarB_RXbuf[25];
					M0_AllDevStatus.radar_B.data.Reserved_01[2]		= uartRadarB_RXbuf[26];
					M0_AllDevStatus.radar_B.data.Reserved_01[3]		= uartRadarB_RXbuf[27];

					//	"210625-020D10"  ---------------------------------------------------
					M0_AllDevStatus.radar_B.data.power						= (uartRadarB_RXbuf[28]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.power						|= uartRadarB_RXbuf[29] & 0x00FF;

					M0_AllDevStatus.radar_B.data.recordPos_X			= uartRadarB_RXbuf[30];
					M0_AllDevStatus.radar_B.data.recordPos_Y			= uartRadarB_RXbuf[31];
					M0_AllDevStatus.radar_B.data.recordPos_Z			= uartRadarB_RXbuf[32];
					M0_AllDevStatus.radar_B.data.record_Distance	= uartRadarB_RXbuf[33];

					M0_AllDevStatus.radar_B.data.record_power			= (uartRadarB_RXbuf[34]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.record_power			|= uartRadarB_RXbuf[35] & 0x00FF;

					M0_AllDevStatus.radar_B.data.motion_index1		= (uartRadarB_RXbuf[36]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.motion_index1		|= uartRadarB_RXbuf[37] & 0x00FF;

					M0_AllDevStatus.radar_B.data.motion_index2		= (uartRadarB_RXbuf[38]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.motion_index2		|= uartRadarB_RXbuf[39] & 0x00FF;

					M0_AllDevStatus.radar_B.data.block_index			= (uartRadarB_RXbuf[40]<<8) & 0xFF00;
					M0_AllDevStatus.radar_B.data.block_index			|= uartRadarB_RXbuf[41] & 0x00FF;
				#endif  	//#if 	M0_RADAR_VER_30_210930
				
				NOP( );
				SysRTC_Get( (M0_RTC_TIME_FRAME*)&(M0_AllDevStatus.radar_B.mcu_RTC) );
				//	TEST 	//UartDataTx_M0toM4_Data( uart_RSP_DUMMY_TEST, (UINT8*)(&M0_AllDevStatus.radar_B.data), sizeof(M0_RADAR_DATA_FRAME) );

				#if  Tst_PRE_SHOOT_ENABLE
					//	PreShooting		==========================================
//					if( IsCapture( (M0_RADAR_FRAME*)&M0_AllDevStatus.radar_B ) != 0 )	{
//						UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_RADAR_B, (uint8_t*)&(M0_AllDevStatus.radar_B), sizeof(M0_RADAR_FRAME) );
//					}  	//if( IsCapture(M0_AllDevStatus.radar_B.data) != 0 )	{
//
//					if( IsDelete( (M0_RADAR_FRAME*)&M0_AllDevStatus.radar_B ) != 0 )	{
//						UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_RADAR_B, (uint8_t*)&(M0_AllDevStatus.radar_B), sizeof(M0_RADAR_FRAME) );
//					}  	//if( IsDelete( (M0_RADAR_FRAME*)&M0_AllDevStatus.radar_B ) != 0 )	{
//					
                UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_RADAR_B, (uint8_t*)&(M0_AllDevStatus.radar_B), sizeof(M0_RADAR_FRAME) );
						
				NOP( );
				#else  	//Tst_PRE_SHOOT_ENABLE
					//	20211014-031270  ---------------------------------------
					//M0_AllDevStatus.radar_B.pre_Result = M0_AllDevStatus.radar_B.data.Result;

					if( M0_AllDevStatus.radar_B.data.Result == 0 )		{
						M0_AllDevStatus.radar_B.pre_car = M0_AllDevStatus.radar_B.car;
						M0_AllDevStatus.radar_B.car = 0;
						RadarB_car01_cnt = 0;
					}

					if( (M0_AllDevStatus.radar_B.data.Result == 1) && (M0_AllDevStatus.radar_B.pre_Result == 1) )  	{
						RadarB_car01_cnt++;

						if( RadarB_car01_cnt > 60 )	{
							M0_AllDevStatus.radar_B.pre_car = M0_AllDevStatus.radar_B.car;
							M0_AllDevStatus.radar_B.car = 1;
							RadarB_car01_cnt = 99;
						}
					}

					#if 	Tst_Radar_Send_AllData
						if( flg_Radar_Info_noSkip )		{
							UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_RADAR_B, (uint8_t*)&(M0_AllDevStatus.radar_B), sizeof(M0_RADAR_FRAME) );
						}

					#else  	//#if 	Tst_Radar_Send_AllData
						if( flg_Radar_Info_noSkip )		{
							#if 	M0_RADAR_VER_30_210930
								if( M0_AllDevStatus.radar_B.car != M0_AllDevStatus.radar_B.pre_car )  	{
									UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_RADAR_B, (uint8_t*)&(M0_AllDevStatus.radar_B), sizeof(M0_RADAR_FRAME) );
								}

							#else  	//#if 	M0_RADAR_VER_30_210930
								if( M0_AllDevStatus.radar_B.data.pre_car_change == 0xFF )	{
									M0_AllDevStatus.radar_B.data.pre_car_change = M0_AllDevStatus.radar_B.data.car_change;
								}
								else 	{
									if( M0_AllDevStatus.radar_B.data.car_change != M0_AllDevStatus.radar_B.data.pre_car_change )		{
										UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_RADAR_B, (uint8_t*)&(M0_AllDevStatus.radar_B), sizeof(M0_RADAR_FRAME) );
										M0_AllDevStatus.radar_B.data.pre_car_change = M0_AllDevStatus.radar_B.data.car_change;
									}
								} 		//if( M0_AllDevStatus.radar_B.data.pre_car_change == 0xFF )	{

							#endif  	//#if 	M0_RADAR_VER_30_210930

						} 		//if( flg_Radar_Info_noSkip )		{
					#endif 		//Tst_Radar_Send_AllData

				#endif  	//Tst_PRE_SHOOT_ENABLE

				M0_AllDevStatus.radar_B.pre_Result = M0_AllDevStatus.radar_B.data.Result;
				M0_AllDevStatus.radar_B.pre_Object_type = M0_AllDevStatus.radar_B.data.Object_type;
				NOP( );
				break;
		} 		//switch( uartRadarB_BUFF.CMD )		{
		uartRadarB_Clear_State( );
	} 		//if( uartRadarB_BUFF.STATE == 10 ) 	{
} 		//void 	UartDataRx_RadarB_CMD( void )

