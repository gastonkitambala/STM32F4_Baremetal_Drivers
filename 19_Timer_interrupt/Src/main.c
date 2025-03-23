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

static void tim2_callback(void);
int main(void)
{
	//Enable clock access to GPIOA
	RCC->AHB1ENR |=GPIOAEN;

	//Set PA5 as output
	GPIOA->MODER |=(1U<<10);
	GPIOA->MODER &=~(1U<<11);

	uart2_tx_init();
	tim2_1hz_init();
	while(1)
	{
		//Wait FOR uif
		while (!(TIM2->SR & SR_UIF)){}

		//Clear UIF
		TIM2->SR &= ~SR_UIF;
		printf("A second elapsed ! \n\r");
		GPIOA->ODR ^= LED_PIN;
	}
}

static void tim2_callback(void)
{
	printf("A second elapsed ! \n\r");
	GPIOA->ODR ^= LED_PIN;
}
void TIM2_IRQHandler(void)
{
	//Clear update interrupt
	TIM2->SR &= ~SR_UIF;
	//Do something
	tim2_callback();
}





