#include <kernel/ADC.h>
#include <kernel/digital_pin.h>
#include <kernel/driver/light_sensor.h>

void initLightSensor() { pin_A6_input(); }

int readLightSensor() { return readADC(6); }
