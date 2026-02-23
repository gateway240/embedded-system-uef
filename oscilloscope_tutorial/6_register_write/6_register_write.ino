// Reference https://www.baldengineer.com/six-oscilloscope-measurements-using-arduino.html
void setup() {
  pinMode(1, OUTPUT);
  digitalWrite(1, LOW);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  delay(1000);  //clear delay for auto-restart

  // turn on pin 1
  PORTD = PORTD | B00000010;
  // turn on pin 3
  PORTD = PORTD | B00001000;
}

void loop() {}