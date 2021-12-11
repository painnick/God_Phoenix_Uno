#include <TimerTC3.h>
//--------------------------------------------
#include <Adafruit_NeoPixel.h>
#include "Effects.h"

#define DEBUG_MODE 1

#if DEBUG_MODE
  #define STRIP_BRIGHT 5
#else
  #define STRIP_BRIGHT 250
#endif

#define HEAD_PIN 6 // 0번 라인 연결 문제
#define COCKPIT_PIN 1
#define TOP_PIN 3 // 2번 라인 연결 문제
#define TAILSIDE_PIN 4
#define ENGINE_PIN 5

Adafruit_NeoPixel head_strip = Adafruit_NeoPixel(11 * 2, HEAD_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel cockpit_strip = Adafruit_NeoPixel(7, COCKPIT_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel engine_strip = Adafruit_NeoPixel(2, ENGINE_PIN, NEO_GRB + NEO_KHZ800);

TimerTC3 timer;

//-------------------------------------------------------------------------------
#define f_side 1
#define r_side 2
#define biyoku 3 // 미익
#define tail_LED 4
#define SW 10

byte w, fire;

//--------------------------------------------------------------------------
void setup()
{
#if DEBUG_MODE
  SerialUSB.begin(9600);
  delay(1000 * 2);
  SerialUSB.println("===== Start Setup =====");
#endif

  // pinMode(SW, INPUT_PULLUP);

#if DEBUG_MODE
  SerialUSB.println("----- Setup end -----");
#endif
}

void firstScene()
{
  analogWrite(TOP_PIN, 250);
  analogWrite(TAILSIDE_PIN, 250);

#if DEBUG_MODE
  SerialUSB.println("Rainbow");
#endif

  head_strip.begin();
  cockpit_strip.begin();
  engine_strip.begin();

  head_strip.setBrightness(STRIP_BRIGHT);
  cockpit_strip.setBrightness(STRIP_BRIGHT);
  engine_strip.setBrightness(STRIP_BRIGHT);

  engine_normal(&engine_strip, 20);

  rainbowCycle(&head_strip, 1, true);
  rainbowCycle(&cockpit_strip, 1, false);

#if DEBUG_MODE
  SerialUSB.println("Wipe");
#endif

  colorWipe(&head_strip, head_strip.Color(0, 0, 0), 10, true);
  colorWipe(&cockpit_strip, cockpit_strip.Color(0, 0, 0), 10, false);

  analogWrite(TOP_PIN, 0);
  analogWrite(TAILSIDE_PIN, 0);
}

//---------------------------------------------------
void loop()
{
#if DEBUG_MODE
  SerialUSB.println("----- Loop start -----");
#endif

  // if (digitalRead(SW) == 0)
  // {
  //   fire = 1;
  // }
  // engine_normal(&strip, 20);

  firstScene();
  delay(1000 * 3);

  // if (fire == 1)
  // {
  //   phoenix(&timer, &strip);
  //   fire = 0;
  // }
#if DEBUG_MODE
  SerialUSB.println("----- Loop end -----");
#endif
}

//----------------------------------------------------------------------------------
void phoenix(TimerTC3* timer, Adafruit_NeoPixel* strip)
{
  timer->stop();
  analogWrite(biyoku, 255);
  after_burner(strip, 10);
  for (int i = 0; i < 1; i++)
  {
    rainbowCycle(strip, 2, true);
  }
  for (int i = 0; i < 20; i++)
  {
    REDCycle(f_side, r_side, strip, 2);
  }
  colorWipe(strip, strip->Color(0, 0, 0), 50, true);
  analogWrite(f_side, 0);
  analogWrite(r_side, 0);
  analogWrite(biyoku, 0);
  timer->start();
}

