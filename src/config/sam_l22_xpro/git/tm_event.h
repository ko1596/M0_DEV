

#ifndef _TM_EVENT_H
#define _TM_EVENT_H


//******************************************************************************
//  Defined
typedef struct _timer_list_ {
  //struct  _timer_list_ *Next;
  UINT32  Title;
  UINT32  period_count;           // the time period in milliseconds
  UINT32  expire_time;            // expire time of tick_count, in 1 millisecond unit.
  UINT8   overflow;               // TRUE if the expire_time is after tick_count overflow.
  UINT8   expired;                // TRUE if the time expired.
  UINT8   close_timer_flag;       // TRUE to close timer entry after time expired
  UINT8   timer_fn_busy;          // TRUE if timer function 'fn' is running
  void    (*fn)(void *param);     // function called after time expired
  void    *fn_param;              // paramater passing to fn().
} TIMER;


//==============================================================================
#define   TIMER_FRAME_TITLE       0x434D8888
#define   TM_EVENT_MAX_NO         20



//******************************************************************************


//******************************************************************************
//  Global
extern  TIMER   tm_Event[];
extern  UINT32  tm_Event_index;

extern  UINT8   timer_1ms_flag;
extern  UINT8   In_Timer_Proc;


#if   Tst_EVK_LED_TST1
  extern  TIMER*  tm_evk_led;
  extern  TIMER*  tm_Tst_SysInfo;
#endif  //#if   Tst_EVK_LED_TST1




//******************************************************************************
//  Function
//******************************************************************************
void  tm_Event_Init( void );

TIMER*  setup_timer(UINT32 count, UINT8 close_timer_flag, void (*fn)(), void *fn_param);
void    close_timer(TIMER *tm);
void    set_expire_time(TIMER *tm);
UINT8   is_timer_expired(TIMER *target_tm);
UINT8   reset_timer( TIMER *target_tm );

void    Update_Timer_Chain(void);


#if   Tst_EVK_LED_TST1
  void  TimerF_LED_TEST(void);
  void  TimerF_Sned_M0_Info(void);
#endif  //#if   Tst_EVK_LED_TST1



#endif // _TM_EVENT_H

