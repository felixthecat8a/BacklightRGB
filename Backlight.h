#ifndef BACKLIGHT_H
#define BACKLIGHT_H

#include <Arduino.h>
#include "Color.h"
#include "RGB.h"

class Backlight {
  private:
    RGB rgb;

  public:
    Backlight(int r, int g, int b): rgb(r, g, b, true) {}

    bool begin() {
      if (!rgb.begin()) {
        return false;
      } else {
        rgb.setHex(0x0A878F);
        return true;
      }
    }

    void setBrightness(uint8_t b) {
      rgb.setBrightness(b);
    }

    void setRGB(uint8_t red, uint8_t green, uint8_t blue) {
      rgb.setRGB(red, green, blue);
    }

    const uint8_t* getRGB() const {
      return rgb.getRGB();
    }

    void setHex(uint32_t hexColor) {
      rgb.setHex(hexColor);
    }

    void setHSV(int h, float s = 1.0, float v = 1.0) {
      rgb.setHSV(h, s, v);
    }

    void setBlack() { rgb.setRGB(Color::BLACK); }
    void setWhite() { rgb.setRGB(Color::WHITE); }
    void setPink() { rgb.setRGB(Color::HOTPINK); }
    void setRed() { rgb.setRGB(Color::RED); }
    void setOrange() { rgb.setRGB(Color::ORANGE); }
    void setYellow() { rgb.setRGB(Color::YELLOW); }
    void setLimeGreen() { rgb.setRGB(Color::LIMEGREEN); }
    void setGreen() { rgb.setRGB(Color::GREEN); }
    void setSpringGreen() { rgb.setRGB(Color::SPRING); }
    void setCyan() { rgb.setRGB(Color::CYAN); }
    void setSkyBlue() { rgb.setRGB(Color::SKYBLUE); }
    void setBlue() { rgb.setRGB(Color::BLUE); }
    void setViolet() { rgb.setRGB(Color::VIOLET); }
    void setMagenta() { rgb.setRGB(Color::MAGENTA); }

    void scaleColor(int value, int fromValue, int toValue) {
      int minValue = min(fromValue, toValue);
      int maxValue = max(fromValue, toValue);
      value = constrain(value, minValue, maxValue);
      int hue = map(value, minValue, maxValue, 0, 359);
      rgb.setHSV(hue);
    }

    String getHexString() const {
      char buffer[8];
      uint32_t hex = rgb.getHex();
      snprintf(buffer, sizeof(buffer), "#%06lX", hex);
      return String(buffer);
    }
};

#endif
