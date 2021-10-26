

// *****************************************************************************
//  comm.c
//    20200824
// *****************************************************************************
//==============================================================================
//------------------------------------------------------------------------------
//..............................................................................
//______________________________________________________________________________


#include "All_Header.h"




//  ****************************************************************************
//  Global

//	Radar 		==================================================================
int 		flg_Radar_Info_noSkip;
int 		Radar_ReStart_state;
TIMER*	tm_Radar_ReStart_state;


int 	radar_X;
int 	radar_Y;
int 	radar_L;
int 	radar_W;
int 	radar_H;


//  ****************************************************************************
//  CRC16_CCITT_KERMIT
//  ZigBee use this
//  ****************************************************************************
UINT16  Get_Kermit_CRC16( UINT8* dataPtr, UINT32 length )
{
  UINT8   i;  
  UINT16  crc16 = 0x0000;
  

  while( length ) {
    crc16 ^= *dataPtr;
    

    for(i=0 ; i<8 ; i++)  {
      if(crc16 & 0x01)  { /* LSB(b0)=1 */
        //crc16 = (crc16>>1) ^ 0xA001;  //  CRC-16 (Modbus)
        crc16 = (crc16>>1) ^ 0x8408;  //  CRC-CCITT (Kermit)
      }
      else  {
        crc16 = crc16 >>1;
      }
    } //  for(i=0 ; i<8 ; i++)  {
    dataPtr++;
    length--;
  } //while( length )
  NOP( );

  return  crc16;
}    //UINT16  Get_Kermit_CRC16( UINT8* dataPtr, UINT32 length )


//  ****************************************************************************
//  CRC16 Modbus
//  ****************************************************************************
UINT16  Get_ModBus_CRC16( UINT8* dataPtr, UINT32 length )
{
  UINT8 i;
  UINT16  crc16 = 0xFFFF;   //  CRC-16 (Modbus)

  while( length ) {
    crc16 ^= *dataPtr;
    for(i=0 ; i<8 ; i++)  {
      if(crc16 & 0x01)  { /* LSB(b0)=1 */
        crc16 = (crc16>>1) ^ 0xA001;  //  CRC-16 (Modbus)
      }
      else  {
        crc16 = crc16 >>1;
      }
    } //  for(i=0 ; i<8 ; i++)  {
    dataPtr++;
    length--;
  } //while( length )

  return  crc16;
}     //UINT16  Get_ModBus_CRC16( UINT8* dataPtr, UINT32 length )
















//  ****************************************************************************
//
//  ****************************************************************************
void 	TimerF_Radar_ReStart_M0_PWon( void )
{
	RadarA_Req_SWversion( );
	RadarB_Req_SWversion( );
} 		//void 	TimerF_Radar_ReStart_M0_PWon( void )


//  ****************************************************************************
//
//  ****************************************************************************
void 	TimerF_Radar_ReStart( void )
{
	UINT8* 		txPtr;
	UINT16 		txLength;
	UINT16 		ckSUM;
	int  i;

	M0_RADAR_SET_FRAME *radarSet_ptr;


  reset_timer( tm_Radar_ReStart_state );

  //============================================================================    
  NOP( );
  switch(  Radar_ReStart_state )		{
  	case 0: 
			close_timer( tm_Radar_ReStart_state );
			Radar_ReStart_state = 0;
  		break;

  	case 1: 
  		PW_RADAR_ON( );
  		Radar_ReStart_state++;
  		break;

  	case 2:
  	case 3:
  		Radar_ReStart_state++;
  		break;

  	case 4:
			RadarA_Req_SWversion( );
			RadarB_Req_SWversion( );
			Radar_ReStart_state++;
  		break;

  	case 5:
  		//	Set Radar A/B 	param.
			NOP( );
			//	Setting RadarA  	----------------------------------------------------
			//if( uartRadarA_Set_param[12] != 0xFF )	{
				txPtr = uartRadarA_TXbuf;
				ckSUM = 0;

				*txPtr = 0x7A;						txPtr++;
				*txPtr = 0xA7;						txPtr++;

				*txPtr = 0x00;						txPtr++;
				*txPtr = 0x00;						txPtr++;

				*txPtr = 0x02;						txPtr++; 				//		CMD

				//	Data  ................................................................
				*txPtr = 0x01;						txPtr++; 			//	Set

				radarSet_ptr = (M0_RADAR_SET_FRAME*)&RadarA_Set_Data;

				radar_X = radarSet_ptr->radar_X;
				radar_Y = radarSet_ptr->radar_Y;
				radar_L = radarSet_ptr->radar_L;
				radar_W = radarSet_ptr->radar_W;
				radar_H = radarSet_ptr->radar_H;
				NOP( );
				NOP( );

				*txPtr = (RadarA_Set_Data.radar_X >> 8);						txPtr++;
				*txPtr = (RadarA_Set_Data.radar_X );								txPtr++;
				*txPtr = (RadarA_Set_Data.radar_Y >> 8);						txPtr++;
				*txPtr = (RadarA_Set_Data.radar_Y );								txPtr++;
				*txPtr = (RadarA_Set_Data.radar_L >> 8);						txPtr++;
				*txPtr = (RadarA_Set_Data.radar_L );								txPtr++;
				*txPtr = (RadarA_Set_Data.radar_W >> 8);						txPtr++;
				*txPtr = (RadarA_Set_Data.radar_W );								txPtr++;
				*txPtr = (RadarA_Set_Data.radar_H >> 8);						txPtr++;
				*txPtr = (RadarA_Set_Data.radar_H );								txPtr++;

				*txPtr = (RadarA_Set_Data.Z_m );										txPtr++;
				*txPtr = (RadarA_Set_Data.Z_p );										txPtr++;
				*txPtr = (RadarA_Set_Data.DoA_E_m );								txPtr++;
				*txPtr = (RadarA_Set_Data.DoA_E_p );								txPtr++;
				*txPtr = (RadarA_Set_Data.DoA_H_m );								txPtr++;
				*txPtr = (RadarA_Set_Data.DoA_H_p );								txPtr++;
				*txPtr = (RadarA_Set_Data.Theta );									txPtr++;
				*txPtr = (RadarA_Set_Data.Phi );										txPtr++;
				*txPtr = (RadarA_Set_Data.L_R );										txPtr++;
				*txPtr = (RadarA_Set_Data.Threshold_Boundary );			txPtr++;

				*txPtr = (RadarA_Set_Data.Threshold_A >> 8);				txPtr++;
				*txPtr = (RadarA_Set_Data.Threshold_A );						txPtr++;
				*txPtr = (RadarA_Set_Data.Threshold_B >> 8);				txPtr++;
				*txPtr = (RadarA_Set_Data.Threshold_B );						txPtr++;

				*txPtr = (RadarA_Set_Data.Peak_amount );						txPtr++;
				*txPtr = (RadarA_Set_Data.Compare_car );						txPtr++;
				*txPtr = (RadarA_Set_Data.Compare_emp );						txPtr++;

				*txPtr = (RadarA_Set_Data.Block_lim >> 8);					txPtr++;
				*txPtr = (RadarA_Set_Data.Block_lim );							txPtr++;

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

				//	TEST 	//UartDataTx_M0toM4_Data( uart_RSP_DUMMY_TEST, (UINT8*)uartRadarA_TXbuf, txLength );
				NOP( );
			//} 		//if( uartRadarA_Set_param[12] != 0xFF )	{
			//else 	{
			//	NOP( );
			//}


			NOP( );
			//	Setting RadarB 		----------------------------------------------------
			//if( uartRadarB_Set_param[12] != 0xFF )	{
				txPtr = uartRadarB_TXbuf;
				ckSUM = 0;

				*txPtr = 0x7A;						txPtr++;
				*txPtr = 0xA7;						txPtr++;

				*txPtr = 0x00;						txPtr++;
				*txPtr = 0x00;						txPtr++;

				*txPtr = 0x02;						txPtr++; 				//		CMD

				//	Data  ................................................................
				*txPtr = 0x01;						txPtr++; 			//	Set

				radarSet_ptr = (M0_RADAR_SET_FRAME*)&RadarB_Set_Data;
				*txPtr = (radarSet_ptr->radar_X >> 8);						txPtr++;
				*txPtr = (radarSet_ptr->radar_X );								txPtr++;
				*txPtr = (radarSet_ptr->radar_Y >> 8);						txPtr++;
				*txPtr = (radarSet_ptr->radar_Y );								txPtr++;
				*txPtr = (radarSet_ptr->radar_L >> 8);						txPtr++;
				*txPtr = (radarSet_ptr->radar_L );								txPtr++;
				*txPtr = (radarSet_ptr->radar_W >> 8);						txPtr++;
				*txPtr = (radarSet_ptr->radar_W );								txPtr++;
				*txPtr = (radarSet_ptr->radar_H >> 8);						txPtr++;
				*txPtr = (radarSet_ptr->radar_H );								txPtr++;

				*txPtr = (radarSet_ptr->Z_m );										txPtr++;
				*txPtr = (radarSet_ptr->Z_p );										txPtr++;
				*txPtr = (radarSet_ptr->DoA_E_m );								txPtr++;
				*txPtr = (radarSet_ptr->DoA_E_p );								txPtr++;
				*txPtr = (radarSet_ptr->DoA_H_m );								txPtr++;
				*txPtr = (radarSet_ptr->DoA_H_p );								txPtr++;
				*txPtr = (radarSet_ptr->Theta );									txPtr++;
				*txPtr = (radarSet_ptr->Phi );										txPtr++;
				*txPtr = (radarSet_ptr->L_R );										txPtr++;
				*txPtr = (radarSet_ptr->Threshold_Boundary );			txPtr++;

				*txPtr = (radarSet_ptr->Threshold_A >> 8);				txPtr++;
				*txPtr = (radarSet_ptr->Threshold_A );						txPtr++;
				*txPtr = (radarSet_ptr->Threshold_B >> 8);				txPtr++;
				*txPtr = (radarSet_ptr->Threshold_B );						txPtr++;

				*txPtr = (radarSet_ptr->Peak_amount );						txPtr++;
				*txPtr = (radarSet_ptr->Compare_car );						txPtr++;
				*txPtr = (radarSet_ptr->Compare_emp );						txPtr++;

				*txPtr = (radarSet_ptr->Block_lim >> 8);					txPtr++;
				*txPtr = (radarSet_ptr->Block_lim );							txPtr++;

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
			//} 		//if( uartRadarB_Set_param[12] != 0xFF )	{
			//else 	{
			//	NOP( );
			//}

  		Radar_ReStart_state++;
  		break;

  	//==========================================================================
  	default:
  		if( Radar_ReStart_state <= RADAR_INFO_SKIP_TM ) 	{
  			NOP( );
  			flg_Radar_Info_noSkip = 1;
  			Radar_ReStart_state++;
  		}
  		else 	{
  			close_timer( tm_Radar_ReStart_state );
  			Radar_ReStart_state = 0;
  		}
  		break;
  } 		//switch(  Radar_ReStart_state )		{

} 		//void 	TimerF_Radar_ReStart( void )

