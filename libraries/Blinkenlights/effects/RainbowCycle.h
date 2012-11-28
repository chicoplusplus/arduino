// This file is included from Effect.h

/*
 * This is similar to the Rainbow effect, but the spectrum
 * is evenly distributed throughout the selection.
 *
 */

class RainbowCycle : public Effect {
  public:
    RainbowCycle(Selection *s, uint32_t wait);

    virtual void next_step(); // called every 1ms
    virtual void print();

  private:
    uint8_t current_color;
    uint32_t wait;
};
