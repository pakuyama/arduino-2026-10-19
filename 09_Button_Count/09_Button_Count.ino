// 아두이노 우노: millis()와 현재값/과거값 비교로 버튼 누른 횟수 세기
// 5번 누를 때마다 LED 토글
// 버튼: A0 (A0 - 버튼 - GND), LED: A5 (A5 - 220옴 - LED - GND)
const int BUTTON_PIN = A0;              // 버튼 핀
const int LED_PIN    = A5;              // LED 핀
const unsigned long DEBOUNCE_MS = 50;   // 채터링(떨림) 무시 시간
const int TOGGLE_EVERY = 5;             // 몇 번 누를 때마다 LED를 토글할지

int lastReading  = HIGH;   // 과거에 읽은 값 (떨림 포함)
int buttonState  = HIGH;   // 떨림이 끝나고 확정된 버튼 상태
unsigned long lastChangeTime = 0;  // 값이 마지막으로 바뀐 시각
int pressCount   = 0;      // 버튼 누른 횟수
int ledState     = LOW;    // LED 상태

void setup()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // 안 누르면 HIGH, 누르면 LOW
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("버튼을 눌러 보세요");
}

void loop()
{
  int reading = digitalRead(BUTTON_PIN);  // 현재값 읽기

  // 현재값이 과거값과 다르면 바뀐 시각을 기록
  if (reading != lastReading)
  {
    lastChangeTime = millis();
  }

  // 값이 DEBOUNCE_MS 동안 그대로 유지되면 진짜 변화로 인정
  if (millis() - lastChangeTime > DEBOUNCE_MS)
  {
    if (reading != buttonState)
    {
      buttonState = reading;

      // HIGH -> LOW 로 바뀐 순간 = 버튼을 누른 순간
      if (buttonState == LOW)
      {
        pressCount++;
        Serial.print("버튼 누른 횟수: ");
        Serial.println(pressCount);

        // 5번 누를 때마다 LED 토글
        if (pressCount % TOGGLE_EVERY == 0)
        {
          ledState = !ledState;
          digitalWrite(LED_PIN, ledState);
          Serial.println(ledState == HIGH ? "LED 켜짐" : "LED 꺼짐");
        }
      }
    }
  }

  lastReading = reading;  // 현재값을 과거값으로 저장
}
