

//******************************************************************************
//  gpio.c
//    20200811
//******************************************************************************
//==============================================================================
//------------------------------------------------------------------------------
//..............................................................................
//______________________________________________________________________________


#include "All_Header.h"




//******************************************************************************
//	Global

//	WDT 		--------------------------------------------------------------------
TIMER*	tm_WDT;
UINT8 	WDT_cnt;

//	M0 wakeup A53 		----------------------------------------------------------
TIMER*	tm_wakeupA53_puls;
UINT8 	wakeupA53_puls_cnt;

UINT8 	wakeupA53_flg;  	// =1, A53 sleep;
													// =0, A53 awake

UINT8  	A53sleep_status;




//	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#if 	Tst_PW_BAT01
		TIMER*	Tst_tm_Bat_change;
		int 		Tst_Bat_changeCnt;
#endif 		//#if 	Tst_PW_BAT01

#if 	Tst_A53_SLEEP_STATE
		TIMER*	Tst_tm_CK_M0_A53_SLEEP_STATUS;
		int  		Tst_A53Sleep;
#endif 		//#if 	Tst_PW_BAT01

#if  	Tst_A53_WAKEUP
		TIMER*  tm_tst_ck_A53sleep;
		UINT8  	tst_wakeupA53_flg;
		UINT8  	tst_mgc;
#endif  	//#if  	Tst_A53_WAKEUP

#if  	Tst_A53_WAKEUP
		UINT8  	Tst_wakeup_flg;
#endif  	//#if  	Tst_A53_WAKEUP



//******************************************************************************
//
//******************************************************************************
// 	27. EIC – External Interrupt Controller 		p420/1092
// 		27.7 Register Summary 										p427/1092
//	7. I/O Multiplexing and Considerations 			p31/1092
//			Table 7-1. PORT Function Multiplexing 	p31/1092
void 	M0_EIC_Initialize( void )
{
  //#define EIC_REGS                         ((eic_registers_t*)0x40002800)                //  \brief EIC Registers Address        */

  // Reset all registers in the EIC module to their initial state and EIC will be disabled.  
  //  EIC reset   --------------------------------------------------------------
  EIC_REGS->EIC_CTRLA |= EIC_CTRLA_SWRST_Msk;
  while((EIC_REGS->EIC_SYNCBUSY & EIC_SYNCBUSY_SWRST_Msk) == EIC_SYNCBUSY_SWRST_Msk)    {
      //  Wait for sync
  }

  /* EIC is clocked by ultra low power clock */
  EIC_REGS->EIC_CTRLA |= EIC_CTRLA_CKSEL_Msk;

  /* NMI Control register */


  //============================================================================
  //	void EIC_Handler( void )
  //============================================================================
  //	P 435/1092,		27.8.10 Configuration n
  //	PC08-EIC/EXTINT[0], MGC3130-TS
	//	PB04-EIC/EXTINT[4], Button - Test Mode
	//	PB05-EIC/EXTINT[5], Button - Burn/ QC Mode  
	//  PC01-EIC/EXTINT[9], SW0
  //  Interrupt sense type and filter control for EXTINT channels 0 to 7
  EIC_REGS->EIC_CONFIG[0] =  	EIC_CONFIG_SENSE0_FALL	| 		//	PC08-EIC/EXTINT[0], MGC3130-TS
															EIC_CONFIG_SENSE1_FALL	| 		//	PC09 EIC/EXTINT[1], ICM20602-INT
															EIC_CONFIG_SENSE2_NONE	|
															EIC_CONFIG_SENSE3_NONE	|
															EIC_CONFIG_SENSE4_FALL	| 		//	PB04-EIC/EXTINT[4], Button - Test Mode
															EIC_CONFIG_SENSE5_FALL	|			//	PB05-EIC/EXTINT[5], Button - Burn/ QC Mode
															EIC_CONFIG_SENSE6_NONE	|
															EIC_CONFIG_SENSE7_NONE;

  //  Interrupt sense type and filter control for EXTINT channels 8 to 15
  EIC_REGS->EIC_CONFIG[1] =  	EIC_CONFIG_SENSE0_NONE	|  
  														#if Tst_EVK_LED_TST1
																EIC_CONFIG_SENSE1_FALL	|			//  PC01-EIC/EXTINT[9], SW0
															#else
																EIC_CONFIG_SENSE1_NONE	|
															#endif 	//#if Tst_EVK_LED_TST1
															EIC_CONFIG_SENSE2_NONE	|
															EIC_CONFIG_SENSE3_NONE	|
															EIC_CONFIG_SENSE4_NONE	|
															EIC_CONFIG_SENSE5_NONE	|
															EIC_CONFIG_SENSE6_NONE	|
															EIC_CONFIG_SENSE7_FALL ; 		//	PA27	EIC/EXTINT[15], Chili2S Wake M0


	//============================================================================
	//  External Interrupt Asynchronous Mode enable 	----------------------------
	//  External Interrupt enable
	
		//	10 0011 0000		0x230, +PC01
	#if Tst_EVK_LED_TST1
		//EIC_REGS->EIC_ASYNCH = 0x0231;
		EIC_REGS->EIC_ASYNCH = 0x0233; 			//	0010 0011 0011
		EIC_REGS->EIC_INTENSET = 0x0233;
	#else
		//	EXTINT[0], MGC3130-TS
		//	EXTINT[1], ICM20602-INT
		//	EXTINT[4], Button - Test Mode
		//	EXTINT[5], Button - Burn/ QC Mode
		//	EXTINT[15], Chili2S Wake M0
		//	0000 0000 0000 0000
		//	1000 0000 0011 0011 = 0x8033
		EIC_REGS->EIC_ASYNCH 		= 0x8033;
		EIC_REGS->EIC_INTENSET 	= 0x8033;
	#endif 	//#if Tst_EVK_LED_TST1





  //============================================================================
  //  Enable the EIC  ----------------------------------------------------------
  EIC_REGS->EIC_CTRLA |= EIC_CTRLA_ENABLE_Msk;
  while((EIC_REGS->EIC_SYNCBUSY & EIC_SYNCBUSY_ENABLE_Msk) == EIC_SYNCBUSY_ENABLE_Msk)  {
      //  Wait for sync
  }
  NOP( );
} 	//void 	M0_EIC_Initialize( void )




//******************************************************************************
//
//******************************************************************************
void 	M0_GPIO_Initialize( void )
{
	//============================================================================
	PORT_REGS->GROUP[LED_R_PORT_GROUP].PORT_DIR |= LED_R_PORT_DIR; 		// LED_R
	PORT_REGS->GROUP[LED_R_PORT_GROUP].PORT_OUT |= LED_R_PORT_OUT; 		// LED_R
	LED_R_L( );

	PORT_REGS->GROUP[LED_G_PORT_GROUP].PORT_DIR |= LED_G_PORT_DIR; 		// LED_G
	PORT_REGS->GROUP[LED_G_PORT_GROUP].PORT_OUT |= LED_G_PORT_OUT; 		// LED_G
	LED_G_L( );

	PORT_REGS->GROUP[LED_B_PORT_GROUP].PORT_DIR |= LED_B_PORT_DIR; 		// LED_B
	PORT_REGS->GROUP[LED_B_PORT_GROUP].PORT_OUT |= LED_B_PORT_OUT; 		// LED_B
	LED_B_L( );

	PORT_REGS->GROUP[LED_Y_PORT_GROUP].PORT_DIR |= LED_Y_PORT_DIR; 		// LED_Y  
  PORT_REGS->GROUP[LED_Y_PORT_GROUP].PORT_OUT |= LED_Y_PORT_OUT; 		// LED_Y
  LED_Y_L( );

  
  //	WDT 		==================================================================
	PORT_REGS->GROUP[SYS_WDT_PORT_GROUP].PORT_DIR |= SYS_WDT_PORT_DIR;
	PORT_REGS->GROUP[SYS_WDT_PORT_GROUP].PORT_OUT |= SYS_WDT_PORT_OUT;
	SYS_WDT_H( );
	WDT_cnt = 0;


	//	PC17 		M0 Wake A53  	----------------------------------------------------
	PORT_REGS->GROUP[M0_WAKEUP_A53_PORT_GROUP].PORT_DIR |= M0_WAKEUP_A53_PORT_DIR;
	PORT_REGS->GROUP[M0_WAKEUP_A53_PORT_GROUP].PORT_OUT |= M0_WAKEUP_A53_PORT_OUT;
	M0_WAKEUP_A53_H( );
	wakeupA53_puls_cnt = 0;
	wakeupA53_flg = 0;
	A53sleep_status = 0;
	#if  	Tst_A53_WAKEUP
		Tst_wakeup_flg = 0;
	#endif  	//#if  	Tst_A53_WAKEUP


	//	PC11 		A53 awake/sleep status 	------------------------------------------
	PORT_REGS->GROUP[M0_A53_SLEEP_STATUS_PORT_GROUP].PORT_DIR &= ~M0_A53_SLEEP_STATUS_PORT_DIR;
	PORT_REGS->GROUP[M0_A53_SLEEP_STATUS_PORT_GROUP].PORT_OUT |= M0_A53_SLEEP_STATUS_PORT_OUT;
	PORT_REGS->GROUP[M0_A53_SLEEP_STATUS_PORT_GROUP].PORT_PINCFG[M0_A53_SLEEP_STATUS_PORT_PIN] = 0x7;

	//	PA27 		Chili2S Wake M0  	------------------------------------------------
	PORT_REGS->GROUP[CHILI2S_WAKE_M0_PORT_GROUP].PORT_DIR &= ~CHILI2S_WAKE_M0_PORT_DIR;
	PORT_REGS->GROUP[CHILI2S_WAKE_M0_PORT_GROUP].PORT_OUT |= CHILI2S_WAKE_M0_PORT_OUT;
	PORT_REGS->GROUP[CHILI2S_WAKE_M0_PORT_GROUP].PORT_PINCFG[CHILI2S_WAKE_M0_PORT_PIN] = 0x7; 


  //	PB20 		//	Radar Power enable 			GPIO(O)  -----------------------------
	PORT_REGS->GROUP[PW_RADAR_PORT_GROUP].PORT_DIR |= PW_RADAR_PORT_DIR;
	PORT_REGS->GROUP[PW_RADAR_PORT_GROUP].PORT_OUT |= PW_RADAR_PORT_OUT;
	PW_RADAR_OFF( );



	PORT_REGS->GROUP[SYS_3V_PORT_GROUP].PORT_DIR |= SYS_3V_PORT_DIR;
	PORT_REGS->GROUP[SYS_3V_PORT_GROUP].PORT_OUT |= SYS_3V_PORT_OUT;
	SYS_3V_H( );

	PORT_REGS->GROUP[SYS_18V_PORT_GROUP].PORT_DIR |= SYS_18V_PORT_DIR;
	PORT_REGS->GROUP[SYS_18V_PORT_GROUP].PORT_OUT |= SYS_18V_PORT_OUT;
	SYS_18V_H( );

	PORT_REGS->GROUP[BAT_PW_CTL_PORT_GROUP].PORT_DIR |= BAT_PW_CTL_PORT_DIR;
	PORT_REGS->GROUP[BAT_PW_CTL_PORT_GROUP].PORT_OUT |= BAT_PW_CTL_PORT_OUT;
	PORT_REGS->GROUP[BAT_PW_CTL_PORT_GROUP].PORT_PINCFG[BAT_PW_CTL_PORT_PIN] = 0x44;  	// 01000100: PULLEN-enable


	//============================================================================
	PORT_REGS->GROUP[PW_SOLAR_EN_PORT_GROUP].PORT_DIR &= ~PW_SOLAR_EN_PORT_DIR;
	PORT_REGS->GROUP[PW_SOLAR_EN_PORT_GROUP].PORT_OUT |= PW_SOLAR_EN_PORT_OUT;
	PORT_REGS->GROUP[PW_SOLAR_EN_PORT_GROUP].PORT_PINCFG[PW_SOLAR_EN_PORT_PIN] = 0x7;

	PORT_REGS->GROUP[PW_DC_EN_PORT_GROUP].PORT_DIR &= ~PW_DC_EN_PORT_DIR;
	PORT_REGS->GROUP[PW_DC_EN_PORT_GROUP].PORT_OUT |= PW_DC_EN_PORT_OUT;
	PORT_REGS->GROUP[PW_DC_EN_PORT_GROUP].PORT_PINCFG[PW_DC_EN_PORT_PIN] = 0x7;

	PORT_REGS->GROUP[PW_BAT_A_EN_PORT_GROUP].PORT_DIR &= ~PW_BAT_A_EN_PORT_DIR;
	PORT_REGS->GROUP[PW_BAT_A_EN_PORT_GROUP].PORT_OUT |= PW_BAT_A_EN_PORT_OUT;
	PORT_REGS->GROUP[PW_BAT_A_EN_PORT_GROUP].PORT_PINCFG[PW_BAT_A_EN_PORT_PIN] = 0x7;

	PORT_REGS->GROUP[PW_BAT_B_EN_PORT_GROUP].PORT_DIR &= ~PW_BAT_B_EN_PORT_DIR;
	PORT_REGS->GROUP[PW_BAT_B_EN_PORT_GROUP].PORT_OUT |= PW_BAT_B_EN_PORT_OUT;
	PORT_REGS->GROUP[PW_BAT_B_EN_PORT_GROUP].PORT_PINCFG[PW_BAT_B_EN_PORT_PIN] = 0x7;


	//============================================================================
	//----------------------------------------------------------------------------
	PORT_REGS->GROUP[BTN_TEST_MODE_PORT_GROUP].PORT_DIR &= ~BTN_TEST_MODE_PORT_DIR;
	PORT_REGS->GROUP[BTN_TEST_MODE_PORT_GROUP].PORT_OUT |= BTN_TEST_MODE_PORT_OUT;
	PORT_REGS->GROUP[BTN_TEST_MODE_PORT_GROUP].PORT_PINCFG[BTN_TEST_MODE_PORT_PIN] = 0x7;

	PORT_REGS->GROUP[BTN_QC_MODE_PORT_GROUP].PORT_DIR &= ~BTN_QC_MODE_PORT_DIR;
  PORT_REGS->GROUP[BTN_QC_MODE_PORT_GROUP].PORT_OUT |= BTN_QC_MODE_PORT_OUT;
  PORT_REGS->GROUP[BTN_QC_MODE_PORT_GROUP].PORT_PINCFG[BTN_QC_MODE_PORT_PIN] = 0x7;


	//============================================================================
  #if Tst_EVK_LED_TST1
		PORT_REGS->GROUP[evk_LED_PORT_GROUP].PORT_DIR |= evk_LED_PORT_DIR;
		PORT_REGS->GROUP[evk_LED_PORT_GROUP].PORT_OUT |= evk_LED_PORT_OUT;

		PORT_REGS->GROUP[evk_SW0_PORT_GROUP].PORT_DIR &= ~evk_SW0_PORT_DIR;
	  PORT_REGS->GROUP[evk_SW0_PORT_GROUP].PORT_OUT |= evk_SW0_PORT_OUT;
	  PORT_REGS->GROUP[evk_SW0_PORT_GROUP].PORT_PINCFG[evk_SW0_PORT_PIN] = 0x7; 				//  PC01 Input - EIC
  #endif 	//#if Tst_EVK_LED_TST1

} 	//void 	M0_GPIO_Initialize( void )


//******************************************************************************
//
//******************************************************************************
//	XOUT32 ==> GPIO  PA01
void 	 XOUT32_PA01_GPIO_Initialize( void )
{
	//==============================================================================
	//	XOUT32 ==> GPIO  PA01
	PORT_REGS->GROUP[XOUT32_PA01_PORT_GROUP].PORT_DIR |= XOUT32_PA01_PORT_DIR;
	PORT_REGS->GROUP[XOUT32_PA01_PORT_GROUP].PORT_OUT |= XOUT32_PA01_PORT_OUT;
	XOUT32_PA01_L( );
	NOP( );
}	//void 	 XOUT32_PA01_GPIO_Initialize( void )












//******************************************************************************
//
//******************************************************************************
void 	TimerF_WDT_active( void )
{
	reset_timer( tm_WDT );

	//============================================================================
	if( (WDT_cnt%2) == 0 )	{
		SYS_WDT_L( );
	}
	else 	{
		SYS_WDT_H( );
	}

	WDT_cnt++;
} 		//void 	TimerF_Radar_PWoff( void )












//******************************************************************************
//
//******************************************************************************
/*
	UINT8 	wakeupA53_flg;  	// =1, A53 sleep;
														// =0, A53 awake
*/
void 	Wakeup_A53( void )
{
	M0_WAKEUP_A53_H( );

	//------------------------------------------------------------------
	if( M0_A53_SLEEP_STATUS_Get( ) == 0 )  	{
		if( wakeupA53_puls_cnt == 0 )		{
			SERCOM1_USART_TX_INT_DISABLE( );
			wakeupA53_puls_cnt++;

			wakeupA53_flg = 1;
			A53sleep_status = 1;
			UartDataTx_M0toM4_Data_NoWakeupA53( uart_M0_WAKEUP_A53, (uint8_t*)&sysInfo, sizeof(M0_SYSTEM_INFO) );

			tm_wakeupA53_puls = setup_timer( 200, 0, (void (*)())TimerF_wakeupA53_puls, NULL );
			TimerF_wakeupA53_puls( );

		}  		//if( wakeupA53_puls_cnt == 0 )		{
	}  		//if( M0_A53_SLEEP_STATUS_Get( ) == 0 )  	{

	//------------------------------------------------------------------
	else 	{
		if( wakeupA53_puls_cnt == 0 )		{
			/*
			wakeupA53_puls_cnt++;

			tm_wakeupA53_puls = setup_timer( 200, 0, (void (*)())TimerF_wakeupA53_puls, NULL );
			TimerF_wakeupA53_puls( );
			*/
		}  	//if( wakeupA53_puls_cnt == 0 )		{
	}  		//if( M0_A53_SLEEP_STATUS_Get( ) == 0 )  	{		else
} 		//void 	Wakeup_A53( void )


//******************************************************************************
//
//******************************************************************************
void 	TimerF_wakeupA53_puls_close( void )
{
	close_timer( tm_wakeupA53_puls );
	A53sleep_status = wakeupA53_flg = wakeupA53_puls_cnt = 0;
	M0_WAKEUP_A53_H( );
	NOP( );
}


//******************************************************************************
//
//******************************************************************************
void 	TimerF_wakeupA53_puls( void )
{
	reset_timer( tm_wakeupA53_puls );

	//============================================================================
	if( (wakeupA53_puls_cnt % 2) >= 1 ) 	{
		M0_WAKEUP_A53_L( );  	//	1 3 5 7 9 11
	}
	else 	{
		M0_WAKEUP_A53_H( );  	//	2 4 6 8 10 12
	}
	
	if( wakeupA53_puls_cnt >= 4 ) 	{
		if( (wakeupA53_puls_cnt % 2) == 0 ) 	{
			wakeupA53_flg = 0;
			SERCOM1_USART_TX_INT_ENABLE( );
		}

		if( (wakeupA53_puls_cnt == 12) && (A53sleep_status >= 1) ) 	{
			UartDataTx_M0toM4_Data_NoWakeupA53( uart_M0_WAKEUP_A53, (uint8_t*)&sysInfo, sizeof(M0_SYSTEM_INFO) );			
		}

		if( wakeupA53_puls_cnt >= 14 ) 	{
			setup_timer( 10, 1, (void (*)())TimerF_wakeupA53_puls_close, NULL );
		}
	}

	wakeupA53_puls_cnt++;
} 		//void 	TimerF_wakeupA53_puls( void )












//	TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#if Tst_EVK_LED_TST1

	//******************************************************************************
	//
	UINT32 	portData(  int group_number )
	{
		return PORT_REGS->GROUP[group_number].PORT_IN;
	} 		//UINT32 	portData( PORT_GROUP group )

#endif 		//#if Tst_EVK_LED_TST1


//	TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#if 	Tst_PW_BAT01

	//******************************************************************************
	//
	void  TimerF_Bat_PW_Change_TEST( void )
	{
		reset_timer( Tst_tm_Bat_change );
	  //============================================================================

	  if( (Tst_Bat_changeCnt%2) == 0 )	{
	  	BAT_PW_CTL_A( );
	  }
	  else 	{
	  	BAT_PW_CTL_B( );
	  }
	  Tst_Bat_changeCnt++;
	} 		//void  TimerF_Bat_PW_Change_TEST( void )

#endif 		//#if 	Tst_PW_BAT01




//	TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#if 	Tst_A53_SLEEP_STATE
	//******************************************************************************
	//
	void  TimerF_A53_SLEEP_TST( void )
	{
		reset_timer( Tst_tm_CK_M0_A53_SLEEP_STATUS );
	  //============================================================================
	  Tst_A53Sleep = M0_A53_SLEEP_STATUS_Get( );
	  NOP( );
	  NOP( );
	  NOP( );
	}
#endif 		//#if 	Tst_PW_BAT01


#if  	Tst_A53_WAKEUP
	//******************************************************************************
	//
	void  Tst_wakeupA53( void )
	{
		Tst_wakeup_flg = 0;
		M0_AllDevStatus.mgc.mgc = tst_mgc;
		tst_mgc++;
		SysRTC_Get( (M0_RTC_TIME_FRAME*)&(M0_AllDevStatus.mgc.mcu_RTC) );
		UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_MGC3130, (uint8_t*)&(M0_AllDevStatus.mgc), sizeof(M0_MGC_DATA_FRAME) );

		tm_tst_ck_A53sleep->period_count = 2000;
		reset_timer( tm_tst_ck_A53sleep );
	}


	//******************************************************************************
	//
	void  TimerF_Tst_ck_A53sleep( void )
	{
		reset_timer( tm_tst_ck_A53sleep );

		if( (M0_A53_SLEEP_STATUS_Get( ) == 0) && (Tst_wakeup_flg == 0) )  	{
			tm_tst_ck_A53sleep->period_count = 35000;
			reset_timer( tm_tst_ck_A53sleep );

			setup_timer( 30000, 1, (void (*)())Tst_wakeupA53, NULL );
			Tst_wakeup_flg = 1;
		}
		else 	{
			tst_mgc = 10;
		}
	}  		//void  TimerF_Tst_ck_A53sleep( void )
#endif  		//#if  	Tst_A53_WAKEUP

