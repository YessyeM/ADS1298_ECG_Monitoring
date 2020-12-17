/***************************************************************************//**
 *   @file   CommCC110L.c
 *   @brief  Implementation of Communication Driver.
 *   @author Jiaxu Meng (jm611@duke.edu)
********************************************************************************
 * Copyright 2012(c) Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *  - The use of this software may or may not infringe the patent rights
 *    of one or more patent holders.  This license does not release you
 *    from the requirement that you obtain separate licenses from these
 *    patent holders to use this software.
 *  - Use of the software either in source or binary form, must be run
 *    on or directly connected to an Analog Devices Inc. component.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
********************************************************************************
 *   SVN Revision: 570
*******************************************************************************/

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "CommCC110L.h"

/***************************************************************************//**
 * @brief Initializes the SPI communication peripheral for the CC110L chip.
 *
 * @param None.
 *
 * @return 0 - Initialization failed, 1 - Initialization succeeded.
*******************************************************************************/
unsigned char CommCC110L_Initialize() {
	
	/* Re-initialize the SSP1 control register 1 and the status register */
	SSP2CON1 = 0x00; // SSP control register 1
	SSP2STAT = 0x00; // SSP status register

	/* SSP1 Status Register bits */
	CommCC110L_SAMPLING = 1; // master mode sampling occurs at the end of data output time (What we originally thought it was)
	CommCC110L_CLKEDGE  = 0; // transmit occurs on transition from active to idle clock state
	
	/* SSP1 Control Register 1 bits */
	CommCC110L_CLKPOL = 0;      // idle state for clock is low
	CommCC110L_MODE   = 0b0100; // set frequency of the shift clock (divide clock frequency by 4)
	CommCC110L_ENABLE = 1;      // enable the SPI

	/* Properly configure the SPI/communication pins */
	
	CommCC110L_SCLK_DIR   = 1; // SCLK on CC110L is input
    CommCC110L_SCLK_ANSEL = 0; // clear analog select bit for clock input
    
	CommCC110L_DIN_DIR   = 1; // DOUT on CC110L is input into the PIC    
	CommCC110L_DIN_ANSEL = 0; // clear analog select bit for data input

	CommCC110L_DOUT_DIR = 0; // DIN on CC110L is output from PIC
    
	CommCC110L_CS_DIR   = 1; // CS on CC110L is output from PIC
    CommCC110L_CS_ANSEL = 0; // clear analog select bit for slave select input
    
	CommCC110L_DRDY_DIR = 0; // DRDY from PIC is output
	CommCC110L_DRDY_NOT = 1; // DRDY is not ready initially
	
    /* Define the global interrupt bits */
    INTERRUPT_PRIORITY   = 1;
    INTERRUPT_GLOBAL     = 1;
    INTERRUPT_PERIPHERAL = 1;
    
    /* Define the MSSP 2 Interrupt bits */
    CommCC110L_SSPINT_ENABLE   = 1;
    CommCC110L_SSPINT_PRIORITY = 1;
    CommCC110L_SSPINTERRUPT    = 0;
    
	return 1;
}

/***************************************************************************//**
 * @brief Writes data to SPI of the CC110L chip.
 *
 * @param data - data represents the write buffer.
 * @param bytesNumber - Number of bytes to write.
 *
 * @return Number of written bytes.
*******************************************************************************/
unsigned char CommCC110L_Write(unsigned char* data,
                               unsigned char bytesNumber)
{
    unsigned char i;
    
    for(i = 0; i < bytesNumber; i++) {
        CommCC110L_DATABUFFER = *data++;
        while (!CommCC110L_SSPINTERRUPT);
        CommCC110L_SSPINTERRUPT = 0; // reset the interrupt flag
    }
    
	return bytesNumber;
}

/***************************************************************************//**
 * @brief Reads data from SPI of the CC110L chip.
 *
 * @param data - Data represents the read buffer.
 * @param bytesNumber - Number of bytes to read.
 *
 * @return Number of read bytes.
*******************************************************************************/
unsigned char CommCC110L_Read(unsigned char* data,
                              unsigned char bytesNumber)
{
    unsigned char i;
    
    for(i = 0; i < bytesNumber; i++) {
        while (!CommCC110L_SSPINTERRUPT); // while transmission has yet to be completed, wait
        *data++ = CommCC110L_DATABUFFER; 
        CommCC110L_SSPINTERRUPT = 0; // reset the interrupt flag
    }
    
    return bytesNumber;
}