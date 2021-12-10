#include <TimerTC3.h>
//--------------------------------------------
#include <Adafruit_NeoPixel.h>
#define HEAD_PIN 0 // Stocker #1
#define COCKPIT_PIN 1
#define TOP_PIN 2
#define TAILSIDE_PIN 3
Adafruit_NeoPixel strip = Adafruit_NeoPixel(15, HEAD_PIN, NEO_GRB + NEO_KHZ800);

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

void phoenix(Adafruit_NeoPixel* strip)
{
  TimerTc3.stop();
  analogWrite(biyoku, 255);
  after_burner(strip, 10);
  for (int i = 0; i < 1; i++)
  {
    rainbowCycle(strip, 2);
  }
  colorWipe_revers(strip, strip->Color(255, 0, 0), 50);
  for (int i = 0; i < 20; i++)
  {
    REDCycle(strip, 2);
  }
  colorWipe(strip, strip->Color(0, 0, 0), 50);
  analogWrite(f_side, 0);
  analogWrite(r_side, 0);
  analogWrite(biyoku, 0);
  TimerTc3.start();
}

//--------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  pinMode(SW, INPUT_PULLUP);

  //---------------------------------------------------
  TimerTc3.initialize(10000);
  TimerTc3.attachInterrupt(TimerCnt);

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
    phoenix(&strip);
    fire = 0;
  }
}

//----------------------------------------------------------------------------------
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

void REDCycle(Adafruit_NeoPixel* strip, uint8_t wait)
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
    analogWrite(f_side, f);
    analogWrite(r_side, r);
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
