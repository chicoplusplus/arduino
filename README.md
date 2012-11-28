Chico++ Arduino Projects
=======


Blinkenlights
-------------

We are working with strands of [Adafruit WS2801 LED pixels](https://www.adafruit.com/products/322), configured in a grid installed
on ceiling tiles. For more information on basic wiring and led function, see their [tutorial](http://learn.adafruit.com/12mm-led-pixels/).

We're using the [Arduino Uno](http://www.arduino.cc/en/Main/arduinoBoardUno) to drive the array.

### Requirements

- Start with a fresh installation of the Arduino distribution. There's no need to install libraries in the main Arduino java library location. Instead,
  clone this repo and go into the IDE and set your "Sketchbook location" to it. It will load the libraries subdirectory automatically.
- You'll need to install [Andy Brown's port of the C++ std library](http://andybrown.me.uk/wk/2011/01/15/the-standard-template-library-stl-for-avr-with-c-streams/).

