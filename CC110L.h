/***************************************************************************//**
 *   @file   CC110L.h
 *   @brief  Header file of the CC110L driver.
 *   @author Jiaxu Meng (jm611@duke.edu)
*******************************************************************************/

#ifndef CC110L_H
#define CC110L_H

/******************************************************************************/
/* CC110L COMMAND STROBES													  */
/******************************************************************************/
#define CC110L_SRES			0x30	// Reset chip
#define CC110L_SFSTXON		0x31	// Enable and calibrate frequency synthesizer
#define CC110L_SXOFF		0x32	// Turn off crystal oscillator
#define CC110L_SCAL			0x33	// Calibrate frequency synthesizer and turn it off
#define CC110L_SRX			0x34	// In Idle state, enable RX
#define CC110L_STX			0x35	// In Idle state, enable TX
#define CC110L_SIDLE		0x36	// Enter Idle state
#define CC110L_SPWD			0x39	// Enter power down mode when CSn goes high
#define CC110L_SFRX			0x3A	// Flush the RX FIFO buffer
#define CC110L_SFTX			0x3B	// Flush the TX FIFO buffer
#define CC110L_SNOP			0x3D	// No operation

/******************************************************************************/
/* CC110L REGISTER ADDRESSES												  */
/******************************************************************************/

/******************************************************************************/
/* CC110L Configuration Registers											  */
/******************************************************************************/
#define CC110L_IOCFG2		0x00
#define CC110L_IOCFG1		0x01
#define CC110L_IOCFG0		0x02
#define CC110L_FIFOTHR		0x03
#define CC110L_SYNC1		0x04
#define CC110L_SYNC0		0x05
#define CC110L_PKTLEN		0x06
#define CC110L_PKTCTRL1		0x07
#define CC110L_PKTCTRL0		0x08
#define CC110L_ADDR			0x09
#define CC110L_CHANNR		0x0A
#define CC110L_FSCTRL1		0x0B
#define CC110L_FSCTRL0		0x0C
#define CC110L_FREQ2		0x0D
#define CC110L_FREQ1		0x0E
#define CC110L_FREQ0		0x0F
#define CC110L_MDMCFG4		0x10
#define CC110L_MDMCFG3		0x11
#define CC110L_MDMCFG2		0x12
#define CC110L_MDMCFG1		0x13
#define CC110L_MDMCFG0		0x14
#define CC110L_DEVIATN		0x15
#define CC110L_MCSM2		0x16
#define CC110L_MCSM1		0x17
#define CC110L_MCSM0		0x18
#define CC110L_FOCCFG		0x19
#define CC110L_BSCFG		0x1A
#define CC110L_AGCCTRL2		0x1B
#define CC110L_AGCCTRL1		0x1C
#define CC110L_AGCCTRL0		0x1D
#define CC110L_FREND1		0x21
#define CC110L_FREND0		0x22
#define CC110L_FSCAL3		0x23
#define CC110L_FSCAL2		0x24
#define CC110L_FSCAL1		0x25
#define CC110L_FSCAL0		0x26
#define CC110L_TEST2		0x2C
#define CC110L_TEST1		0x2D
#define CC110L_TEST0		0x2E

/******************************************************************************/
/* CC110L Status Registers													  */
/******************************************************************************/
#define CC110L_PARTNUM		0x30
#define CC110L_VERSION		0x31
#define CC110L_FREQEST		0x32
#define CC110L_CRCREG		0x33
#define CC110L_RSSI			0x34
#define CC110L_MARCSTATE	0x35
#define CC110L_PKTSTATUS	0x38
#define CC110L_TXBYTES		0x3A
#define CC110L_RXBYTES		0x3B

/******************************************************************************/
/* CC110L CONFIGURATION REGISTER BITS										  */
/******************************************************************************/

/******************************************************************************/
/* CC110L GDO2 Output Pin Configuration										  */
/******************************************************************************/
#define CC110L_IOCFG2_INV		(0b1 << 6)	// Invert output, select active low (1)	

/******************************************************************************/
/* CC110L GDO1 Output Pin Configuration										  */
/******************************************************************************/
#define CC110L_IOCFG1_DS		(0b1 << 7)	// Set high (1) output drive strength on the GDO pins
#define CC110L_IOCFG1_INV		(0b1 << 6)	// Invert output, select active low (1)	

/******************************************************************************/
/* CC110L GDO0 Output Pin Configuration										  */
/******************************************************************************/
#define CC110L_IOCFG0_INV		(0b1 << 6)	// Invert output, select active low (1)	

/******************************************************************************/
/* CC110L RX FIFO and TX FIFO Thresholds									  */
/******************************************************************************/
#define CC110L_FIFOTHR_ADCRETENTION				(0b1 << 6)
																// RX attenuation (typical)
#define CC110L_FIFOTHR_CLOSEINRX_0DB			(0b00 << 4)		//	00 = 0 dB
#define CC110L_FIFOTHR_CLOSEINRX_6DB			(0b01 << 4)		//	01 = 6 dB
#define CC110L_FIFOTHR_CLOSEINRX_12DB			(0b10 << 4)		//	10 = 12 dB
#define CC110L_FIFOTHR_CLOSEINRX_18DB			(0b11 << 4)		//	11 = 18 dB
																// Set the threshold for the RX FIFO and TX FIFO
#define CC110L_FIFOTHR_THRESHOLD_RX4_TX61		(0b0000 << 0)	//	0000 = 4 bytes in RX, 61 byes in TX
#define CC110L_FIFOTHR_THRESHOLD_RX8_TX57		(0b0001 << 0)	//	0001 = 8 bytes in RX, 57 byes in TX
#define CC110L_FIFOTHR_THRESHOLD_RX12_TX53		(0b0010 << 0)	//	0010 = 12 bytes in RX, 53 byes in TX
#define CC110L_FIFOTHR_THRESHOLD_RX16_TX49		(0b0011 << 0)	//	0011 = 16 bytes in RX, 49 byes in TX
#define CC110L_FIFOTHR_THRESHOLD_RX20_TX45		(0b0100 << 0)	//	0100 = 20 bytes in RX, 45 byes in TX
#define CC110L_FIFOTHR_THRESHOLD_RX24_TX41		(0b0101 << 0)	//	0101 = 24 bytes in RX, 41 byes in TX
#define CC110L_FIFOTHR_THRESHOLD_RX28_TX37		(0b0110 << 0)	//	0110 = 28 bytes in RX, 37 byes in TX
#define CC110L_FIFOTHR_THRESHOLD_RX32_TX33		(0b0111 << 0)	//	0111 = 32 bytes in RX, 33 byes in TX
#define CC110L_FIFOTHR_THRESHOLD_RX36_TX29		(0b1000 << 0)	//	1000 = 36 bytes in RX, 29 byes in TX
#define CC110L_FIFOTHR_THRESHOLD_RX40_TX25		(0b1001 << 0)	//	1001 = 40 bytes in RX, 25 byes in TX
#define CC110L_FIFOTHR_THRESHOLD_RX44_TX21		(0b1010 << 0)	//	1010 = 44 bytes in RX, 21 byes in TX
#define CC110L_FIFOTHR_THRESHOLD_RX48_TX17		(0b1011 << 0)	//	1011 = 48 bytes in RX, 17 byes in TX
#define CC110L_FIFOTHR_THRESHOLD_RX52_TX13		(0b1100 << 0)	//	1100 = 52 bytes in RX, 13 byes in TX
#define CC110L_FIFOTHR_THRESHOLD_RX56_TX9		(0b1101 << 0)	//	1101 = 56 bytes in RX, 9 byes in TX
#define CC110L_FIFOTHR_THRESHOLD_RX60_TX5		(0b1110 << 0)	//	1110 = 60 bytes in RX, 5 byes in TX
#define CC110L_FIFOTHR_THRESHOLD_RX64_TX1		(0b1111 << 0)	//	1111 = 64 bytes in RX, 1 byes in TX

/******************************************************************************/
/* CC110L Packet Automation Control	1										  */
/******************************************************************************/
#define CC110L_PKTCTRL1_CRCAUTOFLUSH		(0b1 << 3)	// Enable automatic flush of RX FIFO when CRC is not OK
#define CC110L_PKTCTRL1_APPENDSTATUS		(0b1 << 2)	// When enabled, two status bytes will append to the payload of the packet
														// Controls address check configuration of received packages
#define CC110L_PKTCTRL1_ADRCHECK0			(0b00 << 0)	//	00 = No address check
#define CC110L_PKTCTRL1_ADRCHECK1			(0b01 << 0)	//	01 = Address check, no broadcast
#define CC110L_PKTCTRL1_ADRCHECK2			(0b10 << 0)	//	10 = Address check, 0 (0x00) broadcast
#define CC110L_PKTCTRL1_ADRCHECK3			(0b11 << 0)	//	11 = Address check, 0 (0x00) and 255 (0xFF) broadcast

/******************************************************************************/
/* CC110L Packet Automation Control	0										  */
/******************************************************************************/
																// Format of RX data
#define CC110L_PKTCTRL0_PKTFORMAT_NORMAL			(0b00 << 4)	//	00 = Normal mode, use FIFOs for RX and TX
#define CC110L_PKTCTRL0_PKTFORMAT_SYNCSERIAL		(0b01 << 4)	//	01 = Synchronous serial mode
#define CC110L_PKTCTRL0_PKTFORMAT_RANDOMTX			(0b10 << 4)	//	10 = Random TX mode
#define CC110L_PKTCTRL0_PKTFORMAT_ASYNCSERIAL		(0b11 << 4)	//	11 = Asynchronous serial mode
#define CC110L_PKTCTRL0_CRCEN						(0b1 << 2)	// CRC calculation enabled
																// Configure the packet length
#define CC110L_PKTCTRL0_LENGTH_FIXED				(0b00 << 0)	//	00 = Fixed packet length mode
#define CC110L_PKTCTRL0_LENGTH_VARIABLE				(0b01 << 0)	//	01 = Variable packet length mode
#define CC110L_PKTCTRL0_LENGTH_INFINITE				(0b10 << 0)	//	10 = Infinite packet length mode

/******************************************************************************/
/* CC110L Modem Configuration 2												  */
/******************************************************************************/
#define CC110L_MDMCFG2_DEMDCFILTOFF			(0b1 << 7)		// Disable digital DC filter before demodulator
															// Modulation format
#define CC110L_MDMCFG2_MODFORMAT_2FSK		(0b000 << 4)	//	000 = 2-FSK
#define CC110L_MDMCFG2_MODFORMAT_GFSK		(0b001 << 4)	//	001 = GFSK
#define CC110L_MDMCFG2_MODFORMAT_OOK		(0b011 << 4)	//	011 = OOK
#define CC110L_MDMCFG2_MODFORMAT_4FSK		(0b100 << 4)	//	100 = 4-FSK
#define CC110L_MDMCFG2_MANCHESTEREN			(0b1 << 3)		// Enables Manchester encoding/decoding
															// Combined sync-word qualifier mode
#define CC110L_MDMCFG2_SYNCMODE0			(0b000 << 0)	//	000 = No preamble/sync
#define CC110L_MDMCFG2_SYNCMODE1			(0b001 << 0)	//	001 = 15/16 sync word bits detected
#define CC110L_MDMCFG2_SYNCMODE2			(0b010 << 0)	//	010 = 16/16 sync word bits detected 
#define CC110L_MDMCFG2_SYNCMODE3			(0b011 << 0)	//	011 = 30/32 sync word bits detected
#define CC110L_MDMCFG2_SYNCMODE4			(0b100 << 0)	//	100 = No preamble/sync, carrier-sense above threshold
#define CC110L_MDMCFG2_SYNCMODE5			(0b101 << 0)	//	101 = 15/16, carrier-sense above threshold
#define CC110L_MDMCFG2_SYNCMODE6			(0b110 << 0)	//	110 = 16/16, carrier-sense above threshold
#define CC110L_MDMCFG2_SYNCMODE7			(0b111 << 0)	//	111 = 30/32, carrier-sense above threshold

/******************************************************************************/
/* CC110L Modem Configuration 1												  */
/******************************************************************************/
																// Minimum number of preamble bytes to be transmitted
#define CC110L_MDMCFG1_NUMPREAMBLE_2BYTES		(0b000 << 4)	//	000 = 2 bytes
#define CC110L_MDMCFG1_NUMPREAMBLE_3BYTES		(0b001 << 4)	//	000 = 3 bytes
#define CC110L_MDMCFG1_NUMPREAMBLE_4BYTES		(0b010 << 4)	//	000 = 4 bytes
#define CC110L_MDMCFG1_NUMPREAMBLE_6BYTES		(0b011 << 4)	//	000 = 6 bytes
#define CC110L_MDMCFG1_NUMPREAMBLE_8BYTES		(0b100 << 4)	//	000 = 8 bytes
#define CC110L_MDMCFG1_NUMPREAMBLE_12BYTES		(0b101 << 4)	//	000 = 12 bytes
#define CC110L_MDMCFG1_NUMPREAMBLE_16BYTES		(0b110 << 4)	//	000 = 16 bytes
#define CC110L_MDMCFG1_NUMPREAMBLE_24BYTES		(0b111 << 4)	//	000 = 24 bytes

/******************************************************************************/
/* CC110L Main Radio Control State Machine Configuration 1					  */
/******************************************************************************/
														// Selects CCA_MODE (clear channel indication)
#define CC110L_MCSM1_CCAMODE0				(0b00 << 4)	//	00 = Always
#define CC110L_MCSM1_CCAMODE1				(0b01 << 4)	//	01 = If RSSI below threshold
#define CC110L_MCSM1_CCAMODE2				(0b10 << 4)	//	10 = Unless currently receiving a packet
#define CC110L_MCSM1_CCAMODE3				(0b11 << 4)	//	11 = If RSSI below threshold unless currently receiving a packet
														// Select what should happen when a packet has been received
#define CC110L_MCSM1_RXOFFMODE_IDLE			(0b00 << 2)	//	00 = Idle
#define CC110L_MCSM1_RXOFFMODE_FSTXON		(0b01 << 2)	//	01 = FSTXON
#define CC110L_MCSM1_RXOFFMODE_TX			(0b10 << 2)	//	10 = TX
#define CC110L_MCSM1_RXOFFMODE_RX			(0b11 << 2)	//	11 = Stay in RX
														// Select what should happen when a packet has been sent
#define CC110L_MCSM1_TXOFFMODE_IDLE			(0b00 << 0)	//	00 = Idle
#define CC110L_MCSM1_TXOFFMODE_FSTXON		(0b01 << 0)	//	01 = FSTXON
#define CC110L_MCSM1_TXOFFMODE_TX			(0b10 << 0)	//	10 = Stay in TX (start sending preamble)
#define CC110L_MCSM1_TXOFFMODE_RX			(0b11 << 0)	//	11 = RX

/******************************************************************************/
/* CC110L Main Radio Control State Machine Configuration 0					  */
/******************************************************************************/
														// Automatically calibrate when going to RX or TX or back to Idle
#define CC110L_MCSM0_FSAUTOCAL0				(0b00 << 4)	//	00 = Never (manually calibrate using SCAL strobe)
#define CC110L_MCSM0_FSAUTOCAL1				(0b01 << 4)	//	01 = When going from Idle to RX or TX (or FSTXON)
#define CC110L_MCSM0_FSAUTOCAL2				(0b10 << 4)	//	10 = When going from RX or TX to Idle automatically
#define CC110L_MCSM0_FSAUTOCAL3				(0b11 << 4)	//	11 = Every 4th time when going from RX or TX to Idle automatically
														// Programs the number of times the 6-bit ripple counter must expire
#define CC110L_MCSM0_POTIMEOUT_EXP1			(0b00 << 2)	//	00 = Expire count - 1,   Timeout after XOSC start - about 2.3-2.4 us
#define CC110L_MCSM0_POTIMEOUT_EXP16		(0b01 << 2)	//	01 = Expire count - 16,  Timeout after XOSC start - about 37-39 us
#define CC110L_MCSM0_POTIMEOUT_EXP64		(0b10 << 2)	//	10 = Expire count - 64,  Timeout after XOSC start - about 149-155 us
#define CC110L_MCSM0_POTIMEOUT_EXP256		(0b11 << 2)	//	11 = Expire count - 256, Timeout after XOSC start - about 597-620 us
#define CC110L_MCSM0_XOSCFORCEON			(0b1 << 0)	// Force the XOSC to stay on in the SLEEP state

/******************************************************************************/
/* CC110L Frequency Offset Compensation Configuration						  */
/******************************************************************************/
#define CC110L_FOCCFG_FOCBSCSGATE				(0b1 << 5)	// If set, the demodulator freezes the frequency offset compensation
															// Frequency compensation loop gain to be used before a sync word is detected
#define CC110L_FOCCFG_FOCPRE_1K					(0b00 << 3)	//	00 = K
#define CC110L_FOCCFG_FOCPRE_2K					(0b01 << 3)	//	01 = 2K
#define CC110L_FOCCFG_FOCPRE_3K					(0b02 << 3)	//	10 = 3K
#define CC110L_FOCCFG_FOCPRE_4K					(0b03 << 3)	//	11 = 4K
															// Frequency compensation loop gain to be used after a sync word is detected
#define CC110L_FOCCFG_FOCPOSTK_SAMEPRE			(0b0 << 2)	//	0 = Same as FOC_PRE_K
#define CC110L_FOCCFG_FOCPOSTK_KDIV2			(0b1 << 2)	//	1 = K / 2
															// Saturation point for the frequency offset compensation algorithm
#define CC110L_FOCCFG_FOCLIMIT_NONE				(0b00 << 0)	//	00 = +/- 0 (no frequency offset compensation
#define CC110L_FOCCFG_FOCLIMIT_BWDIV8			(0b01 << 0)	//	01 = +/- BWchan / 8
#define CC110L_FOCCFG_FOCLIMIT_BWDIV4			(0b10 << 0)	//	10 = +/- BWchan / 4
#define CC110L_FOCCFG_FOCLIMIT_BWDIV2			(0b11 << 0)	//	11 = +/- BWchan / 2

/******************************************************************************/
/* CC110L Bit Synchronization Configuration									  */
/******************************************************************************/
													// Clock recovery feedback loop integral gain to be used before a sync word is detected
#define CC110L_BSCFG_BSPRE_1KI			(0b00 << 6)	//	00 = KI
#define CC110L_BSCFG_BSPRE_2KI			(0b01 << 6)	//	01 = 2KI
#define CC110L_BSCFG_BSPRE_3KI			(0b10 << 6)	//	10 = 3KI
#define CC110L_BSCFG_BSPRE_4KI			(0b11 << 6)	//	11 = 4KI
													// Clock recovery feedback loop proportional gain to be used before a sync word is detected
#define CC110L_BSCFG_BSPRE_1KP			(0b00 << 4)	//	00 = KP
#define CC110L_BSCFG_BSPRE_2KP			(0b01 << 4)	//	01 = 2KP
#define CC110L_BSCFG_BSPRE_3KP			(0b10 << 4)	//	10 = 3KP
#define CC110L_BSCFG_BSPRE_4KP			(0b11 << 4)	//	11 = 4KP
													// Clock recovery feedback loop integral gain to be used after a sync word is detected
#define CC110L_BSCFG_BSPOST_SAMEKI		(0b0 << 3)	//	0 = Same as BS_PRE_KI
#define CC110L_BSCFG_BSPOST_KIDIV2		(0b1 << 3)	//	1 = KI / 2
													// Clock recovery feedback loop proportional gain to be used after a sync word is detected
#define CC110L_BSCFG_BSPOST_SAMEKP		(0b0 << 2)	//	0 = Same as BS_PRE_KP
#define CC110L_BSCFG_BSPOST_KPDIV2		(0b1 << 2)	//	1 = KP
													// Saturation point for the data rate offset compensation algorithm
#define CC110L_BSCFG_BSLIMIT_NONE		(0b00 << 0)	//	00 = +/- 0 (No data rate offset compensation performed)
#define CC110L_BSCFG_BSLIMIT_3_125		(0b01 << 0)	//	01 = +/- 3.125% data rate offset
#define CC110L_BSCFG_BSLIMIT_6_25		(0b10 << 0)	//	10 = +/- 6.25% data rate offset
#define CC110L_BSCFG_BSLIMIT_12_5		(0b11 << 0)	//	11 = +/- 12.5% data rate offset

/******************************************************************************/
/* CC110L AGC Control 2														  */
/******************************************************************************/
																// Reduces the maximum allowable DVGA gain
#define CC110L_AGCCTRL2_MAXDVGAGAIN_ALL			(0b00 << 6)		//	00 = All gain settings can be used
#define CC110L_AGCCTRL2_MAXDVGAGAIN_1HIGH		(0b01 << 6)		//	01 = Highest gain setting cannot be used
#define CC110L_AGCCTRL2_MAXDVGAGAIN_2HIGH		(0b10 << 6)		//	10 = 2 highest gain settings cannot be used
#define CC110L_AGCCTRL2_MAXDVGAGAIN_3HIGH		(0b11 << 6)		//	11 = 3 highest gain settings cannot be used
																// Sets the maximum allowable LNA + LNA 2 gain relative to the maximum possible gain
#define CC110L_AGCCTRL2_MAXLNAGAIN_MAX			(0b000 << 3)	//	000 = Maximum possible LNA + LNA 2 gain
#define CC110L_AGCCTRL2_MAXLNAGAIN_2_6DB		(0b001 << 3)	//	001 = About 2.6 dB below maximum possible gain
#define CC110L_AGCCTRL2_MAXLNAGAIN_6_1DB		(0b010 << 3)	//	010 = About 6.1 dB below maximum possible gain
#define CC110L_AGCCTRL2_MAXLNAGAIN_7_4DB		(0b011 << 3)	//	011 = About 7.4 dB below maximum possible gain
#define CC110L_AGCCTRL2_MAXLNAGAIN_9_2DB		(0b100 << 3)	//	100 = About 9.2 dB below maximum possible gain
#define CC110L_AGCCTRL2_MAXLNAGAIN_11_5DB		(0b101 << 3)	//	101 = About 11.45 dB below maximum possible gain
#define CC110L_AGCCTRL2_MAXLNAGAIN_14_6DB		(0b110 << 3)	//	110 = About 14.6 dB below maximum possible gain
#define CC110L_AGCCTRL2_MAXLNAGAIN_17_1DB		(0b111 << 3)	//	111 = About 17.1 dB below maximum possible gain
																// Target value for the averaged amplitude from the digital channel filter (1 LSB = 0 dB)
#define CC110L_AGCCTRL2_MAGNTARGET_24DB			(0b000 << 0)	//	000 = 24 dB
#define CC110L_AGCCTRL2_MAGNTARGET_27DB			(0b001 << 0)	//	001 = 27 dB
#define CC110L_AGCCTRL2_MAGNTARGET_30DB			(0b010 << 0)	//	010 = 30 dB
#define CC110L_AGCCTRL2_MAGNTARGET_33DB			(0b011 << 0)	//	011 = 33 dB
#define CC110L_AGCCTRL2_MAGNTARGET_36DB			(0b100 << 0)	//	100 = 36 dB
#define CC110L_AGCCTRL2_MAGNTARGET_38DB			(0b101 << 0)	//	101 = 38 dB
#define CC110L_AGCCTRL2_MAGNTARGET_40DB			(0b110 << 0)	//	110 = 40 dB
#define CC110L_AGCCTRL2_MAGNTARGET_42DB			(0b111 << 0)	//	111 = 42 dB

/******************************************************************************/
/* CC110L AGC Control 1														  */
/******************************************************************************/
#define CC110L_AGCCTRL1_AGCLNAPRIORITY				(0b1 << 6)		// Selects between two different strategies for LNA and LNA 2 gain adjustment
																	// Sets the relative change threshold for asserting carrier sense
#define CC110L_AGCCTRL1_CARRIERSENSEREL_DIS			(0b00 << 4)		//	00 = Relative carrier sense threshold disabled
#define CC110L_AGCCTRL1_CARRIERSENSEREL_6DB			(0b01 << 4)		//	01 = 6 dB increase in RSSI value
#define CC110L_AGCCTRL1_CARRIERSENSEREL_10DB		(0b10 << 4)		//	10 = 10 dB increase in RSSI value 
#define CC110L_AGCCTRL1_CARRIERSENSEREL_14DB		(0b11 << 4)		//	11 = 14 dB increase in RSSI value
																	// Sets the absolute RSSI threshold for asserting carrier sense
#define CC110L_AGCCTRL1_CARRIERSENSEABS_DIS			(0b1000 << 0)	//	1000 = Absolute carrier sense threshold disabled
#define CC110L_AGCCTRL1_CARRIERSENSEABS_NEG7DB		(0b1001 << 0)	//	1001 = 7 dB below MAGN_TARGET setting
#define CC110L_AGCCTRL1_CARRIERSENSEABS_NEG6DB		(0b1010 << 0)	//	1010 = 6 dB below MAGN_TARGET setting
#define CC110L_AGCCTRL1_CARRIERSENSEABS_NEG5DB		(0b1011 << 0)	//	1011 = 5 dB below MAGN_TARGET setting
#define CC110L_AGCCTRL1_CARRIERSENSEABS_NEG4DB		(0b1100 << 0)	//	1100 = 4 dB below MAGN_TARGET setting
#define CC110L_AGCCTRL1_CARRIERSENSEABS_NEG3DB		(0b1101 << 0)	//	1101 = 3 dB below MAGN_TARGET setting
#define CC110L_AGCCTRL1_CARRIERSENSEABS_NEG2DB		(0b1110 << 0)	//	1110 = 2 dB below MAGN_TARGET setting
#define CC110L_AGCCTRL1_CARRIERSENSEABS_NEG1DB		(0b1111 << 0)	//	1111 = 1 dB below MAGN_TARGET setting
#define CC110L_AGCCTRL1_CARRIERSENSEABS_0DB			(0b0000 << 0)	//	0000 = At MAGN_TARGET setting
#define CC110L_AGCCTRL1_CARRIERSENSEABS_POS1DB		(0b0001 << 0)	//	0001 = 1 dB above MAGN_TARGET setting
#define CC110L_AGCCTRL1_CARRIERSENSEABS_POS2DB		(0b0010 << 0)	//	0010 = 2 dB above MAGN_TARGET setting
#define CC110L_AGCCTRL1_CARRIERSENSEABS_POS3DB		(0b0011 << 0)	//	0011 = 3 dB above MAGN_TARGET setting
#define CC110L_AGCCTRL1_CARRIERSENSEABS_POS4DB		(0b0100 << 0)	//	0100 = 4 dB above MAGN_TARGET setting
#define CC110L_AGCCTRL1_CARRIERSENSEABS_POS5DB		(0b0101 << 0)	//	0101 = 5 dB above MAGN_TARGET setting
#define CC110L_AGCCTRL1_CARRIERSENSEABS_POS6DB		(0b0110 << 0)	//	0110 = 6 dB above MAGN_TARGET setting
#define CC110L_AGCCTRL1_CARRIERSENSEABS_POS7DB		(0b0111 << 0)	//	0111 = 7 dB above MAGN_TARGET setting

/******************************************************************************/
/* CC110L AGC Control 0														  */
/******************************************************************************/
																// Sets the level of hysteresis on the magnitude deviation
#define CC110L_AGCCTRL0_HYSTLEVEL_NONE				(0b00 << 6)	//	00 = No hysteresis
#define CC110L_AGCCTRL0_HYSTLEVEL_LOW				(0b01 << 6)	//	01 = Low hysteresis
#define CC110L_AGCCTRL0_HYSTLEVEL_MEDIUM			(0b10 << 6)	//	10 = Medium hysteresis
#define CC110L_AGCCTRL0_HYSTLEVEL_LARGE				(0b11 << 6)	//	11 = Large hysteresis
																// Sets the number of channel filter samples from a gain adjustment has been made
#define CC110L_AGCCTRL0_WAITTIME_8SAMPLES			(0b00 << 4)	//	00 = 8 samples
#define CC110L_AGCCTRL0_WAITTIME_16SAMPLES			(0b01 << 4)	//	01 = 16 samples
#define CC110L_AGCCTRL0_WAITTIME_24SAMPLES			(0b10 << 4)	//	10 = 24 samples
#define CC110L_AGCCTRL0_WAITTIME_32SAMPLES			(0b11 << 4)	//	11 = 32 samples
																// Control when the AGC gain should be frozen
#define CC110L_AGCCTRL0_AGCFREEZE0					(0b00 << 2)	//	00 = Normal operation
#define CC110L_AGCCTRL0_AGCFREEZE1					(0b01 << 2)	//	01 = Gain setting is frozen when a sync word has been found
#define CC110L_AGCCTRL0_AGCFREEZE2					(0b10 << 2)	//	10 = Manually freeze the analogue gain setting and continue to adjust the digital gain
#define CC110L_AGCCTRL0_AGCFREEZE3					(0b11 << 2)	//	11 = Manually freezes both the analogue and the digital gain setting
																// 2-FSK and 4-FSK: Sets the averaging length for the amplitude from the channel filter
																// OOK: Sets the OOK decision boundary for OOK reception
#define CC110L_AGCCTRL0_FILTERLENGTH_8SAMPLES		(0b00 << 0)	//	00 = Channel filter samples - 8,  OOK decision boundary - 4 dB
#define CC110L_AGCCTRL0_FILTERLENGTH_16SAMPLES		(0b01 << 0)	//	01 = Channel filter samples - 16, OOK decision boundary - 8 dB 
#define CC110L_AGCCTRL0_FILTERLENGTH_32SAMPLES		(0b10 << 0)	//	10 = Channel filter samples - 32, OOK decision boundary - 12 dB
#define CC110L_AGCCTRL0_FILTERLENGTH_64SAMPLES		(0b11 << 0)	//	11 = Channel filter samples - 64, OOK decision boundary - 16 dB

/******************************************************************************/
/* FUNCTIONS																  */
/******************************************************************************/

/******************************************************************************/
/* General Functions Part 1													  */
/******************************************************************************/

/* Initialize the CC110L chip */
unsigned char CC110L_Initialize();

/* Increments the index value */
unsigned char CC110L_IncrementIndex(unsigned char idx, unsigned char max);

/******************************************************************************/
/* Receive Functions														  */
/******************************************************************************/

/* Stores new character to the RC buffer */
void CC110L_RC_WriteBuffer(unsigned char data);

/* Reads a byte of data from the RC buffer */
unsigned char CC110L_RC_ReadBuffer();

/* Reads a byte of data from the RC register */
unsigned char CC110L_RC_ReadByte();

/* Checks if data is available on the RC buffer */
unsigned char CC110L_RC_isDataAvailable();

/* Resets the RC buffer */
void CC110L_RC_Clear();

/******************************************************************************/
/* Transmit Functions														  */
/******************************************************************************/

/* Stores a new character to the TX buffer */
void CC110L_TX_WriteBuffer(unsigned char data);

/* Stores multiple new characters to the TX buffer */
void CC110L_TX_WriteBufferMultiple(unsigned char* data);

/* Stores a frame of data to the TX buffer */
void CC110L_TX_WriteBufferFrame(unsigned char* data, 
								unsigned char frameSize);

/* Sends out a byte on the TX register */
void CC110L_TX_SendByte();

/* Sends out frames of data on the TX register */
void CC110L_TX_SendFrames(unsigned char frameCnt, unsigned char frameSize);

/* Checks if data is available on the TX buffer */
unsigned char CC110L_TX_isDataAvailable();

/* Resets the TX buffer */
void CC110L_TX_Clear();

/******************************************************************************/
/* General Functions Part 2													  */
/******************************************************************************/

/* Clears both RC and TX buffers */
void CC110L_ClearAll();

/* Interrupt service routine for SSP communication */
void CC110L_ISR();

#endif /* CC110L_H */