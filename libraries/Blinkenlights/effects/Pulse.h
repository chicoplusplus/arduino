// This file is included from Effect.h

/*
 * The pulse effect adjusts the brightness of a given color
 * from 0 to 1, back and forth, forever.
 */

class Pulse : public Effect {
  public:
    Pulse(Selection *s, uint32_t frequency, uint32_t color);

    // Called every 1ms (best effort). Render next step and return
    // false if we're totally done.
    virtual bool step();
    virtual void print();
    
  private:
    float hue, saturation, current_brightness;
    bool reverse;
};

