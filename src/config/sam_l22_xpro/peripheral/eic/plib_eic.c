/*******************************************************************************
  External Interrupt Controller (EIC) PLIB

  Company
    Microchip Technology Inc.

  File Name
    plib_eic.c

  Summary
    Source for EIC peripheral library interface Implementation.

  Description
    This file defines the interface to the EIC peripheral library. This
    library provides access to and control of the associated peripheral
    instance.

  Remarks:
    None.

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
/* This section lists the other files that are included in this file.
*/

//#include "plib_eic.h"
#include "All_Header.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data
// *****************************************************************************
// *****************************************************************************

/* EIC Channel Callback object */
EIC_CALLBACK_OBJ    eicCallbackObject[EXTINT_COUNT];




// *****************************************************************************
//
// *****************************************************************************
/*
  typedef struct
  {   //  External Interrupt Controller
    __IO  uint8_t                        EIC_CTRLA;          //  Offset: 0x00 (R/W  8) Control
    __IO  uint8_t                        EIC_NMICTRL;        //  Offset: 0x01 (R/W  8) NMI Control
    __IO  uint16_t                       EIC_NMIFLAG;        //  Offset: 0x02 (R/W  16) NMI Interrupt Flag
    __I   uint32_t                       EIC_SYNCBUSY;       //  Offset: 0x04 (R/   32) Syncbusy register
    __IO  uint32_t                       EIC_EVCTRL;         //  Offset: 0x08 (R/W  32) Event Control
    __IO  uint32_t                       EIC_INTENCLR;       //  Offset: 0x0C (R/W  32) Interrupt Enable Clear
    __IO  uint32_t                       EIC_INTENSET;       //  Offset: 0x10 (R/W  32) Interrupt Enable Set
    __IO  uint32_t                       EIC_INTFLAG;        //  Offset: 0x14 (R/W  32) Interrupt Flag Status and Clear
    __IO  uint32_t                       EIC_ASYNCH;         //  Offset: 0x18 (R/W  32) EIC Asynchronous edge Detection Enable
    __IO  uint32_t                       EIC_CONFIG[2];      //  Offset: 0x1C (R/W  32) Configuration n
  } eic_registers_t;
*/
void EIC_Initialize (void)
{
		//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
}   //void EIC_Initialize (void)




void EIC_InterruptEnable (EIC_PIN pin)
{
    EIC_REGS->EIC_INTENSET = (1UL << pin);
}

void EIC_InterruptDisable (EIC_PIN pin)
{
    EIC_REGS->EIC_INTENCLR = (1UL << pin);
}

void EIC_CallbackRegister(EIC_PIN pin, EIC_CALLBACK callback, uintptr_t context)
{
    if (eicCallbackObject[pin].eicPinNo == pin)
    {
        eicCallbackObject[pin].callback = callback;

        eicCallbackObject[pin].context  = context;
    }
}






















// *****************************************************************************
//
// *****************************************************************************
//void EIC_InterruptHandler(void)
void EIC_Handler( void )
{
  uint8_t currentChannel;
  uint32_t  ck_bit;

  UINT8		 data;


  //	P 433/1092,		27.8.8 Interrupt Flag Status and Clear
  EIC_IntFlagStatus = EIC_REGS->EIC_INTFLAG;
  NOP( );


  for (currentChannel = 0; currentChannel < EXTINT_COUNT; currentChannel++)   {
    ck_bit = (1UL << currentChannel);
    NOP( );

    if( EIC_IntFlagStatus & ck_bit )  {
      NOP( );

      //========================================================================
      //	PC08-EIC/EXTINT[0], MGC3130-TS      ----------------------------------
      //1
      if( EIC_IntFlagStatus & 0x0001 ) {
      	flg_mgc_ts = 1;
      } 

      //	PC09 EIC/EXTINT[1], ICM20602-INT  	----------------------------------
      //	PC09 EIC/EXTINT[1], STK8BA53-INT  	----------------------------------
      else if( EIC_IntFlagStatus & 0x0002 ) {
				NOP( );
				sercom5_i2cm_End( );
				
				i2c_interface.i2c_addr = 0;
				i2c_interface.STATE = 0;

				//	TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				//STK8BA53_i2c_Read( 0x09, &M0_AllDevStatus.g_sensor.stk8ba53.INTSTS1, 1 );
				//STK8BA53_i2c_Read( 0x0A, &M0_AllDevStatus.g_sensor.stk8ba53.INTSTS2, 1 );

				if( M0_AllDevStatus.g_sensor.stk8ba53.flg_INT == 0 ) 	{
					M0_AllDevStatus.g_sensor.stk8ba53.flg_INT = 1;
					M0_AllDevStatus.g_sensor.stk8ba53.acc_INT_X = M0_AllDevStatus.g_sensor.stk8ba53.acc_INT_Y = M0_AllDevStatus.g_sensor.stk8ba53.acc_INT_Z = 0;
					tm_STK8BA53_INT_start = setup_timer( STK8BA53_INT_READ_PERIOD, 0, (void (*)())TimerF_STK8BA53_INT, NULL );
					TimerF_STK8BA53_INT( );
					NOP( );
				}

				data = 0x80;  		//	INT_RST
				STK8BA53_i2c_Write( 0x21, &data, 1 );

      	//ICM20602_acc_Read_INT( );
      	//flg_g_sensor_INT = 1;
      	NOP( );
      } 

      //	PA27	EIC/EXTINT[15]  	Chili2S Wake M0  -----------------------------
      else if( EIC_IntFlagStatus & 0x8000 ) {
      	NOP( );
      	NOP( );
      	NOP( );
      }  		//else if( EIC_IntFlagStatus & 0x8000 ) {

      //	PB04-EIC/EXTINT[4], Button - Test Mode 		----------------------------
      //	10000 	0x10
      else if( EIC_IntFlagStatus & 0x0010 ) {
      	NOP( );
      }       

      //	PB05-EIC/EXTINT[5], Button - Burn/ QC Mode  		----------------------
      //	100000 	0x20
      else if( EIC_IntFlagStatus & 0x0020 ) {
      }       

      // TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      #if   Tst_EVK_LED_TST1

      	//  PC01-EIC/EXTINT[9], SW0
        else if( EIC_IntFlagStatus & 0x0200 ) {
          if( tm_evk_led->Title == TIMER_FRAME_TITLE )  {
            NOP( );
            tm_evk_led->period_count += 25;
          }
        }   //if( EIC_IntFlagStatus & 0x0200 ) {

      #endif  //#if   Tst_EVK_LED_TST1


      EIC_REGS->EIC_INTFLAG = (1UL << currentChannel);    //  Clear interrupt flag
    }   //if( EIC_IntFlagStatus & ck )  {

  }   //for (currentChannel = 0; currentChannel < EXTINT_COUNT; currentChannel++)   {

  NOP( );
}     //void EIC_Handler( void )

