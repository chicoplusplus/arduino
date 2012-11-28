#include "Controller.h"
#include "Effect.h"
#include "Selection.h"
#include "Grid.h"

Controller::Controller(Adafruit_WS2801 *strip) {
  // Initialize strip
  this->strip = strip;
  this->strip->begin();
}

Controller::~Controller() {}

void Controller::render() {
  // Iterate through list of effects
  std::vector<Effect*>::iterator iter;
  for(iter = this->effects.begin(); iter != this->effects.end(); ) {
    // Ask effect to render
    if ( (*iter)->render() ) {
      // Move on to next effect
      iter++;
    }
    else {
      // Effect is complete
      this->effects.erase(iter);
    }
  }

  // Write to strip
  this->strip->show();
}

void Controller::register_effect(Effect *e) {
  this->effects.push_back(e);
}

void Controller::deregister_effect(Effect *e) {
  std::vector<Effect*>::iterator iter;
  for(iter = this->effects.begin(); iter != this->effects.end(); iter++) {
    if (*iter == e) {
      this->effects.erase(iter);
      break;
    }
  }
  delete e;
}

// Print to serial for debugging
void Controller::print() {
  Serial.println("------------------Controller:------------------------");
  Serial.print("num registered_effects = ");
  Serial.println(this->effects.size(), DEC);

  std::vector<Effect*>::iterator iter;
  for(iter = this->effects.begin(); iter != this->effects.end(); iter++) {
    (*iter)->print();
  }
}
