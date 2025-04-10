/*
 * adc.c
 *
 *  Created on: Feb 10, 2025
 *      Author: gaston
 */
#include "stm32f4xx.h"
#include "adc.h"

#define GPIOAEN         (1U<<0)
#define ADC1EN			(1U<<8)
#define ADC_CH1			(1U<<0)
#define ADC_SEQ_LEN1	0x00
#define CR2_ADON		(1U<<0)
#define CR2_SWSTART		(1U<<30)

#define CR2_CONT		(1U<<1)
#define CR1_EOCIE		(1U<<5)



/*
 * adc configured with 3 channels
 * ch2, ch3, ch5
 * first = ch5,
 * second = ch2,
 * third = ch3
 * */

void pa1_adc_interrupt_init(void)
{
	/****** CONFIGURE THE ADC GPIIO PIN ******/
	//Enable access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//Set the mode of PA1 to analog mode
	GPIOA->MODER |= (1<<2);
	GPIOA->MODER |= (1<<3);
	/* Configure the ADC MODULE */

	// Enable clock access to ADC
	RCC->APB2ENR |= ADC1EN;

	//Enable ADC end-of conversion interrupt
	ADC1->CR1 |= CR1_EOCIE;
	//Enable AC interrupt in NVIC
	NVIC_EnableIRQ(ADC_IRQn);
	/*Configure adc parameters*/
	//Conversion sequence start
	ADC1->SQR3 = ADC_CH1;
	//Conversion sequence length
	ADC1->SQR1 = ADC_SEQ_LEN1;
	/* Enable ADC module */
	ADC1->CR2 |= CR2_ADON;
}

void pa1_adc_init(void)
{
	/****** CONFIGURE THE ADC GPIIO PIN ******/
	//Enable access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//Set the mode of PA1 to analog mode
	GPIOA->MODER |= (1<<2);
	GPIOA->MODER |= (1<<3);
	/* Configure the ADC MODULE */

	// Enable clock access to ADC
	RCC->APB2ENR |= ADC1EN;

	/*Configure adc parameters*/
	//Conversion sequence start
	ADC1->SQR3 = ADC_CH1;
	//Conversion sequence length
	ADC1->SQR1 = ADC_SEQ_LEN1;
	/* Enable ADC module */
	ADC1->CR2 |= CR2_ADON;
}

void start_conversion(void)
{
	//Enable continous conversion
	ADC1->CR2 |= CR2_CONT;
	//Start adc conversion
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void)
{
	//Wait for conversion to be complete
	while(!(ADC1->SR & SR_EOC)){}
	//Read converted result
	return ADC1->DR;
}
