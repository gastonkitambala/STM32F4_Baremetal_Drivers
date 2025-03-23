#include "stm32f4xx.h"
#define GPIOAEN			(1U<<0)
#define GPIOCEN			(1U<<2)

#define PIN5			(1U<<5)
#define PIN13			(1U<<13)
#define LED_PIN			PIN5
#define BTN_PIN			PIN13





int main(void)
{
	//Enable clock access to GPIOC and GPIOA
	RCC->AHB1ENR |=GPIOAEN;
	RCC->AHB1ENR |=GPIOCEN;

	//Set PA5 as output
	GPIOA->MODER |=(1U<<10);
	GPIOA->MODER &=~(1U<<11);

	//Set PC13 as INPUT
	GPIOC->MODER &= ~(1<<26);
	GPIOC->MODER &= ~(1<<27);

	while(1)
	{
		//CHECK IF BUTTON IS PRESSED
		if(GPIOC->IDR & BTN_PIN){
			//Turn ON LED
			GPIOA->BSRR = LED_PIN;
		}
		else{
			//Turn OFF LED
			GPIOA->BSRR = (1U<<21);
		}


	}
}
