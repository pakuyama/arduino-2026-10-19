// 아두이노 우노: 가변저항으로 LED 밝기 조절
//  - 아날로그 입력: analogRead()  -> 0 ~ 1023
//  - 아날로그 출력: analogWrite() -> 0 ~ 255 (PWM)
// 가변저항: 바깥 다리 5V / 가운데 다리 A0 / 다른 바깥 다리 GND
// LED: D9 (PWM 핀 ~) - 220옴 - LED(+), LED(-) - GND
const int POT_PIN = A0;   // 가변저항 가운데 다리
const int LED_PIN = 9;    // PWM 핀 (~ 표시: 3, 5, 6, 9, 10, 11)

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int potValue = analogRead(POT_PIN);                // 아날로그 입력 (0 ~ 1023)
  int brightness = map(potValue, 0, 1023, 0, 255);   // 0~1023 -> 0~255 로 변환

  analogWrite(LED_PIN, brightness);                  // 아날로그 출력 (PWM)

  Serial.print("가변저항: ");
  Serial.print(potValue);
  Serial.print("  밝기: ");
  Serial.println(brightness);

  delay(50);
}
