/*
 * systick.c
 *
 *  Created on: Feb 12, 2025
 *      Author: gaston
 */

#include "stm32f4xx.h"

#define SYSTICK_LOAD_VAL			16000
#define CTRL_ENABLE					(1U<<0)
#define CTRL_CLKSRC					(1U<<2)
#define CTRL_COUNTFLAG				(1U<<16)






void systickDelayMS(int delay)
{
	//Configure Systick
	//Reload with number of clocks per milliseconds
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	//Clear Systick current value register
	SysTick->VAL = 0;
	//Enable Systick and select internal clk src
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	for(int i=0; i<delay; i++){
		//Wait until COUNTFLAG is set
		while((SysTick->CTRL & CTRL_COUNTFLAG) == 0){}
	}
	SysTick->CTRL = 0;



}


