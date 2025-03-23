/*
 * exti.c
 *
 *  Created on: Feb 26, 2025
 *      Author: gaston
 */
#include "exti.h"

#define GPIOCEN (1<<2)
#define SYSCFGEN (1<<14)

void pc13_exti_init(void)
{
	//Disable global interrupts
	__disable_irq();
	//Enable clock access for GPIOC
	RCC->AHB1ENR |= GPIOCEN;
	//Enable clock access to SYSCFG
	RCC->APB2ENR |= SYSCFGEN;
	//Set PC13 as input
	GPIOC->MODER &= ~(1<<26);
	GPIOC->MODER &= ~(1<<27);
	//Select PORTC for EXT13
	SYSCFG->EXTICR[3] |= (1<<5);
	//Unmask EXTI13
	EXTI->IMR |= (1<<13);
	//Select falling edge trigger
	EXTI->FTSR |= (1<<13);
	//Enable EXTI line in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	//Enable Global interrupts
	__enable_irq();

}
