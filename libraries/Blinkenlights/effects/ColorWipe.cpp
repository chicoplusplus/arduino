// This file is included from Effect.cpp

#include "Pixel.h"

ColorWipe::ColorWipe(Selection *selection, uint32_t frequency, uint32_t color) : Effect(selection, frequency) {
  this->color = color;
  this->current_pixel = 0;
}

bool ColorWipe::step() {
  // Stop animation once we're out of bounds
  if (current_pixel >= this->selection->size()) {
    return false;
  }

  // Set color of next pixel in the sequence
  this->selection->get(this->current_pixel)->set_pixel_color(this->color);

  // Update state
  this->current_pixel++;

  // Keep going for now
  return true;
}

