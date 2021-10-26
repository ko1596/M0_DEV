

// *****************************************************************************
//  uart_M4.c
//    20200821
// *****************************************************************************
//==============================================================================
//------------------------------------------------------------------------------
//..............................................................................
//______________________________________________________________________________


#include "All_Header.h"




//******************************************************************************
//  Global


#if 	Tst_UART_A53M0_TxRx
	UINT32 		tst_a53m0_Rx_Cnt;

	TIMER*  	tm_Tst01;
#endif 		//#if 	Tst_UART_A53M0_TxRx



//******************************************************************************
//  PrjT109_RTC02
//******************************************************************************
//  [ CC  length16  cmd   crc16   txdata ]
//    length16 = cmd + crc16 + txdata length
//    crc16 ::  from DataPtr ==> DataLength
void   UartDataTx_M0toM4_Data_NoWakeupA53( UINT8 cmd, UINT8* DataPtr, UINT16 DataLength )
{
  UINT16  len = 0;
  UINT16  crc16 = 0;


	////Wakeup_A53( );


	if( DataLength == 0  )  {
		len = 1;
	}
	else  {
		len = DataLength + 1 + 2;   //  DataLength + cmd + crc16
	}

	if( DataLength > 0 )  {
		crc16 = Get_ModBus_CRC16( DataPtr, DataLength );
	}

	// ===========================================================================
	uartM4_DataPut( 0xCC );

	uartM4_DataPut( len );
	uartM4_DataPut( len>>8 );
	uartM4_DataPut( cmd );

	if( DataLength > 0 )  {
		uartM4_DataPut( crc16 );
		uartM4_DataPut( crc16>>8 );
		uartM4_StringPut( DataPtr, DataLength );
	}
	NOP( );
}     //void   UartDataTx_M0toM4_Data_NoWakeupA53( UINT8 cmd, UINT8* DataPtr, UINT16 DataLength )


//******************************************************************************
//  PrjT109_RTC02
//******************************************************************************
//  [ CC  length16  cmd   crc16   txdata ]
//    length16 = cmd + crc16 + txdata length
//    crc16 ::  from DataPtr ==> DataLength
void   UartDataTx_M0toM4_Data( UINT8 cmd, UINT8* DataPtr, UINT16 DataLength )
{
  UINT16  len = 0;
  UINT16  crc16 = 0;


	Wakeup_A53( );


	if( DataLength == 0  )  {
		len = 1;
	}
	else  {
		len = DataLength + 1 + 2;   //  DataLength + cmd + crc16
	}

	if( DataLength > 0 )  {
		crc16 = Get_ModBus_CRC16( DataPtr, DataLength );
	}

	// ===========================================================================
	uartM4_DataPut( 0xCC );

	uartM4_DataPut( len );
	uartM4_DataPut( len>>8 );
	uartM4_DataPut( cmd );

	if( DataLength > 0 )  {
		uartM4_DataPut( crc16 );
		uartM4_DataPut( crc16>>8 );
		uartM4_StringPut( DataPtr, DataLength );
	}
	NOP( );
}     //void   UartDataTx_M0toM4_Data( UINT8 cmd, UINT8* DataPtr, UINT16 DataLength )


//******************************************************************************
//
//******************************************************************************
//  [ CC  length16  cmd   crc16   txdata ]
//    length16 = cmd + crc16 + txdata length
//    crc16 ::  from DataPtr ==> DataLength
void   UartDataTx_M0toM4_DevData( UINT8 cmd, UINT8 dev_subType, UINT8* DataPtr, UINT16 DataLength )
{
	UINT8 	tmpBuf[1024];
  UINT16  len = 0;
  UINT16  crc16 = 0;   
  int 	i;


	Wakeup_A53( );


	if( DataLength == 0  )  {
		len = 1;
	}
	else  {
		len = DataLength + 1 + 2 + 1;   //  DataLength + cmd + crc16 + dev_subType
	}

	tmpBuf[0] = dev_subType;

	if( DataPtr != NULL )		{
		for( i=0 ; i<DataLength ; i++ )	{
			tmpBuf[ i+1 ] = *DataPtr;
			DataPtr++;
		}

		if( DataLength > 0 )  {
			crc16 = Get_ModBus_CRC16( tmpBuf, DataLength+1 );
		} 		//if( DataLength > 0 )  {
	} 		//if( DataPtr != NULL )		{
	
	else 	{
		crc16 = Get_ModBus_CRC16( tmpBuf, 1 );
	} 		//if( DataPtr != NULL )		{					else

	

	// ===========================================================================
	uartM4_DataPut( 0xCC );

	uartM4_DataPut( len );
	uartM4_DataPut( len>>8 );
	uartM4_DataPut( cmd );

	uartM4_DataPut( crc16 );
	uartM4_DataPut( crc16>>8 );

	if( DataPtr != NULL )		{
		uartM4_StringPut( tmpBuf, DataLength+1 );
	}
	else 	{
		uartM4_StringPut( tmpBuf, 1 );
	}
  NOP( );
}     //void   UartDataTx_M0toM4_DevData( UINT8 cmd, UINT8 dev_subType, UINT8* DataPtr, UINT16 DataLength )










// *****************************************************************************
//  PrjT109_RTC02
// *****************************************************************************
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
//  [ CC  length16  cmd   crc16   txdata ]
UINT8   UartDataRx_M4_M0( void )
{
  UINT8   uart_data;

  #if UART_CRC16_CHECK
    UINT16  crc16 = 0;
  #endif    //#if !UART_CRC16_NOCHECK


  while( uartM4_DataGet( &uart_data ) )  {
      NOP( );

    switch( uartM4_BUFF.STATE )  {
      //========================================================================
      case 0:
        if(uart_data == 0xCC) {
          uartM4_BUFF.PTR = 0;
          uartM4_BUFF.LENGTH = 0xFF;
          uartM4_BUFF.STATE = 1;
        }
        NOP( );
        break;


      //  length  --------------------------------------------------------------
      //  [ CC  length16  cmd   crc16   txdata ]
      case 1:
        uartM4_BUFF.LENGTH = uart_data;
        uartM4_BUFF.STATE = 2;
        NOP( );
        break;

      case 2:
        uartM4_BUFF.LENGTH |= uart_data<<8;
        if( (uartM4_BUFF.LENGTH==0) || (uartM4_BUFF.LENGTH>((UINT16)UARTM4_CMD_BUFFFER_SIZE+3)) )    {
          uartM4_Clear_State();
          NOP( );
          return FAILURE;
        } 
        uartM4_BUFF.STATE = 3;
        NOP( );
        break;

      //  CMD   ----------------------------------------------------------------
      case 3:
        uartM4_BUFF.CMD = uart_data;
        uartM4_BUFF.PTR = 1;
        uartM4_BUFF.STATE = 4;
        NOP( );
        if( uartM4_BUFF.LENGTH == 1 ) {
          NOP( );
          return SUCCESS;
        }
        else if( (uartM4_BUFF.LENGTH < 4) ) {
          uartM4_Clear_State();
          NOP( );
          return FAILURE;
        }
        break;


      //  crc16   --------------------------------------------------------------
      case 4:
        uartM4_BUFF.CRC16 = uart_data;
        uartM4_BUFF.PTR = 2;
        uartM4_BUFF.STATE = 5;
        break;

      case 5:
        uartM4_BUFF.CRC16 |= uart_data<<8;
        uartM4_BUFF.PTR = 3;
        uartM4_BUFF.STATE = 6;
        break;



      //========================================================================
      case 6:        
        if( uartM4_BUFF.PTR > uartM4_BUFF.LENGTH )  {
          uartM4_Clear_State( );
          return FAILURE;
        }

        else  {
          uartM4_BUFF.TrData[uartM4_BUFF.PTR-3] = uart_data;
          uartM4_BUFF.PTR++;

          if( uartM4_BUFF.PTR == uartM4_BUFF.LENGTH )  {
            NOP( );

            #if UART_CRC16_CHECK
              crc16 = Get_ModBus_CRC16( uartM4_BUFF.TrData, uartM4_BUFF.LENGTH - 3);
              NOP( );

              if( crc16 != uartM4_BUFF.CRC16 )  {
                NOP( );
                uartM4_Clear_State( );
                return FAILURE;
              }
            #endif  //#if UART_CRC16_CHECK

            NOP( );
            return SUCCESS;
          }     //if( uartM4_BUFF.PTR == uartM4_BUFF.LENGTH )  {          
        }
        NOP( );
        break;


      //========================================================================
      //========================================================================
      default:
        uartM4_Clear_State( );
        break;

    }     //switch( uartM4_BUFF.STATE )  {

  }   //while( uartM4_DataGet( &uart_data ) )  {

  NOP( );
  return FAILURE;
}   //UINT8   UartDataRx_M4_M0( void )




//  ****************************************************************************
//
//  ****************************************************************************
void  UartDataRx_M4_M0_Cmd( void )
{
	uint8_t 	*ptr;
	int 			i;


	//============================================================================
	//
	if( (uartM4_BUFF.PTR == uartM4_BUFF.LENGTH) && (uartM4_BUFF.LENGTH > 0) )  {
		NOP( );
		switch( uartM4_BUFF.CMD )    {
			//  UART TEST ============================================================
			case uart_REQ_DUMMY_TEST:
			  uart_DUMMY_TEST( );
			  break;

			case uart_REQ_UART_TEST01:      
			  NOP( );
			  //uart_TEST01( );
			  break;

			case uart_REQ_UART_TEST02:
			  NOP( );
			  break;

			//  Req. System Info - 0x01  =============================================
			case uart_REQ_SYSTEM_INFO:
			  NOP( );
			  uart_Rsp_System_Info( );
			  break;

			//  Set Devive   =========================================================
			case uart_SET_DEV:
			  NOP( );
			  uart_Set_Devices( );
			  break;

			//	Re-Start device 		==================================================
			case uart_REQ_DEV_RESTART:
				uart_ReStart_Devices( );
				break;

			//  Req. Devices Status  =================================================
			case uart_REQ_DEV_STATUS:
			  uart_Rsp_Devices_Status( );
			  break;

			//  Set RTC  - 0x60  =====================================================
			case uart_SET_RTC:
			  NOP( );
			  if(  uartM4_BUFF.LENGTH == 1 )	{
			  	uart_Req_RTC( );
			  }
			  else {
			  	uart_Set_RTC( );
			  }

			  #if   SERCOM0_ENABLE
			  	Chili2S_Set_RTC( );
			  #endif  	//#if   SERCOM0_ENABLE

			  break;



			//  EEPROM  Write / Read 		==============================================
			case uart_REQ_SAVE_EEPROM:
				uart_Write_EEP( );
				break;
			case uart_REQ_READ_EEPROM:
				uart_Read_EEP( );
				break;

			//  TL_SAM  - 0x68  ======================================================
			  case uart_REQ_ENC:
			  	NOP( );
			  	//	uartM4_BUFF.TrData[1] : reserve
			  	//	//	enc_file_name
			  	ptr = (uint8_t*)&uartM4_BUFF.TrData[1];
			  	for( i=0 ; i<64 ; i++ )	{
			  		TLSAM_Data.name[i] = *ptr;
			  		ptr++;
			  	}

			  	//	enc_dataLength
			  	TLSAM_Data.dataLength = (*ptr<<8) & 0xFF00;				ptr++;
			  	TLSAM_Data.dataLength |= *ptr & 0x00FF;						ptr++;

			  	//	enc_data
			  	memset( TLSAM_Data.data, 0x00, 1024 );
			  	TLSAM_Req_Encrypt( ptr, TLSAM_Data.dataLength );
			  	/*
			  	for( i=0 ; i<TLSAM_Data.dataLength ; i++ )	{
			  		TLSAM_Data.data[i] = *ptr;
			  		ptr++;
			  	}
			  	*/
			  	break;

			//========================================================================
			//========================================================================
			default:
			  NOP( );
			  //uartM4_Clear_State();
			  break;
		}   //switch( uartM4_BUFF.TrData[0] )    {

		NOP( );
		uartM4_Clear_State( );
	}     //if( uartM4_BUFF.PTR == uartM4_BUFF.LENGTH )  {

	else  if( uartM4_BUFF.PTR > uartM4_BUFF.LENGTH )  {
		NOP( );
		uartM4_Clear_State();
	}

}   //void  UartDataRx_M4_M0_Cmd( void )






//******************************************************************************
//
//******************************************************************************
void  uartM4_Clear_State( void )
{
  uartM4_BUFF.CMD = uartM4_BUFF.PTR = uartM4_BUFF.STATE = uartM4_BUFF.LENGTH = 0;
}   //void  uartM4_Clear_State( void )
















//******************************************************************************
//
//******************************************************************************
//	switch( uartM4_BUFF.TrData[0] )	{
void  uart_DUMMY_TEST( void )
{
  NOP( );
  //-------------------------------------------------------------------------+---
  UINT16  dataLength = uartM4_BUFF.LENGTH;


  switch( uartM4_BUFF.TrData[0] )	{
  	//	Tx Rx Dumming Test 		--------------------------------------------------
  	case 0:
			#if 	Tst_UART_A53M0_TxRx
				tst_a53m0_Rx_Cnt ++;
				uartM4_BUFF.TrData[0] = tst_a53m0_Rx_Cnt & 0x00FF;
				uartM4_BUFF.TrData[1] = (tst_a53m0_Rx_Cnt>>8) & 0x00FF;
				uartM4_BUFF.TrData[2] = (tst_a53m0_Rx_Cnt>>16) & 0x00FF;
				uartM4_BUFF.TrData[3] = (tst_a53m0_Rx_Cnt>>24) & 0x00FF;
			#endif 		//#if 	Tst_UART_A53M0_TxRx
				
			UartDataTx_M0toM4_Data( uartM4_BUFF.CMD+0x80, (UINT8*)(uartM4_BUFF.TrData), dataLength-3 );
  		break;


  	//	EERPROM Test - Write 		------------------------------------------------
  	case 1:
  		break;

  	//	EERPROM Test - Read 		------------------------------------------------
  	case 2:
  		break;

  } 		//switch( uartM4_BUFF.TrData[0] )	{


  //-----------------------------------------------------------------------------
  //	const unsigned char FW_PARKINGMETER_L22[32] = {"Prj311_ALL      210521-020Bd0"}; 		//	UART TxRx lost Test

 
  NOP( );
}   //void  uart_DUMMY_TEST( void )


void  uart_DUMMY_TEST_00( void )
{
  NOP( );

  //-------------------------------------------------------------------------+---
  UINT16  dataLength = uartM4_BUFF.LENGTH;
  //UartDataTx_M0toM4_Data( uartM4_BUFF.CMD+0x80, (UINT8*)&dataLength, 2 );

  //-----------------------------------------------------------------------------
  //UartDataTx_M0toM4_Data( uartM4_BUFF.CMD+0x80, (UINT8*)(uartM4_BUFF.TrData), dataLength-3 );

  //-----------------------------------------------------------------------------
  //	const unsigned char FW_PARKINGMETER_L22[32] = {"Prj311_ALL      210521-020Bd0"}; 		//	UART TxRx lost Test
	#if 	Tst_UART_A53M0_TxRx
		tst_a53m0_Rx_Cnt ++;
		uartM4_BUFF.TrData[0] = tst_a53m0_Rx_Cnt & 0x00FF;
		uartM4_BUFF.TrData[1] = (tst_a53m0_Rx_Cnt>>8) & 0x00FF;
		uartM4_BUFF.TrData[2] = (tst_a53m0_Rx_Cnt>>16) & 0x00FF;
		uartM4_BUFF.TrData[3] = (tst_a53m0_Rx_Cnt>>24) & 0x00FF;
	#endif 		//#if 	Tst_UART_A53M0_TxRx
		
	UartDataTx_M0toM4_Data( uartM4_BUFF.CMD+0x80, (UINT8*)(uartM4_BUFF.TrData), dataLength-3 );
 
  NOP( );
}   //void  uart_DUMMY_TEST( void )



//******************************************************************************
//
//******************************************************************************
//  Prj311_ALL
//void  uart_TEST01_01( void )
void  uart_TEST01( void )
{
  int  i;

	for( i=0 ; i<uartM4_BUFF.LENGTH-3 ; i++ ) {
	  //uartM4_BUFF.TrData[i] += 0x11;
	  uartM4_BUFF.TrData[i] ++;
	}
	NOP( );
	UartDataTx_M0toM4_Data( uartM4_BUFF.CMD+0x80, uartM4_BUFF.TrData, uartM4_BUFF.LENGTH - 3);

  NOP( );
}   //void  uart_TEST01( void )



//void  uart_TEST01( void )
void  uart_TEST01_00( void )
{
  int  i;
  
  for( i=0 ; i<uartM4_BUFF.LENGTH-3 ; i++ ) {
    //uartM4_BUFF.TrData[i] += 0x11;
    uartM4_BUFF.TrData[i] ++;
  }
  NOP( );
  UartDataTx_M0toM4_Data( uartM4_BUFF.CMD+0x80, uartM4_BUFF.TrData, uartM4_BUFF.LENGTH - 3);
  NOP( );
}   //void  uart_TEST01( void )


















//******************************************************************************
//
//******************************************************************************
//  M0_SYSTEM_INFO       sysInfo;
void  uart_Send_M0_System_Info( void )
{
	//UartDataTx_M0toM4_Data( uartM4_BUFF.CMD+0x80, (uint8_t*)&sysInfo, sizeof(M0_SYSTEM_INFO) );
	UartDataTx_M0toM4_Data( uart_RSP_SYSTEM_INFO, (uint8_t*)&sysInfo, sizeof(M0_SYSTEM_INFO) );
}


//******************************************************************************
//
//******************************************************************************
//  M0_SYSTEM_INFO       sysInfo;
void  uart_Rsp_System_Info( void )
{ 
	#if 	Tst_UART_A53M0_TxRx
		tst_a53m0_Rx_Cnt = 0;
	#endif 		//#if 	Tst_UART_A53M0_TxRx

  #if !Tst_RTC_DISABLE
  	SysRTC_Get( &(sysInfo.mcu_RTC) );
  #endif 	//#if !Tst_RTC_DISABLE

  //	--------------------------------------------------------------------------
  #if   SERCOM0_ENABLE
  	Chili2S_Req_Info( );
  #endif  	//#if   SERCOM0_ENABLE

  sysInfo.sysTick = systick.tickCounter;
  sysInfo.uartM0_RxCnt++;

  //UartDataTx_M0toM4_Data( uartM4_BUFF.CMD+0x80, (uint8_t*)&sysInfo, sizeof(M0_SYSTEM_INFO) );
  setup_timer( 250, 1, (void (*)())uart_Send_M0_System_Info, NULL );

  sysInfo.TstCnt++;
  NOP( );  
}     //void  uart_Rsp_System_Info( void )


// *****************************************************************************
//
// *****************************************************************************
void 	uart_Set_Devices( void )
{
	UINT8			*txPtr;
	UINT16 		txLength;

	UINT16 		ckSUM;
	int  i;


	switch( uartM4_BUFF.TrData[0] )	{
		//--------------------------------------------------------------------------
		case SUBTYPE_RADAR_A :
			NOP( );
			//	Setting RadarA
			txPtr = uartRadarA_TXbuf;
			ckSUM = 0;

			*txPtr = 0x7A;						txPtr++;
			*txPtr = 0xA7;						txPtr++;

			*txPtr = 0x00;						txPtr++;
			*txPtr = 0x00;						txPtr++;

			*txPtr = 0x02;						txPtr++; 				//		CMD

			//	Data  ................................................................
			*txPtr = 0x01;						txPtr++; 			//	Set

			*txPtr = uartM4_BUFF.TrData[1];						txPtr++; 		//	X
			*txPtr = uartM4_BUFF.TrData[2];						txPtr++;
			*txPtr = uartM4_BUFF.TrData[3];						txPtr++; 		//	Y
			*txPtr = uartM4_BUFF.TrData[4];						txPtr++;
			*txPtr = uartM4_BUFF.TrData[5];						txPtr++; 		//	L
			*txPtr = uartM4_BUFF.TrData[6];						txPtr++;
			*txPtr = uartM4_BUFF.TrData[7];						txPtr++; 		//	W
			*txPtr = uartM4_BUFF.TrData[8];						txPtr++;
			*txPtr = uartM4_BUFF.TrData[9];						txPtr++; 		//	H
			*txPtr = uartM4_BUFF.TrData[10];					txPtr++;

			*txPtr = uartM4_BUFF.TrData[11];					txPtr++; 		//	Tgeta
			*txPtr = uartM4_BUFF.TrData[12];					txPtr++; 		//	Phi
			*txPtr = uartM4_BUFF.TrData[13];					txPtr++; 		//	L_R
			*txPtr = uartM4_BUFF.TrData[14];					txPtr++; 		//	UT

			//	End 	----------------------------------------------------------------
			*txPtr = 0x00;						txPtr++;
			*txPtr = 0x00;						txPtr++;
			*txPtr = 0xD3;						txPtr++;
			*txPtr = 0x3D;						txPtr++;
			//........................................................................
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
			break;

		//--------------------------------------------------------------------------
		case SUBTYPE_RADAR_B :
			NOP( );
			//	Setting RadarB
			txPtr = uartRadarB_TXbuf;
			ckSUM = 0;

			*txPtr = 0x7A;						txPtr++;
			*txPtr = 0xA7;						txPtr++;

			*txPtr = 0x00;						txPtr++;
			*txPtr = 0x00;						txPtr++;

			*txPtr = 0x02;						txPtr++; 				//		CMD

			//	Data  ................................................................
			*txPtr = 0x01;						txPtr++; 			//	Set

			*txPtr = uartM4_BUFF.TrData[1];						txPtr++; 		//	X
			*txPtr = uartM4_BUFF.TrData[2];						txPtr++;
			*txPtr = uartM4_BUFF.TrData[3];						txPtr++; 		//	Y
			*txPtr = uartM4_BUFF.TrData[4];						txPtr++;
			*txPtr = uartM4_BUFF.TrData[5];						txPtr++; 		//	L
			*txPtr = uartM4_BUFF.TrData[6];						txPtr++;
			*txPtr = uartM4_BUFF.TrData[7];						txPtr++; 		//	W
			*txPtr = uartM4_BUFF.TrData[8];						txPtr++;
			*txPtr = uartM4_BUFF.TrData[9];						txPtr++; 		//	H
			*txPtr = uartM4_BUFF.TrData[10];					txPtr++;

			*txPtr = uartM4_BUFF.TrData[11];					txPtr++; 		//	Tgeta
			*txPtr = uartM4_BUFF.TrData[12];					txPtr++; 		//	Phi
			*txPtr = uartM4_BUFF.TrData[13];					txPtr++; 		//	L_R
			*txPtr = uartM4_BUFF.TrData[14];					txPtr++; 		//	UT

			//	End 	----------------------------------------------------------------
			*txPtr = 0x00;						txPtr++;
			*txPtr = 0x00;						txPtr++;
			*txPtr = 0xD3;						txPtr++;
			*txPtr = 0x3D;						txPtr++;
			//........................................................................
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
			break;


		//--------------------------------------------------------------------------
		//	select Bat_A / Bat_B
		case SUBTYPE_PW_BAT :
			//	uartM4_BUFF.TrData[1], Reserve
			if( uartM4_BUFF.TrData[2] == 0 )		{
				BAT_PW_CTL_A( );
			}
			else if( uartM4_BUFF.TrData[2] == 1 )		{
				BAT_PW_CTL_B( );
			}
			break;


		//--------------------------------------------------------------------------
		//	select Bat_A / Bat_B
		case SUBTYPE_LIDAR :
			NOP( );
			switch( uartM4_BUFF.TrData[1] )  	{
				case 0xFD:
					NOP( );
					Chili2S_Set_PAN_ADD( (uartM4_BUFF.TrData[2]+(uartM4_BUFF.TrData[3]<<8)), 
								(uartM4_BUFF.TrData[4]+(uartM4_BUFF.TrData[5]<<8)),
								uartM4_BUFF.TrData[6] );
					break;
			}  	//switch( uartM4_BUFF.TrData[1] )  	{
			break;

		//--------------------------------------------------------------------------
		//--------------------------------------------------------------------------
		default:
			NOP( );
			NOP( );
			break;
	} 		//switch( uartM4_BUFF.TrData[0] )	{

} 		//void 	uart_Set_Devices( void )



//******************************************************************************
//
//******************************************************************************
void 	uart_ReStart_Devices( void )
{
	int  	i;
	int  	index;

	UINT8*  ptr;


	//	Re-Start Radar A+B 	======================================================
	if( (uartM4_BUFF.TrData[0] == SUBTYPE_RADAR_A) || (uartM4_BUFF.TrData[0] == SUBTYPE_RADAR_B) )	{
		NOP( );
		PW_RADAR_OFF( );
		flg_Radar_Info_noSkip = 0;		
		Radar_ReStart_state = 1;

		#if 	M0_RADAR_VER_30_210930
			M0_AllDevStatus.radar_A.pre_Result = 0xFF;
			M0_AllDevStatus.radar_A.pre_Object_type = 0xFF;
			M0_AllDevStatus.radar_B.pre_Result = 0xFF;
			M0_AllDevStatus.radar_B.pre_Object_type = 0xFF;
		#else  	//#if 	M0_RADAR_VER_30_210930
			M0_AllDevStatus.radar_A.data.pre_parking_status = 0xFF;
			M0_AllDevStatus.radar_A.data.pre_car_change = 0xFF;
			M0_AllDevStatus.radar_B.data.pre_parking_status = 0xFF;
			M0_AllDevStatus.radar_B.data.pre_car_change = 0xFF;
		#endif  	//#if 	M0_RADAR_VER_30_210930
		NOP( );
		tm_Radar_ReStart_state = setup_timer( 1000, 0, (void (*)())TimerF_Radar_ReStart, NULL );
		NOP( );

		//==========================================================================
		index = 1;
		ptr = (UINT8*)&RadarA_Set_Data;
		for( i=0 ; i<sizeof(M0_RADAR_SET_FRAME) ; i++ )		{
			uartRadarA_Set_param[i] = uartM4_BUFF.TrData[index];
			*ptr = uartM4_BUFF.TrData[index];
			ptr++;
			index++;
		} 		//for( i=0 ; i<sizeof() ; i++ )		{
		NOP( );
		NOP( );

		ptr = (UINT8*)&RadarB_Set_Data;
		for( i=0 ; i<sizeof(M0_RADAR_SET_FRAME) ; i++ )		{
			uartRadarB_Set_param[i] = uartM4_BUFF.TrData[index];
			*ptr = uartM4_BUFF.TrData[index];
			ptr++;
			index++;
		} 		//for( i=0 ; i<sizeof() ; i++ )		{
		NOP( );
		NOP( );

		/*
		for( i=0 ; i<sizeof(M0_RADAR_SET_FRAME) ; i++ )		{
			uartRadarA_Set_param[i] = uartM4_BUFF.TrData[i+1];
		} 		//for( i=0 ; i<sizeof() ; i++ )		{
		for( i=0 ; i<sizeof(M0_RADAR_SET_FRAME) ; i++ )		{
			uartRadarB_Set_param[i] = uartM4_BUFF.TrData[i+1+ sizeof(M0_RADAR_SET_FRAME) ];
		} 		//for( i=0 ; i<sizeof() ; i++ )		{
		*/
    NOP( );
	} 		//if( (uartM4_BUFF.TrData[0] == SUBTYPE_RADAR_A) || (uartM4_BUFF.TrData[0] == SUBTYPE_RADAR_B) )	{

} 		//void 	uart_ReStart_Devices( void )


//******************************************************************************
//
//******************************************************************************
//  M0_ALLDEV_STATUS_FRAME   M0_AllDevStatus;
void  uart_Rsp_Devices_Status( void )
{

  switch( uartM4_BUFF.TrData[0] )	{
  	//--------------------------------------------------------------------------
  	case SUBTYPE_ADC:
  		NOP( );  
		  SysRTC_Get( (M0_RTC_TIME_FRAME*)&(M0_AllDevStatus.adc_pw.mcu_RTC) );
		  NOP( );
		  UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_ADC, (uint8_t*)&(M0_AllDevStatus.adc_pw), sizeof(M0_POWER_DATA_FRAME) );
  		break;

  	//--------------------------------------------------------------------------
  	case SUBTYPE_RADAR_A:
  	case SUBTYPE_RADAR_B:
  		UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_RADAR_A, (uint8_t*)&(M0_AllDevStatus.radar_A), sizeof(M0_RADAR_FRAME) );
  		UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_RADAR_B, (uint8_t*)&(M0_AllDevStatus.radar_B), sizeof(M0_RADAR_FRAME) );
  		break;

  	//--------------------------------------------------------------------------
  	case SUBTYPE_TEMPERATURE:
  		SysRTC_Get( (M0_RTC_TIME_FRAME*)&(M0_AllDevStatus.temperature.mcu_RTC) );
  		UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_TEMPERATURE, (uint8_t*)&(M0_AllDevStatus.temperature), sizeof(M0_TEMP_DATA_FRAME) );
  		break;

  	//--------------------------------------------------------------------------
  	case SUBTYPE_PW_METER0:
  		UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_PW_METER0, (uint8_t*)&(M0_AllDevStatus.adc_pw.pw_meter), sizeof(M0_PW_METER_DATA_FRAME) );
  		break;

  	//--------------------------------------------------------------------------
  	case SUBTYPE_G_SENSOR:
  		UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_G_SENSOR, (uint8_t*)&(M0_AllDevStatus.g_sensor), sizeof(M0_G_SENSOR_FRAME) );
  		break;

  }		//switch( uartM4_BUFF.TrData[0] )	{

	/*
	//	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  UartDataTx_M0toM4_Data( uart_RSP_DEV_STATUS, (uint8_t*)&M0_AllDevStatus, sizeof(M0_ALLDEV_STATUS_FRAME) );  

  M0_AllDevStatus.TstCnt++;
  */
}   //void  uart_Rsp_Devices_Status( void )


// *****************************************************************************
//
// *****************************************************************************
void  uart_Set_RTC( void )
{
	NOP( );	  
  sysInfo.mcu_RTC.Year = uartM4_BUFF.TrData[0];
  sysInfo.mcu_RTC.Month = uartM4_BUFF.TrData[1];
  sysInfo.mcu_RTC.Day = uartM4_BUFF.TrData[2];
  sysInfo.mcu_RTC.Hour = uartM4_BUFF.TrData[3];
  sysInfo.mcu_RTC.Minute = uartM4_BUFF.TrData[4];
  sysInfo.mcu_RTC.Second = uartM4_BUFF.TrData[5];
  SysRTC_Set( sysInfo.mcu_RTC );
  NOP( );
  SysRTC_Get( &(sysInfo.mcu_RTC) );
  NOP( );
}   //void  uart_Set_RTC( void )


// *****************************************************************************
//
// *****************************************************************************
void  uart_Req_RTC( void )
{
	SysRTC_Get( &(sysInfo.mcu_RTC) );
	UartDataTx_M0toM4_Data( uart_RSP_RTC, (UINT8*)&(sysInfo.mcu_RTC), sizeof(M0_RTC_TIME_FRAME) );

} 		//void  uart_Req_RTC( void )






// *****************************************************************************
//
// *****************************************************************************
void 	uart_Write_EEP( void )
{
	eepData_writeAddr = uartM4_BUFF.TrData[0];
	eepData_writeAddr |= (uartM4_BUFF.TrData[1]<<8) & 0xFF00;

	eepData_writeLength = uartM4_BUFF.TrData[2];
	eepData_writeLength |= (uartM4_BUFF.TrData[3]<<8) & 0xFF00;

	NOP( );
	NOP( );
	eepData_writeBuf = (UINT8*)&uartM4_BUFF.TrData[4];
	eepData_writeByte = 0;
	eep24aa64_i2c_Write( );
	NOP( );
} 		//void 	uart_Write_EEP( void );



// *****************************************************************************
//
// *****************************************************************************
void 	uart_Read_EEP( void )
{
	UINT16  	Addr;
	UINT16  	length;


	Addr = uartM4_BUFF.TrData[0];
	Addr |= (uartM4_BUFF.TrData[1]<<8) & 0xFF00;

	length = uartM4_BUFF.TrData[2];
	length |= (uartM4_BUFF.TrData[3]<<8) & 0xFF00;

	eep24aa64_i2c_Read( Addr, i2c_RxBuf+4, length );

	i2c_RxBuf[0] = uartM4_BUFF.TrData[0];
	i2c_RxBuf[1] = uartM4_BUFF.TrData[1];
	i2c_RxBuf[2] = uartM4_BUFF.TrData[2];
	i2c_RxBuf[3] = uartM4_BUFF.TrData[3];

	UartDataTx_M0toM4_Data( uart_RSP_READ_EEPROM, i2c_RxBuf, length+4 );

} 		//void 	uart_Read_EEP( void )






#if 	Tst_UART_A53M0_TxRx
//******************************************************************************
//
void 	TimerF_Tst_A53M0_TxRx01( void )
{
	reset_timer( tm_Tst01 );

	//============================================================================
	UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_RADAR_A, (uint8_t*)&(M0_AllDevStatus.radar_A), sizeof(M0_RADAR_FRAME) );
	UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_RADAR_B, (uint8_t*)&(M0_AllDevStatus.radar_B), sizeof(M0_RADAR_FRAME) );
} 		//void 	TimerF_Tst_A53M0_TxRx01( void )

#endif 		//#if 	Tst_UART_A53M0_TxRx

