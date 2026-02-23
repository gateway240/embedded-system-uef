// Reference https://www.baldengineer.com/six-oscilloscope-measurements-using-arduino.html
#define TEST_PIN_1 1
#define TEST_PIN_2 3
void setup() {
  pinMode(TEST_PIN_1, OUTPUT);
  digitalWrite(TEST_PIN_1, LOW);
  pinMode(TEST_PIN_2, OUTPUT);
  digitalWrite(TEST_PIN_2, LOW);

  delay(1000);  //clear delay for auto-restart

  // turn on pin 1
  digitalWrite(TEST_PIN_1, HIGH);
  // turn on pin 3
  digitalWrite(TEST_PIN_2, HIGH);
}

void loop() {}