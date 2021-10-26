/*******************************************************************************
  Analog-to-Digital Converter(ADC) PLIB

  Company
    Microchip Technology Inc.

  File Name
    plib_adc.h

  Summary
    ADC PLIB Header File.

  Description
    This file defines the interface to the ADC peripheral library. This
    library provides access to and control of the associated peripheral
    instance.

  Remarks:
    None.

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef PLIB_ADC_H      // Guards against multiple inclusion
#define PLIB_ADC_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/

#include "device.h"
#include "plib_adc_common.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus // Provide C Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/* The following data type definitions are used by the functions in this
    interface and should be considered part it.
*/

// *****************************************************************************
//	define

//	const unsigned char FW_PARKINGMETER_L22[32] = {"Prj311_ALL       20210331-020400"};
//	A Battery - ADC	A 		Battery 電壓偵測				PA02- AIN[0]
//	B Battery - ADC	B 		Battery 電壓偵測				PA06- AIN[6]
//	Solar Battery - ADC	B Battery 電壓偵測				PB06- AIN[14]
#define 	ADC_BATTERY_A_AIN 			ADC_POSINPUT_AIN0
#define 	ADC_BATTERY_B_AIN 			ADC_POSINPUT_AIN6
#define 	ADC_BATTERY_SOLAR_AIN 	ADC_POSINPUT_AIN14


//==============================================================================
#define  	ADC_BAT_A_FACTOR  			2554
#define  	ADC_BAT_B_FACTOR  			2484


// 	TEST 	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// const unsigned char FW_PARKINGMETER_L22[32] = {"Prj311_ALL   20201225-0201T02"};      //  NO RTC
//#define 	ADC_BATTERY_A_AIN 		ADC_POSINPUT_AIN4
//#define 	ADC_BATTERY_B_AIN 		ADC_POSINPUT_AIN5




//  ****************************************************************************
//  Global
extern UINT16  adc_channel;
extern TIMER*  tm_Get_ADC;
extern TIMER*  tm_CK_BAT_logic;


#if 	Tst_ADC_01
	extern TIMER*  tm_ADC_2A53;
#endif 	//#if 	Tst_ADC_01




// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************
/* The following functions make up the methods (set of possible operations) of
    this interface.
*/

void ADC_Initialize( void );

void ADC_Enable( void );

void ADC_Disable( void );

void ADC_ChannelSelect( ADC_POSINPUT positiveInput, ADC_NEGINPUT negativeInput );

void ADC_ConversionStart( void );

uint16_t ADC_ConversionResultGet( void );

void ADC_ComparisonWindowSet(uint16_t low_threshold, uint16_t high_threshold);

void ADC_WindowModeSet(ADC_WINMODE mode);

bool ADC_ConversionSequenceIsFinished(void);


bool ADC_ConversionStatusGet( void );


//  **************************************************************************************
void  TimerF_ADC_DATA( void );
void  TimerF_ckBAT_logic( void );


#if 	Tst_ADC_01
	void  TimerF_ADC_2A53(void);
#endif 	//#if 	Tst_ADC_01


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END

#endif /* PLIB_ADC_H */
