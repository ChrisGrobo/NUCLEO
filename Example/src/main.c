/*
 * nucleo.h
 *
 *  Created on: Aug 27, 2014
 *      Author: Chris
 */
#include "main.h"
#include "nucleo.h"

/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;
uint8_t BlinkSpeed = 0;

/* Private function prototypes -----------------------------------------------*/
RCC_ClocksTypeDef RCC_Clocks;

/* Private functions ---------------------------------------------------------*/


int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f030.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */ 
  
  /* SysTick end of count event each 1ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
  
  nucleo_init();
  ButtonsInitEXTI();
  
  /* Initiate Blink Speed variable */ 
  BlinkSpeed = 0;
  
  /* Infinite loop */
  while (1)
  {
	  if(BlinkSpeed == 0)
	  {
		  GPIOA->BRR = GPIO_Pin_5;//set bit as high
		  Delay (50);
	  }
	  else
	  {
		  GPIOA->BSRR = GPIO_Pin_5;//set bit as low
		  Delay (50);
	  }
  }
}

#ifdef  USE_FULL_ASSERT

/**
* @brief  Reports the name of the source file and the source line number
*         where the assert_param error has occurred.
* @param  file: pointer to the source file name
* @param  line: assert_param error line source number
* @retval None
*/
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
  ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  
  /* Infinite loop */
  while (1)
  {
  }
}
#endif
