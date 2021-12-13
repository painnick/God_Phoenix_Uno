#include "Effects.h"

//----------------------------------------------------------------------------------
uint32_t Wheel(Adafruit_NeoPixel *strip, byte WheelPos)
{
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85)
  {
    return strip->Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170)
  {
    WheelPos -= 85;
    return strip->Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

//----------------------------------------------------------------------------------

void after_burner(Adafruit_NeoPixel *strip, int t)
{
  strip->setBrightness(255);
  for (int i = 0; i < 256; i++)
  {
    strip->setPixelColor(0, strip->Color(i, 255 - i, 255 - i));
    strip->setPixelColor(1, strip->Color(125 + i / 2, i, i));
    strip->show();
    delay(t);
  }
}

void rainbow(Adafruit_NeoPixel *strip, uint8_t wait, bool dual)
{
  uint16_t pixelIndex, colorIndex;

  int numPixels = dual ? strip->numPixels() / 2 : strip->numPixels();

  for (colorIndex = 0; colorIndex < 256; colorIndex++)
  {
    for (pixelIndex = 0; pixelIndex < numPixels; pixelIndex++)
    {
      uint32_t wheelColor = Wheel(strip, (pixelIndex + colorIndex) & 255);
      strip->setPixelColor(pixelIndex, wheelColor);
      if (dual) {
        strip->setPixelColor(numPixels - pixelIndex, wheelColor);
      }
    }
    strip->show();
    delay(wait);
  }
}

void rainbowCycle(Adafruit_NeoPixel *strip, uint8_t wait, bool dual)
{
  uint16_t pixelIndex, colorIndex;

  int numPixels = dual ? strip->numPixels() / 2 : strip->numPixels();

  for (colorIndex = 0; colorIndex < 256; colorIndex++)
  { // 5 cycles of all colors on wheel
    for (pixelIndex = 0; pixelIndex < numPixels; pixelIndex++)
    {
      uint32_t color = Wheel(strip, ((pixelIndex * 256 / numPixels) + colorIndex) & 255);
      strip->setPixelColor(pixelIndex, color);
      if (dual) {
        strip->setPixelColor((numPixels * 2 - 1) - pixelIndex, color);
      }
    }
    strip->show();
    delay(wait);
  }
}

void colorWipe(Adafruit_NeoPixel *strip, uint32_t color, uint8_t wait, bool dual)
{
  int numPixels = dual ? strip->numPixels() / 2 : strip->numPixels();
  for (uint16_t pixelIndex = 0; pixelIndex < numPixels; pixelIndex++)
  {
    strip->setPixelColor((numPixels - 1) - pixelIndex, color);
    if (dual) {
      strip->setPixelColor(numPixels + pixelIndex, color);
    }
    strip->show();
    delay(wait);
  }
}
