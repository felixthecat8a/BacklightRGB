#include <LiquidCrystal.h>
#include "Backlight.h"
#include <MiniNeoPixels.h>

const int rs = 2, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int red = 9, green = 10, blue = 11;
Backlight backlight(red, green, blue);
const int LCD_COLUMNS = 16, LCD_ROWS = 2;

#include "SG.h"
SeaGreen sg;

#define PIXEL_PIN 3
#define PIXEL_COUNT 2
MiniNeoPixels mini(PIXEL_PIN, PIXEL_COUNT);
const int PIXEL_BRIGHTNESS = 15;

void setup() {
  lcd.begin(LCD_COLUMNS, LCD_ROWS);
  backlight.begin();
  mini.begin(PIXEL_BRIGHTNESS);
  lcdStartupScroll();
}

void loop() {
  lcd.clear(); lcd.home(); lcd.print("Color:");
  backlight.setRGB(sg.red, sg.green, sg.blue); 
  setColor("Sea RGB");
  backlight.setHSV(sg.hue, sg.sat, sg.val);
  setColor("Sea HSV");
  backlight.setPink(); setColor("Pink");
  backlight.setRed(); setColor("Red");
  backlight.setOrange(); setColor("Orange");
  backlight.setYellow(); setColor("Yellow");
  backlight.setLimeGreen(); setColor("Lime");
  backlight.setGreen(); setColor("Green");
  backlight.setSpringGreen(); setColor("Spring");
  backlight.setCyan(); setColor("Cyan");
  backlight.setSkyBlue(); setColor("Sky");
  backlight.setBlue(); setColor("Blue");
  backlight.setViolet(); setColor("Violet");
  backlight.setMagenta(); setColor("Magenta");
  backlight.setWhite(); setColor("White");
  lcdOff(500);
  spinColorWheel();
}

void lcdStartupScroll() {
  lcd.home(); lcd.print("Arduino!");
  lcd.setCursor(0, 1); lcd.print("Backlight RGB");
  delay(1000);
  for (int index = 0; index < LCD_COLUMNS; index++) {
    lcd.scrollDisplayLeft(); delay(100);
  }
  lcd.clear();
}

void setColor(const char* name) {
  const uint8_t* color = backlight.getRGB();
  mini.all(color[0],color[1],color[2]);
  lcd.setCursor(7, 0); lcd.print(name); lcd.print("    ");
  lcd.setCursor(0, 1); lcd.print("RGB:");
  lcd.print(color[0]); lcd.print(",");
  lcd.print(color[1]); lcd.print(",");
  lcd.print(color[2]); lcd.print("   ");
  delay(500); fade();
}

void fade() {
  for (int intensity = 255; intensity > 10; intensity -= 5) {
    backlight.setBrightness(intensity); delay(10);
  }
  for (int intensity = 10; intensity < 255; intensity += 5) {
    backlight.setBrightness(intensity); delay(10);
  }
}

void lcdOff(int delayValue) {
  backlight.setBlack(); lcd.clear(); lcd.noDisplay(); mini.off();
  delay(delayValue); lcd.display();
}

void spinColorWheel() {
  lcd.setCursor(0, 0); lcd.print("Spin Color Wheel");
  for (int index = 0; index <= 254; index++) {
    scaleColorMini(index, 0, 254);
    backlight.scaleColor(index, 0, 254); delay(10);
  }
  lcdOff(1000);
}

void scaleColorMini(int value, int fromValue, int toValue) {
  int minValue = min(fromValue, toValue);
  int maxValue = max(fromValue, toValue);
  value = constrain(value, minValue, maxValue);
  int hue = map(value, minValue, maxValue, 0, 359);
  mini.hsv(hue, 255, 255);
}
