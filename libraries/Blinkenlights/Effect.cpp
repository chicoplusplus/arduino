#include "Effect.h"
#include "Selection.h"

Effect::Effect(Selection *selection, uint32_t frequency) {
  this->selection = selection;
  this->frequency = frequency;
  this->last_execution = 0;
}

Effect::~Effect() {
  delete this->selection;
}

// Called by controller every 1ms (best effort)
// Return false if we want to stop rendering and
// be deregistered.
bool Effect::render() {
  // Check if enough time has passed
  unsigned long current_time = millis();
  if (current_time - this->last_execution < this->frequency) {
    return true;
  }

  // Update state
  this->last_execution = current_time;

  // Call subclass implementation
  return this->step();
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

// Include effects here. The arduino build system doesn't allow subdirectories
// but we want to organize our effects into a subdirectory to avoid overwhelming
// the library with them.
#include "effects/ColorWipe.cpp"
#include "effects/Rainbow.cpp"
#include "effects/RainbowCycle.cpp"
#include "effects/WipeCycle.cpp"

