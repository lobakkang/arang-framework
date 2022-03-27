#include <avr/common.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <kernel/EEPROM.h>
#include <kernel/progmem.h>
#include <kernel/uasrt.h>
#include <stdio.h>

const unsigned char __attribute__((section(".payload_data")))
payload_int_data[PAYLOAD_AREA_PAGE_SIZE * BYTE_PER_PAGE] = {
    0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69,
    0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69,
    0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69,
    0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69,
    0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69,
    0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69,
    0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69,
    0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69};

char num_program = -1;
char flash_usage = 0;
short payload_page_addr = -1;

EEPROM_program_table_t getEEPROMtable() {
  unsigned long calculated_CRC = eepromCRC(0, sizeof(EEPROM_program_table_t));
  unsigned long stored_CRC = 0L;
  eepromReadArray((unsigned char *)&stored_CRC, EEPROM_program_table_CRC_addr,
                  sizeof(unsigned long));

  EEPROM_program_table_t table;
  if (calculated_CRC != stored_CRC) {
    num_program = -1;
  } else {
    eepromReadArray((unsigned char *)&table, 0, sizeof(EEPROM_program_table_t));
    return table;
  }
  return table;
}

void loadEEPROMtable() {
  unsigned long calculated_CRC = eepromCRC(0, sizeof(EEPROM_program_table_t));
  unsigned long stored_CRC = 0L;
  eepromReadArray((unsigned char *)&stored_CRC, EEPROM_program_table_CRC_addr,
                  sizeof(unsigned long));

  if (calculated_CRC != stored_CRC) {
    num_program = -1;
  } else {
    EEPROM_program_table_t table;
    eepromReadArray((unsigned char *)&table, 0, sizeof(EEPROM_program_table_t));
    num_program = table.num_program;
    for (int index = 0; index < 32; index++) {
      flash_usage += table.cell[index].page_size;
    }
  }
}

void clearEEPROMtable() {
  EEPROM_program_table_t table;
  table.num_program = 0;
  for (int index = 0; index < 32; index++) {
    table.cell[index].name[0] = 'E';
    table.cell[index].name[1] = 'M';
    table.cell[index].name[2] = 'P';
    table.cell[index].name[3] = 'T';
    table.cell[index].name[4] = 'Y';
    table.cell[index].name[5] = 'L';
    table.cell[index].name[6] = 'O';
    table.cell[index].name[7] = 'L';

    table.cell[index].num_entry = 0;
    table.cell[index].page_addr = 0;
    table.cell[index].page_size = 0;
    table.cell[index].type = 0x69;
  }

  eepromWriteArray((unsigned char *)&table, 0, sizeof(EEPROM_program_table_t));
  unsigned long calculated_CRC = eepromCRC(0, sizeof(EEPROM_program_table_t));
  eepromWriteArray((unsigned char *)&calculated_CRC,
                   EEPROM_program_table_CRC_addr, sizeof(unsigned long));
}

void initPayload() { payload_page_addr = ((short)payload_int_data) / 128; }
