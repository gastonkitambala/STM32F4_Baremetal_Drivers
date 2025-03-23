/*
 * tim.c
 *
 *  Created on: Feb 14, 2025
 *      Author: gaston
 */
#include "stm32f4xx.h"

#define TIM2EN 			(1U<<0)
#define CR1_CEN			(1U<<0)
#define OC_TOGGLE 		((1U<<4) | (1U<<5))
#define CCER_CC1E		(1U<<0) //For channel 1
#define GPIOAEN			(1U<<0)
#define AFR5_TIM		(1u<<20)

void tim2_1hz_init(void){
	//Enable clock access to Timer 2
	RCC->APB1ENR |= TIM2EN;
	// Set Prescalaer value
	TIM2->PSC = 1600 -1; //16 000 000 / 1600 = 10000
	//Set auto-reload value
	TIM2->ARR = 10000 - 1;
	//Clear the counter
	TIM2->CNT = 0;
	//Enable the timer
	TIM2->CR1 = CR1_CEN;
}

void tim2_pa5_output_compare(void){

	//Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER &= ~(1U<<10);
	GPIOA->MODER |= (1U<<11);

	//Set PA5 mode to alternate function

	//Set PA5 alternate function type to TIM2_CH1
	GPIOA->AFR[0] |= AFR5_TIM;
	//Enable clock access to Timer 2
	RCC->APB1ENR |= TIM2EN;
	// Set Prescalaer value
	TIM2->PSC = 1600 -1; //16 000 000 / 1600 = 10000
	//Set auto-reload value
	TIM2->ARR = 10000 - 1;

	//Set the output compare toggle mode
	TIM2->CCMR1 = OC_TOGGLE;
	//Enable TIM2 in compare mode
	TIM2->CCER |= CCER_CC1E;

	//Clear the counter
	TIM2->CNT = 0;
	//Enable the timer
	TIM2->CR1 = CR1_CEN;
}

