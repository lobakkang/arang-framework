#include <kernel/timer.h>

#define MICROSECONDS_PER_TIMER0_OVERFLOW ((64 * 256) / 16)
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)
#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
#define FRACT_MAX (1000 >> 3)

volatile unsigned long timer0_overflow_count = 0;
volatile unsigned long timer0_millis = 0;
static unsigned char timer0_fract = 0;

ISR(TIMER0_OVF_vect) {
  unsigned long m = timer0_millis;
  unsigned char f = timer0_fract;

  m += MILLIS_INC;
  f += FRACT_INC;
  if (f >= FRACT_MAX) {
    f -= FRACT_MAX;
    m += 1;
  }

  timer0_fract = f;
  timer0_millis = m;
  timer0_overflow_count++;
}

unsigned long millis() {
  unsigned long m;
  uint8_t oldSREG = SREG;
  cli();
  m = timer0_millis;
  SREG = oldSREG;
  return m;
}

unsigned long micros() {
  unsigned long m;
  uint8_t oldSREG = SREG, t;
  cli();
  m = timer0_overflow_count;
  t = TCNT0;
  if ((TIFR0 & _BV(TOV0)) && (t < 255)) {
    m++;
  }
  SREG = oldSREG;
  return ((m << 8) + t) * 4;
}

void delayMillis(int ms) {
  uint16_t start = (uint16_t)micros();
  while (ms > 0) {
    if (((uint16_t)micros() - start) >= 1000) {
      ms--;
      start += 1000;
    }
  }
}

void delayMicroseconds(unsigned int us) {
  if (--us == 0)
    return;
  us <<= 2;
  us -= 2;
  __asm__ __volatile__("1: sbiw %0,1"
                       "\n\t"
                       "brne 1b"
                       : "=w"(us)
                       : "0"(us));
}
