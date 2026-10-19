// 아두이노 우노: 버튼 동작 구분 (millis() + 현재값/과거값 비교)
//  - 두 번 빠르게 누르기(더블클릭) -> LED 켜기
//  - 길게 누르기(롱프레스)          -> LED 끄기
//  - 한 번만 누르기                 -> 아무 일도 안 함
// 버튼: A0 (A0 - 버튼 - GND), LED: A5 (A5 - 220옴 - LED - GND)
const int BUTTON_PIN = A0;               // 버튼 핀
const int LED_PIN    = A5;               // LED 핀

const unsigned long DEBOUNCE_MS     = 50;    // 채터링(떨림) 무시 시간
const unsigned long DOUBLE_GAP_MS   = 400;   // 두 번째 클릭까지 기다리는 최대 시간
const unsigned long LONG_PRESS_MS   = 1000;  // 이 시간 이상 누르면 길게 누르기

int lastReading = HIGH;              // 과거에 읽은 값 (떨림 포함)
int buttonState = HIGH;              // 떨림이 끝나고 확정된 버튼 상태
unsigned long lastChangeTime  = 0;   // 값이 마지막으로 바뀐 시각
unsigned long pressStartTime  = 0;   // 버튼을 누르기 시작한 시각
unsigned long lastReleaseTime = 0;   // 버튼을 마지막으로 뗀 시각
int clickCount = 0;                  // 짧게 누른 횟수
bool longPressDone = false;          // 이번 누름에서 길게 누르기를 이미 처리했는지

void setup()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // 안 누르면 HIGH, 누르면 LOW
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(9600);
  Serial.println("더블클릭: LED 켜기 / 길게 누르기: LED 끄기");
}

void loop()
{
  unsigned long now = millis();
  int reading = digitalRead(BUTTON_PIN);  // 현재값 읽기

  // 현재값이 과거값과 다르면 바뀐 시각을 기록
  if (reading != lastReading)
  {
    lastChangeTime = now;
  }
  lastReading = reading;  // 현재값을 과거값으로 저장

  // 값이 DEBOUNCE_MS 동안 그대로 유지되면 진짜 변화로 인정
  if (now - lastChangeTime > DEBOUNCE_MS && reading != buttonState)
  {
    buttonState = reading;

    if (buttonState == LOW)  // 누른 순간
    {
      // 첫 클릭 후 너무 늦게 눌렀으면 새로 시작
      if (clickCount > 0 && now - lastReleaseTime > DOUBLE_GAP_MS)
      {
        clickCount = 0;
      }
      pressStartTime = now;
      longPressDone = false;
    }
    else  // 뗀 순간
    {
      if (!longPressDone)  // 길게 누르기가 아니었으면 짧은 클릭
      {
        clickCount++;
        lastReleaseTime = now;

        if (clickCount == 2)
        {
          digitalWrite(LED_PIN, HIGH);
          Serial.println("더블클릭 -> LED 켜짐");
          clickCount = 0;
        }
      }
    }
  }

  // 누르고 있는 동안: LONG_PRESS_MS가 지나면 길게 누르기
  if (buttonState == LOW && !longPressDone && now - pressStartTime >= LONG_PRESS_MS)
  {
    longPressDone = true;
    clickCount = 0;
    digitalWrite(LED_PIN, LOW);
    Serial.println("길게 누르기 -> LED 꺼짐");
  }

  // 한 번만 누르고 시간이 지나면: 아무 일도 안 하고 초기화
  if (buttonState == HIGH && clickCount == 1 && now - lastReleaseTime > DOUBLE_GAP_MS)
  {
    clickCount = 0;
    Serial.println("한 번 누르기 -> 무시");
  }
}
