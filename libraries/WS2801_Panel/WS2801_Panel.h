#ifndef WS2801_Panel_h
#define WS2801_Panel_h

#include <Arduino.h>
#include "Adafruit_WS2801.h"

class WS2801_Panel {
  public:
    WS2801_Panel(Adafruit_WS2801 strip, uint16_t start_index, uint16_t end_index);
    ~WS2801_Panel();

  void 
    rainbow(uint8_t wait),
    rainbowCycle(uint8_t wait),
    colorWipe(uint32_t c, uint8_t wait);

  uint32_t 
    Color(byte r, byte g, byte b),
    Wheel(byte WheelPos);

  private:
    Adafruit_WS2801 container;
    uint16_t start, end;
};

#endif

