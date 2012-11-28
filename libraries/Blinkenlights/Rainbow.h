#ifndef Blinkenlights_Rainbow_h
#define Blinkenlights_Rainbow_h

#include <Arduino.h>
#include "Effect.h"

/*
 * The rainbow effect updates all pixels in the selection
 * through a continuously rotating set of colors, spanning
 * the entire rainbow.
 *
 */

// Defined elsewhere
class Selection;

class Rainbow : public Effect {
  public:
    Rainbow(Selection *s, uint32_t wait);

    virtual void next_step(); // called every 1ms
    virtual void print();

  private:
    uint8_t current_color;
    uint32_t wait;
};

#endif

