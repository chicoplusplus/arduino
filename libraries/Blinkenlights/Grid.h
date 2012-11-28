#ifndef Blinkenlights_Grid_h
#define Blinkenlights_Grid_h

#include <Arduino.h>
#include "Adafruit_WS2801.h"

/*
 * The space we are working with is an array of ceiling panels, each of which
 * contains what can be thought of as a 3 x 6 grid with two LEDs each, for a total
 * of 36 LEDs per panel. They are strung together like so:
 * 
 *   || ingress
 *   ||
 *   \/
 * -------------------
 * |  *  |   * | *   |
 * |  *  | *   |   * |
 * |-----|-----|-----|
 * |  *  |  *  |  *  |
 * |  *  |  *  |  *  |
 * |------------------
 * |  *  |  *  |  *  |
 * |  *  |  *  |  *  |
 * |------------------
 * |  *  |  *  |  *  |
 * |  *  |  *  |  *  |
 * |------------------
 * |  *  |  *  |  *  |
 * |  *  |  *  |  *  |
 * |------------------
 * | *   |   * |  *  |
 * |   * | *   |  *  |
 * |------------------
 *                ||
 *                ||
 *                \/ egress
 *
 * The grid represents the entire space. You can call select using logical grid coordinates
 * and it will return a Selection object with a list of physical pixels.
 */

// Defined elsewhere
class Selection;
class Pixel;

class Grid {
  public:
    Grid(Adafruit_WS2801 *strip, uint16_t num_panels, uint8_t num_leds_per_panel, uint8_t num_leds_per_pixel);
    ~Grid();

    Selection* select(uint16_t x, uint16_t y, uint8_t w, uint8_t h);
    void print();

  private:
    uint16_t num_panels;
    uint32_t num_pixels;
    uint8_t num_leds_per_panel, 
            num_leds_per_pixel;
    Pixel** pixels; // the full grid
};

#endif

