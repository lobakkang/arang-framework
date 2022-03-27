#include <avr/io.h>
#include <kernel/EEPROM.h>

void eepromWrite(unsigned char data, short addr) {
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

unsigned long eepromCRC(short addr, short length) {
  const unsigned long crc_table[16] = {
      0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4,
      0x4db26158, 0x5005713c, 0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
      0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c};

  unsigned long crc = 0L;
  for (int index = addr; index < (addr + length); index++) {
    crc = crc_table[(crc ^ eepromRead(index)) & 0x0f] ^ (crc >> 4);
    crc = crc_table[(crc ^ (eepromRead(index) >> 4)) & 0x0f] ^ (crc >> 4);
    crc = ~crc;
  }

  return crc;
}

void eepromReadArray(unsigned char *dest, short addr, short length) {
  for (short index = 0; index < length; index++) {
    dest[index] = eepromRead(addr + index);
  }
}

void eepromWriteArray(unsigned char *src, short addr, short length) {
  for (short index = 0; index < length; index++) {
    eepromWrite(src[index], addr + index);
  }
}
