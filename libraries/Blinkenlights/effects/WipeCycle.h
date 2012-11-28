// This file is included from Effect.h

/*
 * The wipe cycle effect operates on entire rows or columns at a time,
 * eventually filling the area with an initial color. It then changes
 * color and goes back in the opposite direction, ad infinitum.
 */

class WipeCycle : public Effect {
  public:
    // horizontal_wipe = operate on columns from left to right and back, otherwise on rows from top to bottom and back
    WipeCycle(Selection *s, uint32_t wait, bool horizontal_wipe=true);

    virtual void next_step(); // called every 1ms

  private:
    uint32_t wait;
    uint16_t current_column; // or row if horizontal_wipe == false
    uint8_t current_color;
    bool horizontal_wipe;
    bool reverse;
};

