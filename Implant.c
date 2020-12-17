/***************************************************************************//**
 *   @file   Implant.c
 *   @brief  Implementation of the implant driver.
 *   @author Jiaxu Meng (jm611@duke.edu)
*******************************************************************************/

/*****************************************************************************/
/* INCLUDE FILES															 */
/*****************************************************************************/
#include "ADS1298.h"
#include "Implant.h"
#include "LogicAnalyzer.h"


/*****************************************************************************/
/* VARIABLES    															 */
/*****************************************************************************/
static unsigned char frameSize = 0;
unsigned char mode;

/*****************************************************************************/
/* FUNCTIONS																 */
/*****************************************************************************/

unsigned char Implant_Initialize(unsigned char* channels) {
    unsigned char status = 0;
    
    /* Initialize the ADS1298 */
	status = ADS1298_Initialize(channels);
	// frameSize = ADS1298_GetFrameSize();
    
    /* Initialize the SPI communication */
    //status &= CC110L_Initialize();
    
	/* Initialize the Logic Analyzer */
	status &= LogicAnalyzer_Initialize();
    
    return status;
}

void Implant_StreamData(unsigned char frameCnt) {
	unsigned char data[50];
	unsigned char i;
	
	/* Start converting data and reading it */
    ADS1298_START_PIN = 1; // bring the START pin high to start converting data
	ADS1298_StartConversion();
	
	/* Iterate through the frames */
	for (i = 0; i < frameCnt; i = i + 1) {
		ADS1298_ReadFrame(data);
		CC110L_TX_WriteBufferMultiple(data);
	}
	
	/* Stop converting data and stop reading it */
	ADS1298_StopConversion();
	ADS1298_START_PIN = 0;
}

unsigned char Implant_ChangeMode(unsigned char cmd, unsigned char* data) {
	unsigned char status;
	switch (cmd) {
		
		/* Mode 0x00
		 * Device is powered OFF.
		 */
		case 0x00:
			if (cmd) {
				status = ADS1298_PowerUp();
				if (status) mode = 0x01;
			} else {
				mode = mode;
			}
			
		/* Mode 0x01
		 * Device is powered ON. All channels are turned off and shorted. Device is idle.
		 */
		case 0x01:
			switch (cmd) {
				/* Turn off the device */
				case 0x00:
					mode = 0x00;
					
				/* Select the channel */
				case 0x01:
					ADS1298_SetChannels(data);
					mode = 0x01;
					
				/* No channels selected */
				default:
					mode = mode;
			}
		
		/* Mode 0x02
		 * Device is powered ON. Channel(s) is/are turned on. Device is idle.
		 */
		case 0x02:
			switch (cmd) {
				/* Turn off the channels */
				case 0x00:
					ADS1298_SetChannels(data);
					mode = 0x01;
					
				/* Start data conversions */
				case 0x01:
					mode = 0x03;
				
				/* Select different channels */
				default:
					ADS1298_SetChannels(data);
					mode = mode;
			}
			
		/* Mode 0x03
		 * Device is converting data. Data is being collected.
		 */
		case 0x03:
			switch (cmd) {
				/* Stop collecting data */
				case 0x00:
					mode = 0x02;
					
				/* Send collected data to the relay box */
				case 0x01:
					mode = 0x04;
				
				/* Change the channel */
				default:
					mode = mode;
			}
		
		/* Mod 0x04
		 * Device is sending data out. Currently, PIC to PIC communication.
		 */
		case 0x04:
			if (cmd) {
				mode = 0x03;
			} else {
				mode = mode;
			}
	}
	
	return mode;
}