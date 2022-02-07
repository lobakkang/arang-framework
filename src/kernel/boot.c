#include <avr/io.h>
#include <kernel/analog_pin.h>
#include <kernel/digital_pin.h>
#include <kernel/timer.h>

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

int main(void) {
  sei();
  init_timer();
  // pin_13_output();

  // while (1) {
  //   pin_13_on();
  //   delayMillis(500);
  //   pin_13_off();
  //   delayMillis(500);
  // }

  fastPWM_pin9(0x01);
  pin_5_output();
  pin_5_on();
  while (1) {
  }
}
