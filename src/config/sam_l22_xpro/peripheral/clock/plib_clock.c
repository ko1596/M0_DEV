/*******************************************************************************
 CLOCK PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_clock.c

  Summary:
    CLOCK PLIB Implementation File.

  Description:
    None

*******************************************************************************/

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

//#include "plib_clock.h"
//#include "device.h"
#include "All_Header.h"




static void OSCCTRL_Initialize(void)
{
    /**************** OSC16M IniTialization *************/
    OSCCTRL_REGS->OSCCTRL_OSC16MCTRL = OSCCTRL_OSC16MCTRL_FSEL(0x0) | OSCCTRL_OSC16MCTRL_ENABLE_Msk;
}


//==============================================================================
//  238/1092    22. OSC32KCTRL – 32KHz Oscillators Controller
static void OSC32KCTRL_Initialize(void)
{
  
  //OSC32KCTRL_REGS->OSC32KCTRL_RTCCTRL = OSC32KCTRL_RTCCTRL_RTCSEL(0);
  //OSC32KCTRL_REGS->OSC32KCTRL_SLCDCTRL = 0;  

  // Configure 32K External Oscillator   ----------------------------------------
    NOP( );
#if !Prj311_ALL_EnabldeTst01
  //	const unsigned char FW_PARKINGMETER_L22[32] = {"Prj311_ALL 20210127-0206002"};  
  OSC32KCTRL_REGS->OSC32KCTRL_XOSC32K = 
          OSC32KCTRL_XOSC32K_STARTUP(3)       // 1s
          | OSC32KCTRL_XOSC32K_ENABLE_Msk 
          | OSC32KCTRL_XOSC32K_EN32K_Msk 
          | OSC32KCTRL_XOSC32K_EN1K_Msk
          //| OSC32KCTRL_XOSC32K_XTALEN_Msk;
          | OSC32KCTRL_XOSC32K_XTALEN_Pos; 		//	!!! RTC NoWrok !!!

#else
	//	const unsigned char FW_PARKINGMETER_L22[32] = {"Prj311_ALL 20210128-0206003"};
  OSC32KCTRL_REGS->OSC32KCTRL_XOSC32K = 
          OSC32KCTRL_XOSC32K_STARTUP(3)       // 1s
          | OSC32KCTRL_XOSC32K_ENABLE_Msk 
          | OSC32KCTRL_XOSC32K_EN32K_Pos 
          | OSC32KCTRL_XOSC32K_EN1K_Msk
          | OSC32KCTRL_XOSC32K_XTALEN_Pos;
#endif 	//#if !Prj311_ALL_EnabldeTst01


  /*
  OSC32KCTRL_REGS->OSC32KCTRL_XOSC32K = 
          OSC32KCTRL_XOSC32K_STARTUP(3)       // 1s
  				//OSC32KCTRL_XOSC32K_STARTUP(0)       // 0.06s
          | OSC32KCTRL_XOSC32K_ENABLE_Msk 
          | OSC32KCTRL_XOSC32K_EN32K_Msk 
          | OSC32KCTRL_XOSC32K_EN1K_Msk
          | OSC32KCTRL_XOSC32K_XTALEN_Msk
          //| OSC32KCTRL_XOSC32K_WRTLOCK_Pos
          | OSC32KCTRL_XOSC32K_WRTLOCK_Msk
          //| OSC32KCTRL_XOSC32K_ENABLE_Pos;
          | OSC32KCTRL_XOSC32K_ENABLE_Msk;
          */




 	//	const unsigned char FW_PARKINGMETER_L22[32] = {"Prj311_ALL 20210112-0205010"};      // sercom3 D modified
  while(!((OSC32KCTRL_REGS->OSC32KCTRL_STATUS & OSC32KCTRL_STATUS_XOSC32KRDY_Msk) == OSC32KCTRL_STATUS_XOSC32KRDY_Msk))   {
      // Waiting for the XOSC32K Ready state
  }
  NOP( );



  OSC32KCTRL_REGS->OSC32KCTRL_SLCDCTRL = 0;
	OSC32KCTRL_REGS->OSC32KCTRL_RTCCTRL = OSC32KCTRL_RTCCTRL_RTCSEL(4);    // XOSC1K 1.024kHz from 32KHz external oscillator
  //OSC32KCTRL_REGS->OSC32KCTRL_RTCCTRL = OSC32KCTRL_RTCCTRL_RTCSEL(5);    // XOSC32K 32.768kHz from 32KHz external crystal oscillator
  //	const unsigned char FW_PARKINGMETER_L22[32] = {"Prj311_ALL 20210112-0205010"};      // sercom3 D modified

  while( (OSC32KCTRL_REGS->OSC32KCTRL_STATUS & 0x01) == 0 )   {
    NOP( );
  }	

  	
  NOP( );
}   //static void OSC32KCTRL_Initialize(void)


static void FDPLL_Initialize(void)
{
	GCLK_REGS->GCLK_PCHCTRL[1] = GCLK_PCHCTRL_GEN(0x1)  | GCLK_PCHCTRL_CHEN_Msk;
  /*
	while ((GCLK_REGS->GCLK_PCHCTRL[1] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)    {
        // Wait for synchronization
  }
  */

    /****************** DPLL Initialization  *********************************/

    /* Configure DPLL    */
    OSCCTRL_REGS->OSCCTRL_DPLLCTRLB = OSCCTRL_DPLLCTRLB_FILTER(0) | OSCCTRL_DPLLCTRLB_LTIME(0)| OSCCTRL_DPLLCTRLB_REFCLK(2) ;


    OSCCTRL_REGS->OSCCTRL_DPLLRATIO = OSCCTRL_DPLLRATIO_LDRFRAC(0) | OSCCTRL_DPLLRATIO_LDR(63);
    /*
    while((OSCCTRL_REGS->OSCCTRL_DPLLSYNCBUSY & OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Msk) == OSCCTRL_DPLLSYNCBUSY_DPLLRATIO_Msk)    {
        // Waiting for the synchronization
    }
    */

    /* Selection of the DPLL Enable */
    OSCCTRL_REGS->OSCCTRL_DPLLCTRLA = OSCCTRL_DPLLCTRLA_ENABLE_Msk   ;
    /*
    while((OSCCTRL_REGS->OSCCTRL_DPLLSYNCBUSY & OSCCTRL_DPLLSYNCBUSY_ENABLE_Msk) == OSCCTRL_DPLLSYNCBUSY_ENABLE_Msk )   {
        // Waiting for the DPLL enable synchronization
    }
    while((OSCCTRL_REGS->OSCCTRL_DPLLSTATUS & (OSCCTRL_DPLLSTATUS_LOCK_Msk | OSCCTRL_DPLLSTATUS_CLKRDY_Msk)) !=
                (OSCCTRL_DPLLSTATUS_LOCK_Msk | OSCCTRL_DPLLSTATUS_CLKRDY_Msk))    {
        // Waiting for the Ready state
    }
    */
}


static void GCLK0_Initialize(void)
{
    
    GCLK_REGS->GCLK_GENCTRL[0] = GCLK_GENCTRL_DIV(2) | GCLK_GENCTRL_SRC(7) | GCLK_GENCTRL_GENEN_Msk;

    while((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL0_Msk) == GCLK_SYNCBUSY_GENCTRL0_Msk)
    {
        /* wait for the Generator 0 synchronization */
    }
}


static void GCLK1_Initialize(void)
{
    GCLK_REGS->GCLK_GENCTRL[1] = GCLK_GENCTRL_DIV(4) | GCLK_GENCTRL_SRC(5) | GCLK_GENCTRL_GENEN_Msk;

    while((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL1_Msk) == GCLK_SYNCBUSY_GENCTRL1_Msk)
    {
        /* wait for the Generator 1 synchronization */
    }
}


/*
static void GCLK2_Initialize(void)
{
    GCLK_REGS->GCLK_GENCTRL[2] = GCLK_GENCTRL_DIV(1) | GCLK_GENCTRL_SRC(4) | GCLK_GENCTRL_GENEN_Msk;

    while((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL2_Msk) == GCLK_SYNCBUSY_GENCTRL2_Msk)
    {
        // wait for the Generator 2 synchronization
    }
}
*/

/*
static void GCLK3_Initialize(void)
{
    GCLK_REGS->GCLK_GENCTRL[3] = GCLK_GENCTRL_DIV(1) | GCLK_GENCTRL_SRC(6) | GCLK_GENCTRL_GENEN_Msk;

    while((GCLK_REGS->GCLK_SYNCBUSY & GCLK_SYNCBUSY_GENCTRL3_Msk) == GCLK_SYNCBUSY_GENCTRL3_Msk)
    {
        // wait for the Generator 3 synchronization
    }
}
*/




//******************************************************************************
//
//******************************************************************************
void CLOCK_Initialize (void)
{
  /* Function to Initialize the Oscillators */
  OSCCTRL_Initialize();

  /* Function to Initialize the 32KHz Oscillators */
  OSC32KCTRL_Initialize();

  /*Initialize Backup Divider*/    
  MCLK_REGS->MCLK_BUPDIV = MCLK_BUPDIV_BUPDIV(0x04);

  GCLK1_Initialize();
  FDPLL_Initialize();
  GCLK0_Initialize();

  //GCLK2_Initialize( );
  //GCLK3_Initialize( );


  /* Selection of the Generator and write Lock for OSCCTRL_FDPLL */
  GCLK_REGS->GCLK_PCHCTRL[1] = GCLK_PCHCTRL_GEN(0x1)  | GCLK_PCHCTRL_CHEN_Msk;
  while ((GCLK_REGS->GCLK_PCHCTRL[1] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)
  {
    /* Wait for synchronization */
  }


  //============================================================================
  //  Table 16-9. PCHCTRLm Mapping    135 / 1092
  //----------------------------------------------------------------------------
  // Selection of the Generator and write Lock for EIC  ========================
  GCLK_REGS->GCLK_PCHCTRL[3] = GCLK_PCHCTRL_GEN(0x0)  | GCLK_PCHCTRL_CHEN_Msk;
  while ((GCLK_REGS->GCLK_PCHCTRL[3] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)
  {
    /* Wait for synchronization */
  }


  //============================================================================
  //  SERCOM CLOCK  ============================================================
  //  GCLK - Generic Clock Controller : 126 / 1092

  //----------------------------------------------------------------------------
  //  SPI - LED control
  #if   SERCOM5_ENABLE
    GCLK_REGS->GCLK_PCHCTRL[21] = GCLK_PCHCTRL_GEN(0x0)  | GCLK_PCHCTRL_CHEN_Msk;
    while ((GCLK_REGS->GCLK_PCHCTRL[21] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)
    {
      /* Wait for synchronization */
    }
  #endif  //#if   SERCOM5_ENABLE

  //----------------------------------------------------------------------------
  //  UART - Radar B
  #if   SERCOM4_ENABLE
    GCLK_REGS->GCLK_PCHCTRL[20] = GCLK_PCHCTRL_GEN(0x0)  | GCLK_PCHCTRL_CHEN_Msk;
    while ((GCLK_REGS->GCLK_PCHCTRL[20] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)
    {
      /* Wait for synchronization */
    }
  #endif  //#if   SERCOM4_ENABLE

  //----------------------------------------------------------------------------  
  //  UART - Radar A
  #if   SERCOM3_ENABLE
    GCLK_REGS->GCLK_PCHCTRL[19] = GCLK_PCHCTRL_GEN(0x0)  | GCLK_PCHCTRL_CHEN_Msk;
    while ((GCLK_REGS->GCLK_PCHCTRL[19] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)
    {
      /* Wait for synchronization */
    }
  #endif  //#if   SERCOM3_ENABLE

  //----------------------------------------------------------------------------
  //  UART ISO7816 - SAM
  #if   SERCOM2_ENABLE
    GCLK_REGS->GCLK_PCHCTRL[18] = GCLK_PCHCTRL_GEN(0x0)  | GCLK_PCHCTRL_CHEN_Msk;
    while ((GCLK_REGS->GCLK_PCHCTRL[18] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)
    {
      /* Wait for synchronization */
    }
  #endif  //#if   SERCOM2_ENABLE

  //----------------------------------------------------------------------------
  //  UART - i.MX8MM M4 
  #if   SERCOM1_ENABLE
    GCLK_REGS->GCLK_PCHCTRL[17] = GCLK_PCHCTRL_GEN(0x0)  | GCLK_PCHCTRL_CHEN_Msk;
    while ((GCLK_REGS->GCLK_PCHCTRL[17] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)
    {
      /* Wait for synchronization */
    }
  #endif  //#if   SERCOM1_ENABLE

  //----------------------------------------------------------------------------
  //  UART - RHMe Module
  #if   SERCOM0_ENABLE
    GCLK_REGS->GCLK_PCHCTRL[16] = GCLK_PCHCTRL_GEN(0x0)  | GCLK_PCHCTRL_CHEN_Msk;
    while ((GCLK_REGS->GCLK_PCHCTRL[16] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)
    {
      /* Wait for synchronization */
    }
  #endif  //#if   SERCOM0_ENABLE


  //----------------------------------------------------------------------------
  // ADC Clock;   Table 16-9. PCHCTRLm Mapping  135/1092
  #if ADC_ENABLE
    GCLK_REGS->GCLK_PCHCTRL[25] = GCLK_PCHCTRL_GEN(0x0)  | GCLK_PCHCTRL_CHEN_Msk;
    while ((GCLK_REGS->GCLK_PCHCTRL[25] & GCLK_PCHCTRL_CHEN_Msk) != GCLK_PCHCTRL_CHEN_Msk)
    {
      // Wait for synchronization
    }
  #endif //#if ADC_ENABLE

}