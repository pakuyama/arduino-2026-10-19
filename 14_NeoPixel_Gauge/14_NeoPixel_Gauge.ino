// 아두이노 우노: 가변저항(A0)으로 네오픽셀 8구 게이지 채우기
// 네오픽셀: DIN -> D10, 5V -> 5V, GND -> GND
// 가변저항: 바깥 다리 5V / 가운데 다리 A0 / 다른 바깥 다리 GND
// 필요한 라이브러리: Adafruit NeoPixel (라이브러리 매니저에서 설치)
#include <Adafruit_NeoPixel.h>

const int PIXEL_PIN  = 10;   // 네오픽셀 신호선
const int PIXEL_NUM  = 8;    // 네오픽셀 개수
const int POT_PIN    = A0;   // 가변저항 가운데 다리
const int BRIGHTNESS = 50;   // 전체 밝기 (0 ~ 255), 너무 밝으면 줄이기

Adafruit_NeoPixel strip(PIXEL_NUM, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();          // 처음엔 모두 끄기
  Serial.begin(9600);
}

void loop()
{
  int potValue = analogRead(POT_PIN);                 // 0 ~ 1023
  int level = map(potValue, 0, 1024, 0, PIXEL_NUM + 1);  // 0 ~ 8 개 켜기 (9단계를 고르게 나눔)

  for (int i = 0; i < PIXEL_NUM; i++)
  {
    if (i < level)
    {
      // 위치에 따라 초록 -> 노랑 -> 빨강 으로 색 바꾸기
      int red   = map(i, 0, PIXEL_NUM - 1, 0, 255);
      int green = map(i, 0, PIXEL_NUM - 1, 255, 0);
      strip.setPixelColor(i, strip.Color(red, green, 0));
    }
    else
    {
      strip.setPixelColor(i, 0);   // 끄기
    }
  }
  strip.show();          // 설정한 색을 실제로 내보내기

  Serial.print("가변저항: ");
  Serial.print(potValue);
  Serial.print("  게이지: ");
  Serial.print(level);
  Serial.print(" / ");
  Serial.println(PIXEL_NUM);

  delay(50);
}
