#ifndef EEPROM_H_
#define EEPROM_H_

void eepromWrite(unsigned char data, short addr);
unsigned char eepromRead(short addr);
unsigned long eepromCRC(short addr, short length);
void eepromReadArray(unsigned char *dest, short addr, short length);
void eepromWriteArray(unsigned char *src, short addr, short length);

#endif
