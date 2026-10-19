// 아두이노 우노: A0 핀에 연결한 버튼 상태를 시리얼 모니터로 출력
const int BUTTON_PIN = A0;  // 버튼이 연결된 핀

void setup()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // 내부 풀업 저항 사용 (안 누르면 HIGH, 누르면 LOW)
  Serial.begin(9600);                 // 시리얼 통신 시작 (속도 9600)
}

void loop()
{
  int state = digitalRead(BUTTON_PIN);  // 버튼 상태 읽기

  if (state == LOW)
  {
    Serial.println("버튼 눌림");
  }
  else
  {
    Serial.println("버튼 안 눌림");
  }

  delay(200);  // 0.2초마다 출력
}
