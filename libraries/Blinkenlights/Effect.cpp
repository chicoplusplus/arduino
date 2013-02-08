#include "Effect.h"
#include "Selection.h"
#include "../TrueRandom/TrueRandom.h"

Effect::Effect(Selection *selection, uint32_t frequency) {
  this->selection = selection;
  this->frequency = frequency;
  this->last_execution = 0;
}

Effect::~Effect() {
  delete this->selection;
}

// Called by controller every 1ms (best effort)
// Return false if we want to stop rendering and
// be deregistered.
bool Effect::render() {
  // Check if enough time has passed
  unsigned long current_time = millis();
  if (current_time - this->last_execution < this->frequency) {
    return true;
  }

  // Update state
  this->last_execution = current_time;

  // Call subclass implementation
  return this->step();
}

/* Helper functions */

// Create a 24 bit color value from RGB
uint32_t Effect::color(byte r, byte g, byte b)
{
  uint32_t c = 0;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r
uint32_t Effect::wheel(byte position)
{
  if (position < 85) {
    return Effect::color(position * 3, 255 - position * 3, 0);
  } else if (position < 170) {
    position -= 85;
    return Effect::color(255 - position * 3, 0, position * 3);
  } else {
    position -= 170; 
    return Effect::color(0, position * 3, 255 - position * 3);
  }
}

// Take an RGB color and return HSV (hue saturation brightness)
// h = [0,360], s = [0,1], v = [0,1]
// if s == 0, then h = -1 (undefined)
void Effect::rgb_to_hsv(uint32_t color, float *h, float *s, float *v)
{
  float min_color, max_color, delta, r, g, b;

  // Decompose color value into RGB and then convert to floats between 0 and 1
  r = (float)((color>>16) & 0xff) / 255.0;
  g = (float)((color>>8) & 0xff) / 255.0;
  b = (float)(color & 0xff) / 255.0;

  min_color = min(min(r,g), b);
  max_color = max(max(r,g), b);
  *v = max_color;       // v
  delta = max_color - min_color;
  if( max_color != 0 )
    *s = delta / max_color;   // s
  else {
    // r = g = b = 0    // s = 0, v is undefined
    *s = 0;
    *h = -1;
    return;
  }
  if( r == max_color )
    *h = ( g - b ) / delta;   // between yellow & magenta
  else if( g == max_color )
    *h = 2 + ( b - r ) / delta; // between cyan & yellow
  else
    *h = 4 + ( r - g ) / delta; // between magenta & cyan
  *h *= 60;       // degrees
  if( *h < 0 )
    *h += 360;
}

// Reverse of the above: take HSV and convert to RGB
uint32_t Effect::hsv_to_rgb(float h, float s, float v)
{
  int i;
  float r, g, b, f, p, q, t;
  if( s == 0 ) {
    // achromatic (grey)
    r = g = b = v;
    return Effect::color(floor(r*255.0),floor(g*255.0),floor(b*255.0));
  }
  h /= 60;      // sector 0 to 5
  i = floor( h );
  f = h - i;      // factorial part of h
  p = v * ( 1 - s );
  q = v * ( 1 - s * f );
  t = v * ( 1 - s * ( 1 - f ) );
  switch( i ) {
    case 0:
      r = v;
      g = t;
      b = p;
      break;
    case 1:
      r = q;
      g = v;
      b = p;
      break;
    case 2:
      r = p;
      g = v;
      b = t;
      break;
    case 3:
      r = p;
      g = q;
      b = v;
      break;
    case 4:
      r = t;
      g = p;
      b = v;
      break;
    default:    // case 5:
      r = v;
      g = p;
      b = q;
      break;
  }
  return Effect::color(floor(r*255.0),floor(g*255.0),floor(b*255.0));
}

void Effect::print_color(uint32_t color) {
  byte r = (byte)((color>>16) & 0xff);
  byte g = (byte)((color>>8) & 0xff);
  byte b = (byte)(color & 0xff);

  Serial.println("");
  Serial.print("color = ");
  Serial.print(color, DEC);
  Serial.print(" (");
  Serial.print(r, DEC);
  Serial.print(",");
  Serial.print(g, DEC);
  Serial.print(",");
  Serial.print(b, DEC);
  Serial.println(")");
  Serial.flush();
}

// Include effects here. The arduino build system doesn't allow subdirectories
// but we want to organize our effects into a subdirectory to avoid overwhelming
// the library with them.
#include "effects/ColorWipe.cpp"
#include "effects/Rainbow.cpp"
#include "effects/RainbowCycle.cpp"
#include "effects/WipeCycle.cpp"
#include "effects/Pulse.cpp"
#include "effects/Sparkle.cpp"

