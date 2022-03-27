#include <kernel/multitasking.h>
#include <kernel/uasrt.h>
#include <kernel/utils.h>

#include <stdio.h>
#include <stdlib.h>

#define task_num 2

char task0_stack[128] = {0};
char task1_stack[128] = {0};

char stack_addr_low[2 * task_num] = {0, 0, 0, 0};

void context_switch() {
  // get from
  // https://blog.vinu.co.in/2012/03/multitasking-in-avr-atmega32.html#more

  asm volatile("push r31\n\t"
               "push r30\n\t"
               "push r29\n\t"
               "push r28\n\t"
               "push r27\n\t"
               "push r26\n\t"
               "push r25\n\t"
               "push r24\n\t"
               "push r23\n\t"
               "push r22\n\t"
               "push r21\n\t"
               "push r20\n\t"
               "push r19\n\t"
               "push r18\n\t"
               "push r17\n\t"
               "push r16\n\t"
               "push r15\n\t"
               "push r14\n\t"
               "push r13\n\t"
               "push r12\n\t"
               "push r11\n\t"
               "push r10\n\t"
               "push r9\n\t"
               "push r8\n\t"
               "push r7\n\t"
               "push r6\n\t"
               "push r5\n\t"
               "push r4\n\t"
               "push r3\n\t"
               "push r2\n\t"
               "push r1\n\t"
               "push r0\n\t"
               // "in r17, SREG\n\t"
               // "push r17\n\t"

               // "pop r17\n\t"
               // "out SREG, r17\n\t"
               "pop r0\n\t"
               "pop r1\n\t"
               "pop r2\n\t"
               "pop r3\n\t"
               "pop r4\n\t"
               "pop r5\n\t"
               "pop r6\n\t"
               "pop r7\n\t"
               "pop r8\n\t"
               "pop r9\n\t"
               "pop r10\n\t"
               "pop r11\n\t"
               "pop r12\n\t"
               "pop r13\n\t"
               "pop r14\n\t"
               "pop r15\n\t"
               "pop r16\n\t"
               "pop r17\n\t"
               "pop r18\n\t"
               "pop r19\n\t"
               "pop r20\n\t"
               "pop r21\n\t"
               "pop r22\n\t"
               "pop r23\n\t"
               "pop r24\n\t"
               "pop r25\n\t"
               "pop r26\n\t"
               "pop r27\n\t"
               "pop r28\n\t"
               "pop r29\n\t"
               "pop r30\n\t"
               "pop r31\n\t");
}

void initMultitasking() {
  stack_addr_low[0] = ((short)task0_stack + 127) & 0x00FF;
  stack_addr_low[1] = (((short)task0_stack + 127) >> 8) & 0x00FF;
  stack_addr_low[2] = ((short)task1_stack + 127) & 0x00FF;
  stack_addr_low[3] = (((short)task1_stack + 127) >> 8) & 0x00FF;
}

void createTask(TaskFunc func, size_t stackSize) {}

void yield() { context_switch(); }
