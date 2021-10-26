/*******************************************************************************
  PORT PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_port.c

  Summary:
    Interface definition of PORT PLIB

  Description:
    This file provides an interface to control and interact with PORT-I/O
    Pin controller module.

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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

/*
#include "plib_port.h"
#include "plib_port2.h"
*/
#include "All_Header.h"


// *****************************************************************************
// *****************************************************************************
// Section: PORT Implementation
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:

    void PORT_Initialize(void)

  Summary:
    Initializes the PORT Library.

  Description:
    This function initializes all ports and pins as configured in the
    MHC Pin Manager.

  Remarks:
    Refer plib_port.h file for more information.
*/

/*
  typedef struct
  {
    __IO  uint32_t                       PORT_DIR;           //  Offset: 0x00 (R/W  32) Data Direction
    __IO  uint32_t                       PORT_DIRCLR;        //  Offset: 0x04 (R/W  32) Data Direction Clear
    __IO  uint32_t                       PORT_DIRSET;        //  Offset: 0x08 (R/W  32) Data Direction Set
    __IO  uint32_t                       PORT_DIRTGL;        //  Offset: 0x0C (R/W  32) Data Direction Toggle
    __IO  uint32_t                       PORT_OUT;           //  Offset: 0x10 (R/W  32) Data Output Value
    __IO  uint32_t                       PORT_OUTCLR;        //  Offset: 0x14 (R/W  32) Data Output Value Clear
    __IO  uint32_t                       PORT_OUTSET;        //  Offset: 0x18 (R/W  32) Data Output Value Set
    __IO  uint32_t                       PORT_OUTTGL;        //  Offset: 0x1C (R/W  32) Data Output Value Toggle
    __I   uint32_t                       PORT_IN;            //  Offset: 0x20 (R/   32) Data Input Value
    __IO  uint32_t                       PORT_CTRL;          //  Offset: 0x24 (R/W  32) Control
    __O   uint32_t                       PORT_WRCONFIG;      //  Offset: 0x28 ( /W  32) Write Configuration
    __IO  uint32_t                       PORT_EVCTRL;        //  Offset: 0x2C (R/W  32) Event Input Control
    __IO  uint8_t                        PORT_PMUX[16];      //  Offset: 0x30 (R/W  8) Peripheral Multiplexing n
    __IO  uint8_t                        PORT_PINCFG[32];    //  Offset: 0x40 (R/W  8) Pin Configuration n
    __I   uint8_t                        Reserved1[0x20];
  } port_group_registers_t;
*/

//    I/O Multiplexing and Considerations ::    31 / 1092
void PORT_Initialize(void)
{
}

// *****************************************************************************
/* Function:
    uint32_t PORT_GroupRead(PORT_GROUP group)

  Summary:
    Read all the I/O pins in the specified port group.

  Description:
    The function reads the hardware pin state of all pins in the specified group
    and returns this as a 32 bit value. Each bit in the 32 bit value represent a
    pin. For example, bit 0 in group 0 will represent pin PA0. Bit 1 will
    represent PA1 and so on. The application should only consider the value of
    the port group pins which are implemented on the device.

  Remarks:
    Refer plib_port.h file for more information.
*/

uint32_t PORT_GroupRead(PORT_GROUP group)
{
    return (((port_group_registers_t*)group)->PORT_IN);
}

// *****************************************************************************
/* Function:
    void PORT_GroupWrite(PORT_GROUP group, uint32_t mask, uint32_t value);

  Summary:
    Write value on the masked pins of the selected port group.

  Description:
    This function writes the value contained in the value parameter to the
    port group. Port group pins which are configured for output will be updated.
    The mask parameter provides additional control on the bits in the group to
    be affected. Setting a bit to 1 in the mask will cause the corresponding
    bit in the port group to be updated. Clearing a bit in the mask will cause
    that corresponding bit in the group to stay unaffected. For example,
    setting a mask value 0xFFFFFFFF will cause all bits in the port group
    to be updated. Setting a value 0x3 will only cause port group bit 0 and
    bit 1 to be updated.

    For port pins which are not configured for output and have the pull feature
    enabled, this function will affect pull value (pull up or pull down). A bit
    value of 1 will enable the pull up. A bit value of 0 will enable the pull
    down.

  Remarks:
    Refer plib_port.h file for more information.
*/

void PORT_GroupWrite(PORT_GROUP group, uint32_t mask, uint32_t value)
{
    /* Write the desired value */
    ((port_group_registers_t*)group)->PORT_OUT = (((port_group_registers_t*)group)->PORT_OUT & (~mask)) | (mask & value);
}

// *****************************************************************************
/* Function:
    uint32_t PORT_GroupLatchRead(PORT_GROUP group)

  Summary:
    Read the data driven on all the I/O pins of the selected port group.

  Description:
    The function will return a 32-bit value representing the logic levels being
    driven on the output pins within the group. The function will not sample the
    actual hardware state of the output pin. Each bit in the 32-bit return value
    will represent one of the 32 port pins within the group. The application
    should only consider the value of the pins which are available on the
    device.

  Remarks:
    Refer plib_port.h file for more information.
*/

uint32_t PORT_GroupLatchRead(PORT_GROUP group)
{
    return (((port_group_registers_t*)group)->PORT_OUT);
}

// *****************************************************************************
/* Function:
    void PORT_GroupSet(PORT_GROUP group, uint32_t mask)

  Summary:
    Set the selected IO pins of a group.

  Description:
    This function sets (drives a logic high) on the selected output pins of a
    group. The mask parameter control the pins to be updated. A mask bit
    position with a value 1 will cause that corresponding port pin to be set. A
    mask bit position with a value 0 will cause the corresponding port pin to
    stay un-affected.

  Remarks:
    Refer plib_port.h file for more information.
*/

void PORT_GroupSet(PORT_GROUP group, uint32_t mask)
{
    ((port_group_registers_t*)group)->PORT_OUTSET = mask;
}

// *****************************************************************************
/* Function:
    void PORT_GroupClear(PORT_GROUP group, uint32_t mask)

  Summary:
    Clears the selected IO pins of a group.

  Description:
    This function clears (drives a logic 0) on the selected output pins of a
    group. The mask parameter control the pins to be updated. A mask bit
    position with a value 1 will cause that corresponding port pin to be clear.
    A mask bit position with a value 0 will cause the corresponding port pin to
    stay un-affected.

  Remarks:
    Refer plib_port.h file for more information.
*/

void PORT_GroupClear(PORT_GROUP group, uint32_t mask)
{
    ((port_group_registers_t*)group)->PORT_OUTCLR = mask;
}

// *****************************************************************************
/* Function:
    void PORT_GroupToggle(PORT_GROUP group, uint32_t mask)

  Summary:
    Toggles the selected IO pins of a group.

  Description:
    This function toggles the selected output pins of a group. The mask
    parameter control the pins to be updated. A mask bit position with a value 1
    will cause that corresponding port pin to be toggled.  A mask bit position
    with a value 0 will cause the corresponding port pin to stay un-affected.

  Remarks:
    Refer plib_port.h file for more information.
*/

void PORT_GroupToggle(PORT_GROUP group, uint32_t mask)
{
    ((port_group_registers_t*)group)->PORT_OUTTGL = mask;
}

// *****************************************************************************
/* Function:
    void PORT_GroupInputEnable(PORT_GROUP group, uint32_t mask)

  Summary:
    Confgiures the selected IO pins of a group as input.

  Description:
    This function configures the selected IO pins of a group as input. The pins
    to be configured as input are selected by setting the corresponding bits in
    the mask parameter to 1.

  Remarks:
    Refer plib_port.h file for more information.
*/

void PORT_GroupInputEnable(PORT_GROUP group, uint32_t mask)
{
    ((port_group_registers_t*)group)->PORT_DIRCLR = mask;
}

// *****************************************************************************
/* Function:
    void PORT_GroupOutputEnable(PORT_GROUP group, uint32_t mask)

  Summary:
    Confgiures the selected IO pins of a group as output.

  Description:
    This function configures the selected IO pins of a group as output. The pins
    to be configured as output are selected by setting the corresponding bits in
    the mask parameter to 1.

  Remarks:
    Refer plib_port.h file for more information.
*/

void PORT_GroupOutputEnable(PORT_GROUP group, uint32_t mask)
{
   ((port_group_registers_t*)group)->PORT_DIRSET = mask;
}
