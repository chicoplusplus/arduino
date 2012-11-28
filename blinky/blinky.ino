#include <Arduino.h>
#include <SPI.h>
#include <pnew.cpp>
#include "Adafruit_WS2801.h"
#include "Controller.h"
#include "Grid.h"
#include "Rainbow.h"
#include "ColorWipe.h"

// Arduino output pins
int dataPin  = 2; // White wire on Adafruit Pixels
int clockPin = 3; // Green wire on Adafruit Pixels

// Don't forget to connect the blue ground wire to Arduino ground,
// and the red +5V wire to vim or +5V

// Set the first variable to the total number of LEDs.
Adafruit_WS2801 *strip = new Adafruit_WS2801(24, dataPin, clockPin);

// Optional: leave off pin numbers to use hardware SPI
// (pinout is then specific to each board and can't be changed)
//Adafruit_WS2801 strip = Adafruit_WS2801(24);

// Assign strip to controller
Controller *controller = new Controller(strip);

// Instantiate our grid with information about layout
int num_panels_x = 3;
int num_panels_y = 1;
int num_pixels_per_panel_x = 4;
int num_pixels_per_panel_y = 2;
int num_leds_per_pixel = 1;
Grid *grid = new Grid(strip, num_panels_x, num_panels_y, num_pixels_per_panel_x, num_pixels_per_panel_y, num_leds_per_pixel);

void setup() {
  // Setup serial interface for debugging
  Serial.begin(9600);

  // Instantiate rainbow effect and register it
  Rainbow *rainbow_effect = new Rainbow(grid->select(0,0,2,2), 20);
  controller->register_effect(rainbow_effect);
  
  // Instantiate colorwipe effect and register it
  ColorWipe *color_wipe_effect = new ColorWipe(grid->select(4,0,4,2), Effect::color(204,51,51), 100);
  controller->register_effect(color_wipe_effect);

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
    controller->do_something();
  }

  //panel1.colorWipe(panel1.Color(255, 0, 0), 50);
  //panel3.rainbowCycle(20);
}

