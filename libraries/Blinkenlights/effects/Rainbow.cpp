// This file is included from Effect.cpp

#include "Pixel.h"

Rainbow::Rainbow(Selection *selection, uint32_t frequency) : Effect(selection, frequency) {
  this->current_color = 0;
}

bool Rainbow::step() {
  // Do our thing
  int i, num_pixels;
  num_pixels = this->selection->size();
  for (i = 0; i < num_pixels; i++) {
    this->selection->get(i)->set_pixel_color(Effect::wheel((i + this->current_color) % 256));
  }  

  // Update state
  this->current_color++;
  this->current_color = this->current_color % 256;

  // Keep going forever
  return true;
}
