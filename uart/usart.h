#ifndef USART_H
#define USART_H

#include <stdint.h>

typedef struct {
    volatile uint32_t SR;    // Status register
    volatile uint32_t DR;    // Data register
    volatile uint32_t BRR;   // Baud rate register
    volatile uint32_t CR1;   // Control register 1
    volatile uint32_t CR2;   // Control register 2
    volatile uint32_t CR3;   // Control register 3
    volatile uint32_t GTPR;  // Guard time and prescaler
} USART_t;

#define USART2 ((USART_t*)0x40004400UL)

// SR flags
#define USART_SR_TXE   (1 << 7)   // TX buffer empty (ready to send)
#define USART_SR_RXNE  (1 << 5)   // RX not empty (data received)
#define USART_SR_TC    (1 << 6)   // Transmission complete

// CR1 bits
#define USART_CR1_UE   (1 << 13)  // USART enable
#define USART_CR1_TE   (1 << 3)   // Transmitter enable
#define USART_CR1_RE   (1 << 2)   // Receiver enable

void usart2_init(uint32_t baud);
void usart2_send_char(char c);
void usart2_send_string(const char *s);
char usart2_recv_char(void);

#endif
