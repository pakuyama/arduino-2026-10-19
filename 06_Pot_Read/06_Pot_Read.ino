// 아두이노 우노: A5 핀의 가변저항 값을 시리얼 모니터로 출력
// 가변저항: 바깥 다리 5V / 가운데 다리 A5 / 다른 바깥 다리 GND
const int POT_PIN = A5;   // 가변저항 가운데 다리가 연결된 핀

void setup()
{
  Serial.begin(9600);     // 시리얼 통신 시작 (속도 9600)
}

void loop()
{
  int value = analogRead(POT_PIN);         // 0 ~ 1023 값 읽기
  float voltage = value * (5.0 / 1023.0);  // 전압(V)으로 바꾸기

  Serial.print("값: ");
  Serial.print(value);
  Serial.print("  전압: ");
  Serial.print(voltage);
  Serial.println(" V");

  delay(200);             // 0.2초마다 출력
}
