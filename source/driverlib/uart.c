//###########################################################################
//
// FILE:   uart.c
//
// TITLE:  C29x UART driver.
//
//###########################################################################
// //
//	Copyright: Copyright (C) Texas Instruments Incorporated
//	All rights reserved not granted herein.
//
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//  Redistributions of source code must retain the above copyright 
//  notice, this list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright
//  notice, this list of conditions and the following disclaimer in the 
//  documentation and/or other materials provided with the   
//  distribution.
//
//  Neither the name of Texas Instruments Incorporated nor the names of
//  its contributors may be used to endorse or promote products derived
//  from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

//###########################################################################

#include "uart.h"

//*****************************************************************************
//
// UART_setConfig()
//
//*****************************************************************************

void
UART_setConfig(uint32_t base, uint32_t uartClk,
               uint32_t baud, uint32_t config)
{
    uint32_t fbrDiv, baudrt;

    baudrt = baud;

    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));
    ASSERT(baudrt != 0U);
    ASSERT(uartClk >= (baudrt * UART_CLK_DIVIDER));

    //
    // Stop the UART.
    //
    UART_disableModule(base);

    //
    // Is the required baud rate greater than the maximum rate supported
    // without the use of high speed mode?
    //
    if((baudrt * 16U) > uartClk)
    {
        //
        // Enable high speed mode.
        //
        HWREG(base + UART_O_CTL) |= UART_CTL_HSE;

        //
        // Half the supplied baud rate to compensate for enabling high speed
        // mode.  This allows the following code to be common to both cases.
        //
        baudrt /= 2U;
    }
    else
    {
        //
        // Disable high speed mode.
        //
        HWREG(base + UART_O_CTL) &= ~(UART_CTL_HSE);
    }

    //
    // Compute the fractional baud rate divider.
    //
    fbrDiv = (((uartClk * 8U) / baudrt) + 1U) / 2U;

    //
    // Set the baud rate.
    //
    HWREGH(base + UART_O_IBRD) = (uint16_t)(fbrDiv / 64U);
    HWREGB(base + UART_O_FBRD) = (uint8_t)(fbrDiv % 64U);

    //
    // Set parity, data length, and number of stop bits.
    //
    HWREGB(base + UART_O_LCRH) = (uint8_t)config;

    //
    // Start the UART.
    //
    UART_enableModule(base);
}

//*****************************************************************************
//
// UART_getConfig()
//
//*****************************************************************************

void
UART_getConfig(uint32_t base, uint32_t uartClk,
               uint32_t *baud, uint32_t *config)
{
    uint32_t integr, frac;

    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Compute the baud rate.
    //
    integr = HWREG(base + UART_O_IBRD);
    frac = HWREG(base + UART_O_FBRD);
    *baud = (uartClk * 4U) / ((64U * integr) + frac);

    //
    // See if high speed mode enabled.
    //
    if((HWREG(base + UART_O_CTL) & UART_CTL_HSE) == UART_CTL_HSE)
    {
        //
        // High speed mode is enabled so the actual baud rate is actually
        // double what was just calculated.
        //
        *baud *= 2U;
    }

    //
    // Get the parity, data length, and number of stop bits.
    //
    *config = (HWREG(base + UART_O_LCRH) &
              (UART_LCRH_SPS | UART_LCRH_WLEN_M | UART_LCRH_STP2 |
               UART_LCRH_EPS | UART_LCRH_PEN));
}

//*****************************************************************************
//
// UART_writeCharNonBlocking()
//
//*****************************************************************************

bool
UART_writeCharNonBlocking(uint32_t base, uint8_t data)
{
    bool ret;

    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // See if there is space in the transmit FIFO.
    //
    if((HWREG(base + UART_O_FR) & UART_FR_TXFF) == 0U)
    {
        //
        // Write this character to the transmit FIFO.
        //
        HWREGB(base + UART_O_DR) = data;

        //
        // Success.
        //
        ret = true;
    }
    else
    {
        //
        // There is no space in the transmit FIFO, so return a failure.
        //
        ret = false;
    }

    return(ret);
}

//*****************************************************************************
//
// UART_writeCharArray()
//
//*****************************************************************************

void
UART_writeCharArray(uint32_t base, uint8_t * const array, uint16_t length)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    uint16_t i;

    //
    // Loop to write (blocking) 'length' number of characters
    //
    for(i = 0U; i < length; i++)
    {
        //
        // Wait until space is available.
        //
        while((HWREG(base + UART_O_FR) & UART_FR_TXFF) == UART_FR_TXFF)
        {
            ;
        }

        //
        // Send the char.
        //
        HWREGB(base + UART_O_DR) = array[i];
    }
}

//*****************************************************************************
//
// UART_readCharArray()
//
//*****************************************************************************

void
UART_readCharArray(uint32_t base, int32_t * const array, uint16_t length)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    uint16_t i;

    //
    // Loop to read (Blocking) 'length' number of characters
    //
    for(i = 0U; i < length; i++)
    {
        //
        // Wait until a char is available.
        //
        while((HWREG(base + UART_O_FR) & UART_FR_RXFE) == UART_FR_RXFE)
        {
            ;
        }

        //
        // Read the char.
        //
        array[i] = (int32_t)(HWREG(base + UART_O_DR));
    }
}

//*****************************************************************************
//
// UART_send9BitAddress()
//
//*****************************************************************************

void
UART_send9BitAddress(uint32_t base, uint8_t addr)
{
    uint32_t lcrh;

    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Wait until the FIFO is empty and the UART is not busy.
    //
    while((HWREG(base + UART_O_FR) & (UART_FR_TXFE | UART_FR_BUSY)) !=
          UART_FR_TXFE)
    {
        ;
    }

    //
    // Force the address/data bit to 1 to indicate this is an address byte.
    //
    lcrh = HWREG(base + UART_O_LCRH);
    HWREG(base + UART_O_LCRH) = ((lcrh & ~UART_LCRH_EPS) |
                                 UART_LCRH_SPS | UART_LCRH_PEN);

    //
    // Send the address.
    //
    HWREGB(base + UART_O_DR) = addr;

    //
    // Wait until the address has been sent.
    //
    while((HWREG(base + UART_O_FR) & (UART_FR_TXFE | UART_FR_BUSY)) !=
          UART_FR_TXFE)
    {
        ;
    }

    //
    // Restore the address/data setting.
    //
    HWREGB(base + UART_O_LCRH) = (uint8_t)lcrh;
}

//*****************************************************************************
//
// UART_stop9BitDataMode()
//
//*****************************************************************************

void
UART_stop9BitDataMode(uint32_t base, uint32_t lcrh)
{
    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Wait until the FIFO is empty and the UART is not busy.
    //
    while((HWREG(base + UART_O_FR) & (UART_FR_TXFE | UART_FR_BUSY)) !=
          UART_FR_TXFE)
    {
    }

    //
    // Restore the address/data setting to enter normal transmission mode.
    //
    HWREGB(base + UART_O_LCRH) = (uint8_t)lcrh;
}

//*****************************************************************************
//
// UART_configure9BitDataMode()
//
//*****************************************************************************

uint32_t
UART_configure9BitDataMode(uint32_t base)
{
    uint32_t lcrh;

    //
    // Check the arguments.
    //
    ASSERT(UART_isBaseValid(base));

    //
    // Wait until the FIFO is empty and the UART is not busy.
    //
    while((HWREG(base + UART_O_FR) & (UART_FR_TXFE | UART_FR_BUSY)) !=
          UART_FR_TXFE)
    {
    }

    //
    // Force the address/data bit to 0 to indicate this is an data byte.
    //
    lcrh = HWREG(base + UART_O_LCRH);
    HWREG(base + UART_O_LCRH) = (lcrh | UART_LCRH_EPS |
                                 UART_LCRH_SPS | UART_LCRH_PEN);

    //
    // Needed to restore the address/data setting after the full
    // 9-bit data transmission.
    //
    return(lcrh);
}

