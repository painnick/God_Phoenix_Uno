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

#define HEAD_PIN 0     // #1
#define COCKPIT_PIN 1  // #2
#define TOP_PIN 2      // #3
#define TAILSIDE_PIN 4 // #5
#define ENGINE_PIN 5   // #6
#define BUTTON_PIN 7   // #8

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

  pinMode(BUTTON_PIN, INPUT);

  head_strip.begin();
  cockpit_strip.begin();

#if DEBUG_MODE
  SerialUSB.println("----- Setup end -----");
#endif
}

void loop()
{
#if DEBUG_MODE
  SerialUSB.println("===== Loop start =====");
#endif

  if (digitalRead(BUTTON_PIN) == 0)
  {
#if DEBUG_MODE
    SerialUSB.println("Button Off");
#endif
    normal_form();
  }
  else
  {
#if DEBUG_MODE
    SerialUSB.println("Button On - Phoenix!!! ");
#endif
    phoenix_form();
  }

  delay(1000);

#if DEBUG_MODE
  SerialUSB.println("----- Loop end -----");
#endif
}

//----------------------------------------------------------------------------------
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
