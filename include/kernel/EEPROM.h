#ifndef EEPROM_H_
#define EEPROM_H_

void eepromWrite(char data, short addr);
unsigned char eepromRead(short addr);
unsigned long eepromCRC(short addr, short length);
void eepromReadArray(char *dest, short addr, short length);
void eepromWriteArray(char *src, short addr, short length);

#endif
