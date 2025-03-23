#include <stdint.h>
#include <stdio.h>

#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"

#define GPIOAEN			(1U<<0)
#define GPIOA_5			(1U<<5)
#define LED_PIN			GPIOA_5



int timestamp = 0;
//Set up a jumper wire from PA5 to PA6
int main(void)
{
	tim2_pa5_output_compare();
	tim3_pa6_intput_capture();

	while(1)
	{
		//Wait until edge is captured
		while(!(TIM3->SR & SR_CC1IF)){}
		//Read value
		timestamp = TIM3->CCR1;
	}
}





