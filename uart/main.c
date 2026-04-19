#include "rcc.h"
#include "gpio.h"
#include "usart.h"

int main(void) {
	usart2_init(9600);

	// send something to usart
	usart2_send_string("UART communication...\r\n");

	while (1) {
		char c = usart2_recv_char();
		usart2_send_char(c);
	}
}

