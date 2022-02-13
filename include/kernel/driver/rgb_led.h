#ifndef RGB_LED_H_
#define RGB_LED_H_

void rgbLedInit();
void rgbLedSetColor(unsigned char idx, unsigned char r, unsigned char g,
                    unsigned char b);
void rgbLedRender();

#endif
