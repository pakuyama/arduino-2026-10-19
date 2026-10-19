// 아두이노 우노 Blink: 보드 내장 LED(13번 핀)를 깜빡임
// DELAY_MS를 1000으로 하면 1초, 100으로 하면 0.1초 간격
const int DELAY_MS = 100;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);    // 13번 핀(보드 내장 LED)을 출력으로 설정
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH); // LED 켜기
  delay(DELAY_MS);
  digitalWrite(LED_BUILTIN, LOW);  // LED 끄기
  delay(DELAY_MS);
}
