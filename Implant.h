/***************************************************************************//**
 *   @file   Implant.h
 *   @brief  Header file for the implant driver.
 *   @author Jiaxu Meng (jm611@duke.edu)
*******************************************************************************/
#ifndef _IMPLANT_H_
#define _IMPLANT_H_

/*****************************************************************************/
/* INCLUDE FILES															 */
/*****************************************************************************/
#include "CommADS1298.h"
#include "ADS1298.h"
#include "CommCC110L.h"
#include "CC110L.h"
#include "LogicAnalyzer.h"

/******************************************************************************/
/* FUNCTIONS PROTOTYPES														  */
/******************************************************************************/

unsigned char Implant_Initialize(unsigned char* channels);

void Implant_StreamData(unsigned char frameCnt);

unsigned char Implant_ChangeMode(unsigned char cmd, unsigned char* data);

#endif /* _IMPLANT_H_ */
