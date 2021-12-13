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

#define HEAD_PIN     0 // #1
#define COCKPIT_PIN  1 // #2
#define TOP_PIN      2 // #3
#define TAILSIDE_PIN 4 // #5
#define ENGINE_PIN   5 // #6 NOT WORK
#define BUTTON_PIN   7 // #8

Adafruit_NeoPixel head_strip = Adafruit_NeoPixel(11 * 2, HEAD_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel cockpit_strip = Adafruit_NeoPixel(7, COCKPIT_PIN, NEO_GRB + NEO_KHZ800);

TimerTC3 timer;

//-------------------------------------------------------------------------------
#define f_side 1
#define r_side 2
#define biyoku 3 // 미익
#define tail_LED 4

byte w, fire;

//--------------------------------------------------------------------------
void setup()
{
#if DEBUG_MODE
  SerialUSB.begin(9600);
  delay(1000 * 2);
  SerialUSB.println("===== Start Setup =====");
#endif

  pinMode(BUTTON_PIN, INPUT);

#if DEBUG_MODE
  SerialUSB.println("----- Setup end -----");
#endif
}

void firstScene()
{
  analogWrite(TOP_PIN, 250);
  analogWrite(TAILSIDE_PIN, 250);

#if DEBUG_MODE
  SerialUSB.println("After Burner");
#endif

  analogWrite(ENGINE_PIN, 50);
  delay(300);
  analogWrite(ENGINE_PIN, 100);
  delay(300);
  analogWrite(ENGINE_PIN, 150);
  delay(300);
  analogWrite(ENGINE_PIN, 250);
  delay(1500);
  analogWrite(ENGINE_PIN, 10);
  delay(500);
  analogWrite(ENGINE_PIN, 250);
  delay(2000);
  analogWrite(ENGINE_PIN, 10);

#if DEBUG_MODE
  SerialUSB.println("Rainbow");
#endif

  head_strip.begin();
  cockpit_strip.begin();

  head_strip.setBrightness(STRIP_BRIGHT);
  cockpit_strip.setBrightness(STRIP_BRIGHT);

  for(int i = 0; i < 5; i ++) {
    rainbowCycle(&head_strip, 1, true);
    rainbowCycle(&cockpit_strip, 1, false);
  }

#if DEBUG_MODE
  SerialUSB.println("Wipe");
#endif

  head_strip.setBrightness(5);
  cockpit_strip.setBrightness(10);

  uint32_t normalColor = head_strip.Color(255, 140, 0);
  colorWipe(&head_strip, normalColor, 10, true);
  colorWipe(&cockpit_strip, normalColor, 10, false);

  analogWrite(TOP_PIN, 0);
  analogWrite(TAILSIDE_PIN, 0);
}

//---------------------------------------------------
void loop()
{
#if DEBUG_MODE
  SerialUSB.println("----- Loop start -----");
#endif

  if (digitalRead(BUTTON_PIN) == 0)
  {
    fire = 1;

#if DEBUG_MODE
    SerialUSB.println("Button Off");
#endif
  } else {
#if DEBUG_MODE
    SerialUSB.println("Button On");
#endif
  }

  firstScene();
  delay(1000 * 3);

  if (fire == 1)
  {
    fire = 0;
  }

#if DEBUG_MODE
  SerialUSB.println("----- Loop end -----");
#endif
}

//----------------------------------------------------------------------------------
