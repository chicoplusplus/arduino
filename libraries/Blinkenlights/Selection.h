#ifndef Blinkenlights_Selection_h
#define Blinkenlights_Selection_h

#include <Arduino.h>

// Defined elsewhere
class Pixel;

// Selection is essentially a two dimensional array of Pixel*, a subset
// of the pixels contained in the grid. We don't own them, we just have
// pointers to them.
class Selection {
  public:
    Selection(uint8_t w, uint8_t h);
    ~Selection();
    
    uint8_t width() { return w; }
    uint8_t height() { return h; }
    uint16_t size() { return w*h; }

    Pixel *get(uint16_t index);
    Pixel *get(uint8_t x, uint8_t y);
    Selection* get_column(uint8_t x);
    Selection* get_row(uint8_t y);

    void set(uint8_t x, uint8_t y, Pixel *pixel);

    void set_pixel_color(uint8_t r, uint8_t g, uint8_t b);
    void set_pixel_color(uint32_t c);

    void print();

  private:
    Pixel **pixels;
    uint8_t w, h;
};

#endif

