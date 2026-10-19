// 아두이노 우노 신호등: 빨강 -> 노랑 -> 초록 순서로 2초씩 켜기
// 빨강: D7, 노랑: D8, 초록: D9 (각 핀 - 220옴 - LED(+), LED(-) - GND)
const int RED_PIN    = 7;
const int YELLOW_PIN = 8;
const int GREEN_PIN  = 9;
const int INTERVAL   = 2000;  // 2초

void setup()
{
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}

void loop()
{
  digitalWrite(RED_PIN, HIGH);     // 빨강 켜기
  delay(INTERVAL);
  digitalWrite(RED_PIN, LOW);      // 빨강 끄기

  digitalWrite(YELLOW_PIN, HIGH);  // 노랑 켜기
  delay(INTERVAL);
  digitalWrite(YELLOW_PIN, LOW);   // 노랑 끄기

  digitalWrite(GREEN_PIN, HIGH);   // 초록 켜기
  delay(INTERVAL);
  digitalWrite(GREEN_PIN, LOW);    // 초록 끄기
}
