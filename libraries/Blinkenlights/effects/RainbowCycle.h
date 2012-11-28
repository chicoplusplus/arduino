// This file is included from Effect.h

/*
 * This is similar to the Rainbow effect, but the spectrum
 * is evenly distributed throughout the selection.
 *
 */

class RainbowCycle : public Effect {
  public:
    RainbowCycle(Selection *s, uint32_t frequency);

    // Called every 1ms (best effort). Render next step and return
    // false if we're totally done.
    virtual bool step();

  private:
    uint8_t current_color;
};
