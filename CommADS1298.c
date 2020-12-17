/***************************************************************************//**
 *   @file   CommADS1298.c
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
#include "CommADS1298.h"

/***************************************************************************//**
 * @brief Initializes the SPI communication peripheral for the ADS1298 chip.
 *
 * @param None.
 *
 * @return 0 - Initialization failed, 1 - Initialization succeeded.
*******************************************************************************/
unsigned char CommADS1298_Initialize() {
	
	/* Re-initialize the SSP1 control register 1 and the status register */
	SSP1CON1 = 0x00; // SSP control register 1
	SSP1STAT = 0x00; // SSP status register

	/* SSP1 Status Register bits */
	CommADS1298_SAMPLING = 1; // master mode sampling occurs at the end of data output time (What we originally thought it was)
	CommADS1298_CLKEDGE = 0; // transmit occurs on transition from active to idle clock state
	
	/* SSP1 Control Register 1 bits */

	CommADS1298_CLKPOL = 0; // idle state for clock is low
	//CommADS1298_CLKPOL = 1; // idle state for clock is high
	
	CommADS1298_FOSC = 0000; // set frequency of the shift clock (divide clock frequency by 4)
	
	CommADS1298_ENABLE = 1; // enable the SPI

	/* Properly configure the SPI/communication pins */
	
	CommADS1298_SCLK_DIR = 0; // SCLK on ADS1298 is output
    
	CommADS1298_DOUT_DIR   = 1; // DOUT on ADS1298 is input into the PIC    
	CommADS1298_DOUT_ANSEL = 0; // clear analog select bit for PIC input

	CommADS1298_DIN_DIR = 0; // DIN on ADS1298 is output from PIC
	
    ADS1298_DRDY1_DIR   = 1; // DRDY on ADS1298 is input into PIC (device 1)
	ADS1298_DRDY1_ANSEL = 0;	// clear analog select bit for DRDY (device 1)
	
    ADS1298_DRDY2_DIR   = 1; // DRDY on ADS1298 is input into PIC (device 2)
	ADS1298_DRDY2_ANSEL = 0;	// clear analog select bit for DRDY (device 2)
    
    CommADS1298_CS1_PIN = 1;  // pdw initialize CS1 state 11/12/19
    CommADS1298_CS2_PIN = 1;  // pdw initialize CS2 state 11/12/19
    
	CommADS1298_CS1_DIR = 0; // CS on ADS1298 is output from PIC (device 1)
	CommADS1298_CS2_DIR = 0; // CS on ADS1298 is output from PIC (device 2)
    
	/* Properly configure the other pins */
	ADS1298_START_PIN = 0;  //initialize state of start pins  pdw 11/12/19
    ADS1298_START_DIR = 0; // START is output
    ADS1298_RESET_PIN = 1;  // initialize state of reset pins pdw 11/12/19
	ADS1298_RESET_DIR = 0; // RESET is output
    ADS1298_PWR_PIN = 0;  //initialize state of power down pins pdw 11/12/19
	ADS1298_PWR_DIR = 0; // PWRDN on ADS1298 is output from PIC

	return 1;
}

/***************************************************************************//**
 * @brief Writes data to SPI of the ADS1298 chip.
 *
 * @param data - data represents the write buffer.
 * @param bytesNumber - Number of bytes to write.
 *
 * @return Number of written bytes.
*******************************************************************************/
unsigned char CommADS1298_Write(unsigned char* data,
                                unsigned char bytesNumber)
{
    unsigned char i;
    
    for(i = 0; i < bytesNumber; i++) {
        CommADS1298_DATABUFFER = *data++;
        while (!CommADS1298_BUFFERFULL);
        CommADS1298_INTERRUPT = 0; // reset the interrupt flag
    }
    
	return bytesNumber;
}

/***************************************************************************//**
 * @brief Reads data from SPI of the ADS1298 chip.
 *
 * @param data - Data represents the read buffer.
 * @param bytesNumber - Number of bytes to read.
 *
 * @return Number of read bytes.
*******************************************************************************/
unsigned char CommADS1298_Read(unsigned char* data,
                               unsigned char bytesNumber)
{
    unsigned char i;
    
    for(i = 0; i < bytesNumber; i++) {  
        CommADS1298_DATABUFFER = 0x00; // write 0's to the data buffer to shift bits in
        while (!CommADS1298_BUFFERFULL); // while transmission has yet to be completed, wait
        *data++ = CommADS1298_DATABUFFER; 
        CommADS1298_INTERRUPT = 0; // reset the interrupt flag
    }
    
    return bytesNumber;
}