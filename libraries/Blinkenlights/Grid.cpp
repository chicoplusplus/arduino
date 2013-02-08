#include "Adafruit_WS2801.h"
#include "Grid.h"
#include "Pixel.h"
#include "Selection.h"

Grid::Grid(Adafruit_WS2801 *strip, uint8_t num_panels_x, uint8_t num_panels_y, uint8_t num_pixels_per_panel_x, uint8_t num_pixels_per_panel_y, uint8_t num_leds_per_pixel) {
  // Store panel configuration for later
  this->num_panels_x = num_panels_x;
  this->num_panels_y = num_panels_y;
  this->num_pixels_per_panel_x = num_pixels_per_panel_x;
  this->num_pixels_per_panel_y = num_pixels_per_panel_y;
  this->num_leds_per_pixel = num_leds_per_pixel;

  // Allocate space for pixel pointers.
  uint32_t num_pixels_x = num_panels_x * num_pixels_per_panel_x;
  uint32_t num_pixels_y = num_panels_y * num_pixels_per_panel_y;
  uint32_t size_of_pixels = sizeof(Pixel*) * num_pixels_x * num_pixels_y;
  this->pixels = (Pixel**) malloc(size_of_pixels);
  memset(this->pixels, NULL, size_of_pixels);

  // Instantiate pixels. Loop through in logical order, and then
  // calculate the strand index.
  int i, j, k, l, strand_index, current_x, current_y;
  strand_index = current_x = current_y = 0;
  for (i = 0; i < this->num_panels_x; i++) {
    for (j = 0; j < this->num_panels_y; j++) {
      for (k = 0; k < this->num_pixels_per_panel_x; k++) {
        for (l = 0; l < this->num_pixels_per_panel_y; l++) {
          // Figure out where we are in the logical grid.
          current_x = (i * this->num_pixels_per_panel_x) + k;
          current_y = (j * this->num_pixels_per_panel_y) + l;

          // Figure out where we are in the strand.
          strand_index = (current_x * num_pixels_y);
          strand_index += (current_x % 2 == 0) ? current_y : (this->num_pixels_per_panel_y - current_y - 1);

          // Instantiate the pixel
          this->pixels[(num_pixels_x * current_y) + current_x] = new Pixel(strip, strand_index, num_leds_per_pixel);
        }
      }
    }
  }
}

Grid::~Grid() {
  int i, num_pixels;
  num_pixels = this->num_panels_x * this->num_pixels_per_panel_x * this->num_panels_y * this->num_pixels_per_panel_y;
  for (i = 0; i < num_pixels; i++) {
    delete this->pixels[i];
  }

  free(this->pixels);
}

Pixel* Grid::get_pixel(uint16_t x, uint16_t y) {
  uint32_t num_pixels_x = this->num_panels_x * this->num_pixels_per_panel_x;
  uint32_t num_pixels_y = this->num_panels_y * this->num_pixels_per_panel_y;
  if (x >= num_pixels_x || y >= num_pixels_y) {
    return NULL;
  }

  return this->pixels[(y*num_pixels_x)+x];
}

// Return a two dimensional array of pixels given coordinates in
// the overall grid.
Selection* Grid::select(uint16_t x, uint16_t y, uint8_t w, uint8_t h) {
  // Instantiate selection - it will have it's own array of pointers
  Selection *selection = new Selection(w, h);

  // Loop through in logical order and pass off pixels to selection
  // for storage
  int i, j;
  for (i = 0; i < w; i++) {
    for (j = 0; j < h; j++) {
      selection->set(i, j, this->get_pixel(x+i, y+j));
    }
  }

  return selection;
}

// Print to serial for debugging
void Grid::print() {
  Serial.println("------------------Grid:------------------------");
  Serial.print("num_panels_x = ");
  Serial.print(this->num_panels_x, DEC);
  Serial.print(", num_panels_y = ");
  Serial.print(this->num_panels_y, DEC);
  Serial.print(", num_pixels_per_panel_x = ");
  Serial.print(this->num_pixels_per_panel_x, DEC);
  Serial.print(", num_pixels_per_panel_y = ");
  Serial.print(this->num_pixels_per_panel_y, DEC);
  Serial.print(", num_leds_per_pixel = ");
  Serial.println(this->num_leds_per_pixel, DEC);
  Serial.flush();
 
  int i, num_pixels;
  num_pixels = this->num_panels_x * this->num_pixels_per_panel_x * this->num_panels_y * this->num_pixels_per_panel_y;
  for (i = 0; i < num_pixels; i++) {
    this->pixels[i]->print();
  }
}
