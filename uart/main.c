#include "rcc.h"
#include "gpio.h"
#include "usart.h"

void usart2_send_char(char c);
char usart2_recv_char(void);

int main(void) {
	RCC->AHB1ENR |= (1 << 0); //enable port A
	RCC->APB1ENR |= (1 << 17); //set it for USART2
	GPIOA->MODER &= ~(0xF << 4);	
	GPIOA->MODER |= (0xA << 4);	
	GPIOA->AFR[0] &= ~(0xFF << 8);
	GPIOA->AFR[0] |= (0x77 << 8);
	USART2->BRR = 16000000/9600;
	USART2->CR1 |= 0x200C;

	// send something to usart
	usart2_send_char('Y');
	usart2_send_char('o');
	usart2_send_char('l');
	usart2_send_char('o');
	usart2_send_char(' ');
	usart2_send_char('s');
	usart2_send_char('t');
	usart2_send_char('a');
	usart2_send_char('r');
	usart2_send_char('t');
	usart2_send_char('i');
	usart2_send_char('n');
	usart2_send_char('g');
	usart2_send_char('.');
	usart2_send_char('.');
	usart2_send_char('.');
	usart2_send_char('.');
	usart2_send_char('\r');
	usart2_send_char('\n');

	while (1) {
		char c = usart2_recv_char();
		usart2_send_char(c);
	}
}

void usart2_send_char( char c) {
	while (!(USART2->SR & USART_SR_TXE));
	USART2->DR = c;
}

char usart2_recv_char(void) {
	while (!(USART2->SR & USART_SR_RXNE));
	return USART2->DR;
}
