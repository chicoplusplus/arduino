#ifndef Blinkenlights_Rainbow_h
#define Blinkenlights_Rainbow_h

#include <Arduino.h>
#include "Effect.h"

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

