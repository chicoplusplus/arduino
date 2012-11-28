// This file is included from Effect.h

/*
 * The rainbow effect updates all pixels in the selection
 * through a continuously rotating set of colors, spanning
 * the entire rainbow.
 *
 */

class Rainbow : public Effect {
  public:
    Rainbow(Selection *s, uint32_t frequency);

    // Called every 1ms (best effort). Render next step and return
    // false if we're totally done.
    virtual bool step();

  private:
    uint8_t current_color;
};
