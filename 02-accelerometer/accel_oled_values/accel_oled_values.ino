#include <Wire.h>
#include <Adafruit_GFX.h>
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

  delay(500);

  Serial.println("time_ms,ax,ay,az");
}

void loop() {
  // Read raw axes (in mg)
  int32_t axes[3];
  accel.Get_X_Axes(axes);

  float ax = axes[0] * 0.001;
  float ay = axes[1] * 0.001;
  float az = axes[2] * 0.001;

  // ---- SERIAL LOGGING ----
  Serial.print(millis());
  Serial.print(',');
  Serial.print(ax, 3);
  Serial.print(',');
  Serial.print(ay, 3);
  Serial.print(',');
  Serial.println(az, 3);

  // ---- OLED DISPLAY ----
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("LIS2DW12 accel");
  display.print("X: "); display.println(ax, 2);
  display.print("Y: "); display.println(ay, 2);
  display.print("Z: "); display.println(az, 2);
  display.display();

  delay(200);
}
