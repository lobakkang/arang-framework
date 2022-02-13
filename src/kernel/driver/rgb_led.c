#include <avr/cpufunc.h>
#include <avr/interrupt.h>
#include <kernel/digital_pin.h>
#include <kernel/driver/rgb_led.h>
#include <kernel/timer.h>

#define NUM_RGB (2)
#define NUM_BYTES (NUM_RGB * 3)
#define DIGITAL_PIN (13)
#define PORT (PORTB)
#define PORT_PIN (PORTB5)
#define NUM_BITS (8)

uint8_t rgb_arr[NUM_BYTES] = {
    0,
};

void rgbLedInit() {
  pin_13_output();
  pin_13_off();
}

void rgbLedSetColor(unsigned char idx, unsigned char r, unsigned char g,
                    unsigned char b) {
  if (idx < NUM_RGB) {
    uint8_t *p = &rgb_arr[idx * 3];
    *p++ = g;
    *p++ = r;
    *p = b;
  }
}

void rgbLedRender() {
  delayMicroseconds(50);

  cli();
  volatile uint8_t *p = rgb_arr, val = *p++, high = PORT | _BV(PORT_PIN),
                   low = PORT & ~_BV(PORT_PIN), tmp = low, nbits = NUM_BITS;
  volatile uint16_t nbytes = NUM_BYTES;
  asm volatile("nextbit:\n\t"
               "sbi  %0, %1\n\t"
               "sbrc %4, 7\n\t"
               "mov  %6, %3\n\t"
               "dec  %5\n\t"
               "nop\n\t"
               "st   %a2, %6\n\t"
               "mov  %6, %7\n\t"
               "breq nextbyte\n\t"
               "rol  %4\n\t"
               "rjmp .+0\n\t"
               "cbi   %0, %1\n\t"
               "rjmp .+0\n\t"
               "nop\n\t"
               "rjmp nextbit\n\t"
               "nextbyte:\n\t"
               "ldi  %5, 8\n\t"
               "ld   %4, %a8+\n\t"
               "cbi   %0, %1\n\t"
               "rjmp .+0\n\t"
               "nop\n\t"
               "dec %9\n\t"
               "brne nextbit\n\t" ::"I"(_SFR_IO_ADDR(PORT)),
               "I"(PORT_PIN), "e"(&PORT), "r"(high), "r"(val), "r"(nbits),
               "r"(tmp), "r"(low), "e"(p), "w"(nbytes));
  sei();
}
