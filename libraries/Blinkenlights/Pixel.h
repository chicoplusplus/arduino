#ifndef Blinkenlights_Pixel_h
#define Blinkenlights_Pixel_h

#include <Arduino.h>
#include "Adafruit_WS2801.h"

class Pixel {
  public:
    Pixel(Adafruit_WS2801 *strip, uint16_t grid_index, uint8_t num_leds);
    ~Pixel();

    void set_pixel_color(uint8_t r, uint8_t g, uint8_t b);
    void set_pixel_color(uint32_t c);
    uint32_t get_pixel_color();
    void print();

  private:
    Adafruit_WS2801 *strip;
    uint16_t grid_index; // our true index in the full strand
    uint8_t num_leds;
};

#endif

