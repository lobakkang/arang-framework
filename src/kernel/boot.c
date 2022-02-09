#include <avr/io.h>
#include <avr/pgmspace.h>

#include <kernel/analog_pin.h>
#include <kernel/digital_pin.h>
#include <kernel/timer.h>
#include <kernel/uasrt.h>

#include <kernel/driver/motor.h>

#define MS_DELAY 3000

void init_timer() {
  TCCR0A = 0b00000011;
  TCCR0B = 0b01000011;
  TCCR1A = 0b00000010;
  TCCR1B = 0b01011011;
  TCCR2A = 0b00000011;
  TCCR2B = 0b01000100;

  TIMSK0 |= 0b00000001;
}

void init_usart() {
  UBRR0H = 0x00;
  UBRR0L = 0x00;

  UCSR0A |= 0b00000010;
  UCSR0B |= 0b10011000;
  UCSR0C |= 0b00000110;
}

const unsigned char PROGMEM text[] =
    "Hello how are you? This is a dummy text that have meaning but just to "
    "waste the memory. :) Aim is to waste the program memory but not the "
    "expensive ram";

int main(void) {
  sei();
  init_timer();
  init_usart();

  motorInit();

  USART_sendFlashArray(text);

  while (1) {
  }
}
