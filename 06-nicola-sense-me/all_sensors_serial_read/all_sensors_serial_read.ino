// Derived from https://docs.arduino.cc/tutorials/nicla-sense-me/cheat-sheet/#standalone-mode

#include "Arduino_BHY2.h"
SensorXYZ accelerometer(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);
Sensor temperature(SENSOR_ID_TEMP);
Sensor gas(SENSOR_ID_GAS);
Sensor pressure(SENSOR_ID_BARO);
SensorQuaternion rotation(SENSOR_ID_RV);
SensorActivity activity(SENSOR_ID_AR);
SensorBSEC bsec(SENSOR_ID_BSEC);

void setup() {
  Serial.begin(115200);
  BHY2.begin();

  accelerometer.begin();
  gyro.begin();
  temperature.begin();
  gas.begin();
  pressure.begin();
  rotation.begin();
  activity.begin();
  bsec.begin();
}

void loop() {
  static auto lastCheck = millis();

  // Update function should be continuously polled
  BHY2.update();

  // Check sensor values every second
  if (millis() - lastCheck >= 1000) {
    lastCheck = millis();
    Serial.println(String("=== Time (ms): ") + millis());
    Serial.println(String("acceleration: ") + accelerometer.toString());
    Serial.println(String("gyroscope: ") + gyro.toString());
    Serial.println(String("temperature: ") + String(int(temperature.value())));
    Serial.println(String("gas: ") + String(gas.value()));
    Serial.println(String("pressure: ") + pressure.toString());
    Serial.println(String("rotation: ") + rotation.toString());
    Serial.println(String("Activity info: ") + activity.toString());
    Serial.println(String("BSEC info: ") + bsec.toString());
  }
}
