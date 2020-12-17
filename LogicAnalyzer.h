/***************************************************************************//**
 *   @file   LogicAnalyzer.h
 *   @brief  Header to the Logic Analyzer driver.
 *   @author Jiaxu Meng (jm611@duke.edu)
*******************************************************************************/

#ifndef LOGICANALYZER_H
#define	LOGICANALYZER_H

#include <p18f46k22.h>

/******************************************************************************/
/* LOGIC ANALYZER PINS  													  */
/******************************************************************************/

#define LogicAnalyzer_BIT7          LATBbits.LATB7
#define LogicAnalyzer_BIT7_DIR      TRISBbits.RB7

#define LogicAnalyzer_BIT6          LATBbits.LATB6
#define LogicAnalyzer_BIT6_DIR      TRISBbits.RB6

#define LogicAnalyzer_BIT5          LATBbits.LATB5
#define LogicAnalyzer_BIT5_DIR      TRISBbits.RB5

#define LogicAnalyzer_BIT4          LATBbits.LATB4
#define LogicAnalyzer_BIT4_DIR      TRISBbits.RB4

#define LogicAnalyzer_BIT3          LATBbits.LATB3
#define LogicAnalyzer_BIT3_DIR      TRISBbits.RB3

#define LogicAnalyzer_BIT2          LATBbits.LATB2
#define LogicAnalyzer_BIT2_DIR      TRISBbits.RB2

#define LogicAnalyzer_BIT1          LATBbits.LATB1
#define LogicAnalyzer_BIT1_DIR      TRISBbits.RB1

#define LogicAnalyzer_BIT0          LATBbits.LATB0
#define LogicAnalyzer_BIT0_DIR      TRISBbits.RB0

#define LogicAnalyzer_CLK           LATDbits.LATD7
#define LogicAnalyzer_CLK_DIR       TRISDbits.RD7

//#define LogicAnalyzer_BIT3          LATAbits.LATA4
//#define LogicAnalyzer_BIT3_DIR      TRISAbits.RA4

//#define LogicAnalyzer_BIT2          LATEbits.LATE2
//#define LogicAnalyzer_BIT2_DIR      TRISEbits.RE2

//#define LogicAnalyzer_BIT1          LATEbits.LATE1
//#define LogicAnalyzer_BIT1_DIR      TRISEbits.RE1

//#define LogicAnalyzer_BIT0          LATEbits.LATE0
//#define LogicAnalyzer_BIT0_DIR      TRISEbits.RE0

//#define LogicAnalyzer_CLK           LATAbits.LATA5
//#define LogicAnalyzer_CLK_DIR       TRISAbits.RA5

/******************************************************************************/
/* FUNCTIONS PROTOTYPES														  */
/******************************************************************************/

/* Initialize the interface to the logic analyzer */
unsigned char LogicAnalyzer_Initialize(void);

/* Print out an 8-bit character to the logic analyzer */
void LogicAnalyzer_OutputChar(unsigned char data);

#endif	/* LOGICANALYZER_H */

