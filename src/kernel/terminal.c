#include <avr/boot.h>
#include <avr/builtins.h>
#include <avr/common.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <kernel/EEPROM.h>
#include <kernel/driver/buzzer.h>
#include <kernel/optiboot.h>
#include <kernel/progmem.h>
#include <kernel/terminal.h>
#include <kernel/timer.h>
#include <kernel/uasrt.h>
#include <kernel/utils.h>
#include <stdlib.h>
#include <string.h>

void terminal() {
  while (1) {
    USART_available = 0;
    USART_buf_ptr = 0;

    USART_sendByte('X');
    USART_sendByte(0x00);
    USART_sendByte(0x00);
    USART_sendByte(0x00);
    USART_sendByte(0x69);

    while (USART_available != 5) {
    }

    switch (USART_buf[0]) {
    case 'A': {
      loadEEPROMtable();
      USART_sendByte('M');
      USART_sendByte(flash_usage);
      USART_sendByte(num_program);
      if (num_program == -1) {
        USART_sendByte(0x01);
      } else {
        USART_sendByte(0x00);
      }
      USART_sendByte(0x69);
    }
    case 'C': {
      USART_sendByte('B');
      USART_sendByte(255);
      USART_sendByte(0x00);
      USART_sendByte(0x00);
      USART_sendByte(0x69);
      delayMillis(10);
      EEPROM_program_table_t table = getEEPROMtable();
      for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 8; j++) {
          USART_sendByte(table.cell[i].name[j]);
        }
      }
      USART_sendByte('B');
      USART_sendByte(127);
      USART_sendByte(0x00);
      USART_sendByte(0x00);
      USART_sendByte(0x69);
      delayMillis(10);
      for (int i = 0; i < 32; i++) {
        USART_sendByte(table.cell[i].num_entry);
        USART_sendByte(table.cell[i].page_addr & 0x00FF);
        USART_sendByte((table.cell[i].page_addr & 0xFF00) >> 8);
        USART_sendByte(table.cell[i].type);
      }
      // }
      // USART_sendByte('B');
      // USART_sendByte(255);
      // USART_sendByte(0x00);
      // USART_sendByte(0x00);
      // USART_sendByte(0x69);
      // for (int i = 32; i < 64; i++) {
      //   for (int j = 0; j < 8; j++) {
      //     USART_sendByte(table.cell[i].name[j]);
      //   }
      // }
    }
    case 'F': {
      clearEEPROMtable();
      USART_sendByte('X');
      USART_sendByte(0x00);
      USART_sendByte(0x00);
      USART_sendByte(0x00);
      USART_sendByte(0x69);
    }
    case 'G': {
      unsigned char flash_offset = USART_buf[1];
      while (flash_offset != 0xFF) {
        unsigned char flash_buf[128];
        USART_available = 0;
        USART_buf_ptr = 0;
        USART_sendByte('X');
        USART_sendByte(0x00);
        USART_sendByte(0x00);
        USART_sendByte(0x00);
        USART_sendByte(0x69);
        // for (int j = 0; j < 32; j++) {
        //   int j_i = j * 8;
        //   USART_sendByte('X');
        //   USART_sendByte(0x00);
        //   USART_sendByte(0x00);
        //   USART_sendByte(0x00);
        //   USART_sendByte(0x69);
        //   for (int i = 0; i < 8; i++) {
        //     while (USART_getAvailable() == 0) {
        //     }
        //     flash_buf[i + j_i] = USART_receiveByte();
        // buzzerTone(4000, 10);
        // delayMillis(10);
        // USART_available = 0;
        // USART_buf_ptr = 0;
        // }
        // }
        for (int j = 0; j < 128; j++) {
          while (USART_available == 0) {
          }
          flash_buf[j] = USART_buf[0];
          USART_available = 0;
          USART_buf_ptr = 0;
          USART_sendByte(flash_buf[j]);
          // buzzerTone(4000, 10);
          delayMillis(10);
        }
        optiboot_writePage(payload_int_data, flash_buf, flash_offset);
        USART_available = 0;
        USART_buf_ptr = 0;
        USART_sendByte('X');
        USART_sendByte(0x00);
        USART_sendByte(0x00);
        USART_sendByte(0x00);
        USART_sendByte(0x69);
        while (USART_available != 5) {
        }
        flash_offset = USART_buf[1];
      }
      ledFlashOrange(3);
    }
    }
  }
}
