#include "rcc.h"
#include "gpio.h"
#include "usart.h"

void usart2_init(uint32_t baud) {
	RCC->AHB1ENR |= (1 << 0); //enable port A
	RCC->APB1ENR |= (1 << 17); //set it for USART2
	GPIOA->MODER &= ~(0xF << 4);	
	GPIOA->MODER |= (0xA << 4);	
	GPIOA->AFR[0] &= ~(0xFF << 8);
	GPIOA->AFR[0] |= (0x77 << 8);
	USART2->BRR = 16000000/baud;
	USART2->CR1 |= 0x200C;

}

void usart2_send_char( char c) {
	while (!(USART2->SR & USART_SR_TXE));
	USART2->DR = c;
}

char usart2_recv_char(void) {
	while (!(USART2->SR & USART_SR_RXNE));
	return USART2->DR;
}

void usart2_send_string(const char *s) {
	while (*s) {
		usart2_send_char(*s++);
	}
}
