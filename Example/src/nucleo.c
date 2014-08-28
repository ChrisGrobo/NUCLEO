/*
 * nucleo.c
 *
 *  Created on: Aug 26, 2014
 *      Author: Chris Thiele
 */

#include "stm32f0xx.h"
#include "nucleo.h"
#include "stm32f0xx_gpio.h"
#include "string.h"

/*Private Variable Declaration*/
static __IO uint32_t TimingDelay;

void nucleo_init(){

	//PA5, LD2 Initialization
	GPIO_InitTypeDef ld2_output_gpio;
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	/*Doesn't wor for some reason -> stm32f0xx_gpio.h doesn't define RCC_...
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);*/
	ld2_output_gpio.GPIO_Speed = GPIO_Speed_10MHz;
	ld2_output_gpio.GPIO_Mode = GPIO_Mode_OUT;
	ld2_output_gpio.GPIO_OType = GPIO_OType_PP;
	ld2_output_gpio.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOA, &ld2_output_gpio);

	//PC13, B1 Initialization
	GPIO_InitTypeDef b1_input_gpio;
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	b1_input_gpio.GPIO_Speed = GPIO_Speed_10MHz;
	b1_input_gpio.GPIO_Mode = GPIO_Mode_IN;
	b1_input_gpio.GPIO_OType = GPIO_OType_PP;
	b1_input_gpio.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOC, &b1_input_gpio);
}

void ButtonsInitEXTI(void)
{
	/*
	//Button is PC13, EXTI13
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

	//SYSCFG->EXTICR13  &= ~(0x000F) ; //clear bits 3:0 in the SYSCFG_EXTICR13 reg
	EXTI->FTSR |= EXTI_RTSR_TR13; //PC13 is connected to PU resistor so make it falling edge
	EXTI->RTSR |= EXTI_IMR_MR13; //might needa change to 0->13
	NVIC_SetPriority(EXTI4_15_IRQn,1); // alternatively NVIC_SetPriority(7,1)

	//Enable the Interrupt
	NVIC_EnableIRQ(EXTI4_15_IRQn);

	*/

	  EXTI_InitTypeDef   EXTI_InitStructure;
	  GPIO_InitTypeDef   GPIO_InitStructure;
	  NVIC_InitTypeDef   NVIC_InitStructure;

	  /* Enable GPIOC clock */
	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	  /* Configure PC13 pin as input floating */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);

	  /* Enable SYSCFG clock */
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	  /* Connect EXTI13 Line to PC13 pin */
	  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);

	  /* Configure EXTI13 line */
	  EXTI_InitStructure.EXTI_Line = EXTI_Line13;
	  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	  EXTI_Init(&EXTI_InitStructure);

	  /* Enable and set EXTI13 Interrupt */
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_15_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);

}

/* Inserts a delay time, nTime: specifies the delay time length, in 1 ms.*/
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/*Decrements the TimingDelay variable.*/
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}
