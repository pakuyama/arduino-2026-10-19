// 아두이노 우노: 외부 인터럽트로 버튼을 누를 때와 뗄 때마다 LED 토글
// 우노의 인터럽트 핀은 D2, D3 두 개뿐이라 버튼은 D2에 연결
// 버튼: D2 (D2 - 버튼 - GND), LED: A5 (A5 - 220옴 - LED - GND)
const int BUTTON_PIN = 2;                // 버튼 핀 (인터럽트 0번)
const int LED_PIN    = A5;               // LED 핀
const unsigned long DEBOUNCE_MS = 50;    // 채터링(떨림) 무시 시간

volatile int ledState = LOW;             // LED 상태 (인터럽트에서 바뀌므로 volatile)
volatile bool changed = false;           // 인터럽트가 일어났는지 표시
volatile unsigned long lastInterruptTime = 0;  // 마지막으로 인정한 인터럽트 시각

// 인터럽트 서비스 루틴: 버튼 핀 값이 바뀔 때마다(누름/뗌) 자동으로 실행
void onButtonChange()
{
  unsigned long now = millis();
  if (now - lastInterruptTime > DEBOUNCE_MS)  // 떨림으로 생긴 인터럽트는 무시
  {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    changed = true;
    lastInterruptTime = now;
  }
}

void setup()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // 안 누르면 HIGH, 누르면 LOW
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
  Serial.begin(9600);

  // CHANGE: HIGH->LOW(누름), LOW->HIGH(뗌) 둘 다에서 인터럽트 발생
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onButtonChange, CHANGE);
  Serial.println("버튼을 누르고 뗄 때마다 LED가 토글됩니다");
}

void loop()
{
  // 시리얼 출력은 시간이 걸리므로 인터럽트 안이 아니라 loop에서 처리
  if (changed)
  {
    changed = false;
    Serial.println(ledState == HIGH ? "LED 켜짐" : "LED 꺼짐");
  }
}
