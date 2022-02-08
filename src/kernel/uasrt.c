#include <kernel/uasrt.h>

volatile unsigned char USART_available = 0;
volatile unsigned char USART_buf_ptr = 0;
volatile unsigned char USART_buf[64];

void USART_sendByte(unsigned char data) {
  while (!(UCSR0A & 0b00100000))
    ;
  UDR0 = data;
}

void USART_sendByteArray(unsigned char *data) {
  int x = 0;
  while (data[x] != 0x00) {
    USART_sendByte(data[x]);
    x++;
  }
}

void USART_sendFlashArray(const unsigned char *data) {
  unsigned char c = pgm_read_byte_near(data);
  int x = 0;
  while (c != 0x00) {
    USART_sendByte(c);
    x++;
    c = pgm_read_byte_near(data + x);
  }
}

unsigned char USART_getAvailable() { return USART_available; }

unsigned char USART_receiveByte() {
  if (USART_available == 0) {
    return 0;
  } else {
    char data = USART_buf[USART_buf_ptr - USART_available];
    USART_available--;
    return data;
  }
  return 0;
}

ISR(USART_RX_vect) {
  while (!(UCSR0A & 0b00100000))
    ;
  unsigned char data = UDR0;
  if (USART_buf_ptr > 64) {
    USART_buf_ptr = 0;
  }
  USART_buf[USART_buf_ptr] = data;
  USART_buf_ptr++;
  USART_available++;
}
