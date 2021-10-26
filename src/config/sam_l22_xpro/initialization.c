/*******************************************************************************
  System Initialization File

  File Name:
    initialization.c

  Summary:
    This file contains source code necessary to initialize the system.

  Description:
    This file contains source code necessary to initialize the system.  It
    implements the "SYS_Initialize" function, defines the configuration bits,
    and allocates any necessary global system resources,
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*
  #include "definitions.h"
  #include "device.h"
*/

#include "All_Header.h"



// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************
#pragma config NVMCTRL_BOOTPROT = 0x7
#pragma config NVMCTRL_EEPROM_SIZE = 0x7
#pragma config BOD33USERLEVEL = 0x6
#pragma config BOD33_DIS = CLEAR
#pragma config BOD33_ACTION = 0x0
#pragma config WDT_ENABLE = CLEAR
#pragma config WDT_ALWAYSON = CLEAR
#pragma config WDT_PER = 0xB
#pragma config WDT_WINDOW = 0xB
#pragma config WDT_EWOFFSET = 0xB
#pragma config WDT_WEN = CLEAR
#pragma config BOD33_HYST = CLEAR
#pragma config NVMCTRL_REGION_LOCKS = 0xffff




// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: System Data
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Library/Stack Initialization Data
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: System Initialization
// *****************************************************************************
// *****************************************************************************



// *****************************************************************************
// *****************************************************************************
// Section: Local initialization functions
// *****************************************************************************
// *****************************************************************************




/*******************************************************************************
  Function:
    void SYS_Initialize ( void *data )

  Summary:
    Initializes the board, services, drivers, application and other modules.

  Remarks:
 */

void SYS_Initialize ( void* data )
{
  //uint8_t *tPtr;


  NVMCTRL_REGS->NVMCTRL_CTRLB = NVMCTRL_CTRLB_RWS(3);
  //NVMCTRL_REGS->NVMCTRL_CTRLB = NVMCTRL_CTRLB_RWS(10);
  //NVMCTRL_REGS->NVMCTRL_CTRLB = NVMCTRL_CTRLB_READMODE_NO_MISS_PENALTY | NVMCTRL_CTRLB_SLEEPPRM_WAKEONACCESS | NVMCTRL_CTRLB_RWS(1) | NVMCTRL_CTRLB_MANW_Msk;

  //============================================================================
  PM_Initialize();

  CLOCK_Initialize();

  SYSTICK_TimerInitialize();    //  D88-Add

  //============================================================================
  memset( (UINT8*)&sysInfo, 0x00, sizeof(M0_SYSTEM_INFO) );

  //============================================================================
  //PORT_Initialize();

  NVMCTRL_Initialize( );

  EVSYS_Initialize();  

  //EIC_Initialize( );            //  D88-Add
  


  //============================================================================
  //  SERCOM
  NOP( );
  #if   SERCOM0_ENABLE
    SERCOM0_USART_Initialize( );  //  Prj312_ALL
  #endif  //#if   SERCOM0_ENABLE

  #if   SERCOM1_ENABLE
    SERCOM1_USART_Initialize( );  //  Prj312_ALL
  #endif  //#if   SERCOM1_ENABLE

  #if   SERCOM2_ENABLE
    SERCOM2_USART_Initialize( );  //  D88-Add
  #endif  //#if   SERCOM2_ENABLE

  #if   SERCOM3_ENABLE
		SERCOM3_USART_Initialize( );  //  const unsigned char FW_PARKINGMETER_L22[32] = {"Prj312_ALL  20210104-0202T01"};      //  NO RTC
	#endif  //#if   SERCOM3_ENABLE

  #if   SERCOM4_ENABLE
    SERCOM4_USART_Initialize( );
  #endif  //#if   SERCOM4_ENABLE

  #if   SERCOM5_ENABLE
    SERCOM5_I2C_Initialize( );
  #endif  //#if   SERCOM5_ENABLE

	RTC_Initialize();
	

  //============================================================================
  NVIC_Initialize();  
  NOP( );

  //============================================================================
  #if ADC_ENABLE
    ADC_Initialize( );  
  #endif  //#if ADC_ENABLE

  //============================================================================
  tm_Event_Init( );

  //============================================================================
  //
  M0_GPIO_Initialize( );
  //LED_RGBY_Initialize( );

  //	MGC3130 		--------------------------------------------------------------
  //mgc3130_i2c_Init( );

  NOP( );


  //	XOUT32 ==> GPIO  PA01
  XOUT32_PA01_GPIO_Initialize( );
}  		//void SYS_Initialize ( void* data )


/*******************************************************************************
 End of File
*/
