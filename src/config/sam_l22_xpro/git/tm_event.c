

//  ****************************************************************************
//  Time Event
//    20201012  D88
//  ****************************************************************************
//==============================================================================
//------------------------------------------------------------------------------
//..............................................................................
//______________________________________________________________________________


#include "All_Header.h"



//  ****************************************************************************
//  Global
TIMER   tm_Event[TM_EVENT_MAX_NO];
UINT32  tm_Event_index;

UINT8   timer_1ms_flag;
UINT8   In_Timer_Proc;


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#if   Tst_EVK_LED_TST1
  TIMER*  tm_evk_led;
  TIMER*  tm_Tst_SysInfo;

  uint8_t  flg_evk_led;
#endif  //#if   Tst_EVK_LED_TST1




//  ****************************************************************************
//
//  ****************************************************************************
void  tm_Event_Init( void )
{
  NOP( );
  timer_1ms_flag = 0;

  memset( (UINT8*)tm_Event, 0x00, sizeof(TIMER)*TM_EVENT_MAX_NO );
  NOP( );
}   //void  tm_Event_Init( void )




//  **************************************************************************************
//
//  **************************************************************************************
TIMER*  setup_timer(UINT32 count, UINT8 close_timer_flag, void (*fn)(), void *fn_param)
{
  int  i;
  for( i=0 ; i<TM_EVENT_MAX_NO ; i++ )    {
    if( tm_Event[i].Title == TIMER_FRAME_TITLE )  {
      NOP();
    }
    
    else {
      tm_Event[i].period_count = count;
      set_expire_time( &tm_Event[i] ); 

      tm_Event[i].Title = TIMER_FRAME_TITLE;
      tm_Event[i].close_timer_flag = close_timer_flag;
      tm_Event[i].fn = fn;
      tm_Event[i].fn_param = fn_param;
      tm_Event[i].timer_fn_busy = 0; 
      return &tm_Event[i];
    }

  }   //for( int i=0 ; i<TM_EVENT_MAX_NO ; i++ )    {
  return 0;
}   //TIMER*  setup_timer(UINT32 count, UINT8 close_timer_flag, void (*fn)(), void *fn_param)


//  **************************************************************************************
//
//  **************************************************************************************
void  close_timer(TIMER *tm)
{
  NOP( );
  if( tm )	{
  	NOP( );
  	memset( (UINT8*)tm, 0x00, sizeof(TIMER) );
  	tm = NULL;
  }
  
}   //void  close_timer(TIMER *tm)


//  **************************************************************************************
//
//  **************************************************************************************
UINT8 is_timer_expired(TIMER *target_tm)
{
  int i;


  if( timer_1ms_flag )  {
    Update_Timer_Chain();     
  }

  for( i=0 ; i<TM_EVENT_MAX_NO ; i++ )  {
    if( tm_Event[i].Title != 0x00 ) {

      if( &tm_Event[i] == target_tm ) {
        return( tm_Event[i].expired );
      }

    }   //if( tm_Event[i].Title != 0x00 ) {
  } //for( int i=0 ; i<TM_EVENT_MAX_NO ; i++ )  {

  return(true); 
}   //UINT8 is_timer_expired(TIMER *target_tm)


//  **************************************************************************************
//
//  **************************************************************************************
UINT8 reset_timer( TIMER *target_tm )
{

  if( target_tm->Title == TIMER_FRAME_TITLE )   {
    set_expire_time( target_tm );
    return true;
  }   //if( target_tm->Title == TIMER_FRAME_TITLE )   {

  return false;
}   //UINT8 reset_timer( TIMER *target_tm )


//  **************************************************************************************
//
//  **************************************************************************************
//  update newest tick
void  set_expire_time(TIMER *tm)
{
  UINT32 tick = systick.tickCounter;

    tm->expire_time = tick + tm->period_count;
    if( tm->expire_time == 0 )  {
      tm->expire_time = 1;
    }
    //tm->overflow = (tm->expire_time < tick) ? 1 : 0;
    tm->expired = 0;

    //  test
    if( tm->expire_time < 0x100 ) {
      NOP( );
      NOP( );
      NOP( );
      NOP( );
    }
}   //void  set_expire_time(TIMER *tm)


//  **************************************************************************************
//
//  **************************************************************************************
void  Update_Timer_Chain( void )
{
  int  i = tm_Event_index;
  int  flg_fn_exec = 0;


  timer_1ms_flag = 0;

  while( 1 )  {
    flg_fn_exec = 0;

    if( tm_Event[i].Title == TIMER_FRAME_TITLE )  {

      //==================================================================================
      //  CK Timer
      NOP( );
      if( systick.tickCounter >= tm_Event[i].expire_time )  {
        if( (systick.tickCounter - tm_Event[i].expire_time) < 0x70000000 ) {
          NOP( );
          flg_fn_exec = 1;
          NOP( );
        }   //if( (systick.tickCounter >= tm_Event[i].expire_time) < 0x70000000 ) {
      }   //if( systick.tickCounter >= tm_Event[i].expire_time )  {

      //==================================================================================
      //  Execute
      if( (flg_fn_exec>0) && (tm_Event[i].expired==0) )   {        

        //--------------------------------------------------------------------------------
        //  Execute Timer Function
        if( tm_Event[i].fn && !tm_Event[i].timer_fn_busy )  {
          tm_Event[i].expired = 1;

          tm_Event[i].timer_fn_busy = 1;
          In_Timer_Proc = 1;

          (*(tm_Event[i].fn))(tm_Event[i].fn_param);

          tm_Event[i].timer_fn_busy = 0;
          In_Timer_Proc = 0;
        }

        //============================================================================
        if( tm_Event[i].close_timer_flag )  {                   
            close_timer( &tm_Event[i] );
        }
      }   //if( (flg_fn_exec>0) && (tm_Event[i].expired==0) )   {

    }   //if( tm_Event[i].Title == TIMER_FRAME_TITLE )  {

    //==========================================================================
    //
    i++;
    if( i >= TM_EVENT_MAX_NO )  {
      i=0;
    }
    else if( i >= tm_Event_index ) {      
      tm_Event_index = i;
      break;
    }
  }   //while( 1 )  {

}   //void  Update_Timer_Chain(void)










//  ****************************************************************************
//
//  ****************************************************************************
#if   Tst_EVK_LED_TST1

//  ****************************************************************************
//
void  TimerF_LED_TEST(void)
{  
  
  NOP( );
  reset_timer( tm_evk_led );
  //============================================================================  
  SysRTC_Get( &(sysInfo.mcu_RTC) );
  NOP( );

  #if  Tst_LEDtstRTC
	  if( (sysInfo.mcu_RTC.Second%2) == 0 )	{
	  	LED_ON( );
	  }
	  else	{
	  	LED_OFF( );
	  }

  #else

	  if( (flg_evk_led%2) == 0 ) {
	    NOP( );
	    LED_ON( );
	  }
	  else {
	    NOP( );
	    LED_OFF( );
	  }

	#endif 	//#if  Tst_LEDtstRTC

  flg_evk_led++;
}   //void  TimerF_ADC_Request(void)


//  ****************************************************************************
//
//  20201019
void  TimerF_Sned_M0_Info(void)
{
	reset_timer( tm_Tst_SysInfo );
  //============================================================================
  NOP( );
  
  #if !Tst_RTC_DISABLE
  	SysRTC_Get( &(sysInfo.mcu_RTC) );
  #endif 	//#if !Tst_RTC_DISABLE

  UartDataTx_M0toM4_Data( uart_RSP_SYSTEM_INFO, (uint8_t*)&sysInfo, sizeof(M0_SYSTEM_INFO) );
  NOP( ) ;
}   //void  TimerF_Sned_M0_Info(void)


#endif  //#if   Tst_EVK_LED_TST1


