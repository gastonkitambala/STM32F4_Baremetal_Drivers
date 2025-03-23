#include <stdint.h>
#include <stdio.h>

#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"


uint32_t sensor_value;
int voltage;

int main(void)
{

	uart2_tx_init();
	pa1_adc_init();

	while(1)
	{
		start_conversion();
		sensor_value = adc_read();
		voltage = sensor_value *(3.3 / 4095);
		printf("Analog Sensor value : %d \n\r", (int)sensor_value);
		printf("Digital sensor value : %d \n\r", voltage);
	}
}





