#include <avr/io.h>
#include <kernel/EEPROM.h>

void eepromWrite(char data, short addr) {
  while (EECR & 0b00000010) {
  }
  EEAR = addr;
  EEDR = data;
  EECR |= 0b00000100;
  EECR |= 0b00000010;
}

unsigned char eepromRead(short addr) {
  while (EECR & 0b00000010) {
  }
  EEAR = addr;
  EECR |= 0b00000001;
  return EEDR;
}
