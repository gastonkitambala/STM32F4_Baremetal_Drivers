#include <stdint.h>
#include <stdio.h>

#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"


uint32_t sensor_value;
//int voltage;

static void adc_callback(void);

int main(void)
{

	uart2_tx_init();
	pa1_adc_interrupt_init();
	start_conversion();

	while(1)
	{

	}
}

static void adc_callback(void)
{
	sensor_value = (ADC1->DR);
	//voltage = sensor_value *(3.3 / 4095);
	printf("Analog Sensor value : %d \n\r", (int)sensor_value);
	//printf("Digital sensor value : %d \n\r", voltage);
}
void ADC_IRQHandler(void)
{
	//Check for EOC in status register (SR)
	if((ADC1->SR & SR_EOC) != 0)
	{
		//Clear EOC
		ADC1->SR &= ~SR_EOC;
		//Do Something
		adc_callback();

	}
}





