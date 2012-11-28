#ifndef Blinkenlights_Grid_h
#define Blinkenlights_Grid_h

#include <Arduino.h>
#include "Adafruit_WS2801.h"

/*
 * The space we are working with is an array of ceiling panels, each of which
 * contains what can be thought of as a 3 x 6 grid with two LEDs each, for a total
 * of 36 LEDs per panel.
 * 
 * The grid represents the entire space. You can call select using logical grid coordinates
 * and it will return a Selection object with a list of physical pixels arranged in a 
 * 2D array based on a logical ordering.
 */

// Defined elsewhere
class Selection;
class Pixel;

class Grid {
  public:
    Grid(Adafruit_WS2801 *strip, uint8_t num_panels_x, uint8_t num_panels_y, uint8_t num_pixels_per_panel_x, uint8_t num_pixels_per_panel_y, uint8_t num_leds_per_pixel);
    ~Grid();

    Pixel* get_pixel(uint16_t x, uint16_t y);
    Selection* select(uint16_t x, uint16_t y, uint8_t w, uint8_t h);
    void print();

  private:
    uint8_t num_panels_x,
            num_panels_y,
            num_pixels_per_panel_x, 
            num_pixels_per_panel_y, 
            num_leds_per_pixel;
    Pixel** pixels; // the full grid
};

#endif

