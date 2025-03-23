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




int main(void)
{
	tim2_pa5_output_compare();
	while(1)
	{

	}
}





