#include "Effects.h"

/**
 * 색상 계산
 **/
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

/**
 * 엔진 발화 효과
 * 
 * engine_pin - 엔진 LED의 핀 번호
 * side_pin - 엔지 사이드 LED의 핀 번호
 * keep - 밝기를 유지할지 여부. false인 경우 어둡게 마무리
 **/
void after_burner(uint32_t engine_pin, uint32_t side_pin, bool keep)
{
  analogWrite(side_pin, 250);

  analogWrite(engine_pin, 50);
  delay(300);
  analogWrite(engine_pin, 100);
  delay(300);
  analogWrite(engine_pin, 150);
  delay(300);
  analogWrite(engine_pin, 250);
  delay(1500);
  analogWrite(engine_pin, 10);
  delay(500);
  analogWrite(engine_pin, 250);
  delay(2000);

  if (keep) {
    analogWrite(side_pin, 250);

  } else {
    analogWrite(engine_pin, 10);

    analogWrite(side_pin, 50);
  }
}

/**
 * 레인보우 색상 변경 효과
 * 
 * strip - NeoPixel
 * wait - 대기 시간(ms)
 * dual - 가운데를 기준으로 퍼저나가는지 여부(헤드 부분)
 **/
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
      if (dual)
      {
        strip->setPixelColor((numPixels * 2 - 1) - pixelIndex, color);
      }
    }
    strip->show();
    delay(wait);
  }
}

/**
 * 차례로 색상 변경
 * 
 * strip - NeoPixel
 * color - 적용할 색상
 * wait - 대기 시간(ms)
 * dual - 가운데를 기준으로 퍼저나가는지 여부(헤드 부분)
 **/
void colorWipe(Adafruit_NeoPixel *strip, uint32_t color, uint8_t wait, bool dual)
{
  int numPixels = dual ? strip->numPixels() / 2 : strip->numPixels();
  for (uint16_t pixelIndex = 0; pixelIndex < numPixels; pixelIndex++)
  {
    strip->setPixelColor((numPixels - 1) - pixelIndex, color);
    if (dual)
    {
      strip->setPixelColor(numPixels + pixelIndex, color);
    }
    strip->show();
    delay(wait);
  }
}
