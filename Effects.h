#include <Adafruit_NeoPixel.h>

void engine_normal(Adafruit_NeoPixel* strip, int t);
void after_burner(Adafruit_NeoPixel* strip, int t);
void rainbow(Adafruit_NeoPixel* strip, uint8_t wait);
uint32_t Wheel(Adafruit_NeoPixel* strip, byte WheelPos);
uint32_t Wheel_R(Adafruit_NeoPixel* strip, byte WheelPos);
void rainbowCycle(Adafruit_NeoPixel* strip, uint8_t wait);
void colorWipe(Adafruit_NeoPixel* strip, uint32_t c, uint8_t wait);
void colorWipe_revers(Adafruit_NeoPixel* strip, uint32_t c, uint8_t wait);
