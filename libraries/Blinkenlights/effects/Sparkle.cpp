// This file is included from Effect.cpp

#include "Pixel.h"
#include <TrueRandom.h>

Sparkle::Sparkle(Selection *selection, uint32_t frequency, uint32_t color, uint8_t density, uint32_t bg) : Effect(selection, frequency) {
  this->color = color;
  this->bg = bg;
  this->density = density;
}

bool Sparkle::step() {
  // Set all pixels to the background color
  this->selection->set_pixel_color(0,0,0);

  // Select some random pixels and set them to the given color
  int i, pixel;
  uint32_t num_pixels = this->selection->size();
  for( i = 0; i < this->density; i++ )  {
    pixel = TrueRandom.random(1, num_pixels);
    this->selection->get(pixel)->set_pixel_color(this->color);
  }

  // Keep going forever
  return true;
}
