/**
 * God Phoenix L.E.D work
 * 
 * @author painnick@gmail.com
 * @see https://smile-dental-clinic.info/wordpress/?p=11441
 **/
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include "DFMiniMp3.h"
#include "Effects.h"

#define _DEBUG 1

#ifdef _DEBUG
#define STRIP_BRIGHT 5
#else
#define STRIP_BRIGHT 250
#endif

#define HEAD_PIN 0     // #1 기수 앞 부분의 NeoPixel
#define COCKPIT_PIN 1  // #2 콕핏 부분의 NeoPixel
#define TOP_PIN 2      // #3 상단의 원형 클리어 안에 심은 LED
#define RX_PIN 3
#define TAILSIDE_PIN 4 // #5 엔진 좌우의 클리어 안에 심은 LED
#define ENGINE_PIN 5   // #6 엔진 클리어 안에 심은 LED
#define TX_PIN 6
#define BUTTON_PIN 7   // #8 신호 입력용 버튼 스위치

Adafruit_NeoPixel head_strip = Adafruit_NeoPixel(11 * 2, HEAD_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel cockpit_strip = Adafruit_NeoPixel(7, COCKPIT_PIN, NEO_GRB + NEO_KHZ800);

class Mp3Notify; 
typedef DFMiniMp3<SoftwareSerial, Mp3Notify> DfMp3; 
SoftwareSerial mySerial(RX_PIN, TX_PIN);
DfMp3 dfmp3(mySerial);

//--------------------------------------------------------------------------
void setup()
{
#ifdef _DEBUG
  SerialUSB.begin(9600);
  delay(1000 * 2);
  SerialUSB.println("===== Start Setup =====");
#endif

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  head_strip.begin();
  cockpit_strip.begin();
  dfmp3.begin(9600, 1000);

  dfmp3.reset();
  dfmp3.setVolume(15);
  delay(100);

#ifdef _DEBUG
  SerialUSB.println("----- Setup end -----");
#endif
}

#ifdef _DEBUG
int lastState = -1;
#endif
void loop()
{
#ifdef _DEBUG
  SerialUSB.println("===== Loop start =====");
#endif

  if (digitalRead(BUTTON_PIN) == LOW)
  {
    if (lastState != LOW) {
#ifdef _DEBUG
      SerialUSB.println("Button Off");
#endif
      normal_form();
    }
    lastState = LOW;
  }
  else
  {
    if (lastState != HIGH) {    
#ifdef _DEBUG
      SerialUSB.println("Button On - Phoenix!!!");
#endif
      phoenix_form();
    }
    lastState = HIGH;
  }

#ifdef _DEBUG
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
#ifdef _DEBUG
      SerialUSB.println("Process - Normal");
#endif

  dfmp3.playGlobalTrack(1);
  delay(100);

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
#ifdef _DEBUG
      SerialUSB.println("Process - PHOENIX!");
#endif

  dfmp3.playGlobalTrack(2);
  delay(100);

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

//----------------------------------------------------------------------------------
class Mp3Notify
{
public:
  static void PrintlnSourceAction(DfMp3_PlaySources source, const char* action)
  {
    if (source & DfMp3_PlaySources_Sd) 
    {
        Serial.print("SD Card, ");
    }
    if (source & DfMp3_PlaySources_Usb) 
    {
        Serial.print("USB Disk, ");
    }
    if (source & DfMp3_PlaySources_Flash) 
    {
        Serial.print("Flash, ");
    }
    Serial.println(action);
  }
  static void OnError(DfMp3& mp3, uint16_t errorCode)
  {
    // see DfMp3_Error for code meaning
    Serial.println();
    Serial.print("Com Error ");
    switch (errorCode)
    {
    case DfMp3_Error_Busy:
      Serial.println("Busy");
      break;
    case DfMp3_Error_Sleeping:
      Serial.println("Sleeping");
      break;
    case DfMp3_Error_SerialWrongStack:
      Serial.println("Serial Wrong Stack");
      break;

    case DfMp3_Error_RxTimeout:
      Serial.println("Rx Timeout!!!");
      break;
    case DfMp3_Error_PacketSize:
      Serial.println("Wrong Packet Size!!!");
      break;
    case DfMp3_Error_PacketHeader:
      Serial.println("Wrong Packet Header!!!");
      break;
    case DfMp3_Error_PacketChecksum:
      Serial.println("Wrong Packet Checksum!!!");
      break;

    default:
      Serial.println(errorCode, HEX);
      break;
    }
  }
  static void OnPlayFinished(DfMp3& mp3, DfMp3_PlaySources source, uint16_t track)
  {
    Serial.print("Play finished for #");
    Serial.println(track);

    Serial.println("Play #1");
    mp3.playGlobalTrack(0);
  }
  static void OnPlaySourceOnline(DfMp3& mp3, DfMp3_PlaySources source)
  {
    PrintlnSourceAction(source, "online");
  }
  static void OnPlaySourceInserted(DfMp3& mp3, DfMp3_PlaySources source)
  {
    PrintlnSourceAction(source, "inserted");
  }
  static void OnPlaySourceRemoved(DfMp3& mp3, DfMp3_PlaySources source)
  {
    PrintlnSourceAction(source, "removed");
  }
};