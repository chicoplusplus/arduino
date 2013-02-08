// This file is included from Effect.cpp

#include "Pixel.h"

Pulse::Pulse(Selection *selection, uint32_t frequency, uint32_t color) : Effect(selection, frequency) {
  this->hue = this->saturation = this->current_brightness = 0;
  Effect::rgb_to_hsv(color, &this->hue, &this->saturation, &this->current_brightness);
  this->reverse = false;
}

bool Pulse::step() {
  // Update state
  if (this->reverse) {
    this->current_brightness -= 0.01;
    if (this->current_brightness < 0.0) {
      this->current_brightness = 0.0;
      this->reverse = false;
    }
  } else {
    this->current_brightness += 0.01;
    if (this->current_brightness > 1.0) {
      this->current_brightness = 1.0;
      this->reverse = true;
    }
  }

  // Calculate new color
  uint32_t new_color = Effect::hsv_to_rgb(this->hue, this->saturation, this->current_brightness);

  // Set pixels
  this->selection->set_pixel_color(new_color);

  // Keep going forever
  return true;
}

// Print to serial for debugging
void Pulse::print() {
  Serial.println("------------------Pulse:------------------------");
  Serial.print("hue = ");
  Serial.print(this->hue, DEC);
  Serial.print(", saturation = ");
  Serial.print(this->saturation, DEC);
  Serial.print(", brightness = ");
  Serial.print(this->current_brightness, DEC);
  Serial.flush();
  print_color(Effect::hsv_to_rgb(this->hue, this->saturation, this->current_brightness));
}
