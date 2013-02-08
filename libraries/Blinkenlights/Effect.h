#ifndef Blinkenlights_Effect_h
#define Blinkenlights_Effect_h

#include <Arduino.h>

/* 
 * Base class for effects. To write your own, inherit from this class
 * and overwrite step(), then include the h file at the bottom of
 * this file and the cpp file at the bottom of Effect.cpp
 */

// Defined elsewhere
class Selection;

class Effect {
  public:
    Effect(Selection *s, uint32_t frequency); // Effect owns selection once constructed and will deallocate it when no longer needed
    ~Effect();

    // Called every 1ms (best effort) by controller. Return false
    // if we want to stop rendering and be deregistered.
    bool render();

    // Implemented by subclasses 
    virtual bool step() {}
    virtual void print() {}
  
    // Helper functions
    static uint32_t 
      color(byte r, byte g, byte b),
      hsv_to_rgb(float h, float s, float v),
      wheel(byte position);
    static void 
      rgb_to_hsv(uint32_t color, float *h, float *s, float *v);

    static void print_color(uint32_t color);

  protected:
    uint32_t frequency; // how often to move to the next step (in ms)
    Selection *selection; // the selection of pixels we are operating on
    uint32_t last_execution; // the last time we successfully finished step()
};

// Include effects here. The arduino build system doesn't allow subdirectories
// but we want to organize our effects into a subdirectory to avoid overwhelming
// the library with them.
#include "effects/ColorWipe.h"
#include "effects/Rainbow.h"
#include "effects/RainbowCycle.h"
#include "effects/WipeCycle.h"
#include "effects/Pulse.h"
#include "effects/Sparkle.h"

#endif

