#include <avr/io.h>
#include <kernel/ADC.h>

void initADC() {
  ADCSRA |= 0b10000111;
  ADMUX |= 0b01000000;
}

int readADC(unsigned char pin) {
  ADMUX &= 0b11110000;
  ADMUX |= pin;
  ADCSRA |= 0b01000000;
  while ((ADCSRA & 0b01000000) != 0) {
  }
  return ADC;
}
