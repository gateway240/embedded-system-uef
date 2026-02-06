#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LIS2DW12Sensor.h>

// OLED config
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

#define GRAPH_TOP 16
#define GRAPH_HEIGHT 48
#define GRAPH_MID (GRAPH_TOP + GRAPH_HEIGHT / 2)
#define GRAPH_SCALE 10.0   // pixels per g

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
LIS2DW12Sensor accel(&Wire);

uint8_t graphX = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Wire.begin();

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("LIS2DW12 Graph");
  display.display();

  // Accelerometer init
  if (accel.begin() != 0) {
    display.println("Accel FAIL");
    display.display();
    while (1);
  }

  accel.Enable_X();

  Serial.println("time_ms,ax,ay,az");

  delay(1000);
}

void loop() {
  int32_t axes[3];
  accel.Get_X_Axes(axes);

  // Convert mg → g
  float ax = axes[0] * 0.001;
  float ay = axes[1] * 0.001;
  float az = axes[2] * 0.001;

  // ---- SERIAL LOG ----
  Serial.print(millis());
  Serial.print(",");
  Serial.print(ax, 3);
  Serial.print(",");
  Serial.print(ay, 3);
  Serial.print(",");
  Serial.println(az, 3);

  // ---- GRAPH ----
  if (graphX == 0) {
    display.clearDisplay();

    // Labels
    display.setCursor(0, 0);
    display.print("X Y Z (g)");

    // Zero line
    display.drawLine(0, GRAPH_MID, SCREEN_WIDTH, GRAPH_MID, SSD1306_WHITE);
  }

  int16_t yx = GRAPH_MID - ax * GRAPH_SCALE;
  int16_t yy = GRAPH_MID - ay * GRAPH_SCALE;
  int16_t yz = GRAPH_MID - az * GRAPH_SCALE;

  yx = constrain(yx, GRAPH_TOP, GRAPH_TOP + GRAPH_HEIGHT - 1);
  yy = constrain(yy, GRAPH_TOP, GRAPH_TOP + GRAPH_HEIGHT - 1);
  yz = constrain(yz, GRAPH_TOP, GRAPH_TOP + GRAPH_HEIGHT - 1);

  // X axis (solid)
  display.drawPixel(graphX, yx, SSD1306_WHITE);

  // Y axis (dotted)
  if (graphX % 2 == 0)
    display.drawPixel(graphX, yy, SSD1306_WHITE);

  // Z axis (thicker)
  display.drawPixel(graphX, yz, SSD1306_WHITE);
  display.drawPixel(graphX, yz + 1, SSD1306_WHITE);

  display.display();

  graphX++;
  if (graphX >= SCREEN_WIDTH) {
    graphX = 0;
  }

  delay(50);  // ~20 Hz refresh
}
