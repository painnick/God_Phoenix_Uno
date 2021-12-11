#include "Effects.h"

void engine_normal(Adafruit_NeoPixel *strip, int t)
{
  strip->setPixelColor(0, strip->Color(125, 0, 0));
  strip->setPixelColor(1, strip->Color(0, 250, 250));
  strip->show();
  delay(t);
  strip->setPixelColor(0, strip->Color(50, 0, 0));
  strip->setPixelColor(1, strip->Color(50, 0, 0));
  strip->show();
  delay(t);
}

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

  for (colorIndex = 0; colorIndex < 256 * 5; colorIndex++)
  { // 5 cycles of all colors on wheel
    for (pixelIndex = 0; pixelIndex < numPixels; pixelIndex++)
    {
      uint32_t wheelColor = Wheel(strip, ((pixelIndex * 256 / numPixels) + colorIndex) & 255);
      strip->setPixelColor(pixelIndex, wheelColor);
      if (dual) {
        strip->setPixelColor((numPixels - 1) + numPixels - pixelIndex, wheelColor);
      }
    }
    strip->show();
    delay(wait);
  }
}

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

uint32_t Wheel_R(Adafruit_NeoPixel *strip, byte WheelPos)
{
  WheelPos = 255 - WheelPos;
  if (WheelPos > 122)
  {
    return strip->Color(255 - WheelPos, 0, 0);
  }
  if (WheelPos < 123)
  {
    return strip->Color(132 + WheelPos, 0, 0);
  }
}

void colorWipe(Adafruit_NeoPixel *strip, uint32_t color, uint8_t wait)
{
  uint16_t numPixels = strip->numPixels();
  for (uint16_t i = 0; i < numPixels; i++)
  {
    strip->setPixelColor(i, color);
    strip->show();
    delay(wait);
  }
}
void colorWipe_revers(Adafruit_NeoPixel *strip, uint32_t c, uint8_t wait)
{
  for (uint16_t i = 0; i < 12; i++)
  {
    strip->setPixelColor(11 - i, c);
    strip->show();
    delay(wait);
  }
}

void REDCycle(int front_side, int rear_side, Adafruit_NeoPixel *strip, uint8_t wait)
{
  uint16_t i, j, f, r;

  for (j = 0; j < 256 * 2; j++)
  {
    if (j < 256)
    {
      f = 255 - j;
      r = j;
    }
    if (j > 255)
    {
      f = j - 255;
      r = 255 - (j - 255);
    }

    for (i = 0; i < 11; i++)
    {
      strip->setPixelColor(i, Wheel_R(strip, ((i * 256 / 11) + j) & 255));
    }
    analogWrite(front_side, f);
    analogWrite(rear_side, r);
    strip->setPixelColor(10, strip->Color(250, 0, 0));     // 150
    strip->setPixelColor(11, strip->Color(250, 0, 0));     // 150
    strip->setPixelColor(12, strip->Color(255, 255, 255)); // 150
    strip->setPixelColor(13, strip->Color(255, 255, 255)); // 150
    strip->show();
    delay(wait);
    //  int randTime= random(2,6);
    //  delay(randTime);
  }
}
