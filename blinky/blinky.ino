#include <Arduino.h>
#include <SPI.h>
#include <pnew.cpp>
#include "Adafruit_WS2801.h"
#include "Controller.h"
#include "Grid.h"
#include "Effect.h"

// Arduino output pins
// Don't forget to connect the blue ground wire to Arduino ground,
// and the red +5V wire to vim or +5V
int dataPin  = 2; // White wire on Adafruit Pixels
int clockPin = 3; // Green wire on Adafruit Pixels

// Globals
Controller *controller;

void setup() {
  // Setup serial interface for debugging
  Serial.begin(9600);

  // Information about grid layout
  int num_panels_x = 8;
  int num_panels_y = 1;
  int num_pixels_per_panel_x = 1;
  int num_pixels_per_panel_y = 9;
  int num_leds_per_pixel = 1;
  int num_total_leds = num_panels_x * num_panels_y * num_pixels_per_panel_x * num_pixels_per_panel_y * num_leds_per_pixel;

  // Setup the strip, controller, and grid
  // Optional: leave off pin numbers to use hardware SPI (pinout is then specific to each board and can't be changed)
  Adafruit_WS2801 *strip = new Adafruit_WS2801(num_total_leds, dataPin, clockPin);

  // Instantiate controller
  controller = new Controller(strip);

  // Instantiate grid
  Grid *grid = new Grid(strip, num_panels_x, num_panels_y, num_pixels_per_panel_x, num_pixels_per_panel_y, num_leds_per_pixel);

  // Rainbow
  //Rainbow *rainbow_effect = new Rainbow(grid->select(0,0,3,2), 20);
  //controller->register_effect(rainbow_effect);
  
  // Wipe cycle
  //WipeCycle *horizontal_wipe = new WipeCycle(grid->select(0,0,8,9), 250);
  //controller->register_effect(horizontal_wipe);

  // Color wipe
  //ColorWipe *color_wipe = new ColorWipe(grid->select(0,0,8,9), 250, Effect::color(1,0,0));
  //controller->register_effect(color_wipe);
  
  // Rainbow cycle
  //RainbowCycle *rainbow_cycle_effect = new RainbowCycle(grid->select(0,0,12,12), 20);
  //controller->register_effect(rainbow_cycle_effect);

  // Pulse
  Pulse *pulse_effect = new Pulse(grid->select(0,0,8,9), 20, Effect::color(255,255,0));
  controller->register_effect(pulse_effect);

  // Debug:
  //controller->print();
  //grid->print();
}

// Check for passage of 1ms and tell the controller to do something
unsigned long last_execution = 0;
void loop() {
  // Check if 1ms has passed
  unsigned long current_time = millis();
  if (current_time - last_execution >= 1) {
    last_execution = current_time;
    controller->render();
  }
}

