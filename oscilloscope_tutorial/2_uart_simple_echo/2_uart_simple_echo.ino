// Reference: https://www.baldengineer.com/six-oscilloscope-measurements-using-arduino.html
void setup() {
  Serial.begin(9600);
  while (!Serial);
}

void loop() {
  if (Serial.available())
    Serial.write(Serial.read());
}