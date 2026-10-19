// 아두이노 우노: 신호등 + 인터럽트 버튼
//  - 평소: 초록(5초) -> 노랑(2초) -> 빨강(5초) 반복
//  - D2 버튼을 누르면 인터럽트 발생 -> 모든 불 켜짐
//  - 한 번 더 누르면 다시 신호등 동작
// 빨강: D7, 노랑: D8, 초록: D9 (각각 220옴 저항 - LED - GND)
// 버튼: D2 (D2 - 버튼 - GND)
const int RED_PIN    = 7;
const int YELLOW_PIN = 8;
const int GREEN_PIN  = 9;
const int BUTTON_PIN = 2;   // 인터럽트 0번 핀

const unsigned long GREEN_MS  = 5000;  // 초록불 시간
const unsigned long YELLOW_MS = 2000;  // 노란불 시간
const unsigned long RED_MS    = 5000;  // 빨간불 시간
const unsigned long DEBOUNCE_MS = 200; // 버튼 떨림 무시 시간

volatile bool allOnMode = false;              // 모든 불 켜기 모드인지
volatile bool modeChanged = false;            // 모드가 바뀌었는지 표시
volatile unsigned long lastInterruptTime = 0;

int step = 0;                     // 0: 초록, 1: 노랑, 2: 빨강
unsigned long stepStartTime = 0;  // 현재 신호가 시작된 시각

// 인터럽트 서비스 루틴: 버튼을 누르는 순간 자동으로 실행
void onButtonPress()
{
  unsigned long now = millis();
  if (now - lastInterruptTime > DEBOUNCE_MS)
  {
    allOnMode = !allOnMode;
    if (allOnMode)  // 바로 모든 불 켜기
    {
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(YELLOW_PIN, HIGH);
      digitalWrite(GREEN_PIN, HIGH);
    }
    modeChanged = true;
    lastInterruptTime = now;
  }
}

// 신호 하나만 켜고 나머지는 끄기
void showStep(int s)
{
  digitalWrite(GREEN_PIN,  s == 0 ? HIGH : LOW);
  digitalWrite(YELLOW_PIN, s == 1 ? HIGH : LOW);
  digitalWrite(RED_PIN,    s == 2 ? HIGH : LOW);
}

void setup()
{
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // 안 누르면 HIGH, 누르면 LOW
  Serial.begin(9600);

  // FALLING: HIGH -> LOW 로 바뀌는 순간(누르는 순간) 인터럽트 발생
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onButtonPress, FALLING);

  showStep(step);
  stepStartTime = millis();
  Serial.println("신호등 시작");
}

void loop()
{
  unsigned long now = millis();

  if (modeChanged)
  {
    modeChanged = false;
    if (allOnMode)
    {
      // 인터럽트 직후 loop가 신호를 바꿨을 수도 있으니 한 번 더 모두 켜기
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(YELLOW_PIN, HIGH);
      digitalWrite(GREEN_PIN, HIGH);
      Serial.println("버튼 인터럽트 -> 모든 불 켜짐");
    }
    else
    {
      Serial.println("신호등 다시 시작");
      step = 0;               // 초록불부터 다시
      showStep(step);
      stepStartTime = now;
    }
  }

  if (allOnMode)
  {
    return;  // 모든 불 켜기 모드에서는 신호를 바꾸지 않음
  }

  // delay() 대신 millis()로 시간 확인 -> 버튼에 바로 반응 가능
  unsigned long duration = (step == 0) ? GREEN_MS : (step == 1) ? YELLOW_MS : RED_MS;
  if (now - stepStartTime >= duration)
  {
    step = (step + 1) % 3;    // 초록 -> 노랑 -> 빨강 -> 초록 ...
    showStep(step);
    stepStartTime = now;
  }
}
