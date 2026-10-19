// 아두이노 우노: A0 핀을 디지털 출력으로 써서 LED 깜빡이기
// A0 - 220옴 - LED(+), LED(-) - GND
void setup()
{
  pinMode(A0, OUTPUT);    // A0 핀을 디지털 출력으로 설정
}

void loop()
{
  digitalWrite(A0, HIGH); // LED 켜기
  delay(1000);            // 1초 대기
  digitalWrite(A0, LOW);  // LED 끄기
  delay(1000);            // 1초 대기
}
