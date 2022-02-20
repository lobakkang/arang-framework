#ifndef USART_H_
#define USART_H_

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

extern volatile unsigned char USART_available;
extern volatile unsigned char USART_buf_ptr;
extern volatile unsigned char USART_buf[64];

void USART_sendByte(unsigned char data);
void USART_sendByteArray(unsigned char *data);
void USART_sendFlashArray(const char *data);

unsigned char USART_getAvailable();
unsigned char USART_receiveByte();

#endif
