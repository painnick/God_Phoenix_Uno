#include <TimerTC3.h>
//--------------------------------------------
#include <Adafruit_NeoPixel.h>
#include "Effects.h"

#define HEAD_PIN 0 // Stocker #1
#define COCKPIT_PIN 1
#define TOP_PIN 2
#define TAILSIDE_PIN 3
Adafruit_NeoPixel strip = Adafruit_NeoPixel(15, HEAD_PIN, NEO_GRB + NEO_KHZ800);
TimerTC3 timer;

//-------------------------------------------------------------------------------
#define f_side 1
#define r_side 2
#define biyoku 3 // 미익
#define tail_LED 4
#define SW 10

byte w, fire;

//--------------------------------------------------------------------------
void TimerCnt()
{
  w++;
  if (w > 100 && w < 200)
  {
    analogWrite(biyoku, 250);
  }
  else
  {
    analogWrite(biyoku, 0);
  }
  if (w >= 200)
  {
    w = 0;
  }
}

void phoenix(TimerTC3* timer, Adafruit_NeoPixel* strip)
{
  timer->stop();
  analogWrite(biyoku, 255);
  after_burner(strip, 10);
  for (int i = 0; i < 1; i++)
  {
    rainbowCycle(strip, 2);
  }
  colorWipe_revers(strip, strip->Color(255, 0, 0), 50);
  for (int i = 0; i < 20; i++)
  {
    REDCycle(f_side, r_side, strip, 2);
  }
  colorWipe(strip, strip->Color(0, 0, 0), 50);
  analogWrite(f_side, 0);
  analogWrite(r_side, 0);
  analogWrite(biyoku, 0);
  timer->start();
}

//--------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  pinMode(SW, INPUT_PULLUP);

  //---------------------------------------------------
  timer.initialize(10000);
  timer.attachInterrupt(TimerCnt);

  strip.begin();
  strip.setBrightness(250);
  rainbowCycle(&strip, 1);
  colorWipe(&strip, strip.Color(0, 0, 0), 50);
  analogWrite(tail_LED, 255);
}

//---------------------------------------------------
void loop()
{

  if (digitalRead(SW) == 0)
  {
    fire = 1;
  }
  engine_normal(&strip, 20);

  if (fire == 1)
  {
    phoenix(&timer, &strip);
    fire = 0;
  }
}

//----------------------------------------------------------------------------------
