#include <avr/common.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <kernel/progmem.h>

void page_erase(unsigned char addr) {
  cli();
  asm volatile("");
  sei();
}
