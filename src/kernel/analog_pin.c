#include <kernel/analog_pin.h>

void fastPWM_pin6(unsigned char val) {
  DDRD |= 0b01000000;
  TCCR0A |= 0b10000000;
  OCR0A = val;
}

void fastPWM_pin5(unsigned char val) {
  DDRD |= 0b00100000;
  TCCR0A |= 0b00010000;
  OCR0B = val;
}

void fastPWM_pin11(unsigned char val) {
  DDRB |= 0b00001000;
  TCCR2A |= 0b01000000;
  OCR2A = val;
}

void fastPWM_pin3(unsigned char val) {
  DDRD |= 0b00001000;
  TCCR2A |= 0b00010000;
  OCR2B = val;
}

void fastPWM_pin9(unsigned char val) {
  DDRB |= 0b00000010;
  TCCR1A |= 0b10000000;
  ICR1 = 255;
  OCR1A = val;
}

void fastPWM_pin10(unsigned char val) {
  DDRB |= 0b00000100;
  TCCR1A |= 0b00100000;
  ICR1 = 255;
  OCR1B = val;
}
