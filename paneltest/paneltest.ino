#include <SPI.h>
#include <Adafruit_WS2801.h>
#include <WS2801_Panel.h>

// We start with strands of 12mm Adafruit WS2801 LED Pixels:
// https://www.adafruit.com/products/322
// http://learn.adafruit.com/12mm-led-pixels

// This interface is for control of "panels" within the strand.

// Arduino output pins
int dataPin  = 2; // White wire on Adafruit Pixels
int clockPin = 3; // Green wire on Adafruit Pixels

// Don't forget to connect the blue ground wire to Arduino ground,
// and the red +5V wire to vim or +5V

// Set the first variable to the NUMBER of pixels.
Adafruit_WS2801 strip = Adafruit_WS2801(24, dataPin, clockPin);

// Optional: leave off pin numbers to use hardware SPI
// (pinout is then specific to each board and can't be changed)
//Adafruit_WS2801 strip = Adafruit_WS2801(25);

// Set up panels within the strip
WS2801_Panel panel1 = WS2801_Panel(strip, 0, 7);
WS2801_Panel panel2 = WS2801_Panel(strip, 8, 15);
WS2801_Panel panel3 = WS2801_Panel(strip, 16, 24);


void setup() {
  strip.begin();
  strip.show();
}

void loop() {
  panel1.colorWipe(panel1.Color(255, 0, 0), 50);
  panel2.rainbow(20);
  panel3.rainbowCycle(20);
}

