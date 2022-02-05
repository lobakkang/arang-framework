#include "kernel/digital_pin.h"
#include "kernel/timer.h"
#include <avr/io.h>

#define MS_DELAY 3000

void init_timer() {
  TCCR0A |= 0b00000011;
  TCCR0B |= 0b01000011;
  TCCR1A |= 0b00000010;
  TCCR1B |= 0b01000011;
  TCCR2A |= 0b00000010;
  TCCR2B |= 0b01000011;

  TIMSK0 |= 0b00000001;
}

int main(void) {
  sei();
  init_timer();
  pin_7_output();

  while (1) {
    pin_7_on();
    delayMillis(500);
    pin_7_off();
    delayMillis(500);
  }
}
