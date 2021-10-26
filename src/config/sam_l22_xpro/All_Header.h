

// *****************************************************************************
//==============================================================================
//------------------------------------------------------------------------------
//..............................................................................
//______________________________________________________________________________

#ifndef ALL_HEADER_H
#define ALL_HEADER_H




//******************************************************************************
//  System Defined
//#define 	MCU_ATSAML22N18A 		1
#define 	MCU_ATSAML22N17A 		1

#define   UART_CRC16_CHECK		1

#define   SERCOM0_ENABLE    1 			//	Chili2S 
#define   SERCOM1_ENABLE    1 			//	i.MX8MM M4 通訊
#define   SERCOM2_ENABLE    1 			//	ISO7816-UART
#define   SERCOM3_ENABLE    1 			//	Radar A
#define   SERCOM4_ENABLE    1 			//	Radar B
#define   SERCOM5_ENABLE    1

#define   ADC_ENABLE        1




//  TEST  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#define 	Tst_Radar_Send_AllData		1

#define 	Tst_PRE_SHOOT_ENABLE				1


//    TEST  ====================================================================
//#define   Tst_EVK_LED_TST1    1

//#define   Tst_SET_RTC         1

//#define   Tst_RTC_DISABLE    1

//#define 	Tst_LEDtstRTC 			1

//	MGC3130 TEST 		------------------------------------------------------------

//	Radar-A TEST 		------------------------------------------------------------

//	Radar Power Off/On Test 	..................................................

//	A53 Sleep /Wakeup  Test 	..................................................


//	ADC TEST 		----------------------------------------------------------------
//#define 	Tst_ADC_01					1

//	ICM20602 TEST 		----------------------------------------------------------
//#define 	Tst_ICM_I2C					1
//#define 	Tst_ICM_01					1

//#define 	Tst_STK8BA53_01					1

//#define 	Tst_STK8BA53_NORMAL_SHOW	1


//	A53 Wake Up 		------------------------------------------------------------
//#define 	Tst_CK_A53_WAKEUP				1
//#define 	Tst_A53_WAKEUP					1


//	TL-SAM 		------------------------------------------------------------------
#define 	Tst_TLSAM_01 				1

//	LM75A 		------------------------------------------------------------------
//#define 	Tst_LM75_01 				1


//	UART, A53-M0 TxRx Test 	----------------------------------------------------
#define 	Tst_UART_A53M0_TxRx		1


//	Power Test 	----------------------------------------------------------------
//#define 	Tst_PW_BAT01 					1
//#define 	Tst_A53_SLEEP_STATE			1

#define 	Tst_LTC2944_CK 					1


//	SERCOM0 Chili2S UART  	----------------------------------------------------
#if  SERCOM0_ENABLE

	//#define 	Tst_Chili2S_UART 				1
	//#define 	Tst_Chili2S_LIDAR 			1

#endif  	//#if  SERCOM0_ENABLE











//******************************************************************************
#include <stdio.h>
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <string.h>
#include "definitions.h"                // SYS function prototypes


//------------------------------------------------------------------------------
#include "device.h"
#include <stdint.h>


//------------------------------------------------------------------------------
#include <All_define.h>

//==============================================================================
#include "git/tm_event.h"

#include "git/global.h"
#include "git/gpio.h"
#include "git/time.h"
#include "git/comm.h"
#include "git/uart_M4.h"
#include "git/mgc3130.h"
#include "git/lm75.h"
#include "git/LTC2944.h"
#include "git/eeprom.h"
//#include "git/g_icm20602.h"
#include "git/g_stk8ba53.h"

#include "git/PreShooting_header.h"


//==============================================================================
#include "peripheral/nvmctrl/plib_nvmctrl.h"
#include "peripheral/evsys/plib_evsys.h"

#include "peripheral/port/plib_port.h"
#include "peripheral/port/plib_port2.h"

#include "peripheral/clock/plib_clock.h"
#include "peripheral/nvic/plib_nvic.h"
#include "peripheral/systick/plib_systick.h"
#include "peripheral/pm/plib_pm.h"

#include "peripheral/eic/plib_eic.h"

#include "peripheral/sercom5/i2cm/sercom5_i2cm.h"
#include "peripheral/sercom4/uart/sercom4_uart.h"
#include "peripheral/sercom3/uart/sercom3_uart.h"
#include "peripheral/sercom2/uart/sercom2_uart.h"
#include "peripheral/sercom1/uart/sercom1_uart.h"
#include "peripheral/sercom0/uart/sercom0_uart.h"

#include "peripheral/adc/plib_adc.h"
#include "peripheral/adc/plib_adc_common.h"







//******************************************************************************
//  Defined



//******************************************************************************
//  Global
extern  SYSTICK_OBJECT systick;

//extern  uint8_t FW_PARKINGMETER_L22[];
extern  const unsigned char FW_PARKINGMETER_L22[];



//******************************************************************************




#endif // ALL_HEADER_H

