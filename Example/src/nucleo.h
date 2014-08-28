/*
 * nucleo.h
 *
 *  Created on: Aug 27, 2014
 *      Author: Chris
 */
#ifndef NUCLEO_H_
#define NUCLEO_H_
#include "stm32f0xx_nucleo.h"

void nucleo_init();
void ButtonsInitEXTI(void);
void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);


#endif /* NUCLEO_H_ */


