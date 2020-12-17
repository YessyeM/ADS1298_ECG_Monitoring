/***************************************************************************//**
 *   @file   ADS1298.c
 *   @brief  Implementation of ADS1298 Driver.
 *   @author Jiaxu Meng (jm611@duke.edu)
*******************************************************************************/

/*****************************************************************************/
/* INCLUDE FILES															 */
/*****************************************************************************/
#include "CommADS1298.h"
#include "ADS1298.h"			

/*****************************************************************************/
/* CONSTANTS    															 */
/*****************************************************************************/
static unsigned char frameSize1;
static unsigned char frameSize2;

/*****************************************************************************/
/* FUNCTIONS																 */
/*****************************************************************************/

/***************************************************************************//**
 * @brief	Writes a single opcode to the ADS1298.
 * 
 * @param	writeVal - Char denoting the opcode you want to write.
 * 
 * @return	None.
*******************************************************************************/
void ADS1298_WriteSingleOpCode(unsigned char writeVal) {
	CommADS1298_Write(&writeVal, 1);
}

/***************************************************************************//**
 * @brief	Writes data to the registers of the ADS1298. 
 * 
 * @param 	address - Char denoting the initial address to write to.
 * @param 	writeNum - Char denoting the number of registers to write.
 * @param 	regVals - Pointer to the array containing the values to write.
 * 
 * @return 	None.
*******************************************************************************/
void ADS1298_WriteRegisters(unsigned char device,
							unsigned char address, 
							unsigned char writeNum, 
							unsigned char* regVals) {
	unsigned char writeOpCode[2] = {0, 0};
	
	/* Define the opcode */
	writeOpCode[0] = ADS1298_WREG + address;
	writeOpCode[1] = writeNum - 1;
	
	/* Write the opcode and register values */
    if (device == 1) {
		CommADS1298_CS1_PIN = 0;
		CommADS1298_Write(writeOpCode, 2);
		CommADS1298_Write(regVals, writeNum);
		CommADS1298_CS1_PIN = 1;
	} else if (device == 2) {
		CommADS1298_CS2_PIN = 0;
		CommADS1298_Write(writeOpCode, 2);
		CommADS1298_Write(regVals, writeNum);
		CommADS1298_CS2_PIN = 1;
	}
}

/***************************************************************************//**
 * @brief	Reads data from the registers of the ADS1298. 
 * 
 * @param	address - Char denoting the initial address to read from.
 * @param	writeNum - Char denoting the number of registers to read.
 * @param	regVals - Pointer to the array storing the read register data.
 * 
 * @return	None.
*******************************************************************************/
void ADS1298_ReadRegisters(unsigned char device, 
						   unsigned char address,
						   unsigned char readNum, 
						   unsigned char* regVals) {
	unsigned char readOpCode[2] = {0, 0};
	
	/* Define the opcode */
	readOpCode[0] = (unsigned char) ADS1298_RREG + address;
	readOpCode[1] = readNum - 1;
	
	/* Write the opcode and read the register values */
	if (device == 1) {
		CommADS1298_CS1_PIN = 0;
		CommADS1298_Write(readOpCode, 2);
		CommADS1298_Read(regVals, readNum);
		CommADS1298_CS1_PIN = 1;
	} else if (device == 2) {
		CommADS1298_CS2_PIN = 0;
		CommADS1298_Write(readOpCode, 2);
		CommADS1298_Read(regVals, readNum);
		CommADS1298_CS2_PIN = 1;
	}
}

/***************************************************************************//**
 * @brief	Goes through the power-up sequencing of the device. Before device
 *          power up, all digital and analog inputs must be low. At the time of 
 *          power up, keep all these signals low until the power supplies have
 *          stabilized. Allow time for the supply voltages to reach their final
 *          to reach their final value, and then begin supplying the master 
 *          clock signal to the CLK pin. Wait for time t_POR (wait after power 
 *          up until reset, 2^18 clock cycles), then transmit a reset pulse. 
 *          Issue the reset after t_POR or after VCAP1 voltage is greater than 
 *          1.1 V depends on RC time constant). 
 * 
 * @param	None.
 * 
 * @return	1 - power-up success, 0 - power-up failed.
*******************************************************************************/
unsigned char ADS1298_PowerUp() {
	unsigned int i = 0;
    
	/* Bring the PWR pin HIGH to turn on the device */
	ADS1298_PWR_PIN = 1;
	for (i = 0; i < 50000; i++) {} 
	
    /* Reset the device by toggling the RESET pin */
    ADS1298_RESET_PIN = 0;
    for (i = 0; i < 500; i++) {} // wait at least 18 shift clock cycles
    ADS1298_RESET_PIN = 1;
    for (i = 0; i < 500; i++) {} // wait at least 18 shift clock cycles
    
	/* Reset the device by issuing the RESET opcode */
    /*change*/
    CommADS1298_CS1_PIN = 0;
    ADS1298_WriteSingleOpCode(ADS1298_RESET);
    CommADS1298_CS1_PIN = 1;
    CommADS1298_CS2_PIN = 0;
    ADS1298_WriteSingleOpCode(ADS1298_RESET);
	CommADS1298_CS2_PIN = 1;
    for (i = 0; i < 500; i++) {} // wait at least 18 shift clock cycles
    
    /* Stop the read data continuously mode (SDATAC) */
    /*change*/
	CommADS1298_CS1_PIN = 0;
    ADS1298_WriteSingleOpCode(ADS1298_SDATAC);
    CommADS1298_CS1_PIN = 1;
    CommADS1298_CS2_PIN = 0;
    ADS1298_WriteSingleOpCode(ADS1298_SDATAC);
	CommADS1298_CS2_PIN = 1;
    for (i = 0; i < 50; i++) {} // wait at least 4 shift clock cycles
    
    /* Stop the data conversion (STOP) */
    ADS1298_START_PIN = 0;
    for (i = 0; i < 50; i++) {} // wait at least 4 shift clock cycles
    
	return 1;
}

/***************************************************************************//**
 * @brief	Turns off the device.
 * 
 * @param	None.
 * 
 * @return	1 - power-up success, 0 - power-up failed
*******************************************************************************/
unsigned char ADS1298_PowerDown() {
    unsigned char i;
    
	/* Stop the read data continuously mode (SDATAC) */
    /*change*/
	CommADS1298_CS1_PIN = 0;
    ADS1298_WriteSingleOpCode(ADS1298_SDATAC);
    CommADS1298_CS1_PIN = 1;
    CommADS1298_CS2_PIN = 0;
    ADS1298_WriteSingleOpCode(ADS1298_SDATAC);
	CommADS1298_CS2_PIN = 1;
    for (i = 0; i < 50; i++) {} // wait at least 4 shift clock cycles
	
	/* Stop the data conversion (STOP) */
	ADS1298_START_PIN = 0;
    for (i = 0; i < 50; i++) {} // wait at least 4 shift clock cycles
	
	/* Bring the PWR pin LOW in order to turn off the device */
	ADS1298_PWR_PIN = 0;
	for (i = 0; i < 50000; i++) {} 
	
	return 1;
}

/***************************************************************************//**
 * @brief	Computes the size of a single frame of data in bytes for each 
 *          device. Every frame has a 24 bit status word. 
 * 
 * @param	None.
 * 
 * @return	None.
*******************************************************************************/
void ADS1298_ComputeFrameSize() {
	unsigned char i;
    unsigned char numCh1 = 0; // number of channels active in device 1
	unsigned char numCh2 = 0; // number of channels active in device 2
    unsigned char chRegVals[16];
    
    /* Read the register values containing the channel settings */
    ADS1298_ReadRegisters(1, ADS1298_CH1SET, 8, chRegVals);
	ADS1298_ReadRegisters(2, ADS1298_CH1SET, 8, chRegVals + 8);
    
    /* Iterate through the channel values to see which ones are powered down */
    for (i = 0; i < 16; i = i + 1) {
        if ((chRegVals[i] & 0b10000000) == 0x00) { // if not powered down, increment
			if ((i >= 0) && (i < 8))  { numCh1 = i + 1; } 
			if ((i >= 8) && (i < 16)) { numCh2 = i - 7; }
        }
    }
    
    /* Calculate the frame size */
	if (numCh1 > 0) { frameSize1 = (numCh1 * 3) + 3; } // each channel spits out 24 bits of data and status word is 24 bits
	else { frameSize1 = 0; } // if there are no channels active, set frame size to 0
	if (numCh2 > 0) { frameSize2 = (numCh2 * 3) + 3; }
	else { frameSize2 = 0; }
}

/***************************************************************************//**
 * @brief	Turns the specified channels on and off.
 * 
 * @param	Pointer to 2 character array storing information on which channels
 *          to turn on and turn off.
 * 
 * @return	None.
*******************************************************************************/
void ADS1298_SetChannels(unsigned char* channels) {
    unsigned char writeVals[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	unsigned char i, j;
	
	/* Iterate through the 2 devices */
	for (i = 0; i < 2; i = i + 1) {
		
		/* Iterate through the 8 channels of one device */
		for (j = 0; j < 8; j = j + 1) {
			/* Define the register values for the channel settings */
			if (((channels[i] >> (7 - j)) & 0x01) == 0x01) { // turn channel on
				writeVals[j] = ADS1298_CHSET_GAIN_12 | ADS1298_CHSET_MUX_TEST;
			} else { // turn channel off
				writeVals[j] = ADS1298_CHSET_PD | ADS1298_CHSET_MUX_SHORT;
			}
		}
		
		/* Send the register values */
		ADS1298_WriteRegisters(i + 1, ADS1298_CH1SET, 8, writeVals);
	}
	
	/* Compute the new frame size */
	ADS1298_ComputeFrameSize();
}

/***************************************************************************//**
 * @brief	Starts continuous data conversions.
 * 
 * @param	None.
 * 
 * @return	None.
*******************************************************************************/
void ADS1298_StartConversion() {
	/* Issue the RDATAC command to read data continuously */
    /*change*/
    CommADS1298_CS1_PIN = 0;
    ADS1298_WriteSingleOpCode(ADS1298_RDATAC);
    CommADS1298_CS1_PIN = 1;
    CommADS1298_CS2_PIN = 0;
    ADS1298_WriteSingleOpCode(ADS1298_RDATAC);
	CommADS1298_CS2_PIN = 1;
}

/***************************************************************************//**
 * @brief	Stops continuous data conversions.
 * 
 * @param	None.
 * 
 * @return	None.
*******************************************************************************/
void ADS1298_StopConversion() {
	/* Issue the SDATAC opcode to stop reading data */
    /*change*/
    CommADS1298_CS1_PIN = 0;
    ADS1298_WriteSingleOpCode(ADS1298_SDATAC);
    CommADS1298_CS1_PIN = 1;
    CommADS1298_CS2_PIN = 0;
    ADS1298_WriteSingleOpCode(ADS1298_SDATAC);
	CommADS1298_CS2_PIN = 1;
}

/***************************************************************************//**
 * @brief	Reads a single frame of data from the implant.
 * 
 * @param	pDataBuffer - Pointer to the array storing the streamed data.
 * 
 * @return	None.
*******************************************************************************/
void ADS1298_ReadFrame(unsigned char* pDataBuffer) {
	/* Wait for the DRDY_NOT line to go low */
	while (ADS1298_DRDY1_NOT || ADS1298_DRDY2_NOT);
	
	/* If frame size for device 1 is 0, do not read from device 1 */
	if (frameSize1 != 0) { // device 1

		/* Bring the CS pin low */
		CommADS1298_CS1_PIN = 0;

		/* Read all the data in the frame */
		CommADS1298_Read(pDataBuffer, 3); // read the header
		CommADS1298_Read(pDataBuffer, frameSize1 - 3); // overwrite the header

		/* Increment the address of pDataBuffer */
		pDataBuffer = pDataBuffer + (frameSize1 - 3);

		/* Bring the CS pin high */
		CommADS1298_CS1_PIN = 1;

	/* If frame size for device 2 is 0, do not read from device 2 */
	} else if (frameSize2 != 0) { // device 2

		/* Bring the CS pin low */
		CommADS1298_CS2_PIN = 0;

		/* Read all the data in the frame */
		CommADS1298_Read(pDataBuffer, 3); // read the header
		CommADS1298_Read(pDataBuffer, frameSize2 - 3); // overwrite the header

		/* Increment the address of pDataBuffer */
		pDataBuffer = pDataBuffer + (frameSize2 - 3);

		/* Bring the CS pin high */
		CommADS1298_CS2_PIN = 1;
	}
}

/***************************************************************************//**
 * @brief	Streams electrogram data from the ADS1298. You could use the START
 *          pin, but using the START opcode means less wires are needed.
 * 
 * @param	pDataBuffer - Pointer to the array storing the streamed data.
 * @param	frameCnt - Long denoting the number of frames to collect.
 * 
 * @return	None.
*******************************************************************************/
void ADS1298_ReadData(unsigned char* pDataBuffer, 
					  unsigned long frameCnt) {
	unsigned char i;
	
	/* Bring the START pin high to start converting data */
    ADS1298_START_PIN = 1;
	
    /* If you just want to read a single frame of data */
    if (frameCnt == 1) { 
        
        /* If frame size for device 1 is 0, do not read from device 1 */
        if (frameSize1 != 0) {
            
            /* Bring the CS pin low */
            CommADS1298_CS1_PIN = 0;

            /* Wait for the DRDY_NOT line to go low */
            while (ADS1298_DRDY1_NOT);

            /* Issue the RDATA opcode to read a single frame of data */
            ADS1298_WriteSingleOpCode(ADS1298_RDATA);

            /* Read the data in the frame */
            CommADS1298_Read(pDataBuffer, frameSize1);

            /* Issue the STOP opcode to stop converting data */
            ADS1298_WriteSingleOpCode(ADS1298_STOP);

            /* Exit from the current device by bringing CS high */
            CommADS1298_CS1_PIN = 1;

        /* If frame size for device 2 is 0, do not read from device 2 */
        } else if (frameSize2 != 0) {

            /* Bring the CS pin low */
            CommADS1298_CS2_PIN = 0;

            /* Wait for the DRDY_NOT line to go low */
            while (ADS1298_DRDY2_NOT);

            /* Issue the RDATA opcode to read a single frame of data */
            ADS1298_WriteSingleOpCode(ADS1298_RDATA);

            /* Read the data in the frame */
            CommADS1298_Read(pDataBuffer, frameSize2);

            /* Exit from the current device by bringing CS high */
            CommADS1298_CS2_PIN = 1;
        }
        
        /* Bring the START pin low to stop the data conversions */
        ADS1298_START_PIN = 0;
        return;
    }
    
    /* Issue the RDATAC command to read data continuously */
    /*change*/
    CommADS1298_CS1_PIN = 0;
    ADS1298_WriteSingleOpCode(ADS1298_RDATAC);
    CommADS1298_CS1_PIN = 1;
    CommADS1298_CS2_PIN = 0;
    ADS1298_WriteSingleOpCode(ADS1298_RDATAC);
	CommADS1298_CS2_PIN = 1;
    
    /* Iterate through the specified number of frames */
	for (i = 0; i < frameCnt; i = i + 1) {
		
        /* Wait for the DRDY_NOT line to go low */
        while (ADS1298_DRDY1_NOT || ADS1298_DRDY2_NOT);
        
        /* If frame size for device 1 is 0, do not read from device 1 */
        if (frameSize1 != 0) { // device 1

            /* Bring the CS pin low */
            CommADS1298_CS1_PIN = 0;

            /* Read all the data in the frame */
            CommADS1298_Read(pDataBuffer, 3); // read the header
            CommADS1298_Read(pDataBuffer, frameSize1 - 3); // overwrite the header

            /* Increment the address of pDataBuffer */
            pDataBuffer = pDataBuffer + (frameSize1 - 3);

            /* Bring the CS pin high */
            CommADS1298_CS1_PIN = 1;

        /* If frame size for device 2 is 0, do not read from device 2 */
        } else if (frameSize2 != 0) { // device 2

            /* Bring the CS pin low */
            CommADS1298_CS2_PIN = 0;

            /* Read all the data in the frame */
            CommADS1298_Read(pDataBuffer, 3); // read the header
            CommADS1298_Read(pDataBuffer, frameSize2 - 3); // overwrite the header

            /* Increment the address of pDataBuffer */
            pDataBuffer = pDataBuffer + (frameSize2 - 3);

            /* Bring the CS pin high */
            CommADS1298_CS2_PIN = 1;
        }
	}
    
    /* Issue the SDATAC opcode to stop reading data */
    /*change*/
    CommADS1298_CS1_PIN = 0;
    ADS1298_WriteSingleOpCode(ADS1298_SDATAC);
    CommADS1298_CS1_PIN = 1;
    CommADS1298_CS2_PIN = 0;
    ADS1298_WriteSingleOpCode(ADS1298_SDATAC);
	CommADS1298_CS2_PIN = 1;
    for (i = 0; i < 50; i++) {} // wait at least 4 shift clock cycles
    
    /* Bring the START pin low to stop the data conversions */
    ADS1298_START_PIN = 0;
}

/***************************************************************************//**
 * @brief	Gets the total frame size.
 * 
 * @param	None.
 * 
 * @return	Total frame size (sum of the frame sizes from both devices).
*******************************************************************************/
unsigned long ADS1298_GetFrameSize() {
	return (frameSize1 + frameSize2);
}

/***************************************************************************//**
 * @brief Initialize the ADS1298 registers for testing. 
 * 
 * @param None.
 * 
 * @return 1 - initialization success, 0 - initialization failed
*******************************************************************************/
unsigned char ADS1298_RegistersForTesting(unsigned char* channels) {
	unsigned char writeVals[25] = {0, 0, 0, 0, 0, \
                                   0, 0, 0, 0, 0, \
                                   0, 0, 0, 0, 0, \
								   0, 0, 0, 0, 0, \
								   0, 0, 0, 0, 0};
	
	/* Define the common register values to write*/
	/* CONFIG1    */ writeVals[0]  = ADS1298_CONFIG1_HR | ADS1298_CONFIG1_DR_2K; // 0x84
	/* CONFIG2    */ writeVals[1]  = ADS1298_CONFIG2_WCTCHOPCONST | ADS1298_CONFIG2_INTTEST | ADS1298_CONFIG2_TESTAMP | ADS1298_CONFIG2_TESTFREQ_AC20;
	/* CONFIG3    */ writeVals[2]  = ADS1298_CONFIG3_INTREFEN | (0b1u << 6);
	/* LOFF       */ writeVals[3]  = 0x00;
	/* CHXSET     */ // channel settings in index values 4 to 11
	/* RLD_SENSP  */ writeVals[12] = 0x00;
	/* RLD_SENSN  */ writeVals[13] = 0x00;
	/* LOFF_SENSP */ writeVals[14] = 0x00;
	/* LOFF_SENSN */ writeVals[15] = 0x00;
	/* LOFF_FLIP  */ writeVals[16] = 0x00;
	/* LOFF_STATP */ writeVals[17] = 0x00;
	/* LOFF_STATN */ writeVals[18] = 0x00;
	/* GPIO       */ writeVals[19] = 0x00;
	/* PACE       */ writeVals[20] = 0x00;
	/* RESP       */ writeVals[21] = 0x00;
	/* CONFIG4    */ writeVals[22] = 0x00;
	/* WCT1       */ writeVals[23] = 0x00;
	/* WCT2       */ writeVals[24] = 0x00;
	
    /* Write the standard configuration registers */
    ADS1298_WriteRegisters(1, ADS1298_CONFIG1, 4, writeVals);
    ADS1298_WriteRegisters(2, ADS1298_CONFIG1, 4, writeVals);
    
	/* Set the channels */
	ADS1298_SetChannels(channels);
	
	return 1;
}

/***************************************************************************//**
 * @brief Initialize the ADS1298 registers. 
 * 
 * @param channels - 2 bytes (16 bits) denoting the channels we want to turn on.
 * 
 * @return 1 - initialization success, 0 - initialization failed
*******************************************************************************/
unsigned char ADS1298_Initialize(unsigned char* channels) {
	unsigned char status = 0;
	
	/* Initialize the device */
	status = CommADS1298_Initialize();
	if (!status) { return 0; } // if initialization was unsuccessful, return 0
	
	/* Power up the device */
	status = ADS1298_PowerUp(); // if initialization was successful, power up the device
	if (!status) { return 0; } // if the power up was unsuccessful, return 0
	
	/* Set the registers for testing */
	status = ADS1298_RegistersForTesting(channels);
	if (!status) { return 0; }
	
    /* Compute the frame size */
    ADS1298_ComputeFrameSize();
    
	return 1;
}