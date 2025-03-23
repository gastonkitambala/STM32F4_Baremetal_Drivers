/*
 * uart.c
 *
 *  Created on: Feb 7, 2025
 *      Author: gaston
 */
#include "uart.h"
#define GPIOAEN			(1U<<0)
#define UART2EN			(1U<<17)

#define CR1_TE			(1U<<3)
#define CR1_RE			(1U<<2)
#define CR1_UE			(1U<<13)
#define SR_TXE			(1U<<7)
#define SR_RXNE		    (1U<<5)

#define SYS_FREQ		16000000
#define APB1_CLK 		SYS_FREQ

#define UART_BAUDRATE	115200

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t Baudrate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t Baudrate);
void uart2_write(int ch);


int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}
void uart2_rxtx_init(void)
{
	//Configure UART gpio pins
	//Enable clock access to gpioa
	RCC->AHB1ENR |= GPIOAEN;
	//Set PA2 Mode to alternate function mode
	GPIOA->MODER &= ~(1<<4);
	GPIOA->MODER |=  (1<<5);

	//Set PA2 alternate function type to UART_TX (AF7)
	GPIOA->AFR[0] |= (1<<8);
	GPIOA->AFR[0] |= (1<<9);
	GPIOA->AFR[0] |= (1<<10);
	GPIOA->AFR[0] &= ~(1<<11);

	//Set PA3 mode to alternate function mode
	GPIOA->MODER &= ~(1<<6);
	GPIOA->MODER |=  (1<<7);

	//Set PA3 alternate function type to UART_RX (AF07)
	GPIOA->AFR[0] |= (1<<12);
	GPIOA->AFR[0] |= (1<<13);
	GPIOA->AFR[0] |= (1<<14);
	GPIOA->AFR[0] &= ~(1<<15);


	//Configure UART module
	//Enable access to UART2
	RCC->APB1ENR |= UART2EN;
	//Configure baudrate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE );
	//Configure the transfer direction
	USART2->CR1 = (CR1_TE | CR1_RE);
	//Enable UART module
	USART2->CR1 |= CR1_UE;
}

void uart2_tx_init(void)
{
	//Configure UART gpio pins
	//Enable clock access to gpioa
	RCC->AHB1ENR |= GPIOAEN;
	//Set PA2 Mode to alternate function mode
	GPIOA->MODER &= ~(1<<4);
	GPIOA->MODER |=  (1<<5);

	//Set PA2 alternate function type to UART_TX (AF7)
	GPIOA->AFR[0] |= (1<<8);
	GPIOA->AFR[0] |= (1<<9);
	GPIOA->AFR[0] |= (1<<10);
	GPIOA->AFR[0] &= ~(1<<11);


	//Configure UART module
	//Enable access to UART2
	RCC->APB1ENR |= UART2EN;
	//Configure baudrate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE );
	//Configure the transfer direction
	USART2->CR1 = CR1_TE;
	//Enable UART module
	USART2->CR1 |= CR1_UE;
}

char uart2_read(void)
{
	//Make sure the receive data register is not empty
	while (!(USART2->SR & SR_RXNE)){}

	//Read Data
	return USART2->DR;
}


void uart2_write(int ch)
{
	//Make sure the transmit data register is empty
	while (!(USART2->SR & SR_TXE)){}
	//Write to transmit data register
	USART2->DR = (ch & 0xFF);

}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t Baudrate)
{
	USARTx->BRR = compute_uart_bd(PeriphClk, Baudrate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t Baudrate)
{
	return ((PeriphClk +(Baudrate/2U))/Baudrate);
}
