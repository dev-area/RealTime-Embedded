/**
  ******************************************************************************
  * @file    SysTick/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    09/13/2010
  * @brief   Main program body.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"


int main(void)
{
  volatile int *p = (int *)0xe000e010;
  
  /* Initialize Leds LD3 and LD4 mounted on STM32VLDISCOVERY board */  
  STM32vldiscovery_LEDInit(LED3);
  STM32vldiscovery_LEDInit(LED4);

  p[1] = 12000000 -1;			   // how many ticks to count val must fit 24 bit
  p[2] = 0;						   
  p[0] = 0x7;
  while (1)
  {
  }
}
 volatile int g=0;
void my_timer_isr(void)
{
	
	volatile int *p=(volatile int *)0x4001100c;	 // gpio address 
	volatile int *p2=(volatile int *)0x422201a4; // gpio sddress - bit banding

 //   STM32vldiscovery_LEDToggle(LED3);
//	*p^=0x200;
	*p2 ^=1;
}


/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
