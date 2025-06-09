//RGB.cpp
#include "RGB.h"

RGB::RGB(int redPin, int greenPin, int bluePin, bool isCommonAnode) {
  _redPin = redPin; _greenPin = greenPin; _bluePin = bluePin;
  _isCommonAnode = isCommonAnode; _brightness = 255;
  _currentRGB[0] = _currentRGB[1] = _currentRGB[2] = 0;
}

bool RGB::begin() {
  if (_redPin < 0 || _greenPin < 0 || _bluePin < 0) { return false; }
  #ifdef ESP32 // Setup for ESP32 boards
    ledcSetup(0, 5000, 8); // Channel 0, 5 kHz freq, 8-bit resolution
    ledcSetup(1, 5000, 8); // Channel 1, 5 kHz freq, 8-bit resolution
    ledcSetup(2, 5000, 8); // Channel 2, 5 kHz freq, 8-bit resolution
    ledcAttachPin(_redPin, 0);  // Attach red pin to Channel 0
    ledcAttachPin(_greenPin, 1); // Attach green pin to Channel 1
    ledcAttachPin(_bluePin, 2);  // Attach blue pin to Channel 2
  #else // Setup for non-ESP32 boards
    pinMode(_redPin, OUTPUT);
    pinMode(_greenPin, OUTPUT);
    pinMode(_bluePin, OUTPUT);
  #endif
  return true;
}

void RGB::setRGB(const uint8_t rgb[3]) {
  showRGB(rgb[0], rgb[1], rgb[2]);
}

void RGB::setRGB(uint8_t red, uint8_t green, uint8_t blue) {
  showRGB(red, green, blue);
}

const uint8_t* RGB::getRGB() const {
  return _currentRGB;
}

void RGB::setHex(uint32_t hexColor) {
  uint8_t red = (hexColor >> 16) & 0xFF;
  uint8_t green = (hexColor >> 8) & 0xFF;
  uint8_t blue = hexColor & 0xFF;
  showRGB(red, green, blue);
}

const uint32_t RGB::getHex() const {
  return ((uint32_t)_currentRGB[0] << 16) | 
         ((uint32_t)_currentRGB[1] << 8)  | 
          (uint32_t)_currentRGB[2];
}

void RGB::setBrightness(uint8_t brightness) {
  _brightness = constrain(brightness, 0, 255);
  showRGB(_currentRGB[0], _currentRGB[1], _currentRGB[2]);
}

const uint8_t RGB::getBrightness() const {
  return _brightness;
}

uint8_t RGB::setColor(uint8_t color) {
  color = map(constrain(color, 0, 255), 0, 255, 0, _brightness);
  if (_isCommonAnode) { color = 255 - color; }
  return color;
}

void RGB::showRGB(uint8_t red, uint8_t green, uint8_t blue) {
  _currentRGB[0] = red;
  _currentRGB[1] = green;
  _currentRGB[2] = blue;
  #ifdef ESP32 // Use ESP32 PWM for RGB values
    ledcWrite(0, setColor(red));   // Write red value to Channel 0
    ledcWrite(1, setColor(green)); // Write green value to Channel 1
    ledcWrite(2, setColor(blue));  // Write blue value to Channel 2
  #else // Use analogWrite for non-ESP32 boards
    analogWrite(_redPin, setColor(red));
    analogWrite(_greenPin, setColor(green));
    analogWrite(_bluePin, setColor(blue));
  #endif
}

void RGB::setHSV(int hue, float sat, float val) {
  hue = constrain(hue, 0, 359);
  sat = constrain(sat, 0.0, 1.0);
  val = constrain(val, 0.0, 1.0);
  const int SECTOR_SIZE = 60;
  int hueSector = hue / SECTOR_SIZE;
  float hueFraction = (hue / (float)SECTOR_SIZE) - hueSector;
  float minVal = val * (1.0f - sat);
  float intVal1 = val * (1.0f - sat * hueFraction);
  float intVal2 = val * (1.0f - sat * (1.0f - hueFraction));
  float red, green, blue;
  switch (hueSector % 6) {
    case 0: red = val, green = intVal2, blue = minVal; break;
    case 1: red = intVal1, green = val, blue = minVal; break;
    case 2: red = minVal, green = val, blue = intVal2; break;
    case 3: red = minVal, green = intVal1, blue = val; break;
    case 4: red = intVal2, green = minVal, blue = val; break;
    case 5: red = val, green = minVal, blue = intVal1; break;
    default: red = green = blue = 0; break;
  }
  showRGB((int)(red * 255), (int)(green * 255), (int)(blue * 255));
}
