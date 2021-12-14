/**
 * God Phoenix L.E.D work
 * 
 * @author painnick@gmail.com
 * @see https://smile-dental-clinic.info/wordpress/?p=11441
 **/
#include <Adafruit_NeoPixel.h>
#include "Effects.h"

#define DEBUG_MODE 1

#if DEBUG_MODE
#define STRIP_BRIGHT 5
#else
#define STRIP_BRIGHT 250
#endif

#define HEAD_PIN 0     // #1 기수 앞 부분의 NeoPixel
#define COCKPIT_PIN 1  // #2 콕핏 부분의 NeoPixel
#define TOP_PIN 2      // #3 상단의 원형 클리어 안에 심은 LED
#define TAILSIDE_PIN 4 // #5 엔진 좌우의 클리어 안에 심은 LED
#define ENGINE_PIN 5   // #6 엔진 클리어 안에 심은 LED
#define BUTTON_PIN 7   // #8 신호 입력용 버튼 스위치

Adafruit_NeoPixel head_strip = Adafruit_NeoPixel(11 * 2, HEAD_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel cockpit_strip = Adafruit_NeoPixel(7, COCKPIT_PIN, NEO_GRB + NEO_KHZ800);

//--------------------------------------------------------------------------
void setup()
{
#if DEBUG_MODE
  SerialUSB.begin(9600);
  delay(1000 * 2);
  SerialUSB.println("===== Start Setup =====");
#endif

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  head_strip.begin();
  cockpit_strip.begin();

#if DEBUG_MODE
  SerialUSB.println("----- Setup end -----");
#endif
}

#if DEBUG_MODE
uint32_t count = 0;
#endif
void loop()
{
#if DEBUG_MODE
  SerialUSB.println("===== Loop start =====");
#endif

  if (digitalRead(BUTTON_PIN) == LOW)
  {
#if DEBUG_MODE
    SerialUSB.println("Button Off");
    count = 0;
#endif
    normal_form();
  }
  else
  {
#if DEBUG_MODE
    count++;
    SerialUSB.print("Button On - Phoenix!!! ");
    SerialUSB.println(count);
#endif
    phoenix_form();
  }

#if DEBUG_MODE
  delay(1000);

  SerialUSB.println("----- Loop end -----");
#endif
}

//----------------------------------------------------------------------------------
/**
 * 노말 모드
 * NeoPixel은 1가지 색으로 설정하고, 일반 LED의 밝기는 다소 어두운 상태로 켠다
 **/
void normal_form()
{
  analogWrite(TOP_PIN, 50);

  after_burner(ENGINE_PIN, TAILSIDE_PIN, false);

  head_strip.setBrightness(5);
  cockpit_strip.setBrightness(10);

  uint32_t normalColor = head_strip.Color(255, 140, 0);
  colorWipe(&head_strip, normalColor, 10, true);
  colorWipe(&cockpit_strip, normalColor, 10, false);
}

/**
 * 피닉스 모드
 * 레인보우 효과와 함께 일반 LED들의 밝기도 최대로 한다.
 **/
void phoenix_form()
{
  analogWrite(TOP_PIN, 250);

  after_burner(ENGINE_PIN, TAILSIDE_PIN, true);

  head_strip.setBrightness(STRIP_BRIGHT);
  cockpit_strip.setBrightness(STRIP_BRIGHT);

  for (int i = 0; i < 5; i++)
  {
    rainbowCycle(&head_strip, 1, true);
    rainbowCycle(&cockpit_strip, 1, false);
  }
}
