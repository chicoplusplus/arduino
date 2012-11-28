#ifndef Blinkenlights_Effect_h
#define Blinkenlights_Effect_h

#include <Arduino.h>

// Defined elsewhere
class Selection;

class Effect {
  public:
    Effect(Selection *s); // Effect owns selection once constructed and will deallocate it when no longer needed
    ~Effect();

    // Implemented by subclasses 
    virtual void next_step() {} // Called every 1ms
    virtual void print() {}
  
    // Helper functions
    static uint32_t 
      color(byte r, byte g, byte b),
      wheel(byte position);

  protected:
    Selection *selection;
    uint32_t last_execution;
};

#endif

