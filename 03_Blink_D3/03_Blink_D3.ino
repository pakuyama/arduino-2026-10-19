// 아두이노 우노: 디지털 3번 핀의 LED 켜고 끄기
// D3 - 220옴 - LED(+), LED(-) - GND
const int LED_PIN = 3;           // LED가 연결된 디지털 3번 핀

void setup()
{
  pinMode(LED_PIN, OUTPUT);      // 3번 핀을 출력으로 설정
}

void loop()
{
  digitalWrite(LED_PIN, HIGH);   // LED 켜기
  delay(1000);                   // 1초 대기
  digitalWrite(LED_PIN, LOW);    // LED 끄기
  delay(1000);                   // 1초 대기
}
