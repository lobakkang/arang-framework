#ifndef TIMER_H_
#define TIMER_H_

#include <avr/interrupt.h>
#include <avr/io.h>

unsigned long millis();
unsigned long micros();
void delayMillis(int ms);
void delayMicroseconds(unsigned int us);

#endif
