// This file is included from Effect.cpp

#include "Pixel.h"

ColorWipe::ColorWipe(Selection *selection, uint32_t color, uint32_t wait) : Effect(selection) {
  this->color = color;
  this->wait = wait;
  this->current_pixel = 0;
}

void ColorWipe::next_step() {
  // Check if enough time has passed
  unsigned long current_time = millis();
  if (current_time - this->last_execution < this->wait) {
    return;
  }

  // Make sure we're still in bounds
  if (current_pixel >= this->selection->width() * this->selection->height()) {
    return;
  }

  // Set color of next pixel in the sequence
  this->selection->get(this->current_pixel)->set_pixel_color(this->color);

  // Update state
  this->current_pixel++;
  this->last_execution = current_time;
}

void ColorWipe::print() {
  Serial.println("----------------ColorWipe effect:-----------------------------");
  Serial.print("color = ");
  Serial.print(color, DEC);
  Serial.print(", wait = ");
  Serial.print(wait, DEC);
  Serial.print(", last_execution = ");
  Serial.println(last_execution, DEC);
  this->selection->print();
}
