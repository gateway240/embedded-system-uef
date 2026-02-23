#define PWM_PIN A3
void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(PWM_PIN, 128); // 50% duty cycle
}
