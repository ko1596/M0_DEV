/*******************************************************************************
  NVIC PLIB Implementation

  Company:
    Microchip Technology Inc.

  File Name:
    plib_nvic.c

  Summary:
    NVIC PLIB Source File

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

//#include "device.h"
//#include "plib_nvic.h"

#include "All_Header.h"


// *****************************************************************************
// *****************************************************************************
// Section: NVIC Implementation
// *****************************************************************************
// *****************************************************************************

void NVIC_Initialize( void )
{
  NOP( );

  /* Enable NVIC Controller */
  __DMB();
  __enable_irq();


  NOP( );

    // Enable the interrupt sources and configure the priorities as configured
  //    from within the "Interrupt Manager" of MHC.
  #if   SERCOM0_ENABLE
    NVIC_SetPriority(SERCOM0_IRQn, 3);
    NVIC_EnableIRQ(SERCOM0_IRQn);
  #endif  //#if   SERCOM1_ENABLE

  // Enable the interrupt sources and configure the priorities as configured
  //    from within the "Interrupt Manager" of MHC.
  #if   SERCOM1_ENABLE
    NVIC_SetPriority(SERCOM1_IRQn, 3);
    NVIC_EnableIRQ(SERCOM1_IRQn);
  #endif  //#if   SERCOM1_ENABLE

  // Enable the interrupt sources and configure the priorities as configured
  //    from within the "Interrupt Manager" of MHC.
  #if   SERCOM2_ENABLE
    NVIC_SetPriority(SERCOM2_IRQn, 3);
    NVIC_EnableIRQ(SERCOM2_IRQn);
  #endif  //#if   SERCOM2_ENABLE

  // Enable the interrupt sources and configure the priorities as configured
  //    from within the "Interrupt Manager" of MHC.
  #if   SERCOM3_ENABLE
    NVIC_SetPriority(SERCOM3_IRQn, 3);
    NVIC_EnableIRQ(SERCOM3_IRQn);
  #endif  //#if   SERCOM1_ENABLE

  // Enable the interrupt sources and configure the priorities as configured
  //    from within the "Interrupt Manager" of MHC.
  #if   SERCOM4_ENABLE
    NVIC_SetPriority(SERCOM4_IRQn, 3);
    NVIC_EnableIRQ(SERCOM4_IRQn);
  #endif  //#if   SERCOM4_ENABLE

  // Enable the interrupt sources and configure the priorities as configured
  //    from within the "Interrupt Manager" of MHC.
  #if   SERCOM5_ENABLE
    NVIC_SetPriority(SERCOM5_IRQn, 3);
    NVIC_EnableIRQ(SERCOM5_IRQn);
  #endif  //#if   SERCOM1_ENABLE

  // Enable the interrupt sources and configure the priorities as configured
  //    from within the "Interrupt Manager" of MHC.
  NVIC_SetPriority(EIC_IRQn, 4);
  NVIC_EnableIRQ(EIC_IRQn);

  NOP( );
  return;
}
