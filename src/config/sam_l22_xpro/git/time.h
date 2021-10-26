

#ifndef _TIME_H
#define _TIME_H


//******************************************************************************
//  Defined


//******************************************************************************


//******************************************************************************
//  Global
//extern  M0_RTC_TIME_FRAME    Sys_RTC;

extern 	TIMER *tm_tstRTC;


//******************************************************************************
//  Function
//******************************************************************************
void    NOP( void );

void    RTC_Initialize( void );
void    SysRTC_Get( M0_RTC_TIME_FRAME* rtc );
void    SysRTC_Set( M0_RTC_TIME_FRAME rtc );

void  WaitMS( UINT32 waitCnt );



// TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void 	TimerF_tst_RTC( void );


#endif // _TIME_H

