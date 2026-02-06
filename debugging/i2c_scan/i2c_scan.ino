#include <Wire.h>

#define SDA_PIN 4
#define SCL_PIN 5

void setup() {
  Wire.begin(); // Initialize I2C
  Serial.begin(9600); 
  while (!Serial);   // important on Nano Every
}

void loop() {
  Serial.println("Scanning I2C devices...");

  byte error, address;
  int nDevices = 0;

  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if(address < 16) Serial.print("0");
      Serial.println(address, HEX);
      nDevices++;
    }
  }

  if (nDevices == 0) Serial.println("No I2C devices found");

  Serial.println("-------------------------");
  delay(2000);  // Wait 2 seconds before scanning again
}
