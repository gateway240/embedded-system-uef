#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// SSD1306 128x64 I2C, full buffer
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

#define NAME "Саша"

// Draw a big heart using circles + triangle
void drawBigHeart(int cx, int topY, int r) {
  // Top lobes
  u8g2.drawDisc(cx - r, topY + r, r);
  u8g2.drawDisc(cx + r, topY + r, r);

  // Bottom triangle (overlaps circles for smooth transition)
  u8g2.drawTriangle(
    cx - 2.05 * r, topY + r,   // wider left
    cx + 2.05 * r, topY + r,   // wider right
    cx, topY + 3.4 * r       // deeper bottom
  );
}

// Draw centered text inside heart
void drawCenteredName(const char* name) {
  u8g2.setFont(u8g2_font_cu12_t_cyrillic);
  u8g2.setDrawColor(0); // cut-out effect (black text inside white heart)

  int textWidth = u8g2.getUTF8Width(name);
  int x = (128 - textWidth) / 2;
  int y = 36;  // baseline, visually centered

  u8g2.drawUTF8(x, y, name);
  u8g2.setDrawColor(1); // restore for other drawing
}

void setup() {
  u8g2.begin();
  u8g2.enableUTF8Print(); 

  u8g2.clearBuffer();

  // Draw heart
  drawBigHeart(64, 4, 18);

  // Draw centered Cyrillic name
  drawCenteredName(NAME);

  // Push to display
  u8g2.sendBuffer();
}

void loop() {
  // static display
}
