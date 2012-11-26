#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

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
