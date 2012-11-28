#ifndef Blinkenlights_ColorWipe_h
#define Blinkenlights_ColorWipe_h

#include <Arduino.h>
#include "Effect.h"

/*
 * The color wipe effect changes each pixel in turn
 * to the given color.
 */

// Defined elsewhere
class Selection;

class ColorWipe : public Effect {
  public:
    ColorWipe(Selection *s, uint32_t color, uint32_t wait);

    virtual void next_step(); // called every 1ms
    virtual void print();

  private:
    uint32_t color, 
             wait;
    uint16_t current_pixel;
};

#endif

