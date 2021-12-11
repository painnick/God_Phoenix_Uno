#include <Adafruit_NeoPixel.h>
#include <TimerTC3.h>

uint32_t Wheel(Adafruit_NeoPixel* strip, byte WheelPos);
uint32_t Wheel_R(Adafruit_NeoPixel* strip, byte WheelPos);

void rainbow(Adafruit_NeoPixel* strip, uint8_t wait, bool dual);
void rainbowCycle(Adafruit_NeoPixel* strip, uint8_t wait, bool dual);
void colorWipe(Adafruit_NeoPixel* strip, uint32_t c, uint8_t wait);

void engine_normal(Adafruit_NeoPixel* strip, int t);
void after_burner(Adafruit_NeoPixel* strip, int t);
void colorWipe_revers(Adafruit_NeoPixel* strip, uint32_t c, uint8_t wait);
void REDCycle(int front_side, int rear_side, Adafruit_NeoPixel* strip, uint8_t wait);
