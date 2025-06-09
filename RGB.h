//RGB.h
#ifndef RGB_H
#define RGB_H

#include <Arduino.h>

class RGB {
  private:
    bool _isCommonAnode;
    int _redPin, _greenPin, _bluePin;
    uint8_t _brightness = 255;
    uint8_t _currentRGB[3];
    uint8_t setColor(uint8_t color);
    inline void showRGB(uint8_t red, uint8_t green, uint8_t blue);

  public:
    RGB(int redPin, int greenPin, int bluePin, bool isCommonAnode);
    bool begin();
    void setRGB(const uint8_t rgb[3]);
    void setRGB(uint8_t red, uint8_t green, uint8_t blue);
    const uint8_t* getRGB() const;
    void setHex(uint32_t hexColor);
    const uint32_t getHex() const;
    void setBrightness(uint8_t brightness);
    const uint8_t getBrightness() const;
    void setHSV(int hue, float sat = 1.0, float val = 1.0);
};

#endif
