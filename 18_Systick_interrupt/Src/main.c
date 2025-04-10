#include <stdint.h>
#include <stdio.h>

#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"

#define GPIOAEN			(1U<<0)
#define GPIOA_5			(1U<<5)
#define LED_PIN			GPIOA_5


static void sysTickCallback(void);
int main(void)
{
	//Enable clock access to GPIOA
	RCC->AHB1ENR |=GPIOAEN;

	//Set PA5 as output
	GPIOA->MODER |=(1U<<10);
	GPIOA->MODER &=~(1U<<11);

	uart2_tx_init();
	systick_1hz_interrupt();

	while(1)
	{

	}
}


static void sysTickCallback(void)
{
	printf("A second elapsed ! \n\r");
	GPIOA->ODR ^= LED_PIN;
	//systickDelayMS(1000);
}
void SysTick_Handler(void)
{
	sysTickCallback();
}





