 /*******************************************************************************
  Analog-to-Digital Converter(ADC) PLIB

  Company
    Microchip Technology Inc.

  File Name
    plib_adc.c

  Summary
    ADC PLIB Implementation File.

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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/

//#include "plib_adc.h"
#include "All_Header.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data
// *****************************************************************************
// *****************************************************************************

#define ADC_LINEARITY_POS  (0)
#define ADC_LINEARITY_Msk   (0x7 << ADC_LINEARITY_POS)

#define ADC_BIASCAL_POS  (3)
#define ADC_BIASCAL_Msk   (0x7 << ADC_BIASCAL_POS)

// *****************************************************************************
// *****************************************************************************
// Section: ADC Implementation
// *****************************************************************************
// *****************************************************************************


//	const unsigned char FW_PARKINGMETER_L22[32] = {"Prj311_ALL       20210331-020400"};
//	A Battery - ADC	A 		Battery 電壓偵測				PA02- AIN[0]
//	B Battery - ADC	B 		Battery 電壓偵測				PA06- AIN[6]
//	Solar Battery - ADC	B Battery 電壓偵測				PB06- AIN[14]


//  ****************************************************************************
//  Global
	UINT16  adc_channel;
	TIMER*  tm_Get_ADC;

	TIMER*  tm_CK_BAT_logic;


//  TEST    --------------------------------------------------------------------
#if 	Tst_ADC_01
	TIMER*  tm_ADC_2A53;
#endif 	//#if 	Tst_ADC_01



// *****************************************************************************
// Initialize ADC module



//  ****************************************************************************
//
//  ****************************************************************************
//  p871/1092,  41.6.2.1 Initialization
//  p881/1092,  41.7 Register Summary
void ADC_Initialize( void )
{
	//============================================================================
	/*
	  #if ADC_ENABLE
	    PORT_REGS->GROUP[0].PORT_PINCFG[4] = 0x1;    //  The peripheral multiplexer selection is enabled
	    PORT_REGS->GROUP[0].PORT_PINCFG[5] = 0x1;    //  The peripheral multiplexer selection is enabled
	    //  4/2=2; 5/2=2.5;
	    PORT_REGS->GROUP[0].PORT_PMUX[2] = 0x11;     //  Peripheral function B selected
	  #endif  //#if ADC_ENABLE
	*/	



	//============================================================================
	/* Reset ADC */
	ADC_REGS->ADC_CTRLA = ADC_CTRLA_SWRST_Msk;
	while((ADC_REGS->ADC_SYNCBUSY & ADC_SYNCBUSY_SWRST_Msk) == ADC_SYNCBUSY_SWRST_Msk)
	{
	  // Wait for Synchronization
	}

	// Write linearity calibration in BIASREFBUF and bias calibration in BIASCOMP
	ADC_REGS->ADC_CALIB = (uint32_t)(ADC_CALIB_BIASREFBUF(((*(uint64_t*)OTP5_ADDR) & ADC_LINEARITY_Msk))) \
	  | ADC_CALIB_BIASCOMP((((*(uint64_t*)OTP5_ADDR) & ADC_BIASCAL_Msk) >> ADC_BIASCAL_POS));

	// Prescaler
	ADC_REGS->ADC_CTRLB = ADC_CTRLB_PRESCALER_DIV2;
	// Sampling length
	ADC_REGS->ADC_SAMPCTRL = ADC_SAMPCTRL_SAMPLEN(8);

	// Reference
	ADC_REGS->ADC_REFCTRL = ADC_REFCTRL_REFSEL_INTVCC2;
	//ADC_REGS->ADC_REFCTRL = ADC_REFCTRL_REFSEL_INTREF;

	// Input pin
	//ADC_REGS->ADC_INPUTCTRL = (uint16_t) ADC_POSINPUT_AIN0;
	//ADC_REGS->ADC_INPUTCTRL = (uint16_t)ADC_POSINPUT_AIN0 | (uint16_t)ADC_POSINPUT_AIN6;

	// Resolution & Operation Mode
	//ADC_REGS->ADC_CTRLC = ADC_CTRLC_RESSEL_12BIT | ADC_CTRLC_WINMODE(0) | ADC_CTRLC_FREERUN_Msk;
	//ADC_REGS->ADC_CTRLC = ADC_CTRLC_RESSEL_12BIT | ADC_CTRLC_WINMODE(0) ;
	ADC_REGS->ADC_CTRLC = ADC_CTRLC_RESSEL_12BIT;


	// Clear all interrupt flags
	//ADC_REGS->ADC_INTFLAG = ADC_INTFLAG_Msk;
	// Enable interrupts
	//ADC_REGS->ADC_INTENSET = ADC_INTENSET_RESRDY_Msk;
	while(ADC_REGS->ADC_SYNCBUSY)
	{
	  // Wait for Synchronization
	}


	//============================================================================
	//memset( ((UINT8*)adc_data), 0x00, sizeof(M0_POWER_DATA_FRAME) );
	M0_AllDevStatus.adc_pw.adc0 = M0_AllDevStatus.adc_pw.adc1 = M0_AllDevStatus.adc_pw.adc2 = M0_AllDevStatus.adc_pw.adc3 = 0;
	M0_AllDevStatus.TstCnt = 0;
	//adc_channel = 0;

	//ADC_ChannelSelect( ADC_POSINPUT_AIN0, ADC_INPUTCTRL_MUXNEG_GND );
	//ADC_ChannelSelect( ADC_POSINPUT_AIN0 | ADC_POSINPUT_AIN6, ADC_INPUTCTRL_MUXNEG_GND );

	//ADC_Enable( );
}   //void ADC_Initialize( void )



/* Enable ADC module */
void ADC_Enable( void )
{
    ADC_REGS->ADC_CTRLA |= ADC_CTRLA_ENABLE_Msk;
    while(ADC_REGS->ADC_SYNCBUSY)
    {
        /* Wait for Synchronization */
    }
}

/* Disable ADC module */
void ADC_Disable( void )
{
    ADC_REGS->ADC_CTRLA &= ~ADC_CTRLA_ENABLE_Msk;
    while(ADC_REGS->ADC_SYNCBUSY)
    {
        /* Wait for Synchronization */
    }
}

/* Configure channel input */
void ADC_ChannelSelect( ADC_POSINPUT positiveInput, ADC_NEGINPUT negativeInput )
{
    /* Configure pin scan mode and positive and negative input pins */
    ADC_REGS->ADC_INPUTCTRL = (uint16_t) positiveInput | (uint16_t) negativeInput;

    while((ADC_REGS->ADC_SYNCBUSY & ADC_SYNCBUSY_INPUTCTRL_Msk) == ADC_SYNCBUSY_INPUTCTRL_Msk)
    {
        /* Wait for Synchronization */
    }
}

/* Start the ADC conversion by SW */
void ADC_ConversionStart( void )
{
    /* Start conversion */
    ADC_REGS->ADC_SWTRIG |= ADC_SWTRIG_START_Msk;

    while((ADC_REGS->ADC_SYNCBUSY & ADC_SYNCBUSY_SWTRIG_Msk) == ADC_SYNCBUSY_SWTRIG_Msk)
    {
        /* Wait for Synchronization */
    }
}

/* Check whether auto sequence conversion is done */
bool ADC_ConversionSequenceIsFinished(void)
{
    bool seq_status = false;
    if ((ADC_REGS->ADC_SEQSTATUS & ADC_SEQSTATUS_SEQBUSY_Msk) != ADC_SEQSTATUS_SEQBUSY_Msk)
    {
        seq_status = true;
    }
    return seq_status;
}

/* Configure window comparison threshold values */
void ADC_ComparisonWindowSet(uint16_t low_threshold, uint16_t high_threshold)
{
    ADC_REGS->ADC_WINLT = low_threshold;
    ADC_REGS->ADC_WINUT = high_threshold;
    while((ADC_REGS->ADC_SYNCBUSY))
    {
        /* Wait for Synchronization */
    }
}

void ADC_WindowModeSet(ADC_WINMODE mode)
{
    ADC_REGS->ADC_CTRLC &= ~ADC_CTRLC_WINMODE_Msk;
    ADC_REGS->ADC_CTRLC |= (mode << ADC_CTRLC_WINMODE_Pos);
    while((ADC_REGS->ADC_SYNCBUSY))
    {
        /* Wait for Synchronization */
    }
}

/* Read the conversion result */
uint16_t ADC_ConversionResultGet( void )
{
    return (uint16_t)ADC_REGS->ADC_RESULT;
}

/* Check whether result is ready */
bool ADC_ConversionStatusGet( void )
{
    bool status;
    status =  (bool)((ADC_REGS->ADC_INTFLAG & ADC_INTFLAG_RESRDY_Msk) >> ADC_INTFLAG_RESRDY_Pos);
    if (status == true)
    {
        ADC_REGS->ADC_INTFLAG = ADC_INTFLAG_RESRDY_Msk;
    }
    return status;
}












//	const unsigned char FW_PARKINGMETER_L22[32] = {"Prj311_ALL       20210331-020400"};
//	A Battery - ADC	A 		Battery 電壓偵測				PA02- AIN[0]
//	B Battery - ADC	B 		Battery 電壓偵測				PA06- AIN[6]
//	Solar Battery - ADC	B Battery 電壓偵測				PB06- AIN[14]
/*
	typedef struct  {	
	  UINT32 adc0;
	  UINT32 adc1;
	  UINT32 adc2;
	  UINT32 adc3;
	  M0_RTC_TIME_FRAME  mcu_RTC;
	}M0_POWER_DATA_FRAME;
*/

//  ****************************************************************************
//
//  ****************************************************************************
void  TimerF_ADC_DATA(void)
{
	reset_timer( tm_Get_ADC );

	//============================================================================
	/*
	M0_AllDevStatus.adc_pw.pw_EN = 0x00;
	if( PW_SOLAR_EN_Get() == 0 )	{
		M0_AllDevStatus.adc_pw.pw_EN |= PW_EN_SOLAR;
	}
	else if( PW_DC_EN_Get() == 0 )	{
		M0_AllDevStatus.adc_pw.pw_EN |= PW_EN_DC_IN;
	}
	else if( PW_BAT_A_EN_Get() == 0 )	{
		M0_AllDevStatus.adc_pw.pw_EN |= PW_EN_BAT_A;
	}
	else if( PW_BAT_B_EN_Get() == 0 )	{
		M0_AllDevStatus.adc_pw.pw_EN |= PW_EN_BAT_B;
	}
	*/

	//	Get ADC  -----------------------------------------------------------------
	NOP( );
	ADC_Enable( );

	switch( adc_channel % 3 )   {
	  case 0:
	    ADC_REGS->ADC_INPUTCTRL = (uint16_t) ADC_BATTERY_A_AIN;
	    ADC_ChannelSelect( ADC_BATTERY_A_AIN, ADC_INPUTCTRL_MUXNEG_GND );
	    break;

	  case 1:
	    ADC_REGS->ADC_INPUTCTRL = (uint16_t) ADC_BATTERY_B_AIN;
	    ADC_ChannelSelect( ADC_BATTERY_B_AIN, ADC_INPUTCTRL_MUXNEG_GND );
	    break;

	  case 2:
	    ADC_REGS->ADC_INPUTCTRL = (uint16_t) ADC_BATTERY_SOLAR_AIN;
	    ADC_ChannelSelect( ADC_BATTERY_SOLAR_AIN, ADC_INPUTCTRL_MUXNEG_GND );
	    break;
	}   //switch( adc_channel % 2 )   {


	//ADC_Enable( );

	ADC_ConversionStart( );
	while( ADC_ConversionSequenceIsFinished( ) != true )   {
	  NOP( );
	}
	NOP( );

	switch( adc_channel % 3 )   {
	  case 0:
	    M0_AllDevStatus.adc_pw.adc0 = (UINT32)ADC_ConversionResultGet( );
	    NOP();
	    break;
	  
	  case 1:
	    M0_AllDevStatus.adc_pw.adc1 = (UINT32)ADC_ConversionResultGet( );
	    NOP();
	    break;

	  case 2:
	    M0_AllDevStatus.adc_pw.adc2 = (UINT32)ADC_ConversionResultGet( );
	    NOP();
	    break;
	}   //switch( adc_channel % 2 )   {  
	NOP();
	//ADC_Disable( );
	adc_channel++;
	NOP( );


	//============================================================================
	M0_AllDevStatus.adc_pw.pw_EN = 0x00;
	if( PW_SOLAR_EN_Get() == 0 )	{
		M0_AllDevStatus.adc_pw.pw_EN |= PW_EN_SOLAR;

		M0_AllDevStatus.adc_pw.V_batA = M0_AllDevStatus.adc_pw.adc0 * ADC_BAT_A_FACTOR / 1000;
		M0_AllDevStatus.adc_pw.V_batB = M0_AllDevStatus.adc_pw.adc1 * ADC_BAT_B_FACTOR / 1000;
		M0_AllDevStatus.adc_pw.V_Solar = M0_AllDevStatus.adc_pw.pw_meter.bat_v;
		M0_AllDevStatus.adc_pw.V_DC = VOLT_NOUSED;
	}
	
	else if( PW_DC_EN_Get() == 0 )	{
		M0_AllDevStatus.adc_pw.pw_EN |= PW_EN_DC_IN;

		M0_AllDevStatus.adc_pw.V_batA = M0_AllDevStatus.adc_pw.adc0 * ADC_BAT_A_FACTOR / 1000;
		M0_AllDevStatus.adc_pw.V_batB = M0_AllDevStatus.adc_pw.adc1 * ADC_BAT_B_FACTOR / 1000;
		M0_AllDevStatus.adc_pw.V_Solar = VOLT_NOUSED;
		M0_AllDevStatus.adc_pw.V_DC = M0_AllDevStatus.adc_pw.pw_meter.bat_v;
		
	}

	else if( PW_BAT_A_EN_Get() == 0 )	{
		M0_AllDevStatus.adc_pw.pw_EN |= PW_EN_BAT_A;
		
		M0_AllDevStatus.adc_pw.V_batA = M0_AllDevStatus.adc_pw.pw_meter.bat_v;
		M0_AllDevStatus.adc_pw.V_batB = M0_AllDevStatus.adc_pw.adc1 * ADC_BAT_B_FACTOR / 1000;
		M0_AllDevStatus.adc_pw.V_Solar = VOLT_NOUSED;
		M0_AllDevStatus.adc_pw.V_DC = VOLT_NOUSED;
	}
	else if( PW_BAT_B_EN_Get() == 0 )	{
		M0_AllDevStatus.adc_pw.pw_EN |= PW_EN_BAT_B;

		M0_AllDevStatus.adc_pw.V_batB = M0_AllDevStatus.adc_pw.pw_meter.bat_v;
		M0_AllDevStatus.adc_pw.V_batA = M0_AllDevStatus.adc_pw.adc0 * ADC_BAT_A_FACTOR / 1000;
		M0_AllDevStatus.adc_pw.V_Solar = VOLT_NOUSED;
		M0_AllDevStatus.adc_pw.V_DC = VOLT_NOUSED;
	}
	NOP( );
}   //void  TimerF_ADC_DATA(void)













//  ****************************************************************************
//
//  ****************************************************************************
void  TimerF_ckBAT_logic( void )
{
	UINT32 	V_bat_A;
	UINT32 	V_bat_B;

  
  reset_timer( tm_CK_BAT_logic );


  //============================================================================
  //	Battery CK Logic
  //	BAT_PW_CTL_A( );  	BAT_PW_CTL_B( );
  V_bat_A = M0_AllDevStatus.adc_pw.adc0 * ADC_BAT_A_FACTOR / 1000;
  if( V_bat_A < 6200 )		{
  	V_bat_A = 9999;
  }
  V_bat_B = M0_AllDevStatus.adc_pw.adc1 * ADC_BAT_B_FACTOR / 1000;
  if( V_bat_B < 6200 )		{
  	V_bat_B = 9999;
  }

  if( (M0_AllDevStatus.adc_pw.pw_EN & (PW_EN_SOLAR|PW_EN_DC_IN) ) == 0 )		{
  	if( V_bat_A <= V_bat_B )		{
  		BAT_PW_CTL_A( );
  	}
  	else  {
  		BAT_PW_CTL_B( );
  	}

  }  	//if( (M0_AllDevStatus.adc_pw.pw_EN & (PW_EN_SOLAR|PW_EN_DC_IN) ) == 0 )		{

  NOP( );
}  		//void  TimerF_ckBAT_logic( void )












#if 	Tst_ADC_01

//  ****************************************************************************
//
//  ****************************************************************************
void  TimerF_ADC_2A53(void)
{
  reset_timer( tm_ADC_2A53 );

  //============================================================================    
  NOP( );
  SysRTC_Get( (M0_RTC_TIME_FRAME*)&(M0_AllDevStatus.adc_pw.mcu_RTC) );

  NOP( );
  UartDataTx_M0toM4_DevData( uart_RSP_DEV_STATUS, SUBTYPE_ADC, (uint8_t*)&(M0_AllDevStatus.adc_pw), sizeof(M0_POWER_DATA_FRAME) );
  NOP( );
} 		//void  TimerF_ADC_2A53(void)


#endif 	//#if 	Tst_ADC_01

