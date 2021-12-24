#include <Adafruit_NeoPixel.h>

enum COLOR_FILL_TYPE {
  ALL = 0,
  ODD,
  EVEN
};

uint32_t Wheel(Adafruit_NeoPixel *strip, byte WheelPos);

void rainbow(Adafruit_NeoPixel *strip, uint8_t wait, bool dual);
void rainbowCycle(Adafruit_NeoPixel *strip, uint8_t wait, bool dual);
void colorWipe(Adafruit_NeoPixel *strip, uint32_t c, uint8_t wait, bool dual, COLOR_FILL_TYPE type = COLOR_FILL_TYPE::ALL);

void after_burner(uint32_t engine_pin, uint32_t side_pin, bool keep);
