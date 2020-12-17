/***************************************************************************//**
 *   @file   ADS1298.h
 *   @brief  Header file of ADS1298 driver.
 *   @author Jiaxu Meng (jm611@duke.edu)
*******************************************************************************/

#ifndef ADS1298_H
#define ADS1298_H

/******************************************************************************/
/* ADS1298 OPCODE COMMANDS													  */
/******************************************************************************/

/******************************************************************************/
/* ADS1298 Opcode System Commands											  */
/******************************************************************************/
#define ADS1298_WAKEUP		0x02	// wakeup from standby mode
#define ADS1298_STANDBY		0x04	// enter standby mode
#define ADS1298_RESET		0x06	// reset the device
#define ADS1298_START		0x08	// start/restart conversions
#define ADS1298_STOP		0x0A	// stop conversion

/******************************************************************************/
/* ADS1298 Opcode Data Read Commands										  */
/******************************************************************************/
#define ADS1298_RDATAC		0x10	// read data continuous mode
#define ADS1298_SDATAC		0x11	// stop read data continuous mode
#define ADS1298_RDATA		0x12	// read data by command

/******************************************************************************/
/* ADS1298 Opcode Register Read Commands									  */
/******************************************************************************/
#define ADS1298_RREG		0x20	// first byte of read register command
#define ADS1298_WREG		0x40	// first byte of write register command

/******************************************************************************/
/* ADS1298 REGISTER ADDRESSES												  */
/******************************************************************************/
#define ADS1298_ID				0x00
#define ADS1298_CONFIG1			0x01
#define ADS1298_CONFIG2			0x02
#define ADS1298_CONFIG3			0x03
#define ADS1298_LOFF			0x04
#define ADS1298_CH1SET			0x05
#define ADS1298_CH2SET			0x06
#define ADS1298_CH3SET			0x07
#define ADS1298_CH4SET			0x08
#define ADS1298_CH5SET			0x09
#define ADS1298_CH6SET			0x0A
#define ADS1298_CH7SET			0x0B
#define ADS1298_CH8SET			0x0C
#define ADS1298_RLDSENSP		0x0D
#define ADS1298_RLDSENSN		0x0E
#define ADS1298_LOFFSENSP		0x0F
#define ADS1298_LOFFSENSN		0x10
#define ADS1298_LOFFFLIP		0x11
#define ADS1298_LOFFSTATP		0x12
#define ADS1298_LOFFSTATN		0x13
#define ADS1298_GPIO			0x14
#define ADS1298_PACE			0x15
#define ADS1298_RESP			0x16
#define ADS1298_CONFIG4			0x17
#define ADS1298_WCT1			0x18
#define ADS1298_WCT2			0x19

/******************************************************************************/
/* ADS1298 REGISTER VALUES													  */
/******************************************************************************/

/******************************************************************************/
/* ADS1298 ID Control Register												  */
/******************************************************************************/
#define ADS1298_ID_DEVID		(0b111u << 5) // Device ID mask
#define ADS1298_ID_CHID			(0b111u << 0) // Channel ID mask

/******************************************************************************/
/* ADS1298 Configuration Register 1											  */
/******************************************************************************/
#define ADS1298_CONFIG1_HR			(0b1u << 7)		// High-resolution or low-power mode
													//	0 = LP mode
													//	1 = HR mode
#define ADS1298_CONFIG1_DAISYDIS	(0b1u << 6)		// Daisy-chain or multiple readback mode
													//	0 = Daisy-chain mode 
													//	1 = Multiple readback mode
#define ADS1298_CONFIG1_CLK			(0b1u << 5)  	// CLK connection
													//	0 = Oscillator clock output disabled
													//	1 = Oscillator clock output enabled
													// Output data rate
#define ADS1298_CONFIG1_DR_32K		(0b000u << 0)	//	000 = HR: 32kSPS, LP: 16kSPS
#define ADS1298_CONFIG1_DR_16K		(0b001u << 0)	//	001 = HR: 16kSPS, LP: 8kSPS
#define ADS1298_CONFIG1_DR_8K		(0b010u << 0)	//	010 = HR: 8kSPS,  LP: 4kSPS
#define ADS1298_CONFIG1_DR_4K		(0b011u << 0)	//	011 = HR: 4kSPS,  LP: 2kSPS
#define ADS1298_CONFIG1_DR_2K		(0b100u << 0)	//	100 = HR: 2kSPS,  LP: 1kSPS
#define ADS1298_CONFIG1_DR_1K		(0b101u << 0)	//	101 = HR: 1kSPS,  LP: 500kSPS
#define ADS1298_CONFIG1_DR_500		(0b110u << 0)	//	110 = HR: 500SPS, LP: 250kSPS

/******************************************************************************/
/* ADS1298 Configuration Register 2											  */
/******************************************************************************/
#define ADS1298_CONFIG2_WCTCHOPCONST		(0b1u << 5)	// WCT chopping scheme
														//	0 = Chopping frequency varies
														//	1 = Chopping frequency constant at fMOD/16
#define ADS1298_CONFIG2_INTTEST				(0b1u << 4)	// Test signal source
														//	0 = Test signals are driven externally
														//	1 = Test signals are driven internally
#define ADS1298_CONFIG2_TESTAMP				(0b1u << 2)	// Test signal amplitude
														//	0 = 1 x -(VREFP-VREFN) / 2400V
														//	1 = 2 x -(VREFP-VREFN) / 2400V
														// Test signal frequency
#define ADS1298_CONFIG2_TESTFREQ_AC21		(0b00u << 0)	//	00 = Pulsed at fCLK/2^21
#define ADS1298_CONFIG2_TESTFREQ_AC20		(0b01u << 0)	//	01 = Pulsed at fCLK/2^20
#define ADS1298_CONFIG2_TESTFREQ_NONE		(0b11u << 0)	//	10 = Not used
#define ADS1298_CONFIG2_TESTFREQ_DC			(0b11u << 0)	//	11 = At DC


/******************************************************************************/
/* ADS1298 Configuration Register 3											  */
/******************************************************************************/
#define ADS1298_CONFIG3_INTREFEN		(0b01u << 7)	// Power-down reference buffer
													//	0 = Power-down internal reference buffer
													//	1 = Enable internal reference buffer
#define ADS1298_CONFIG3_VREF4V			(0b01u << 5)	// Reference voltage
													//	0 = VREFP is 2.4V
													//	1 = VREFP is 4V (only to be used with 5V supply)
#define ADS1298_CONFIG3_RLDMEAS			(0b01u << 4) // RLD measurement
													//	0 = Open
													//	1 = RLD_IN signal is routed to channel that has the MUX_Setting 010
#define ADS1298_CONFIG3_RLDREFINT		(0b01u << 3)	// RLDREF signal
													//	0 = RLDREF signal fed externally
													//	1 = RLDREF signal (AVDD-AVSS)/2 generated internally
#define ADS1298_CONFIG3_RLDBUFFEN		(0b01u << 2)	// RLD buffer power
													//	0 = RLD buffer is powered down
													//	1 = RLD buffer is enable
#define ADS1298_CONFIG3_RLDLOFFSENS		(0b01u << 1)	// RLD sense function
													//	0 = RLD sense disabled
													//	1 = RLD sens is enabled
#define ADS1298_CONFIG3_RLDSTAT			(0b11u << 0)	// RLD lead-off status mask
													//	0 = RLD is connected
													//	1 = RLD is not connected

/******************************************************************************/
/* ADS1298 Lead-Off Control Register										  */
/******************************************************************************/
														// Lead-off comparator threshold
#define ADS1298_LOFF_COMPTH_95			(0b000u << 5)	//	000 = Pos: 95%,   Neg: 5%
#define ADS1298_LOFF_COMPTH_92_5		(0b001u << 5)	//	001 = Pos: 92.5%, Neg: 7.5%
#define ADS1298_LOFF_COMPTH_90			(0b010u << 5)	//	010 = Pos: 90%,   Neg: 10%
#define ADS1298_LOFF_COMPTH_87_5		(0b011u << 5)	//	011 = Pos: 87.5%, Neg: 12.5%
#define ADS1298_LOFF_COMPTH_85			(0b100u << 5)	//	100 = Pos: 85%,   Neg: 15%
#define ADS1298_LOFF_COMPTH_80			(0b101u << 5)	//	101 = Pos: 80%,   Neg: 20%
#define ADS1298_LOFF_COMPTH_75			(0b110u << 5)	//	110 = Pos: 75%,   Neg: 25%
#define ADS1298_LOFF_COMPTH_70			(0b111u << 5)	//	111 = Pos: 70%,   Neg: 30%
#define ADS1298_LOFF_VLEADOFF			(0b1u << 4)		// Lead-off detection mode
														//	0 = Current source mode lead-off
														//	1 = Pullup or pulldown resistor mode lead-off
														// Lead-off current magnitude
#define ADS1298_LOFF_ILEADOFF_6			(0b00u << 2)		//	00 = 6nA
#define ADS1298_LOFF_ILEADOFF_12		(0b01u << 2)		//	01 = 12nA
#define ADS1298_LOFF_ILEADOFF_18		(0b10u << 2)		//	10 = 18nA
#define ADS1298_LOFF_ILEADOFF_24		(0b11u << 2)		//	11 = 24nA
														// Lead-off frequency
#define ADS1298_LOFF_FLEADOFF_AC		(0b01u << 0)		//	01 = AC lead-off detection at fDR/4
#define ADS1298_LOFF_FLEADOFF_DC		(0b11u << 0)		//	11 = DC lead-off detection

/******************************************************************************/
/* ADS1298 Individual Channel Settings Registers							  */
/******************************************************************************/
#define ADS1298_CHSET_PD				(0b01u << 7)	// Power-down
                                                        //	0 = Normal operation
                                                        //	1 = Channel power-down
                                                        // PGA gain
#define ADS1298_CHSET_GAIN_6			(0b000u << 4)	//	000 = 6
#define ADS1298_CHSET_GAIN_1			(0b001u << 4)	//	001 = 1
#define ADS1298_CHSET_GAIN_2			(0b010u << 4)	//	010 = 2
#define ADS1298_CHSET_GAIN_3			(0b011u << 4)	//	011 = 3
#define ADS1298_CHSET_GAIN_4			(0b100u << 4)	//	100 = 4
#define ADS1298_CHSET_GAIN_8			(0b101u << 4)	//	101 = 8
#define ADS1298_CHSET_GAIN_12			(0b110u << 4)	//	110 = 12
                                                    	// Channel input
#define ADS1298_CHSET_MUX_ELEC          (0b000u << 0)	//	000 = Normal electrode input
#define ADS1298_CHSET_MUX_SHORT     	(0b001u << 0)	//	001 = Input shorted (for offset or noise measurements)
#define ADS1298_CHSET_MUX_RLDMEAS		(0b010u << 0)	//	010 = RLD measurements
#define ADS1298_CHSET_MUX_MVDD          (0b011u << 0)	//	011 = MVDD for supply measurement
#define ADS1298_CHSET_MUX_TEMP          (0b100u << 0)	//	100 = Temperature sensor
#define ADS1298_CHSET_MUX_TEST      	(0b101u << 0)	//	101 = Test signal
#define ADS1298_CHSET_MUX_RLDDRP		(0b110u << 0)	//	110 = RLD_DRP
#define ADS1298_CHSET_MUX_RLDDRN		(0b111u << 0)	//	111 = RLD_DRN

/******************************************************************************/
/* ADS1298 RLD (Positive/Negative) Signal Derivation Register				  */
/******************************************************************************/
#define ADS1298_RLDSENS_8		(0b1u << 7)	// INX(P/N) to RLD
#define ADS1298_RLDSENS_7		(0b1u << 6)	//	0 = disabled
#define ADS1298_RLDSENS_6		(0b1u << 5)	//	1 = enabled
#define ADS1298_RLDSENS_5		(0b1u << 4)
#define ADS1298_RLDSENS_4		(0b1u << 3)
#define ADS1298_RLDSENS_3		(0b1u << 2)
#define ADS1298_RLDSENS_2		(0b1u << 1)
#define ADS1298_RLDSENS_1		(0b1u << 0)

/******************************************************************************/
/* ADS1298 (Positive/Negative) Signal Lead-Off Detection Register			  */
/******************************************************************************/
#define ADS1298_LOFFSENS_8		(0b1u << 7)	// INX(P/N) lead off
#define ADS1298_LOFFSENS_7		(0b1u << 6)	//	0 = disabled
#define ADS1298_LOFFSENS_6		(0b1u << 5)	//	1 = enabled
#define ADS1298_LOFFSENS_5		(0b1u << 4)
#define ADS1298_LOFFSENS_4		(0b1u << 3)
#define ADS1298_LOFFSENS_3		(0b1u << 2)
#define ADS1298_LOFFSENS_2		(0b1u << 1)
#define ADS1298_LOFFSENS_1		(0b1u << 0)

/******************************************************************************/
/* ADS1298 Lead-Off Flip Register											  */
/******************************************************************************/
#define ADS1298_LOFFFLIP_8		(0b1u << 7)	// Channel X LOFF polarity flip
#define ADS1298_LOFFFLIP_7		(0b1u << 6)	//	0 = no flip: INXP is pulled to AVDD and INXN is pulled to AVSS
#define ADS1298_LOFFFLIP_6		(0b1u << 5)	//	1 = flipped: INXP is pulled to AVSS and INXN is pulled to AVDD
#define ADS1298_LOFFFLIP_5		(0b1u << 4)
#define ADS1298_LOFFFLIP_4		(0b1u << 3)
#define ADS1298_LOFFFLIP_3		(0b1u << 2)
#define ADS1298_LOFFFLIP_2		(0b1u << 1)
#define ADS1298_LOFFFLIP_1		(0b1u << 0)

/******************************************************************************/
/* ADS1298 Lead-Off (Positive/Negative) Signal Status Register				  */
/******************************************************************************/
#define ADS1298_LOFFSTAT_IN8OFF		(0b1u << 7)	// Channel X positive channel lead-off status
#define ADS1298_LOFFSTAT_IN7OFF		(0b1u << 6)	//	0 = electrode is on
#define ADS1298_LOFFSTAT_IN6OFF		(0b1u << 5)	//	1 = electrode is off
#define ADS1298_LOFFSTAT_IN5OFF		(0b1u << 4)
#define ADS1298_LOFFSTAT_IN4OFF		(0b1u << 3)
#define ADS1298_LOFFSTAT_IN3OFF		(0b1u << 2)
#define ADS1298_LOFFSTAT_IN2OFF		(0b1u << 1)
#define ADS1298_LOFFSTAT_IN1OFF		(0b1u << 0)

/******************************************************************************/
/* ADS1298 General-Purpose I/O Register										  */
/******************************************************************************/
#define ADS1298_GPIO_DATA		(0b1111u << 4)	// GPIO data mask
#define ADS1298_GOIO_CTRLIN		(0b0001u << 4)	// GPIO control
												//	0 = Output
												//	1 = Input

/******************************************************************************/
/* ADS1298 Pace Detect Register												  */
/******************************************************************************/
												// Pace even channels
#define ADS1298_PACE_EVEN_2			(0b00u << 3)	//	00 = Channel 2
#define ADS1298_PACE_EVEN_4			(0b01u << 3)	//	01 = Channel 4
#define ADS1298_PACE_EVEN_6			(0b10u << 3)	//	10 = Channel 6
#define ADS1298_PACE_EVEN_8			(0b11u << 3)	//	11 = Channel 8
												// Pace odd channels
#define ADS1298_PACE_ODD_1			(0b00u << 1)	//	00 = Channel 1
#define ADS1298_PACE_ODD_3			(0b01u << 1)	//	01 = Channel 3
#define ADS1298_PACE_ODD_5			(0b10u << 1)	//	10 = Channel 5
#define ADS1298_PACE_ODD_7			(0b11u << 1)	//	11 = Channel 7
#define ADS1298_PACE_PACEBUFFEN		(0b1u << 0)	// Pace detect buffer
												//	0 = Pace detect buffer turned off
												//	1 = Pace detect buffer turned on

/******************************************************************************/
/* ADS1298 Respiration Control Register										  */
/******************************************************************************/
#define ADS1298_RESP_DEMODEN			(0b1u << 7)		// Enables respiration demodulation circuitry
														//	0 = Off
														//	1 = On
#define ADS1298_RESP_MODEN				(0b1u << 6)		// Enables respiration modulation circuitry
														//	0 = Off
														//	1 = On
														// Respiration phase
#define ADS1298_RESP_PH_22_5			(0b000u << 2)	//	000 = 22.5deg
#define ADS1298_RESP_PH_45				(0b001u << 2)	//	001 = 45deg
#define ADS1298_RESP_PH_67_5			(0b010u << 2)	//	010 = 67.5deg
#define ADS1298_RESP_PH_90				(0b011u << 2)	//	011 = 90deg
#define ADS1298_RESP_PH_112_5			(0b100u << 2)	//	100 = 112.5deg
#define ADS1298_RESP_PH_135				(0b101u << 2)	//	101 = 135deg
#define ADS1298_RESP_PH_157_5			(0b110u << 2)	//	110 = 157.5deg
														// Respiration control
#define ADS1298_RESP_CTRL_NONE			(0b00u << 0)		//	00 = No respiration
#define ADS1298_RESP_CTRL_EXT			(0b01u << 0)		//	01 = External respiration
#define ADS1298_RESP_CTRL_INTINT		(0b10u << 0)		//	10 = Internal respiration with internal signals
#define ADS1298_RESP_CTRL_INTUSER		(0b11u << 0)		//	11 = Internal respiration with user-generated signals

/******************************************************************************/
/* ADS1298 Configuration Register 4											  */
/******************************************************************************/
															// Respiration modulation frequency
#define ADS1298_CONFIG4_RESPFREQ_64K		(0b000u << 5)	//	000 = 64kHz modulation clock
#define ADS1298_CONFIG4_RESPFREQ_32K		(0b001u << 5)	//	001 = 32kHz modulation clock
#define ADS1298_CONFIG4_RESPFREQ_16K		(0b010u << 5)	//	010 = 16kHz square wave
#define ADS1298_CONFIG4_RESPFREQ_8K			(0b011u << 5)	//	011 = 8kHz square wave
#define ADS1298_CONFIG4_RESPFREQ_4K			(0b100u << 5)	//	100 = 4kHz square wave
#define ADS1298_CONFIG4_RESPFREQ_2K			(0b101u << 5)	//	101 = 2kHz square wave
#define ADS1298_CONFIG4_RESPFREQ_1K			(0b110u << 5)	//	110 = 1kHz square wave
#define ADS1298_CONFIG4_RESPFREQ_500		(0b111u << 5)	//	111 = 500Hz square wave
#define ADS1298_CONFIG4_SINGLSHOT			(0b1u << 3)		// Single-shot conversion
															//	0 = continuous conversion mode
															//	1 = Single-shot mode
#define ADS1298_CONFIG4_WCTTORLD			(0b1u << 2)		// Connect the WCT to RLD
															//	0 = WCT to RLD connection off
															//	1 = WCT to RLD connection on
#define ADS1298_CONFIG4_LOFFCOMPEN			(0b1u << 1)		// Lead-off comparator power-down
															//	0 = Lead-off comparators disabled
															//	1 = Lead-off comparators enabled

/******************************************************************************/
/* ADS1298 Wilson Central Terminal and Augmented Lead Control Register		  */
/******************************************************************************/
#define ADS1298_WCT1_AVFCH6				(0b1u << 7)		// Enable (WCTA+WCTB)/2 to negative input of channel 6
														//	0 = Disabled
														//	1 = Enabled
#define ADS1298_WCT1_AVLCH5				(0b1u << 6)		// Enable (WCTA+WCTC)/2 to negative input of channel 6
#define ADS1298_WCT1_AVRCH7				(0b1u << 5)		// Enable (WCTB+WCTC)/2 to negative input of channel 6
#define ADS1298_WCT1_AVRCH4				(0b1u << 4)		// Enable (WCTB+WCTC)/2 to negative input of channel 6
#define ADS1298_WCT1_WCTAEN				(0b1u << 3)		// Power-down WCTA
														//	0 = Powered down
														//	1 = Powered on
														// WCT Amplifier A selection
#define ADS1298_WCT1_WCTA_CH1POS		(0b000u << 0)	//	000 = Channel 1 positive input connected to WCTA amplifier
#define ADS1298_WCT1_WCTA_CH1NEG		(0b001u << 0)	//	001 = Channel 1 negative input connected to WCTA amplifier
#define ADS1298_WCT1_WCTA_CH2POS		(0b010u << 0)	//	010 = Channel 2 positive input connected to WCTA amplifier
#define ADS1298_WCT1_WCTA_CH2NEG		(0b011u << 0)	//	011 = Channel 2 negative input connected to WCTA amplifier
#define ADS1298_WCT1_WCTA_CH3POS		(0b100u << 0)	//	100 = Channel 3 positive input connected to WCTA amplifier
#define ADS1298_WCT1_WCTA_CH3NEG		(0b101u << 0)	//	101 = Channel 3 negative input connected to WCTA amplifier
#define ADS1298_WCT1_WCTA_CH4POS		(0b110u << 0)	//	110 = Channel 4 positive input connected to WCTA amplifier
#define ADS1298_WCT1_WCTA_CH4NEG		(0b111u << 0)	//	111 = Channel 4 negative input connected to WCTA amplifier

/******************************************************************************/
/* ADS1298 Wilson Central Terminal Control Register							  */
/******************************************************************************/
#define ADS1298_WCT2_WCTCEN             (0b1u << 7)	// Powered-down WCTC
                                                    	//	0 = Powered down
                                                        //	1 = Powered on
#define ADS1298_WCT2_WCTBEN             (0b1u << 6)	// Powered-down WCTB
														// WCT Amplifier B selection
#define ADS1298_WCT2_WCTB_CH1POS		(0b000u << 3)	//	000 = Channel 1 positive input connected to WCTB amplifier
#define ADS1298_WCT2_WCTB_CH1NEG		(0b001u << 3)	//	001 = Channel 1 negative input connected to WCTB amplifier
#define ADS1298_WCT2_WCTB_CH2POS		(0b010u << 3)	//	010 = Channel 2 positive input connected to WCTB amplifier
#define ADS1298_WCT2_WCTB_CH2NEG		(0b011u << 3)	//	011 = Channel 2 negative input connected to WCTB amplifier
#define ADS1298_WCT2_WCTB_CH3POS		(0b100u << 3)	//	100 = Channel 3 positive input connected to WCTB amplifier
#define ADS1298_WCT2_WCTB_CH3NEG		(0b101u << 3)	//	101 = Channel 3 negative input connected to WCTB amplifier
#define ADS1298_WCT2_WCTB_CH4POS		(0b110u << 3)	//	110 = Channel 4 positive input connected to WCTB amplifier
#define ADS1298_WCT2_WCTB_CH4NEG		(0b111u << 3)	//	111 = Channel 4 negative input connected to WCTB amplifier
														// WCT Amplifier C selection
#define ADS1298_WCT2_WCTC_CH1POS		(0b000u << 0)	//	000 = Channel 1 positive input connected to WCTC amplifier
#define ADS1298_WCT2_WCTC_CH1NEG		(0b001u << 0)	//	001 = Channel 1 negative input connected to WCTC amplifier
#define ADS1298_WCT2_WCTC_CH2POS		(0b010u << 0)	//	010 = Channel 2 positive input connected to WCTC amplifier
#define ADS1298_WCT2_WCTC_CH2NEG		(0b011u << 0)	//	011 = Channel 2 negative input connected to WCTC amplifier
#define ADS1298_WCT2_WCTC_CH3POS		(0b100u << 0)	//	100 = Channel 3 positive input connected to WCTC amplifier
#define ADS1298_WCT2_WCTC_CH3NEG		(0b101u << 0)	//	101 = Channel 3 negative input connected to WCTC amplifier
#define ADS1298_WCT2_WCTC_CH4POS		(0b110u << 0)	//	110 = Channel 4 positive input connected to WCTC amplifier
#define ADS1298_WCT2_WCTC_CH4NEG		(0b111u << 0)	//	111 = Channel 4 negative input connected to WCTC amplifier

/******************************************************************************/
/* FUNCTIONS PROTOTYPES														  */
/******************************************************************************/

/* Writes a single opcode to a ADS1298 chip */
void ADS1298_WriteSingleOpCode(unsigned char writeVals);

/* Writes values to the registers of the ADS1298 */
void ADS1298_WriteRegisters(unsigned char device, 
							unsigned char address, 
							unsigned char writeNum, 
							unsigned char* regVals);

/* Reads values from the registers of the ADS1298 */
void ADS1298_ReadRegisters(unsigned char device, 
						   unsigned char address, 
						   unsigned char writeNum, 
						   unsigned char* regVals);

/* Powers up the ADS1298 chip */
unsigned char ADS1298_PowerUp(void);						   
						
/* Powers down the ADS1298 chip */
unsigned char ADS1298_PowerDown(void);
						
/* Computes the frame size for each ADS1298 chip */
void ADS1298_ComputeFrameSize(void);

/* Sets the channels for the ADS1298 chip */
void ADS1298_SetChannels(unsigned char* channels);

/* Start data conversions */
void ADS1298_StartConversion(void);

/* Stop data conversions */
void ADS1298_StopConversion(void);

/* Read a single frame of data */
void ADS1298_ReadFrame(unsigned char* pDataBuffer);

/* Reads data from the ADS1298 */
void ADS1298_ReadData(unsigned char* pDataBuffer,
					  unsigned long frameCnt);

/* Gets the total frame size */
unsigned long ADS1298_GetFrameSize(void);

/* Sets the registers for testing */
unsigned char ADS1298_RegistersForTesting(unsigned char* channels);

/* Initializes the ADS1298 */
unsigned char ADS1298_Initialize(unsigned char* channels);

#endif /* ADS1298_H */