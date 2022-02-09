#include "kernel/analog_pin.h"
#include "kernel/digital_pin.h"
#include <kernel/driver/motor.h>

void motorInit() {
  pin_4_output();
  pin_7_output();
}

void motorLeftSpeed(unsigned char speed) {
  motor_left_speed = speed;
  fastPWM_pin5(speed);
}

void motorRightSpeed(unsigned char speed) {
  motor_right_speed = speed;
  fastPWM_pin6(speed);
}

void motorLeftReverse(unsigned char reversed) {
  if (reversed) {
    pin_4_on();
  } else {
    pin_4_off();
  }
}

void motorRightReverse(unsigned char reversed) {
  if (reversed) {
    pin_7_on();
  } else {
    pin_7_off();
  }
}
