#include <WS2801_Panel.h>

WS2801_Panel::WS2801_Panel(Adafruit_WS2801 strip, uint16_t start_index, uint16_t end_index) {
  container = strip;
  start = start_index;
  end = end_index;
}

WS2801_Panel::~WS2801_Panel(void) { }

// Cycle through all colors of the rainbow
void WS2801_Panel::rainbow(uint8_t wait) {
  int i, j;

  for (j = 0; j < 256; j++) {
    for (i = start; i <= end; i++) {
      container.setPixelColor(i, Wheel((i + j) % 255));
    }  
    container.show(); // write all the pixels out
    delay(wait);
  }
}

// Slightly different, one that makes the rainbow wheel equally distributed 
// along the chain
void WS2801_Panel::rainbowCycle(uint8_t wait) {
  int i, j;
  int num_pixels = (end-start+1);

  for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 256 colors in the wheel
    for (i=start; i <= end; i++) {
      // tricky math! we use each pixel as a fraction of the full 256-color wheel
      // (thats the i / num_pixels part)
      // Then add in j which makes the colors go around per pixel
      // the % 256 is to make the wheel cycle around
      container.setPixelColor(i, Wheel( ((i * 256 / num_pixels) + j) % 256) );
    }  
    container.show(); // write all the pixels out
    delay(wait);
  }
}


// Fill the dots one after the other with said color
// good for testing purposes
void WS2801_Panel::colorWipe(uint32_t c, uint8_t wait) {
  int i;

  for (i=start; i <= end; i++) {
    container.setPixelColor(i, c);
    container.show();
    delay(wait);
  }
}

/* Helper functions */

// Create a 24 bit color value from R,G,B
uint32_t WS2801_Panel::Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r
uint32_t WS2801_Panel::Wheel(byte position)
{
  if (position < 85) {
    return Color(position * 3, 255 - position * 3, 0);
  } else if (position < 170) {
    position -= 85;
    return Color(255 - position * 3, 0, position * 3);
  } else {
    position -= 170; 
    return Color(0, position * 3, 255 - position * 3);
  }
}
