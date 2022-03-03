#include "kernel/progmem.h"
#include <kernel/EEPROM.h>
#include <kernel/terminal.h>
#include <kernel/timer.h>
#include <kernel/uasrt.h>
#include <stdlib.h>
#include <string.h>

void terminal() {
  while (1) {
    USART_available = 0;
    USART_buf_ptr = 0;

    USART_sendByte('X');
    USART_sendByte(0x00);
    USART_sendByte(0x00);
    USART_sendByte(0x00);
    USART_sendByte(0x69);

    while (USART_available != 5) {
    }

    switch (USART_buf[0]) {
    case 'A': {
      loadEEPROMtable();
      USART_sendByte('M');
      USART_sendByte(flash_usage);
      USART_sendByte(num_program);
      if (num_program == -1) {
        USART_sendByte(0x01);
      } else {
        USART_sendByte(0x00);
      }
      USART_sendByte(0x69);
    }
    }
  }
}
