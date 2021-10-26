

//******************************************************************************
//  Prj312_ALL   T
//      D88 Test  -   20200824-1077
//        Input interrupt Test
//******************************************************************************

/*
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
 * */
#include "All_Header.h"


//==============================================================================
//                                             "0123456789ABCDEF0123456789ABCDEF"
#if 	!Tst_Radar_Send_AllData

	#if  !Tst_A53_WAKEUP
		//                                             "0123456789ABCDEF0123456789ABCDEF"
		const unsigned char FW_PARKINGMETER_L22[32] = {"Prj312_ALL       20211014-031276"}; 		//	M0_RADAR_FRAME; car pre_car

		//const unsigned char FW_PARKINGMETER_L22[32] = {"Prj312_ALL       20211005-031262"}; 		//	M0_RADAR_SET_FRAME
		//const unsigned char FW_PARKINGMETER_L22[32] = {"Prj312_ALL       20210928-031251"}; 		//	M0_RADAR_VER_30_210930		
		//const unsigned char FW_PARKINGMETER_L22[32] = {"Prj312_ALL       20210928-031236"}; 		//	Battery CK logic; modify  M0_POWER_DATA_FRAME

	#else  		//#if  !Tst_A53_WAKEUP
		//                                             "0123456789ABCDEF0123456789ABCDEF"
		const unsigned char FW_PARKINGMETER_L22[32] = {"Prj312_ALL    20210924-03121b T6"}; 		//	TimerF_wakeupA53_puls

	#endif  	//#if  !Tst_A53_WAKEUP

#else  	//#if 	!Tst_Radar_Send_AllData

	//                                             "0123456789ABCDEF0123456789ABCDEF"
	const unsigned char FW_PARKINGMETER_L22[32] = {"Prj312_ALL  1014-031276   PS fix"}; 		//	PreShooting fix
//    const unsigned char FW_PARKINGMETER_L22[32] = {"Prj312_ALL  1014-031276 RadarTst"}; 		//	M0_RADAR_FRAME
	//const unsigned char FW_PARKINGMETER_L22[32] = {"Prj312_ALL  1006-031262 RadarTst"}; 		//	RadarA_Req_SWversion
	//const unsigned char FW_PARKINGMETER_L22[32] = {"Prj312_ALL  1005-031255 RadarTst"}; 		//	M0_RADAR_SET_FRAME
	//const unsigned char FW_PARKINGMETER_L22[32] = {"Prj312_ALL       20210928-031251"}; 		//	M0_RADAR_VER_30_210930

#endif 		//#if 	!Tst_Radar_Send_AllData




// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{  
	//int Tst_rtc = 1;

  NOP( );
  NOP( );
  NOP( );
  NOP( );


  //============================================================================
  /* Initialize all modules */
  SYS_Initialize ( NULL );
  
  SYSTICK_TimerStart();


  //  Initial 	****************************************************************
  memset( (UINT8*)&M0_AllDevStatus, 0x00, sizeof(M0_ALLDEV_STATUS_FRAME) );
  memcpy( sysInfo.FW_ver, FW_PARKINGMETER_L22, 32);

  //----------------------------------------------------------------------------
  #if Tst_SET_RTC
    NOP( );
    /*
    sysInfo.mcu_RTC.Year = 21;
    sysInfo.mcu_RTC.Month = 3;
    sysInfo.mcu_RTC.Day = 2;
    sysInfo.mcu_RTC.Hour = 17;
    sysInfo.mcu_RTC.Minute = 12;
    sysInfo.mcu_RTC.Second = 0;
    SysRTC_Set( sysInfo.mcu_RTC );
    */
    NOP( );
  #endif  //#if Tst_SET_RTC
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


	//	Devive 		================================================================


	//	Radar 		----------------------------------------------------------------
	flg_Radar_Info_noSkip = 0;

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


  //	EIC 		==================================================================
  M0_EIC_Initialize( );


  //	Devices 		==============================================================
  memset( (UINT8*)&i2c_interface, 0x00, sizeof(I2C_INTERFACE) );
  
  mgc3130_i2c_Init( );
  mgc3130_hw_Reset( );
  lm75_i2c_Init( );
  eep24aa64_i2c_Init( );
  //ICM20602_i2c_Init( );
  STK8BA53_i2c_Init( );
  
  LTC2944_i2c_Init( );
  //	LTV2944 Control: 	----------------------------------------------
  //LTC2944_Write_ControlReg( 0x80 | 0x3C );
  //LTC2944_Write_ControlReg( 0xC0 | 0x3C );  
  //LTC2944_Write_ControlReg( 0xF8  );		//	LTV2944 Control: 11 111 00 0
  //LTC2944_Write_ControlReg( 0xC0  );		//	LTV2944 Control: 11 000 00 0
  //LTC2944_Write_ControlReg( 0xE8  );		//	LTV2944 Control: 11 101 00 0
  LTC2944_Write_ControlReg( 0xF0  );		//	LTV2944 Control: 11 110 00 0
  //LTC2944_Write_ControlReg( 0x70  );		//	LTV2944 Control: 01 110 00 0
  //LTC2944_Write_ControlReg( 0xB0  );		//	LTV2944 Control: 10 110 00 0

  
  
  //============================================================================
  #if  Tst_PRE_SHOOT_ENABLE
  	Radar_Initialization( );
  #endif  	//#if  Tst_PRE_SHOOT_ENABLE


  //  **************************************************************************
  //  main while
  //  **************************************************************************
  NOP( );


	//	TEST  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  #if   Tst_EVK_LED_TST1
  	tm_evk_led = setup_timer( 25, 0, (void (*)())TimerF_LED_TEST, NULL );
  	//tm_evk_led = setup_timer( 500, 0, (void (*)())TimerF_LED_TEST, NULL );
  #endif //#if   Tst_EVK_LED_TST1

  #if !Tst_RTC_DISABLE
  	SysRTC_Get( &(sysInfo.mcu_RTC) );
  	NOP( );
  #endif 	//#if !Tst_RTC_DISABLE
  //UartDataTx_M0toM4_Data( uart_RSP_SYSTEM_INFO, (uint8_t*)&sysInfo, sizeof(M0_SYSTEM_INFO) );


	#if 	Tst_UART_A53M0_TxRx
		//tm_Tst01 = setup_timer( 1000, 0, (void (*)())TimerF_Tst_A53M0_TxRx01, NULL );
	#endif 		//#if 	Tst_UART_A53M0_TxRx


  #if 	Tst_STK8BA53_01
  	TimerF_LTC2944_Read( );
  	tm_STK8BA53_Req = setup_timer( 5000, 0, (void (*)())TimerF_STK8BA53_Normal_Read, NULL );
  	//TimerF_STK8BA53_Normal_Read( );
  	
  	//M0_AllDevStatus.g_sensor.stk8ba53.flg_INT = 1;
		//tm_STK8BA53_INT_start = setup_timer( 10, 0, (void (*)())TimerF_STK8BA53_INT, NULL );
		//TimerF_STK8BA53_INT( );
  #endif  	//#if 	Tst_STK8BA53_01

	#if 	Tst_A53_SLEEP_STATE
		Tst_tm_CK_M0_A53_SLEEP_STATUS = setup_timer( 1000, 0, (void (*)())TimerF_A53_SLEEP_TST, NULL );
	#endif 		//#if 	Tst_A53_SLEEP_STATE


	#if 	Tst_Chili2S_UART
		tm_Chili2S_UART = setup_timer( 3000, 0, (void (*)())TimerF_Tst_Chili2S_UART, NULL );
		TimerF_Tst_Chili2S_UART( );
	#endif  	//#if 	Tst_Chili2S_UART


	#if  	Tst_A53_WAKEUP
			tm_tst_ck_A53sleep = setup_timer( 2000, 0, (void (*)())TimerF_Tst_ck_A53sleep, NULL );
	#endif  	//#if  	Tst_A53_WAKEUP




	//****************************************************************************
	// 	Devices Setting  *********************************************************

	//	WDT 		==================================================================
	WDT_cnt = 0;
	tm_WDT = setup_timer( 1000, 0, (void (*)())TimerF_WDT_active, NULL );
	TimerF_WDT_active( );


	//	ADC 	====================================================================
	tm_Get_ADC = setup_timer( 1000, 0, (void (*)())TimerF_ADC_DATA, NULL );
	TimerF_ADC_DATA( );


	//	LTC2944 ==================================================================
	//#if 	!Tst_STK8BA53_01
	#if  !Tst_LTC2944_CK
		tm_ltc2944_read = setup_timer( 10000, 0, (void (*)())TimerF_LTC2944_Read, NULL );
	#else
		tm_ltc2944_read = setup_timer( 1000, 0, (void (*)())TimerF_LTC2944_Read, NULL );
	#endif  	//#if  !Tst_LTC2944_CK
	TimerF_LTC2944_Read( );
	//#endif  		//#if 	!Tst_STK8BA53_01


	//tm_CK_BAT_logic = setup_timer( 10000, 0, (void (*)())TimerF_ckBAT_logic, NULL );  	//10sec
	tm_CK_BAT_logic = setup_timer( 5000, 0, (void (*)())TimerF_ckBAT_logic, NULL );  	//10sec
	TimerF_ckBAT_logic( );


	//	Radar A/B 	==============================================================
  //	Req. Radar A/B FW version
  PW_RADAR_ON( );
  tm_Radar_ReStart_state = setup_timer( 1000, 1, (void (*)())TimerF_Radar_ReStart_M0_PWon, NULL );
  //uart_ReStart_Devices( );


	//	LM75 		==================================================================
	//#if 	!Tst_STK8BA53_01
	tm_lm75_read = setup_timer( 2000, 0, (void (*)())TimerF_LM75_Read, NULL );
	TimerF_LM75_Read( );
	//#endif  		//#if 	!Tst_STK8BA53_01


	//	STK8BA53 =================================================================
	//tm_STK8BA53_Req = setup_timer( 2333, 0, (void (*)())TimerF_STK8BA53_Normal_Read, NULL );
	tm_STK8BA53_Req = setup_timer( 10000, 0, (void (*)())TimerF_STK8BA53_Normal_Read, NULL );
	TimerF_STK8BA53_Normal_Read( );

  
  //	TL-SAM 	==================================================================
  tm_TLSAM = setup_timer( 500, 0, (void (*)())TimerF_TLSAM_ReqFWversion, NULL );


  //	Chili2S info.  	==========================================================
  #if   SERCOM0_ENABLE
  	Chili2S_Set_RTC( );
  	//Chili2S_Req_Info( );
  	setup_timer( 200, 1, (void (*)())Chili2S_Req_Info, NULL );
  #endif  	//#if   SERCOM0_ENABLE



	// ***************************************************************************
	// 		while loop
	// ***************************************************************************
	while ( true )    {

		NOP( );
		Update_Timer_Chain( );
		NOP( );

		//===========================================================================
		//	A53 - M0
		NOP( );
		UartDataRx_M4_M0( );
		UartDataRx_M4_M0_Cmd( );
		NOP( );

		// 	Radar A 		=============================================================
		UartDataRx_RadarA( );
		UartDataRx_RadarA_CMD( );

		// 	Radar B 		=============================================================
		UartDataRx_RadarB( );
		UartDataRx_RadarB_CMD( );

		// 	TL-SAM		==============================================================
		UartDataRx_TLSAM( );
		UartDataRx_TLSAM_CMD( );
		
		//	Chili2S 	==============================================================
		#if  SERCOM0_ENABLE
			UartDataRx_Chili2S( );
			UartDataRx_Chili2S_CMD( );
		#endif  	//#if  SERCOM0_ENABLE

		//==========================================================================
		//	CK I2C
		mgc3130_GetData( );

		//==========================================================================
		//	CK I2C
		//ICM20602_AlarmMsg( );



	  //	

	  //	TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


	  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	}   //while ( true )    {

  /* Execution should not come here during normal operation */

  return ( EXIT_FAILURE );
} 	//int main ( void )	

/*******************************************************************************
 End of File
*/

