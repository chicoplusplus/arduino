#ifndef Blinkenlights_Controller_h
#define Blinkenlights_Controller_h

#include <Arduino.h>
#include <iterator>
#include <vector>
#include "Adafruit_WS2801.h"

/*
 * We start with strands of 12mm Adafruit WS2801 LED Pixels:
 * https://www.adafruit.com/products/322
 * http://learn.adafruit.com/12mm-led-pixels
 *
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
 */

// Defined elsewhere
class Grid;
class Effect;
class Selection;

// Set the interrupt timer, register effects, issue callbacks, and handle redrawing the led array
class Controller {
  public:
    Controller(Adafruit_WS2801 *strip);
    ~Controller();

    void register_effect(Effect *e);
    void deregister_effect(Effect *e);
    void do_something();
    void print();

  private:
    Adafruit_WS2801 *strip;
    std::vector<Effect*> effects;
};

#endif

