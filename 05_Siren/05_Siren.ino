// 아두이노 우노: LED 2개로 경찰차 사이렌처럼 번갈아 깜빡이기
const int LED_RED  = 3;   // 빨간 LED 핀
const int LED_BLUE = 8;   // 파란 LED 핀

const int FLASH_COUNT = 3;  // 한쪽이 연속으로 깜빡이는 횟수
const int FLASH_ON    = 50; // 켜져 있는 시간(ms)
const int FLASH_OFF   = 50; // 꺼져 있는 시간(ms)

void setup()
{
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

// 지정한 LED를 빠르게 여러 번 깜빡이는 함수
void flash(int pin)
{
  for (int i = 0; i < FLASH_COUNT; i++)
  {
    digitalWrite(pin, HIGH);
    delay(FLASH_ON);
    digitalWrite(pin, LOW);
    delay(FLASH_OFF);
  }
}

void loop()
{
  flash(LED_RED);   // 빨간 LED 3번 깜빡
  delay(100);       // 잠깐 쉬기
  flash(LED_BLUE);  // 파란 LED 3번 깜빡
  delay(100);
}
