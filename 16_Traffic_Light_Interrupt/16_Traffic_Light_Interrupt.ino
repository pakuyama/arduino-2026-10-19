// 아두이노 우노 신호등: 빨강 -> 노랑 -> 초록 순서로 2초씩 켜기
//  - D2 버튼을 누르면 인터럽트 발생 -> 모든 불 켜짐
//  - 다시 누르면 전부 꺼졌다가(1초) 빨강부터 처음부터 다시 동작
// 빨강: D7, 노랑: D8, 초록: D9 (각 핀 - 220옴 - LED(+), LED(-) - GND)
// 버튼: D2 (D2 - 버튼 - GND)
const int RED_PIN    = 7;
const int YELLOW_PIN = 8;
const int GREEN_PIN  = 9;
const int BUTTON_PIN = 2;                // 인터럽트 핀 (우노는 D2, D3만 가능)
const unsigned long INTERVAL    = 2000;  // 2초
const unsigned long DEBOUNCE_MS = 200;   // 버튼 떨림 무시 시간
const unsigned long OFF_MS      = 1000;  // 다시 시작하기 전 전부 꺼져 있는 시간

const int LIGHTS[3] = {RED_PIN, YELLOW_PIN, GREEN_PIN};  // 켜지는 순서

volatile bool allOnMode = false;              // 모든 불 켜기 모드인지
volatile bool modeChanged = false;            // 모드가 바뀌었는지 표시
volatile unsigned long lastInterruptTime = 0;

int step = 0;                     // -1: 전부 꺼짐, 0: 빨강, 1: 노랑, 2: 초록
unsigned long stepStartTime = 0;  // 현재 신호가 시작된 시각

// 인터럽트 서비스 루틴: 버튼을 누르는 순간 자동으로 실행
void onButtonPress()
{
  unsigned long now = millis();
  if (now - lastInterruptTime > DEBOUNCE_MS)
  {
    allOnMode = !allOnMode;
    modeChanged = true;
    lastInterruptTime = now;
  }
}

// 모든 불 켜기
void allOn()
{
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(YELLOW_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
}

// 현재 순서의 불 하나만 켜고 나머지는 끄기
void showStep(int s)
{
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(LIGHTS[i], i == s ? HIGH : LOW);
  }
}

void setup()
{
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // 안 누르면 HIGH, 누르면 LOW

  // FALLING: 버튼을 누르는 순간(HIGH -> LOW) 인터럽트 발생
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onButtonPress, FALLING);

  showStep(step);
  stepStartTime = millis();
}

void loop()
{
  unsigned long now = millis();

  if (modeChanged)
  {
    modeChanged = false;
    if (allOnMode)
    {
      allOn();                // 전체 켜기
    }
    else
    {
      step = -1;              // 먼저 전부 끄고, OFF_MS 뒤에 빨강부터 다시
      showStep(step);
      stepStartTime = now;
    }
  }

  if (allOnMode)
  {
    allOn();
    return;                   // 전체 켜기 모드에서는 신호를 바꾸지 않음
  }

  // delay() 대신 millis()로 2초 확인 -> 버튼에 바로 반응
  unsigned long duration = (step == -1) ? OFF_MS : INTERVAL;
  if (now - stepStartTime >= duration)
  {
    step = (step + 1) % 3;    // (전부 꺼짐 ->) 빨강 -> 노랑 -> 초록 -> 빨강 ...
    showStep(step);
    stepStartTime = now;
  }
}
