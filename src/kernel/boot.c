#include <avr/boot.h>
#include <avr/builtins.h>
#include <avr/common.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include <stdio.h>
#include <stdlib.h>

#include <kernel/ADC.h>
#include <kernel/analog_pin.h>
#include <kernel/digital_pin.h>
#include <kernel/optiboot.h>
#include <kernel/progmem.h>
#include <kernel/terminal.h>
#include <kernel/timer.h>
#include <kernel/uasrt.h>
#include <kernel/utils.h>

#include <kernel/driver/buzzer.h>
#include <kernel/driver/light_sensor.h>
#include <kernel/driver/motor.h>
#include <kernel/driver/rgb_led.h>

#define MS_DELAY 3000

void init_timer() {
  TCCR0A = 0b00000011;
  TCCR0B = 0b01000011;
  TCCR1A = 0b00000010;
  TCCR1B = 0b01011011;
  TCCR2A = 0b00000011;
  TCCR2B = 0b01000100;

  TIMSK0 |= 0b00000001;
}

void init_usart() {
  UBRR0H = 0x00;
  UBRR0L = 0x00;

  UCSR0A |= 0b00000010;
  UCSR0B |= 0b10011000;
  UCSR0C |= 0b00000110;
}

int main(void) {
  sei();
  init_timer();
  init_usart();
  initADC();

  motorInit();
  rgbLedInit();
  initLightSensor();
  initPayload();

  rgbLedSetColor(0, 0, 0, 0);
  rgbLedSetColor(1, 0, 0, 0);
  rgbLedRender();

  USART_buf_ptr = 0;
  USART_available = 0;

  // USART_sendByte('P');
  // USART_sendByte(0x00);
  // USART_sendByte(0x00);
  // USART_sendByte(0x00);
  // USART_sendByte(0x69);
  delayMillis(50);
  if (USART_available == 5) {
    if (USART_receiveByte() == 0x69) {
      buzzerTone(4000, 50);
      delayMillis(50);
      buzzerTone(4000, 50);
      terminal();
      while (1) {
      }
    }
  } else {
    // clearEEPROMtable();
    // while (1) {
    // }

    char tmp_str[64];
    sprintf(
        tmp_str, "%d %p %d 0x%X 0x%X 0x%X\n", pgm_read_byte(payload_int_data),
        payload_int_data, (int)payload_page_addr, pgm_read_byte(GET_LOCK_BITS),
        pgm_read_byte(GET_LOW_FUSE_BITS), pgm_read_byte(GET_HIGH_FUSE_BITS));
    USART_sendByteArray((unsigned char *)tmp_str);

    unsigned char lateral[128] = {
        0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87,
        0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87,
    };
    optiboot_writePage(payload_int_data, lateral, 1);
    USART_sendByteArray((unsigned char *)"done\n");
  }

  // USART_sendFlashArray(text);

  while (1) {
  }
}
