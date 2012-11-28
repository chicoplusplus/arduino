// This file is included from Effect.h

/*
 * The color wipe effect changes each pixel in turn
 * to the given color.
 */

class ColorWipe : public Effect {
  public:
    ColorWipe(Selection *s, uint32_t color, uint32_t wait);

    virtual void next_step(); // called every 1ms
    virtual void print();

  private:
    uint32_t color, 
             wait;
    uint16_t current_pixel;
};

