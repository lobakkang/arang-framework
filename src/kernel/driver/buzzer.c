#include "kernel/digital_pin.h"
#include "kernel/timer.h"
#include <kernel/driver/buzzer.h>

void buzzerTone(unsigned short frequency, unsigned short duration) {
  int period = 1000000L / frequency;
  int pulse = period / 2;
  pin_8_output();
  for (uint32_t i = 0; i < duration * 1000L; i += period) {
    pin_8_on();
    delayMicroseconds(pulse);
    pin_8_off();
    delayMicroseconds(pulse);
  }
}
