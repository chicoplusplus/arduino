#include "Adafruit_WS2801.h"
#include "Grid.h"
#include "Pixel.h"
#include "Selection.h"

Grid::Grid(Adafruit_WS2801 *strip, uint16_t num_panels, uint8_t num_leds_per_panel, uint8_t num_leds_per_pixel) {
  // Store panel configuration for later
  this->num_panels = num_panels;
  this->num_leds_per_panel = num_leds_per_panel;
  this->num_leds_per_pixel = num_leds_per_pixel;
  this->num_pixels = num_panels * (num_leds_per_panel/num_leds_per_pixel);

  // Instantiate pixels
  this->pixels = (Pixel**) malloc(sizeof(Pixel*) * this->num_pixels);
  int i;
  for (i = 0; i < this->num_pixels; i++) {
    this->pixels[i] = new Pixel(strip, i, num_leds_per_pixel);
  }
}

Grid::~Grid() {
  int i;
  for (i = 0; i < this->num_pixels; i++) {
    delete this->pixels[i];
  }

  free(this->pixels);
}

// Return a two dimensional array of pixels given coordinates in
// the overall grid.
//
// For now, this code assumes the wiring of our initial prototype
// boards, but this calculation will change depending on the final
// wiring. 
//
Selection* Grid::select(uint16_t x, uint16_t y, uint8_t w, uint8_t h) {
  Selection *selection = new Selection(w,h);

  int i, j, xx, yy;
  for (i = 0, xx = x; xx < w; i++, xx++) {
    for (j = 0, yy = y; yy < h; j++, yy++) {
      selection->set(i, j, this->pixels[(xx*2)+yy]);
    }
  }

  return selection;
}

// Print to serial for debugging
void Grid::print() {
  Serial.println("------------------Grid:------------------------");
  Serial.print("num_panels = ");
  Serial.print(num_panels, DEC);
  Serial.print(", num_leds_per_panel = ");
  Serial.print(num_leds_per_panel, DEC);
  Serial.print(", num_leds_per_pixel = ");
  Serial.print(num_leds_per_pixel, DEC);
  Serial.print(", num_pixels = ");
  Serial.println(num_pixels, DEC);

  int i;
  for (i = 0; i < this->num_pixels; i++) {
    this->pixels[i]->print();
  }
}
