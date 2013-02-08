// This file is included from Effect.h

/*
 * Pick a random pixel and set it to the given color
 */

class Sparkle : public Effect {
  public:
    Sparkle(Selection *s, uint32_t frequency, uint32_t color, uint8_t density, uint32_t bg = 0);

    // Called every 1ms (best effort). Render next step and return
    // false if we're totally done.
    virtual bool step();
    virtual void print();
    
  private:
    uint8_t density;
    uint32_t color, bg;
};

