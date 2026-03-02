#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <LIS2DW12Sensor.h>  // from stm32duino LIS2DW12 library
#include <DFRobot_BMM150.h>

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
DFRobot_BMM150_I2C bmm150(&Wire, I2C_ADDRESS_4);

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

  // Init magnetometer
  while (bmm150.begin()) {
    Serial.println("bmm150 init failed, Please try again!");
    delay(1000);
  }
  Serial.println("bmm150 init success!");
  bmm150.setOperationMode(BMM150_POWERMODE_NORMAL);
  bmm150.setPresetMode(BMM150_PRESETMODE_HIGHACCURACY);
  bmm150.setRate(BMM150_DATA_RATE_10HZ);
  bmm150.setMeasurementXYZ();

  Serial.println("");
  delay(500);

  Serial.println("time_ms,ax,ay,az,gx,gy,gz,mx,my,mz");
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

  sBmm150MagData_t magData = bmm150.getGeomagneticData();
  Serial.print("mag x = "); Serial.print(magData.x); Serial.println(" uT");
  Serial.print("mag y = "); Serial.print(magData.y); Serial.println(" uT");
  Serial.print("mag z = "); Serial.print(magData.z); Serial.println(" uT");
  float compassDegree = bmm150.getCompassDegree();
  Serial.print("the angle between the pointing direction and north (counterclockwise) is:");
  Serial.println(compassDegree);
  Serial.println("--------------------------------");

  // ---- OLED DISPLAY ----
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("   X  |   Y   |   Z  ");

  display.println("LIS2DW12 accel(m/s^2)");
  display.print(ax);
  display.print(" | ");
  display.print(ay);
  display.print(" | ");
  display.println(az);

  display.println("MPU6050 gyro (rad/s)");
  display.print(g.gyro.x);
  display.print(" | ");
  display.print(g.gyro.y);
  display.print(" | ");
  display.println(g.gyro.z);

  display.println("BMM150 mag (uT)");
  display.print(magData.x);
  display.print(" | ");
  display.print(magData.y);
  display.print(" | ");
  display.println(magData.z);

  display.display();

  delay(500);
}
