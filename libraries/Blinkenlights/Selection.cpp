#include "Selection.h"
#include "Pixel.h"
#include "Effect.h"

Selection::Selection(uint8_t w, uint8_t h) {
  this->pixels = (Pixel**) malloc(sizeof(Pixel*) * w * h);
  this->w = w;
  this->h = h;
}

Selection::~Selection() {
  // pixels is a dynamically allocated array of pointers
  // we want to delete the pointers but not what they point to
  // (the pixels stored in the grid)
  free(this->pixels);
}

// Set the pixel (in coordinate system of the selection)
void Selection::set(uint8_t x, uint8_t y, Pixel *pixel) {
  if (x >= this->w || y >= this->h) {
    return;
  }

  this->pixels[(y * this->w) + x] = pixel;
}

// Get a pixel by coordinate
Pixel* Selection::get(uint8_t x, uint8_t y) {
  if (x >= this->w || y >= this->h) {
    return NULL;
  }

  return this->pixels[(y * this->w) + x];
}

// Get an individual pixel by index. Useful for iterating over the entire list.
Pixel* Selection::get(uint16_t index) {
  if (index >= this->w * this->h) {
    return NULL;
  }

  return this->pixels[index];
}

// Return a new selection containing just one row. Note that you
// are expected to delete return value when you're done with it.
Selection* Selection::get_row(uint8_t y) {
  Selection *row = new Selection(this->w, 1);
  
  int i;
  for (i = 0; i < this->w; i++) {
    row->set(i, 0, this->get(i, y));
  }

  return row;
}

// Return a new selection containing just one column. Note that you
// are expected to delete return value when you're done with it.
Selection* Selection::get_column(uint8_t x) {
  Selection *col = new Selection(1, this->h);
  
  int i;
  for (i = 0; i < this->h; i++) {
    col->set(0, i, this->get(x, i));
  }

  return col;
}

void Selection::set_pixel_color(uint8_t r, uint8_t g, uint8_t b) {
  this->set_pixel_color(Effect::color(r,g,b));
}

void Selection::set_pixel_color(uint32_t c) {
  int i, num_pixels;
  num_pixels = this->size();
  for (i = 0; i < num_pixels; i++) {
    this->get(i)->set_pixel_color(c);
  } 
}


// Print to serial for debugging
void Selection::print() {
  Serial.println("----------------Selection:-----------------------------");

  int i, num_pixels;
  num_pixels = this->w * this->h;

  for (i = 0; i < num_pixels; i++) {
    this->pixels[i]->print();
  }
}
