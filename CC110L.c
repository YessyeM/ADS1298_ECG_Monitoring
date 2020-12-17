/***************************************************************************//**
 *   @file   CC110L.c
 *   @brief  Implementation of the CC110L Driver.
 *   @author Jiaxu Meng (jm611@duke.edu)
*******************************************************************************/

/******************************************************************************/
/* INCLUDE FILES															  */
/******************************************************************************/
#include "CommCC110L.h"
#include "CC110L.h"

/******************************************************************************/
/* DEFINITIONS  															  */
/******************************************************************************/
#define MAX_TX_SIZE     64
#define MAX_RC_SIZE     64

/******************************************************************************/
/* GLOBAL VARIABLES															  */
/******************************************************************************/
unsigned char TX_BUFFER[MAX_TX_SIZE], RC_BUFFER[MAX_RC_SIZE];
unsigned char TX_HEAD, TX_TAIL, RC_HEAD, RC_TAIL;

/******************************************************************************/
/* FUNCTIONS																  */
/******************************************************************************/

/******************************************************************************/
/* General Functions Part 1													  */
/******************************************************************************/

/***************************************************************************//**
 * @brief Initializes the CC110L (in this case initialize the swinging buffers). 
 *
 * @param None.
 * 
 * @return None.
*******************************************************************************/
unsigned char CC110L_Initialize() {
    unsigned char status, i;
    
    /* Initialize the SPI communication */
    status = CommCC110L_Initialize();
    
    /* Initialize the RC and TX buffers */
    RC_HEAD = RC_TAIL = TX_HEAD = TX_TAIL = 0;
    for (i = 0; i < MAX_RC_SIZE; i = i + 1) { RC_BUFFER[i] = 0; }
    
    return 1;
}

/***************************************************************************//**
 * @brief Increment the specified index and check if the end of the buffer has
 *        been reached. If the end has been reached, the index is wrapped back 
 *        around to the beginning of the buffer.
 *
 * @param idx - Index that you desire to increment.
 * @param max - Maximum index that you can go to (buffer size).
 * 
 * @return Incremented index value.
*******************************************************************************/
unsigned char CC110L_IncrementIndex(unsigned char idx, 
									unsigned char max) {
	if (++idx == max) { idx = 0; } // increment index; and if buffer end reached, start from beginning
	return idx; // return the index
}

/******************************************************************************/
/* Receive Functions														  */
/******************************************************************************/

/***************************************************************************//**
 * @brief Stores the new character that is received on the serial communication
 *        into the input buffer.
 *
 * @param None.
 * 
 * @return None.
*******************************************************************************/
void CC110L_RC_WriteBuffer(unsigned char data) {
	/* Write the data to the current head of the buffer */
	RC_BUFFER[RC_HEAD] = data;
	
	/* Increment the head of the buffer */
	RC_HEAD = CC110L_IncrementIndex(RC_HEAD, MAX_RC_SIZE);
	
	/* If you have reached the tail, increment the tail of the buffer */
	if (RC_HEAD == RC_TAIL) { RC_TAIL = CC110L_IncrementIndex(RC_TAIL, MAX_RC_SIZE); }
}

/***************************************************************************//**
 * @brief Retrieves a received value from the RC buffer
 *
 * @param None.
 * 
 * @return Oldest character in the RC buffer.
*******************************************************************************/
unsigned char CC110L_RC_ReadBuffer() {
	unsigned char data;
	
	/* Temporarily disable the interrupts */
	INTERRUPT_GLOBAL = 0;
	
	/* Read the data from the end of the buffer */
	data = RC_BUFFER[RC_TAIL];
	
	/* Increment the tail of the buffer */
	RC_TAIL = CC110L_IncrementIndex(RC_TAIL, MAX_RC_SIZE);
	
	/* Re-enable the interrupt */
	INTERRUPT_GLOBAL = 1;
	
	return data;
}

/***************************************************************************//**
 * @brief Reads a byte off the RC register and writes it to the RC buffer.
 *
 * @param None.
 * 
 * @return None.
*******************************************************************************/
unsigned char CC110L_RC_ReadByte() {
    unsigned char data;
    
    /* Read a byte of data from the SPI */
    CommCC110L_Read(&data, 1);
    
	/* Read the data from the RC register */
	CC110L_RC_WriteBuffer(data);
	
	return data;
}

/***************************************************************************//**
 * @brief Checks if there is received data available to be read.
 *
 * @param None.
 * 
 * @return 1 - data is available to be read, 0 - data is not available.
*******************************************************************************/
unsigned char CC110L_RC_isDataAvailable() {
	return (RC_HEAD != RC_TAIL);
}

/***************************************************************************//**
 * @brief Resets the RC buffer.
 *
 * @param None.
 * 
 * @return None.
*******************************************************************************/
void CC110L_RC_Clear() {
	RC_HEAD = RC_TAIL = 0; // reset the head and the tail to the beginning of the buffer
}

/******************************************************************************/
/* Transmit Functions														  */
/******************************************************************************/

/***************************************************************************//**
 * @brief Stores a character that needs to be transmitted on the TX buffer.
 *
 * @param Byte of data to write to the transmit buffer.
 * 
 * @return None.
*******************************************************************************/
void CC110L_TX_WriteBuffer(unsigned char data) {
	/* Temporarily disable interrupts */
	INTERRUPT_GLOBAL = 0;
	
	/* Write the data to the current head of the buffer */
	TX_BUFFER[TX_HEAD] = data;
	
	/* Increment the head of the buffer */
	TX_HEAD = CC110L_IncrementIndex(TX_HEAD, MAX_TX_SIZE);
	
	/* If you have reached the tail, increment the tail of the buffer */
	if (TX_HEAD == TX_TAIL) { TX_TAIL = CC110L_IncrementIndex(TX_TAIL, MAX_RC_SIZE); }
	
	/* Re-enable the interrupts */
	INTERRUPT_GLOBAL = 1;
}

/***************************************************************************//**
 * @brief Puts multiple bytes of data into the transmit buffer.
 *
 * @param None.
 * 
 * @return None.
*******************************************************************************/
void CC110L_TX_WriteBufferMultiple(unsigned char* data) {
	/* Iterate through the data */
	while (*data != 0x00) { // while there is still data in the vector
		
		/* Write the data to the buffer */
		CC110L_TX_WriteBuffer(*data);
		
		/* Increment the data address */
		data = data + 1;
	}
}

/***************************************************************************//**
 * @brief Puts one frame of ADS1298 data into the transmit buffer.
 *
 * @param None.
 * 
 * @return None.
*******************************************************************************/
void CC110L_TX_WriteBufferFrame(unsigned char* data,  
								unsigned char frameSize) {
	unsigned char dummyIdx, i;
	
	/* Temporarily disable interrupts */
	INTERRUPT_GLOBAL = 0;
	
	/* Say that data is not ready */
	CommCC110L_DRDY_NOT = 1;
	
	/* Check if space is available in the transmit buffer */
    dummyIdx = TX_HEAD;
    for (i = 0; i < frameSize; i = i + 1) {
        dummyIdx = CC110L_IncrementIndex(dummyIdx, MAX_TX_SIZE);
    }
	
	/* Set the DRDY to data ready */
	CommCC110L_DRDY_NOT = 0;
	
	/* Re-enable the interrupts */
	INTERRUPT_GLOBAL = 1;
}

/***************************************************************************//**
 * @brief Outputs a byte of data to the Serial communication line.
 *
 * @param None.
 * 
 * @return None.
*******************************************************************************/
void CC110L_TX_SendByte() {
	/* Temporarily disable interrupts */
	INTERRUPT_GLOBAL = 0;
	
	/* Write the data at the end of the transmit buffer to the transmit register */
	CommCC110L_Write(&TX_BUFFER[TX_TAIL], 1);
	
	/* Increment the tail of the buffer */
	TX_TAIL = CC110L_IncrementIndex(TX_TAIL, MAX_TX_SIZE);
	
	/* Re-enable interrupts */
	INTERRUPT_GLOBAL = 1;
}

/***************************************************************************//**
 * @brief Outputs a frame of data to the Serial communication line.
 *
 * @param None.
 * 
 * @return None.
*******************************************************************************/
void CC110L_TX_SendFrames(unsigned char frameCnt, unsigned char frameSize) {
	unsigned char i, j;
	
	/* Temporarily disable interrupts */
	INTERRUPT_GLOBAL = 0;
	
	/* Set the DRDY to data not ready */
	CommCC110L_DRDY_NOT = 1;
	
	/* Iterate through the frames */
	for (i = 0; i < frameCnt; i = i + 1) {
		
		/* Iterate through the bytes in the frame */
		for (j = 0; j < frameSize; j = j + 1) {
			
			/* Write the data at the end of the transmit buffer to the transmit register */
			CommCC110L_Write(&TX_BUFFER[TX_TAIL], 1);
			
			/* Increment the tail of the buffer */
			TX_TAIL = CC110L_IncrementIndex(TX_TAIL, MAX_TX_SIZE);
			
			/* If you are overflowing, no data is available */
			if (!CC110L_TX_isDataAvailable()) {
				INTERRUPT_GLOBAL = 1;
				return;
			}
		}
	}
	
	/* Re-enable interrupts */
	INTERRUPT_GLOBAL = 1;
}

/***************************************************************************//**
 * @brief Checks if there is data available to be transmitted on the TX buffer.
 *
 * @param None.
 * 
 * @return 1 - data is available to be transmitted, 0 - data is not available..
*******************************************************************************/
unsigned char CC110L_TX_isDataAvailable() {
	return (TX_HEAD != TX_TAIL);
}

/***************************************************************************//**
 * @brief Resets the TX buffer.
 *
 * @param None.
 * 
 * @return None.
*******************************************************************************/
void CC110L_TX_Clear() {
	TX_HEAD = TX_TAIL = 0; // reset the head and the tail to the beginning of the buffer
}

/******************************************************************************/
/* General Functions Part 2													  */
/******************************************************************************/

/***************************************************************************//**
 * @brief Clears both the receive and transmit buffers.
 *
 * @param None.
 * 
 * @return None.
*******************************************************************************/
void CC110L_ClearAll() {
	CC110L_TX_Clear();
	CC110L_RC_Clear();
}

/***************************************************************************//**
 * @brief Interrupt service routing for EUSART communication.
 *
 * @param None.
 * 
 * @return None.
*******************************************************************************/
void CC110L_ISR() {
    if (CommCC110L_SSPINTERRUPT & CommCC110L_SSPINT_ENABLE) {
        CC110L_TX_WriteBuffer(0x41);
        CC110L_TX_WriteBuffer(0x52);
        CC110L_TX_WriteBuffer(0x73);
        CC110L_TX_SendByte();
        CC110L_TX_SendByte();
        CC110L_TX_SendByte();
        
        LATBbits.LATB7 = !LATBbits.LATB7;
    }
}