#include <kernel/driver/rgb_led.h>
#include <kernel/timer.h>
#include <kernel/utils.h>

void ledFlashOrange(unsigned char times) {
  while (1) {
    for (int x = 0; x < times; x++) {
      rgbLedSetColor(0, 140, 56, 0);
      rgbLedSetColor(1, 140, 56, 0);
      rgbLedRender();
      delayMillis(300);
      rgbLedSetColor(0, 0, 0, 0);
      rgbLedSetColor(1, 0, 0, 0);
      rgbLedRender();
      delayMillis(300);
    }
    delayMillis(2500);
  }
}
