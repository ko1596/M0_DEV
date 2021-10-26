

//  ****************************************************************************
//==============================================================================
//------------------------------------------------------------------------------
//..............................................................................
//______________________________________________________________________________


#include "All_Header.h"






//******************************************************************************
//  Global
//M0_RTC_TIME_FRAME    Sys_RTC;

TIMER *tm_tstRTC;




//  ****************************************************************************
//
//  ****************************************************************************
void    NOP( void )
{
  /*
  int i;
  int j;

  for( i=0 ; i<10 ; i++ ) {
    j=i;
    i=j;
  }
  */
  ;
}     //void    NOP( void )




//  ****************************************************************************
//
//  ****************************************************************************
//  344/1092  Register Summary - CLOCK
//  [ParkMeterSAML22   20200826-010A5]
void  RTC_Initialize( void )
{  
  int  rst_flg;


  NOP( );
  
  if( RTC_REGS->MODE2.RTC_CTRLA & 0x0002 )  {
    NOP( );
    rst_flg = 0;
  }
  else  {
    RTC_REGS->MODE2.RTC_CTRLA |= RTC_MODE2_CTRLA_SWRST_Msk;    
    rst_flg = 1;
  }
  while((RTC_REGS->MODE2.RTC_SYNCBUSY & RTC_MODE2_SYNCBUSY_SWRST_Msk) == RTC_MODE2_SYNCBUSY_SWRST_Msk)
  {
      // Wait for synchronization after Software Reset
  }
  
  //RTC_REGS->MODE2.RTC_CTRLA |= RTC_MODE2_CTRLA_SWRST_Msk;    
  //rst_flg = 1;

  /*
  //  Sample Code   ------------------------------------------------------------
  RTC_REGS->MODE2.RTC_CTRLA = RTC_MODE2_CTRLA_MODE(2) 
            | RTC_MODE2_CTRLA_PRESCALER(0xB) 
            | RTC_MODE2_CTRLA_CLOCKSYNC_Msk 
            | RTC_MODE2_CTRLA_ENABLE_Msk 
            | RTC_MODE2_CTRLA_BKTRST_Msk ;
            */
  //  Prj311_ALL  ----------------------------------------------------------           
  RTC_REGS->MODE2.RTC_CTRLA = RTC_MODE2_CTRLA_MODE(2) 
            | RTC_MODE2_CTRLA_PRESCALER(0x0B) 
            | RTC_MODE2_CTRLA_CLOCKSYNC_Msk 
            | RTC_MODE2_CTRLA_ENABLE_Msk 
            | RTC_MODE2_CTRLA_BKTRST_Msk ;
  while((RTC_REGS->MODE2.RTC_SYNCBUSY & RTC_MODE2_SYNCBUSY_ENABLE_Msk) == RTC_MODE2_SYNCBUSY_ENABLE_Msk)
  {
      // Wait for Synchronization after Enabling RTC
  }

  //==========================================================================
  if( rst_flg == 1 )  {
    NOP( );
    sysInfo.mcu_RTC.Year = 55;
    sysInfo.mcu_RTC.Month = 5;
    sysInfo.mcu_RTC.Day = 5;
    sysInfo.mcu_RTC.Hour = 5;
    sysInfo.mcu_RTC.Minute = 5;
    sysInfo.mcu_RTC.Second = 5;
    SysRTC_Set( sysInfo.mcu_RTC );
    NOP( );
    SysRTC_Get( &(sysInfo.mcu_RTC) );
    NOP( );
  }     //if( rst_flg == 1 )  {

  //==========================================================================
  //RTC_REGS->MODE2.RTC_INTENSET = 0x100;
}     //void  RTC_Initialize(void)




//  ****************************************************************************
//
//  ****************************************************************************
void  SysRTC_Get( M0_RTC_TIME_FRAME* rtc )
{
  uint32_t dataClockCalendar = 0;

  
  memset( ((UINT8*)rtc), 0x00, sizeof(M0_RTC_TIME_FRAME) );
  NOP( );
  while((RTC_REGS->MODE2.RTC_SYNCBUSY & RTC_MODE2_SYNCBUSY_CLOCKSYNC_Msk) == RTC_MODE2_SYNCBUSY_CLOCKSYNC_Msk)
  {
      // Synchronization before reading value from CLOCK Register
  }
  dataClockCalendar = RTC_REGS->MODE2.RTC_CLOCK;


  NOP( );
  rtc->Year = (dataClockCalendar & 0xFC000000) >> 26;
  rtc->Month = (dataClockCalendar & 0x03C00000) >> 22;
  rtc->Day = (dataClockCalendar & 0x003E0000) >> 17;

  rtc->Hour = (dataClockCalendar & 0x0001F000) >> 12;
  rtc->Minute = (dataClockCalendar & 0x00000FC0) >> 6;
  rtc->Second = dataClockCalendar & 0x0000003F;
  NOP( );
}     //void  SysRTC_Get( M0_RTC_TIME_FRAME* rtc )


//  ****************************************************************************
//
//  ****************************************************************************
void  SysRTC_Set( M0_RTC_TIME_FRAME rtc )
{
  uint32_t dataClockCalendar = 0;

 
  dataClockCalendar = ((UINT32)(rtc.Year) & 0x3F) << 26;
  NOP( );
  dataClockCalendar |= ((UINT32)(rtc.Month) & 0x0F) << 22;
  NOP( );
  dataClockCalendar |= ((UINT32)(rtc.Day) & 0x1F) << 17;
  NOP( );

  dataClockCalendar |= ((UINT32)(rtc.Hour) & 0x1F) << 12;
  NOP( );
  dataClockCalendar |= ((UINT32)(rtc.Minute) & 0x3F) << 6;
  NOP( );
  dataClockCalendar |= ((UINT32)(rtc.Second) & 0x3F);
  NOP( );

  NOP( );
  RTC_REGS->MODE2.RTC_CLOCK = dataClockCalendar;
  while((RTC_REGS->MODE2.RTC_SYNCBUSY & RTC_MODE2_SYNCBUSY_CLOCK_Msk) == RTC_MODE2_SYNCBUSY_CLOCK_Msk)
  {
    // Synchronization after writing value to CLOCK Register
  }
  NOP( );
}     //void  SysRTC_Set( M0_RTC_TIME_FRAME rtc )






//  ****************************************************************************
//
//  ****************************************************************************
void  WaitMS( UINT32 waitCnt )
{
  UINT32  tickCounter = systick.tickCounter;

  while( 1 )    {

    if( systick.tickCounter > tickCounter ) {
      if( (systick.tickCounter - tickCounter) >= waitCnt )    {
        break;
      }
    }
    else if( systick.tickCounter < tickCounter ) {
      if( (systick.tickCounter + (0xFFFFFFFF-tickCounter)) >= waitCnt ) {
        break;
      }
    }
    else  {
      NOP( );
    }
  }   //while( 1 )    {

}   //void  WaitMS( UINT32 waitCnt )












// TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void 	TimerF_tst_RTC( void )
{
  NOP( );
  reset_timer( tm_tstRTC );
  //============================================================================  

  NOP( );
  SysRTC_Get( &(sysInfo.mcu_RTC) );
  NOP( );
}


