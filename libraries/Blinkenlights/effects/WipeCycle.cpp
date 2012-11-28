// This file is included from Effect.cpp

#include "Pixel.h"

WipeCycle::WipeCycle(Selection *selection, uint32_t frequency, bool horizontal_wipe) : Effect(selection, frequency) {
  this->horizontal_wipe = horizontal_wipe;
  this->current_column = 0;
  this->current_color = 0;
  this->reverse = false;
}

bool WipeCycle::step() {
  // Do our thing
  int i, num_pixels;
  uint32_t wheel_color;
  Selection *line;
  bool reversed = false;

  // Check orientation of effect
  if (this->horizontal_wipe) {
    // Check for reversal conditions
    if (!this->reverse && this->current_column >= this->selection->width() - 1) {
      // Switch to right to left
      this->current_column = this->selection->width() - 1;
      this->reverse = true;
      reversed = true;
    } 
    else if (this->reverse && this->current_column <= 0) {
      // Switch back to left to right
      this->current_column = 0;
      this->reverse = false;
      reversed = true;
    }

    // Get the column
    line = this->selection->get_column(this->current_column);
  }
  else {
    // Check for reversal conditions
    if (!this->reverse && this->current_column >= this->selection->height() - 1) {
      // Switch to bottom to top
      this->current_column = this->selection->height() - 1;
      this->reverse = true;
      reversed = true;
    } 
    else if (this->reverse && this->current_column <= 0) {
      // Switch back to top to bottom
      this->current_column = 0;
      this->reverse = false;
      reversed = true;
    }

    // Get the row
    line = this->selection->get_row(this->current_column);
  }

  // Change color if we reversed
  if (reversed) {
    this->current_color += 20;
    this->current_color = this->current_color % 256;
  }

  // Update color of row/column
  wheel_color = Effect::wheel(this->current_color);
  num_pixels = line->size();
  for (i = 0; i < num_pixels; i++) {
    line->get(i)->set_pixel_color(wheel_color);
  }  

  // Clean up
  delete line;

  // Update state
  this->current_column = this->reverse ? this->current_column - 1 : this->current_column + 1;

  // Go on forever
  return true;
}
