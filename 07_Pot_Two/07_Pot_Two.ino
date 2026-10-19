// 아두이노 우노: 가변저항 2개(A4, A5) 값을 각각 읽어 시리얼 모니터로 출력
const int POT1_PIN = A4;  // 가변저항 1 가운데 다리
const int POT2_PIN = A5;  // 가변저항 2 가운데 다리

void setup()
{
  Serial.begin(9600);     // 시리얼 통신 시작 (속도 9600)
}

void loop()
{
  int value1 = analogRead(POT1_PIN);  // 가변저항 1 값 (0 ~ 1023)
  int value2 = analogRead(POT2_PIN);  // 가변저항 2 값 (0 ~ 1023)

  float voltage1 = value1 * (5.0 / 1023.0);  // 전압(V)으로 바꾸기
  float voltage2 = value2 * (5.0 / 1023.0);

  Serial.print("POT1: ");
  Serial.print(value1);
  Serial.print(" (");
  Serial.print(voltage1);
  Serial.print(" V)   POT2: ");
  Serial.print(value2);
  Serial.print(" (");
  Serial.print(voltage2);
  Serial.println(" V)");

  delay(200);             // 0.2초마다 출력
}
