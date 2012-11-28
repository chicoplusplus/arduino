// This file is included from Effect.h

/*
 * The color wipe effect changes each pixel in turn
 * to the given color.
 */

class ColorWipe : public Effect {
  public:
    ColorWipe(Selection *s, uint32_t frequency, uint32_t color);

    // Called every 1ms (best effort). Render next step and return
    // false if we're totally done.
    virtual bool step();
    
  private:
    uint32_t color;
    uint16_t current_pixel;
};

