#include "Selection.h"
#include "Pixel.h"

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

Pixel* Selection::get(uint8_t x, uint8_t y) {
  if (x >= this->w || y >= this->h) {
    return NULL;
  }

  return this->pixels[(y * this->w) + x];
}

Pixel* Selection::get(uint16_t index) {
  if (index >= this->w * this->h) {
    return NULL;
  }

  return this->pixels[index];
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
