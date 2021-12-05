#include <MsTimer2.h>
//--------------------------------------------
#include <Adafruit_NeoPixel.h>
#define PIN 12
Adafruit_NeoPixel strip = Adafruit_NeoPixel(15, PIN, NEO_GRB + NEO_KHZ800);

//-------------------------------------------------------------------------------
#define f_side 1
#define r_side 2
#define biyoku 3
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

void engine_normal(int t)
{
  strip.setPixelColor(13, strip.Color(125, 0, 0));
  strip.setPixelColor(12, strip.Color(125, 0, 0));
  strip.setPixelColor(11, strip.Color(0, 250, 250));
  strip.show();
  delay(t);
  strip.setPixelColor(13, strip.Color(50, 0, 0));
  strip.setPixelColor(12, strip.Color(50, 0, 0));
  strip.show();
  delay(t);
}

void after_burner(int t)
{
  strip.setBrightness(255);
  for (int i = 0; i < 256; i++)
  {
    strip.setPixelColor(11, strip.Color(i, 255 - i, 255 - i));
    strip.setPixelColor(13, strip.Color(125 + i / 2, i, i));
    strip.setPixelColor(12, strip.Color(125 + i / 2, i, i));
    strip.show();
    delay(t);
  }
}

void phoenix()
{
  MsTimer2::stop();
  analogWrite(biyoku, 255);
  after_burner(10);
  for (int i = 0; i < 1; i++)
  {
    rainbowCycle(2);
  }
  colorWipe_revers(strip.Color(255, 0, 0), 50);
  for (int i = 0; i < 20; i++)
  {
    REDCycle(2);
  }
  colorWipe(strip.Color(0, 0, 0), 50);
  analogWrite(f_side, 0);
  analogWrite(r_side, 0);
  analogWrite(biyoku, 0);
  MsTimer2::start();
}

//--------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  pinMode(SW, INPUT_PULLUP);

  //---------------------------------------------------
  MsTimer2::set(10, TimerCnt);

  strip.begin();
  strip.setBrightness(250);
  rainbowCycle(1);
  colorWipe(strip.Color(0, 0, 0), 50);
  analogWrite(tail_LED, 255);
}

//---------------------------------------------------
void loop()
{

  if (digitalRead(SW) == 0)
  {
    fire = 1;
  }
  engine_normal(20);

  if (fire == 1)
  {
    phoenix();
    fire = 0;
  }
}

//----------------------------------------------------------------------------------
void rainbow(uint8_t wait)
{
  uint16_t i, j;

  for (j = 0; j < 256; j++)
  {
    for (i = 0; i < strip.numPixels(); i++)
    {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void colorWipe(uint32_t c, uint8_t wait)
{
  for (uint16_t i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
void colorWipe_revers(uint32_t c, uint8_t wait)
{
  for (uint16_t i = 0; i < 12; i++)
  {
    strip.setPixelColor(11 - i, c);
    strip.show();
    delay(wait);
  }
}

void rainbowCycle(uint8_t wait)
{
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++)
  { // 5 cycles of all colors on wheel
    for (i = 0; i < 11; i++)
    {
      strip.setPixelColor(i, Wheel(((i * 256 / 11) + j) & 255));
    }
    strip.setPixelColor(11, strip.Color(250, 0, 0));     // 150
    strip.setPixelColor(12, strip.Color(255, 255, 255)); // 150
    strip.setPixelColor(13, strip.Color(255, 255, 255)); // 150
    strip.show();
    delay(wait);
  }
}

void REDCycle(uint8_t wait)
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
      strip.setPixelColor(i, Wheel_R(((i * 256 / 11) + j) & 255));
    }
    analogWrite(f_side, f);
    analogWrite(r_side, r);
    strip.setPixelColor(10, strip.Color(250, 0, 0));     // 150
    strip.setPixelColor(11, strip.Color(250, 0, 0));     // 150
    strip.setPixelColor(12, strip.Color(255, 255, 255)); // 150
    strip.setPixelColor(13, strip.Color(255, 255, 255)); // 150
    strip.show();
    delay(wait);
    //  int randTime= random(2,6);
    //  delay(randTime);
  }
}

uint32_t Wheel(byte WheelPos)
{
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85)
  {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170)
  {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

uint32_t Wheel_R(byte WheelPos)
{
  WheelPos = 255 - WheelPos;
  if (WheelPos > 122)
  {
    return strip.Color(255 - WheelPos, 0, 0);
  }
  if (WheelPos < 123)
  {
    return strip.Color(132 + WheelPos, 0, 0);
  }
}
