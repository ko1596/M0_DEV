

#ifndef GIT_GPIO_H
#define GIT_GPIO_H




//******************************************************************************
//  Defined
//==============================================================================
//	XOUT32 ==> GPIO  PA01
#define  XOUT32_PA01_PORT_GROUP			0
#define  XOUT32_PA01_PORT_PIN				1
#define  XOUT32_PA01_PORT_DIR				0x02 		//	10 	0x02
#define  XOUT32_PA01_PORT_OUT				0x02
#define  XOUT32_PA01_H()              		(PORT_REGS->GROUP[XOUT32_PA01_PORT_GROUP].PORT_OUTSET = 1 << XOUT32_PA01_PORT_PIN)
#define  XOUT32_PA01_L()              		(PORT_REGS->GROUP[XOUT32_PA01_PORT_GROUP].PORT_OUTCLR = 1 << XOUT32_PA01_PORT_PIN)


//	PC17 		M0 Wake A53  	------------------------------------------------------
#define  M0_WAKEUP_A53_PORT_GROUP		2
#define  M0_WAKEUP_A53_PORT_PIN			17
#define  M0_WAKEUP_A53_PORT_DIR			0x20000 		//	100000000000000000
#define  M0_WAKEUP_A53_PORT_OUT			0x20000 		//	100000000000000000
#define  M0_WAKEUP_A53_H()      		(PORT_REGS->GROUP[M0_WAKEUP_A53_PORT_GROUP].PORT_OUTSET = 1 << M0_WAKEUP_A53_PORT_PIN)
#define  M0_WAKEUP_A53_L()      		(PORT_REGS->GROUP[M0_WAKEUP_A53_PORT_GROUP].PORT_OUTCLR = 1 << M0_WAKEUP_A53_PORT_PIN)

//#define  M0_WAKEUP_A53_TIME 				50 		// ms
#define  M0_WAKEUP_A53_TIME 				200 	// ms
#define  M0_WAKEUP_A53_DELAY 				500		// ms
#define  M0_WAKEUP_A53_DELAY2				100		// ms
#define  M0_WAKEUP_A53_BAT_I 				200 	// mA


//	PA27 		Chili2S Wake M0  	--------------------------------------------------
//	EIC/EXTINT[15] 		1000000000000000 0x8000
#define  CHILI2S_WAKE_M0_PORT_GROUP			0
#define  CHILI2S_WAKE_M0_PORT_PIN				27
#define  CHILI2S_WAKE_M0_PORT_DIR 			0x8000000 		//	1000000000000000000000000000
#define  CHILI2S_WAKE_M0_PORT_OUT 			0x8000000 		//	1000000000000000000000000000
#define  CHILI2S_WAKE_M0_Get( )					(((PORT_REGS->GROUP[CHILI2S_WAKE_M0_PORT_GROUP].PORT_IN >> CHILI2S_WAKE_M0_PORT_PIN)) & 0x0001)

/*
//	PA08 		A53 awake/sleep status 	--------------------------------------------
#define  M0_A53_SLEEP_STATUS_PORT_GROUP			0
#define  M0_A53_SLEEP_STATUS_PORT_PIN				8
#define  M0_A53_SLEEP_STATUS_PORT_DIR 			0x0000100 		//	PA08	100000000
#define  M0_A53_SLEEP_STATUS_PORT_OUT 			0x0000100 		//	PA08	100000000
*/

//	PC11 		A53 awake/sleep status 	--------------------------------------------
//	EIC/EXTINT[3] 		100000000000 	0x800
#define  M0_A53_SLEEP_STATUS_PORT_GROUP			2
#define  M0_A53_SLEEP_STATUS_PORT_PIN				11
#define  M0_A53_SLEEP_STATUS_PORT_DIR 			0x0000800 		//	PC11	100000000000
#define  M0_A53_SLEEP_STATUS_PORT_OUT 			0x0000800 		//	PC11	100000000000
#define  M0_A53_SLEEP_STATUS_Get( )					(((PORT_REGS->GROUP[M0_A53_SLEEP_STATUS_PORT_GROUP].PORT_IN >> M0_A53_SLEEP_STATUS_PORT_PIN)) & 0x0001)


//	PB20 		//	Radar Power enable 			GPIO(O)  -------------------------------
#define  PW_RADAR_PORT_GROUP					1
#define  PW_RADAR_PORT_PIN						20
#define  PW_RADAR_PORT_DIR						0x100000 		//	100000000000000000000
#define  PW_RADAR_PORT_OUT						0x100000 		//	100000000000000000000
#define  PW_RADAR_H()              		(PORT_REGS->GROUP[PW_RADAR_PORT_GROUP].PORT_OUTSET = 1 << PW_RADAR_PORT_PIN)
#define  PW_RADAR_L()              		(PORT_REGS->GROUP[PW_RADAR_PORT_GROUP].PORT_OUTCLR = 1 << PW_RADAR_PORT_PIN)
//#define  PW_RADAR_OFF() 							PW_RADAR_H()
//#define  PW_RADAR_ON() 								PW_RADAR_L()
#define  PW_RADAR_OFF() 							PW_RADAR_L()  		//	20210813-03104C
#define  PW_RADAR_ON() 								PW_RADAR_H()  		//	20210813-03104C


//	PB16		//	System +5V Output Control -1	系統電源輸出控制	GPIO(O)												PB16- GPIO
/*  		XXX  No used 				210604-020C80
#define  SYS_5V_PORT_GROUP					1
#define  SYS_5V_PORT_PIN						16
#define  SYS_5V_PORT_DIR						0x10000 		//	10000000000000000 	0x10000
#define  SYS_5V_PORT_OUT						0x10000
#define  SYS_5V_H()              		(PORT_REGS->GROUP[SYS_5V_PORT_GROUP].PORT_OUTSET = 1 << SYS_5V_PORT_PIN)
#define  SYS_5V_L()              		(PORT_REGS->GROUP[SYS_5V_PORT_GROUP].PORT_OUTCLR = 1 << SYS_5V_PORT_PIN)
*/

//	PB17		//	System +3.3V Output Control -2	系統電源輸出控制	GPIO(O)												PB17- GPIO
#define  SYS_3V_PORT_GROUP					1
#define  SYS_3V_PORT_PIN						17
#define  SYS_3V_PORT_DIR						0x20000 		//	100000000000000000 	0x20000
#define  SYS_3V_PORT_OUT						0x20000
#define  SYS_3V_H()              		(PORT_REGS->GROUP[SYS_3V_PORT_GROUP].PORT_OUTSET = 1 << SYS_3V_PORT_PIN)
#define  SYS_3V_L()              		(PORT_REGS->GROUP[SYS_3V_PORT_GROUP].PORT_OUTCLR = 1 << SYS_3V_PORT_PIN)

//	PB18		//	System +1.8V Output Control -3	系統電源輸出控制	GPIO(O)												PB18- GPIO
#define  SYS_18V_PORT_GROUP					1
#define  SYS_18V_PORT_PIN						18
#define  SYS_18V_PORT_DIR						0x40000 		//	1000000000000000000 	0x40000
#define  SYS_18V_PORT_OUT						0x40000
#define  SYS_18V_H()              		(PORT_REGS->GROUP[SYS_18V_PORT_GROUP].PORT_OUTSET = 1 << SYS_18V_PORT_PIN)
#define  SYS_18V_L()              		(PORT_REGS->GROUP[SYS_18V_PORT_GROUP].PORT_OUTCLR = 1 << SYS_18V_PORT_PIN)

//	PB19;			低電壓電池供電控制(+/A BAT OUT; -/B BAT OUT)
#define  BAT_PW_CTL_PORT_GROUP				1
#define  BAT_PW_CTL_PORT_PIN					19
#define  BAT_PW_CTL_PORT_DIR					0x80000 		//	10000000000000000000 	0x80000
#define  BAT_PW_CTL_PORT_OUT					0x80000
#define  BAT_PW_CTL_H()              	(PORT_REGS->GROUP[BAT_PW_CTL_PORT_GROUP].PORT_OUTSET = 1 << BAT_PW_CTL_PORT_PIN)
#define  BAT_PW_CTL_L()              	(PORT_REGS->GROUP[BAT_PW_CTL_PORT_GROUP].PORT_OUTCLR = 1 << BAT_PW_CTL_PORT_PIN)
#define  BAT_PW_CTL_A()				BAT_PW_CTL_H()
#define  BAT_PW_CTL_B()				BAT_PW_CTL_L()


//	PC26; 		WDT trigger
#define  SYS_WDT_PORT_GROUP				2
#define  SYS_WDT_PORT_PIN					26
#define  SYS_WDT_PORT_DIR					0x4000000 		//	1 0000000000 0000000000 000000
#define  SYS_WDT_PORT_OUT					0x4000000
#define  SYS_WDT_H()              	(PORT_REGS->GROUP[SYS_WDT_PORT_GROUP].PORT_OUTSET = 1 << SYS_WDT_PORT_PIN)
#define  SYS_WDT_L()              	(PORT_REGS->GROUP[SYS_WDT_PORT_GROUP].PORT_OUTCLR = 1 << SYS_WDT_PORT_PIN)





//========================================================================
//	Solar Battery - Power Good(Low Active)	Solar Battery 供電通知	GPIO(I)					PB11- GPIO
//	DC Input - Power Good(Low Active)	DC Input  供電通知	GPIO(I)					PB12- GPIO
//	A Battery - Power Good(Low Active)	A Battery 供電通知	GPIO(I)					PB13- GPIO
//	B Battery - Power Good(Low Active)	B Battery 供電通知	GPIO(I)					PB14- GPIO

//	PB11 		Solar Battery 供電通知	 		------------------------------------
#define 	PW_SOLAR_EN_PORT_GROUP				1
#define 	PW_SOLAR_EN_PORT_PIN					11
#define 	PW_SOLAR_EN_PORT_DIR 				0x800
#define 	PW_SOLAR_EN_PORT_OUT 				0x800
#define 	PW_SOLAR_EN_Get( )			(((PORT_REGS->GROUP[PW_SOLAR_EN_PORT_GROUP].PORT_IN >> PW_SOLAR_EN_PORT_PIN)) & 0x0001)

//	PB12 		DC Input 供電通知	 		----------------------------------------
#define 	PW_DC_EN_PORT_GROUP					1
#define 	PW_DC_EN_PORT_PIN						12
#define 	PW_DC_EN_PORT_DIR 						0x1000
#define 	PW_DC_EN_PORT_OUT 						0x1000
#define 	PW_DC_EN_Get( )			(((PORT_REGS->GROUP[PW_DC_EN_PORT_GROUP].PORT_IN >> PW_DC_EN_PORT_PIN)) & 0x0001)

//	PB13 		Bat_A 供電通知	 		------------------------------------------
#define 	PW_BAT_A_EN_PORT_GROUP				1
#define 	PW_BAT_A_EN_PORT_PIN					13
#define 	PW_BAT_A_EN_PORT_DIR 				0x2000
#define 	PW_BAT_A_EN_PORT_OUT 				0x2000
#define 	PW_BAT_A_EN_Get( )			(((PORT_REGS->GROUP[PW_BAT_A_EN_PORT_GROUP].PORT_IN >> PW_BAT_A_EN_PORT_PIN)) & 0x0001)

//	PB14 		Bat_B 供電通知	 		------------------------------------------
#define 	PW_BAT_B_EN_PORT_GROUP				1
#define 	PW_BAT_B_EN_PORT_PIN					14
#define 	PW_BAT_B_EN_PORT_DIR 				0x4000
#define 	PW_BAT_B_EN_PORT_OUT 				0x4000
#define 	PW_BAT_B_EN_Get( )			(((PORT_REGS->GROUP[PW_BAT_B_EN_PORT_GROUP].PORT_IN >> PW_BAT_B_EN_PORT_PIN)) & 0x0001)




//========================================================================
//	PB04		Button - Test Mode
//	PB04		EIC/EXTINT[4]
#define  BTN_TEST_MODE_PORT_GROUP			1
#define  BTN_TEST_MODE_PORT_PIN				4
#define  BTN_TEST_MODE_PORT_DIR 			0x0010 		//	10000		0x0010
#define  BTN_TEST_MODE_PORT_OUT 			0x0010

//	PB05		Button - Burn IN Mode / QC Mode
//	PB05		EIC/EXTINT[5]
#define  BTN_QC_MODE_PORT_GROUP				1
#define  BTN_QC_MODE_PORT_PIN					5
#define  BTN_QC_MODE_PORT_DIR 				0x0020
#define  BTN_QC_MODE_PORT_OUT 				0x0020




//==============================================================================
//	LED_R 		PB08- GPIO 		100000000 		0x100
//	LED_G 		PB09- GPIO 		1000000000 		0x200
//	LED_V 		PC12- GPIO 		1000000000000.	0x1000
//	LED_Y 		PC13- GPIO 		10000000000000.	0x2000
#define  LED_R_PORT_GROUP			1
#define  LED_R_PORT_PIN				8
#define  LED_R_PORT_DIR 			0x0400
#define  LED_R_PORT_OUT 			0x0400

#define  LED_G_PORT_GROUP			1
#define  LED_G_PORT_PIN				9
#define  LED_G_PORT_DIR 			0x0800
#define  LED_G_PORT_OUT 			0x0800

#define  LED_B_PORT_GROUP			2
#define  LED_B_PORT_PIN				12
#define  LED_B_PORT_DIR 			0x1000
#define  LED_B_PORT_OUT 			0x1000

#define  LED_Y_PORT_GROUP			2
#define  LED_Y_PORT_PIN				13
#define  LED_Y_PORT_DIR 			0x2000
#define  LED_Y_PORT_OUT 			0x2000

//------------------------------------------------------------------------------
#define  LED_R_H() 				(PORT_REGS->GROUP[LED_R_PORT_GROUP].PORT_OUTSET = 1 << LED_R_PORT_PIN)
#define  LED_R_L() 				(PORT_REGS->GROUP[LED_R_PORT_GROUP].PORT_OUTCLR = 1 << LED_R_PORT_PIN)
#define  LED_R_Get()			(((PORT_REGS->GROUP[LED_R_PORT_GROUP].PORT_IN >> LED_R_PORT_PIN)) & LED_R_PORT_DIR)

#define  LED_G_H() 				(PORT_REGS->GROUP[LED_G_PORT_GROUP].PORT_OUTSET = 1 << LED_G_PORT_PIN)
#define  LED_G_L() 				(PORT_REGS->GROUP[LED_G_PORT_GROUP].PORT_OUTCLR = 1 << LED_G_PORT_PIN)

#define  LED_B_H() 				(PORT_REGS->GROUP[LED_B_PORT_GROUP].PORT_OUTSET = 1 << LED_B_PORT_PIN)
#define  LED_B_L() 				(PORT_REGS->GROUP[LED_B_PORT_GROUP].PORT_OUTCLR = 1 << LED_B_PORT_PIN)

#define  LED_Y_H() 				(PORT_REGS->GROUP[LED_Y_PORT_GROUP].PORT_OUTSET = 1 << LED_Y_PORT_PIN)
#define  LED_Y_L() 				(PORT_REGS->GROUP[LED_Y_PORT_GROUP].PORT_OUTCLR = 1 << LED_Y_PORT_PIN)



//==============================================================================
//
#if Tst_EVK_LED_TST1
	//	SAML22   EVK 	 -----------------------------------------------------------
	//		EVK LED 	PC27	
	#define  evk_LED_PORT_GROUP			2
	#define  evk_LED_PORT_PIN				27
	#define  evk_LED_PORT_DIR 			0x8000000 		//	PC27	1000000000000000000000000000
	#define  evk_LED_PORT_OUT 			0x8000000 		//	PC27

	//		EVK SW0 	PC01
	#define  evk_SW0_PORT_GROUP			2
	#define  evk_SW0_PORT_PIN				1
	#define  evk_SW0_PORT_DIR 			0x0000002 		//	PC01	
	#define  evk_SW0_PORT_OUT 			0x0000002 		//	PC01

	#define  evk_SW0_Get( )					(((PORT_REGS->GROUP[evk_SW0_PORT_GROUP].PORT_IN >> evk_SW0_PORT_PIN)) & 0x0001)

	//  D88   ====================================================================
	#define LED_OFF()               (PORT_REGS->GROUP[2].PORT_OUTSET = 1 << evk_LED_PORT_PIN)
	#define LED_ON()                (PORT_REGS->GROUP[2].PORT_OUTCLR = 1 << evk_LED_PORT_PIN)
#endif 	//#if Tst_EVK_LED_TST1




//******************************************************************************
//	Global
//	WDT 		--------------------------------------------------------------------
extern	TIMER*	tm_WDT;
extern 	UINT8 	WDT_cnt;

//	M0 wakeup A53 		----------------------------------------------------------
extern 	TIMER*	tm_wakeupA53_puls;
extern 	UINT8 	wakeupA53_puls_cnt;
extern 	UINT8 	wakeupA53_flg;




//	TEST  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#if 	Tst_PW_BAT01
		extern 	TIMER*	Tst_tm_Bat_change;
		extern 	int 		Tst_Bat_changeCnt;
#endif 		//#if 	Tst_PW_BAT01

#if 	Tst_A53_SLEEP_STATE
		extern 	TIMER*	Tst_tm_CK_M0_A53_SLEEP_STATUS;
		extern 	int  		Tst_A53Sleep;
#endif 		//#if 	Tst_PW_BAT01

#if  	Tst_A53_WAKEUP
		extern 	TIMER*  tm_tst_ck_A53sleep;
		extern 	UINT8  	tst_wakeupA53_flg;
#endif  	//#if  	Tst_A53_WAKEUP



//******************************************************************************
//  Function
void 	 XOUT32_PA01_GPIO_Initialize( void );

void 	M0_GPIO_Initialize( void );
//void 	LED_RGBY_Initialize( void );

void 	M0_EIC_Initialize( void );

void 	Wakeup_A53( void );
void 	TimerF_wakeupA53_puls( void );

void 	TimerF_WDT_active( void );





#if 	Tst_PW_BAT01
	void  TimerF_Bat_PW_Change_TEST(void);
#endif 		//#if 	Tst_PW_BAT01


#if Tst_EVK_LED_TST1
	UINT32 	portData(  int group_number );
#endif 		//#if Tst_EVK_LED_TST1


#if 	Tst_A53_SLEEP_STATE
	void  TimerF_A53_SLEEP_TST( void );
#endif 		//#if 	Tst_PW_BAT01


#if  	Tst_A53_WAKEUP
	void  TimerF_Tst_ck_A53sleep( void );
#endif  	//#if  	Tst_A53_WAKEUP


#endif // GIT_GPIO_H

