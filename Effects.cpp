#include "Effects.h"

void engine_normal(Adafruit_NeoPixel* strip, int t)
{
  strip->setPixelColor(13, strip->Color(125, 0, 0));
  strip->setPixelColor(12, strip->Color(125, 0, 0));
  strip->setPixelColor(11, strip->Color(0, 250, 250));
  strip->show();
  delay(t);
  strip->setPixelColor(13, strip->Color(50, 0, 0));
  strip->setPixelColor(12, strip->Color(50, 0, 0));
  strip->show();
  delay(t);
}

void after_burner(Adafruit_NeoPixel* strip, int t)
{
  strip->setBrightness(255);
  for (int i = 0; i < 256; i++)
  {
    strip->setPixelColor(11, strip->Color(i, 255 - i, 255 - i));
    strip->setPixelColor(13, strip->Color(125 + i / 2, i, i));
    strip->setPixelColor(12, strip->Color(125 + i / 2, i, i));
    strip->show();
    delay(t);
  }
}

void rainbow(Adafruit_NeoPixel* strip, uint8_t wait)
{
  uint16_t i, j;

  for (j = 0; j < 256; j++)
  {
    for (i = 0; i < strip->numPixels(); i++)
    {
      strip->setPixelColor(i, Wheel(strip, (i + j) & 255));
    }
    strip->show();
    delay(wait);
  }
}

uint32_t Wheel(Adafruit_NeoPixel* strip, byte WheelPos)
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

uint32_t Wheel_R(Adafruit_NeoPixel* strip, byte WheelPos)
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

void rainbowCycle(Adafruit_NeoPixel* strip, uint8_t wait)
{
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++)
  { // 5 cycles of all colors on wheel
    for (i = 0; i < 11; i++)
    {
      strip->setPixelColor(i, Wheel(strip, ((i * 256 / 11) + j) & 255));
    }
    strip->setPixelColor(11, strip->Color(250, 0, 0));     // 150
    strip->setPixelColor(12, strip->Color(255, 255, 255)); // 150
    strip->setPixelColor(13, strip->Color(255, 255, 255)); // 150
    strip->show();
    delay(wait);
  }
}

void colorWipe(Adafruit_NeoPixel* strip, uint32_t c, uint8_t wait)
{
  for (uint16_t i = 0; i < strip->numPixels(); i++)
  {
    strip->setPixelColor(i, c);
    strip->show();
    delay(wait);
  }
}
void colorWipe_revers(Adafruit_NeoPixel* strip, uint32_t c, uint8_t wait)
{
  for (uint16_t i = 0; i < 12; i++)
  {
    strip->setPixelColor(11 - i, c);
    strip->show();
    delay(wait);
  }
}

void REDCycle(int front_side, int rear_side, Adafruit_NeoPixel* strip, uint8_t wait)
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
