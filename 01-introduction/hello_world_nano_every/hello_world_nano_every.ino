void setup() {
  Serial.begin(9600);
  while (!Serial);   // important on Nano Every
}

void loop() {
  Serial.println("Hello World!");
  delay(1000);
}
