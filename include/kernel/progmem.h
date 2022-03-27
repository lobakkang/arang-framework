#ifndef PROGMEM_H_
#define PROGMEM_H_

#include <stdint.h>
typedef struct {
  char name[8];
  char type;
  short page_addr;
  char page_size;
  char num_entry;
} EEPROM_program_cell_t;

typedef struct {
  char num_program;
  EEPROM_program_cell_t cell[32];
} EEPROM_program_table_t;

#define EEPROM_program_table_CRC_addr 1000
#define BYTE_PER_PAGE 128
#define PAYLOAD_AREA_PAGE_SIZE 2

extern char num_program;
extern char flash_usage;
extern short payload_page_addr;

extern const unsigned char __attribute__((section(".payload_data")))
payload_int_data[PAYLOAD_AREA_PAGE_SIZE * BYTE_PER_PAGE];

EEPROM_program_table_t getEEPROMtable();
void loadEEPROMtable();
void clearEEPROMtable();

void initPayload();

#endif
