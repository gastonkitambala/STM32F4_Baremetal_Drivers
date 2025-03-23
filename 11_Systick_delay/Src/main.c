#include <stdint.h>
#include <stdio.h>

#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"

#define GPIOAEN			(1U<<0)
#define GPIOA_5			(1U<<5)
#define LED_PIN			GPIOA_5



int main(void)
{
	//Enable clock access to GPIOA
	RCC->AHB1ENR |=GPIOAEN;

	//Set PA5 as output
	GPIOA->MODER |=(1U<<10);
	GPIOA->MODER &=~(1U<<11);

	uart2_tx_init();

	while(1)
	{
		printf("A second elapsed ! \n\r");
		GPIOA->ODR ^= LED_PIN;
		systickDelayMS(1000);
	}
}





