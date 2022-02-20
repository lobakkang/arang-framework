#include <kernel/terminal.h>
#include <kernel/timer.h>
#include <kernel/uasrt.h>
#include <string.h>

void terminal() {
  USART_sendFlashArray(
      PSTR("Arang Framework v1.0\nTerminal console started\nType `help` to get "
           "available command\n>"));
  while (1) {
    while (USART_buf[USART_buf_ptr - 1] != '\r') {
    }
    USART_buf[USART_buf_ptr - 1] = 0;
    if (strcmp("help", (char *)USART_buf) == 0) {
      USART_sendFlashArray(
          PSTR("available command:\nstatus - check system status"
               "\ndefault - set default program\n>"));
    } else if (strcmp("status", (char *)USART_buf) == 0) {
      // USART_sendFlashArray(PSTR("\n>"));
      USART_sendFlashArray(PSTR("Checking EEPROM PROG table...\n"));

    } else {
      USART_sendFlashArray(PSTR("unknown command\n>"));
    }

    for (int i = 0; i < 64; i++) {
      USART_buf[i] = 0;
    }
    USART_buf_ptr = 0;
    USART_available = 0;
  }
}
