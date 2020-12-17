/******************************************************************************/
/* COMBILER INFORMATION														  */
/******************************************************************************/

/* Configuration settings */
#pragma config WDTEN = OFF
#pragma config FOSC  = INTIO67
#pragma config XINST = OFF

/* Configure the interrupt settings */
#pragma interrupt InterruptHigh
#pragma code InterruptVectorHigh = 0x08

/******************************************************************************/
/* INCLUDE FILES															  */
/******************************************************************************/
#include <p18f46k22.h>
#include <stdio.h>
#include <stdlib.h>

#include "CommADS1298.h"
#include "ADS1298.h"
#include "CommCC110L.h"
#include "CC110L.h"
#include "Implant.h"
#include "LogicAnalyzer.h"

/******************************************************************************/
/* INTERRUPTS																  */
/******************************************************************************/
void InterruptVectorHigh() { 
	_asm
		goto InterruptHigh
	_endasm
}

void InterruptHigh() {
    //CC110L_ISR();
}

/******************************************************************************/
/* MAIN FUNCTION															  */
/******************************************************************************/
void main() {
	unsigned char status, i;
    unsigned char dummy[100];
    unsigned char channels[2] = {0, 0};
    
	/* Set the PIC clock frequency */
	/* bit 7   (IDLEN):  0   = Device enter Sleep mode on SLEEP instruction
	 * bit 6-4 (IRCF):   111 = 16 MHz internal RC oscillator
	 * bit 3   (OSTS):   0   = Device is running from internal oscillator
	 * bit 2   (HFIOFS): 1   = HFINTOSC frequency is stable
	 * bit 1-0 (SCS):    1x  = Internal oscillator block
	 */
    OSCCON = 0b01110110; // set clock to 16 MHz
	
    /* Initialize the implant */
	channels[0] = 0b10000000; // device 1 channels
	channels[1] = 0b00000000; // device 2 channels
    Implant_Initialize(channels);
    
	/* Keep reading these registers */
	if (status) {
		while (0) {
            
            /* Read register data */
            //ADS1298_ReadRegisters(1, ADS1298_ID, 12, dummy);
            //ADS1298_ReadRegisters(2, ADS1298_ID, 12, dummy);
            
            /* Read the test data */
            //ADS1298_ReadData(dummy, 30ul);
            
            /* Print the data to the logic analyzer */
            //for (i = 0; i < 30; i = i + 1) {
                //LogicAnalyzer_OutputChar(dummy[(i * 3) + 1]); // output value of the first channel
            //}
		}
	}
}