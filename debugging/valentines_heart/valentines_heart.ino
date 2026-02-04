#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

#define NAME "Alex"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void drawBigHeart(int cx, int topY, int size) {
  int r = size;

  // Top lobes
  display.fillCircle(cx - r, topY + r, r, SSD1306_WHITE);
  display.fillCircle(cx + r, topY + r, r, SSD1306_WHITE);

  // Bottom point
  display.fillTriangle(
    cx - 2.05 * r, topY + r,   // wider left
    cx + 2.05 * r, topY + r,   // wider right
    cx, topY + 3.4 * r,       // deeper bottom
    SSD1306_WHITE
  );
}

void drawCenteredName(const char* name) {
  display.setTextSize(2);

  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(name, 0, 0, &x1, &y1, &w, &h);

  int x = (SCREEN_WIDTH - w) / 2;
  int y = 26;  // visually centered inside heart

  display.setTextColor(SSD1306_BLACK); // cut-out effect
  display.setCursor(x, y);
  display.print(name);
}

void setup() {
  delay(500);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for (;;);
  }

  display.clearDisplay();


  // BIG heart centered
  int cx = SCREEN_WIDTH / 2;
  drawBigHeart(cx, 4, 18);
  drawCenteredName(NAME);

  display.display();
}

void loop() {
}
