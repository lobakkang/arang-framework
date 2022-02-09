#ifndef MOTOR_H_
#define MOTOR_H_

#include <kernel/digital_pin.h>

#define POLAR_NORMAL 0x00
#define POLAR_REVERSE 0xFF

unsigned char motor_right_speed = 0;
unsigned char motor_left_speed = 0;

void motorInit();

void motorLeftSpeed(unsigned char speed);
void motorRightSpeed(unsigned char speed);

void motorLeftReverse(unsigned char reversed);
void motorRightReverse(unsigned char reversed);

#endif
