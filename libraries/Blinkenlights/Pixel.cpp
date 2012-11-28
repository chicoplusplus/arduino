#include "Pixel.h"
#include "Adafruit_WS2801.h"

Pixel::Pixel(Adafruit_WS2801 *strip, uint16_t grid_index, uint8_t num_leds) {
  this->strip = strip;
  this->grid_index = grid_index;
  this->num_leds = num_leds;
}

Pixel::~Pixel() {}

void Pixel::set_pixel_color(uint8_t r, uint8_t g, uint8_t b) {
  int i;
  for (i = this->grid_index; i < this->grid_index + this->num_leds; i++) {
    this->strip->setPixelColor(i, r, g, b);
  }
}

void Pixel::set_pixel_color(uint32_t c) {
  int i;
  for (i = this->grid_index; i < this->grid_index + this->num_leds; i++) {
    this->strip->setPixelColor(i, c);
  }
}

uint32_t Pixel::get_pixel_color() {
  return this->strip->getPixelColor(this->grid_index);
}

// Print to serial for debugging
void Pixel::print() {
  Serial.print("grid index = ");
  Serial.print(grid_index, DEC);
  Serial.print(", num_leds = ");
  Serial.println(num_leds, DEC);
}
