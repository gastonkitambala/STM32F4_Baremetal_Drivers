#include <stdint.h>
//Where LED is connected
//The PORT : A
//The pin number : 5
#define PERIPH_BASE		    	(0x40000000UL)
#define AHB1PERIPH_OFFSET 		(0x00020000UL)

#define AHB1PERIPH_BASE 		(PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET 			(0x0000UL) //
#define GPIOA_BASE 				(AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET 				(0x3800UL)
#define RCC_BASE 				(AHB1PERIPH_BASE + RCC_OFFSET)

#define GPIOAEN					(1U<<0)

#define PIN5 					(1U<<5)
#define LED_PIN					 PIN5

#define __IO					volatile
//(1<<10) //Set bit 10 to 1
//&= ~(1<<11) //Set bit 11 to 0


typedef struct
{
	volatile uint32_t MODER;
	volatile uint32_t DUMMY [4];
	volatile uint32_t ODR;
}GPIO_TypeDef;

typedef struct
{
	volatile uint32_t DUMMY[12];
	volatile uint32_t AHB1ENR;
}RCC_Typedef;

#define RCC						((RCC_Typedef*)RCC_BASE)
#define GPIOA					((GPIO_TypeDef*)GPIOA_BASE)

int main(void)
{
	// 1. Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	// 2. Set PA5 as output pin
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);
	while(1)
	{
	//3. Set PA5 High
		//GPIOA_OD_R |= LED_PIN;
	//4. TOggle PA5
		GPIOA->ODR ^= LED_PIN;
		for(int i=0; i<100000; i++){}
	}
}
