#include "Effect.h"
#include "Selection.h"

Effect::Effect(Selection *selection) {
  this->selection = selection;
  this->last_execution = 0;
}

Effect::~Effect() {
  delete this->selection;
}

/* Helper functions */

// Create a 24 bit color value from R,G,B
uint32_t Effect::color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r
uint32_t Effect::wheel(byte position)
{
  if (position < 85) {
    return Effect::color(position * 3, 255 - position * 3, 0);
  } else if (position < 170) {
    position -= 85;
    return Effect::color(255 - position * 3, 0, position * 3);
  } else {
    position -= 170; 
    return Effect::color(0, position * 3, 255 - position * 3);
  }
}
