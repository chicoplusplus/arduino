#include <Arduino.h>
#include <SPI.h>
#include <pnew.cpp>
#include "Adafruit_WS2801.h"
#include "Controller.h"
#include "Grid.h"
#include "Rainbow.h"

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

// Instantiate our grid: number of panels, number of leds per panel, number of leds per "pixel"
Grid *grid = new Grid(strip, 3, 8, 1);

void setup() {
  // Setup serial interface for debugging
  Serial.begin(9600);

  // Instantiate effect on a certain subset and register it
  Rainbow *rainbowEffect = new Rainbow(grid->select(0,0,2,2), 20);
  controller->register_effect(rainbowEffect);

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

