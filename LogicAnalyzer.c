/***************************************************************************//**
 *   @file   LogicAnalyzer.c
 *   @brief  Implementation of the Logic Analyzer driver used to print data out 
 *           to the logic analyzer.
 *   @author Jiaxu Meng (jm611@duke.edu)
*******************************************************************************/

#include "LogicAnalyzer.h"

/***************************************************************************//**
 * @brief  Configures the pins on the PIC to output to the Logic Analyzer.
 *         Logic Analyzer can display data that is 1 byte (8 bits) long.
 *
 * @param  None.
 *
 * @return None.
*******************************************************************************/
unsigned char LogicAnalyzer_Initialize(){
    
    /* It outputs 1 byte and a clock as follows:
     * Data bits 0-3  output on Port E 0-2 and Port A 4
     * Data bits 4-7  output on Port B 4-7
     * Clock output on Port A 5
     */
    LogicAnalyzer_BIT7_DIR = 0; // most significant bit (bit 7)
    LogicAnalyzer_BIT6_DIR = 0; // bit 6
    LogicAnalyzer_BIT5_DIR = 0; // bit 5
    LogicAnalyzer_BIT4_DIR = 0; // bit 4
    LogicAnalyzer_BIT3_DIR = 0; // bit 3
    LogicAnalyzer_BIT2_DIR = 0; // bit 2
    LogicAnalyzer_BIT1_DIR = 0; // bit 1
    LogicAnalyzer_BIT0_DIR = 0; // least significant bit (bit 0)
    LogicAnalyzer_CLK_DIR = 0;
	
	return 1;
}

/***************************************************************************//**
 * @brief  Outputs a byte of data to the logic analyzer.
 *
 * @param  data - Byte of data that you want to output to logic analyzer.
 *
 * @return None.
*******************************************************************************/
void LogicAnalyzer_OutputChar(unsigned char data) {
    unsigned char i;
    
    /* Turn on the appropriate bits */
    LogicAnalyzer_BIT7 = (data >> 7) & 0x01; // most significant bit (bit 7)
    LogicAnalyzer_BIT6 = (data >> 6) & 0x01; // bit 6
    LogicAnalyzer_BIT5 = (data >> 5) & 0x01; // bit 5
    LogicAnalyzer_BIT4 = (data >> 4) & 0x01; // bit 4
    LogicAnalyzer_BIT3 = (data >> 3) & 0x01; // bit 3
    LogicAnalyzer_BIT2 = (data >> 2) & 0x01; // bit 2
    LogicAnalyzer_BIT1 = (data >> 1) & 0x01; // bit 1
    LogicAnalyzer_BIT0 = (data >> 0) & 0x01; // least significant bit (bit 0)
    
    /* Toggle clock bit */
    LogicAnalyzer_CLK = 1;
    LogicAnalyzer_CLK = 0;
}