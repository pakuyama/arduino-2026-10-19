// 아두이노 우노: 3, 8, 10번 핀의 LED를 1초 간격으로 차례대로 켜기
// (수업 코드 디버깅: 세미콜론 누락, LED3 안 꺼지는 문제 수정)
const int LED_PIN1 = 3;   // LED1 핀
const int LED_PIN2 = 8;   // LED2 핀
const int LED_PIN3 = 10;  // LED3 핀

void setup()
{
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);
}

void loop()
{
  digitalWrite(LED_PIN1, HIGH); // LED1 켜기
  delay(1000);
  digitalWrite(LED_PIN1, LOW);  // LED1 끄기

  digitalWrite(LED_PIN2, HIGH); // LED2 켜기
  delay(1000);
  digitalWrite(LED_PIN2, LOW);  // LED2 끄기

  digitalWrite(LED_PIN3, HIGH); // LED3 켜기
  delay(1000);
  digitalWrite(LED_PIN3, LOW);  // LED3 끄기
}
