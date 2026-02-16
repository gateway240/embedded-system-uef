#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <LIS2DW12Sensor.h>  // from stm32duino LIS2DW12 library

// OLED config
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Create LIS2DW12 instance
// Note: constructor takes TwoWire reference from Wire.h
LIS2DW12Sensor accel(&Wire);
Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Wire.begin();

  // Init OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("OLED init failed");
    while (1);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.println("Init LIS2DW12...");
  display.display();

  // Init accelerometer
  if (accel.begin() != 0) {
    Serial.println("LIS2DW12 init failed");
    display.println("Accel init failed");
    display.display();
    while (1);
  }
  // Enable sensor
  accel.Enable_X();

  // Init Gyro
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
  }

  Serial.println("");
  delay(500);

  Serial.println("time_ms,ax,ay,az,gx,gy,gz");
}

void loop() {
  // Accelerometer - Read raw axes (in mg)
  int32_t axes[3];
  accel.Get_X_Axes(axes);

  float ax = axes[0] * 0.01;
  float ay = axes[1] * 0.01;
  float az = axes[2] * 0.01;

  // Gyroscope - new sensor events with the readings
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // ---- SERIAL LOGGING ----
  Serial.print("Time: ");
  Serial.println(millis());

  Serial.print("LIS2DW12 Acceleration Y: ");
  Serial.print(ay, 3);
  Serial.print(", X: ");
  Serial.print(ax, 3);
  Serial.print(", Z: ");
  Serial.print(az, 3);
  Serial.println(" m/s^2");

  Serial.print("MPU Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("MPU Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("MPU Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");

  // ---- OLED DISPLAY ----
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("LIS2DW12 accel");
  display.print("X: ");
  display.println(ax, 2);
  display.print("Y: ");
  display.println(ay, 2);
  display.print("Z: ");
  display.print(az, 2);
  display.println("  m/s^2");

  display.println("MPU6050 gyro");
  display.print("X: ");
  display.println(g.gyro.x);
  display.print("Y: ");
  display.println(g.gyro.y);
  display.print("Z: ");
  display.print(g.gyro.z);
  display.println(" rad/s");
  display.display();

  delay(500);
}
