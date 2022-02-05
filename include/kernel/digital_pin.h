#ifndef PIN_H_
#define PIN_H_

#include <avr/io.h>

inline void pin_0_output() {
  DDRD |= 0b00000001;
}

inline void pin_1_output() {
  DDRD |= 0b00000010;
}

inline void pin_2_output() {
  DDRD |= 0b00000100;
}

inline void pin_3_output() {
  DDRD |= 0b00001000;
}

inline void pin_4_output() {
  DDRD |= 0b00010000;
}

inline void pin_5_output() {
  DDRD |= 0b00100000;
}

inline void pin_6_output() {
  DDRD |= 0b01000000;
}

inline void pin_7_output() {
  DDRD |= 0b10000000;
}

inline void pin_8_output() {
  DDRB |= 0b00000001;
}

inline void pin_9_output() {
  DDRB |= 0b00000010;
}

inline void pin_10_output() {
  DDRB |= 0b00000100;
}

inline void pin_11_output() {
  DDRB |= 0b00001000;
}

inline void pin_12_output() {
  DDRB |= 0b00010000;
}

inline void pin_13_output() {
  DDRB |= 0b00100000;
}

inline void pin_0_input() {
  DDRD &= 0b11111110;
}

inline void pin_1_input() {
  DDRD &= 0b11111101;
}

inline void pin_2_input() {
  DDRD &= 0b11111011;
}

inline void pin_3_input() {
  DDRD &= 0b11110111;
}

inline void pin_4_input() {
  DDRD &= 0b11101111;
}

inline void pin_5_input() {
  DDRD &= 0b11011111;
}

inline void pin_6_input() {
  DDRD &= 0b10111111;
}

inline void pin_7_input() {
  DDRD &= 0b01111111;
}

inline void pin_8_input() {
  DDRB &= 0b11111110;
}

inline void pin_9_input() {
  DDRB &= 0b11111101;
}

inline void pin_10_input() {
  DDRB &= 0b11111011;
}

inline void pin_11_input() {
  DDRB &= 0b11110111;
}

inline void pin_12_input() {
  DDRB &= 0b11101111;
}

inline void pin_13_input() {
  DDRB &= 0b11011111;
}

inline void pin_0_on() {
  PORTD |= 0b00000001;
}

inline void pin_1_on() {
  PORTD |= 0b00000010;
}

inline void pin_2_on() {
  PORTD |= 0b00000100;
}

inline void pin_3_on() {
  PORTD |= 0b00001000;
}

inline void pin_4_on() {
  PORTD |= 0b00010000;
}

inline void pin_5_on() {
  PORTD |= 0b00100000;
}

inline void pin_6_on() {
  PORTD |= 0b01000000;
}

inline void pin_7_on() {
  PORTD |= 0b10000000;
}

inline void pin_8_on() {
  PORTB |= 0b00000001;
}

inline void pin_9_on() {
  PORTB |= 0b00000010;
}

inline void pin_10_on() {
  PORTB |= 0b00000100;
}

inline void pin_11_on() {
  PORTB |= 0b00001000;
}

inline void pin_12_on() {
  PORTB |= 0b00010000;
}

inline void pin_13_on() {
  PORTB |= 0b00100000;
}

inline void pin_0_off() {
  PORTD &= 0b11111110;
}

inline void pin_1_off() {
  PORTD &= 0b11111101;
}

inline void pin_2_off() {
  PORTD &= 0b11111011;
}

inline void pin_3_off() {
  PORTD &= 0b11110111;
}

inline void pin_4_off() {
  PORTD &= 0b11101111;
}

inline void pin_5_off() {
  PORTD &= 0b11011111;
}

inline void pin_6_off() {
  PORTD &= 0b10111111;
}

inline void pin_7_off() {
  PORTD &= 0b01111111;
}

inline void pin_8_off() {
  PORTB &= 0b11111110;
}

inline void pin_9_off() {
  PORTB &= 0b11111101;
}

inline void pin_10_off() {
  PORTB &= 0b11111011;
}

inline void pin_11_off() {
  PORTB &= 0b11110111;
}

inline void pin_12_off() {
  PORTB &= 0b11101111;
}

inline void pin_13_off() {
  PORTB &= 0b11011111;
}

#endif
