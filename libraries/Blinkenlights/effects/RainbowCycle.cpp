// This file is included from Effect.cpp

#include "Pixel.h"

RainbowCycle::RainbowCycle(Selection *selection, uint32_t frequency) : Effect(selection, frequency) {
  this->current_color = 0;
}

bool RainbowCycle::step() {
  // Do our thing
  int i, num_pixels;
  num_pixels = this->selection->size();
  for (i = 0; i < num_pixels; i++) {
    // tricky math! we use each pixel as a fraction of the full 256-color wheel (thats the i / num_pixels part)
    // Then add in current_color which makes the colors go around per pixel
    // the % 256 is to make the wheel cycle around
    this->selection->get(i)->set_pixel_color(Effect::wheel( ((i * 256 / num_pixels) + this->current_color) % 256 ));
  }  

  // Update state
  this->current_color++;
  this->current_color = this->current_color % 256;
  
  // Keep going forever
  return true;
}
