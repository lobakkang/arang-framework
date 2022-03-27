#ifndef MULTITASKING_H__
#define MULTITASKING_H__

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>

typedef void (*TaskFunc)(void);

void context_switch();
void initMultitasking();
void createTask(TaskFunc func, size_t stackSize);
void yield();

#endif
