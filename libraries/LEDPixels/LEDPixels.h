/*
  LEDPixels.h - A Library for use with LED Pixels using the LPD6803 Controller chip
  Copyright (c) 2010 Ben Moyes http:www.bliptronics.com  All right reserved.
  Portions of this library based on the TimerOne library by Michael Polli and Jesse Tane

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef LEDPixels_h
#define LEDPixels_h

#define RESOLUTION 65536    // Timer1 is 16 bit

#include "WProgram.h"
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>


class LEDPixels
{
  private:
    static LEDPixels* _LEDPixels;   
  public:
    LEDPixels();
    void doOutput();
    void setRange(unsigned int startLED, unsigned int endLED, unsigned int color );
    void setLEDFast(unsigned int LED, byte rr, byte gg, byte bb);
    void setLEDFast(unsigned int LED, unsigned int color);
    unsigned int Translate(byte x, byte y);
    void box(byte x0, byte y0, byte x1, byte y1, unsigned int color);
    void swap(int * a, int * b);
    void line(int x0,  int y0, int x1, int y1, unsigned int color);

    unsigned int color(unsigned char r, unsigned char g, unsigned char b);
    void show();
    
    unsigned int pwmPeriod;
    unsigned char clockSelectBits;

    unsigned int gridHeight;
    unsigned int gridWidth;
    void setPixel(int x, int y, int color);

    // methods
    void initialize(long microseconds, int * DisplayAddress,unsigned int LEDCount, char clkPin, char dataPin );
    void start();
    void stop();
    void restart();
    void pwm(char pin, int duty, long microseconds=-1);
    void disablePwm(char pin);
    void attachInterrupt(void (*isr)(), long microseconds=-1);
    void detachInterrupt();
    void setPeriod(long microseconds);


};

#endif

