#define PWM_PIN 13
void setup() {
  pinMode(PWM_PIN, OUTPUT);
  // put your setup code here, to run once:
}

void loop() {
  digitalWrite(PWM_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(PWM_PIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second

}
