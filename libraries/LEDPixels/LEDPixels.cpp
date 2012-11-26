/*
  LEDPixels.cpp - A Library for use with LED Pixels using the LPD6803 Controller chip
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

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "WProgram.h"
#include "LEDPixels.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/

// User config.
int clockPin = 12;  //GREEN wire
int dataPin  = 11;   //YELLOW wire
int NoOfLEDs = 25;  //Total number of LEDs in your string.


// Globals used by interrupt code.
char  SendMode=0;   // Used in interrupt 0=start,1=header,2=data,3=data done
char  BitCount=0;   // Used in interrupt
char  LedIndex=0;   // Used in interrupt - Which LED we are sending.
char  BlankCounter=0;  //Used in interrupt.
unsigned int BitMask;   //Used in interrupt.

//Display[] array holds the 15 bit RGB values for each LED.
//You'll need one for each LED, we're using 25 LEDs here.
//Note you've only got limited memory, so you can only control 
//Several hundred LEDs on a normal arduino. Double that on a Duemilanove.
int * Display;

/******************************************************************************
 * Constructors
 ******************************************************************************/
LEDPixels LP1;              //Preinstatiate

ISR(TIMER1_OVF_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
  LP1.doOutput();
}


LEDPixels::LEDPixels()
{
    //Set the pins to use here
}


void LEDPixels::doOutput()
{
 switch(SendMode)
  {
    
    case 3:                        //Done..just send clocks with zero data
      digitalWrite(dataPin, 0);    //You'll need 255 clocks for a LED to diplsay 1 color pwm.
      digitalWrite(clockPin, HIGH);
      digitalWrite(clockPin, LOW);
      break;
    case 2:               //Sending Data
      if (BitCount==0)    //First bit is always 1 followed by 15 bits of LED color.
        {  digitalWrite(dataPin, 1);
            BitMask=0x8000;//Init bit mask
        }
      else if(BitMask & Display[LedIndex])  //If not the first bit then output the next bits (Starting with MSB bit 15 down.)
        digitalWrite(dataPin, 1);
      else
        digitalWrite(dataPin, 0);
      
      BitMask>>=1;
      BitCount++;
      
      if(BitCount == 16)    //Last bit?
      {
        LedIndex++;        //Move to next LED
        if (LedIndex < NoOfLEDs) //Still more leds to go or are we done?
        {
          BitCount=0;      //Start from the fist bit of the next LED             
        }
        else
          SendMode=3;  //No more LEDs to go, we are done!
      }
      // Clock out data.
      digitalWrite(clockPin, HIGH);
      digitalWrite(clockPin, LOW);
      break;      
    case 1:            //Header
        if (BitCount < 32)              
        {
        digitalWrite(dataPin, 0);
        BitCount++;
        if(BitCount==32) 
          {
            SendMode++;      //If this was the last bit of header then move on to data.
            LedIndex=0;
            BitCount=0;
          }
        }
      digitalWrite(clockPin, HIGH);
      digitalWrite(clockPin, LOW);
      
      break;
    case 0:            //Start
      if(!BlankCounter)    //AS SOON AS CURRENT pwm IS DONE. BlankCounter 
      {
        BitCount=0;
        LedIndex=0;
        SendMode=1; 
      }  
      digitalWrite(clockPin, HIGH);
      digitalWrite(clockPin, LOW);
      
      break;   
  }
  //Keep track of where the LEDs are at in their pwm cycle. 
  BlankCounter++;
}


//Translate x and y to a LED index number in an array.
//Assume LEDS are layed out in a zig zag manner eg for a 3x3:
//0 5 6
//1 4 7
//2 3 8
unsigned int LEDPixels::Translate(byte x, byte y)
{
	if(x%2)
	{
		return(((x+1) * gridHeight)- 1 - y);
	}
	else
	{
		return((x * gridHeight) + y);
	}
}

void LEDPixels::setPixel(int x, int y, int color)
{
    Display[Translate(y,x)]=color;
}
// Draw a line in defined color between two points
// Using Bresenham's line algorithm, optimized for no floating point.
void LEDPixels::line(int x0,  int y0, int x1, int y1, unsigned int color)
{
     boolean steep;
     steep= abs(y1 - y0) > abs(x1 - x0);
     if (steep)
    {
         swap(&x0, &y0);
         swap(&x1, &y1);
    }
     if (x0 > x1)
    {
         swap(&x0, &x1);
         swap(&y0, &y1);
    }
     int deltax = x1 - x0;
     int deltay = abs(y1 - y0);
     int error = 0;
     int ystep;
     int y = y0;
     int x;
     if (y0 < y1) 
       ystep = 1; 
     else 
       ystep = -1;
     for (x=x0; x<=x1; x++) // from x0 to x1
       {
         if (steep)
          Display[Translate(y,x)]=color;    //Fast way of settings LEDs in grid.
         else 
           Display[Translate(x,y)]=color;   //Fast way of settings LEDs in grid.
         error = error + deltay;
         if (2 * error >= deltax)
           {
           y = y + ystep;
           error = error - deltax;
           }
       }
}

//Swap the values of two variables, for use when drawing lines.
void LEDPixels::swap(int * a, int * b)
{
  int temp;
  temp=*b;
  *b=*a;
  *a=temp;
}


void LEDPixels::box(byte x0, byte y0, byte x1, byte y1, unsigned int color)
{
  line(x0,y0,x1,y0,color);
  line(x1,y0,x1,y1,color);
  line(x1,y1,x0,y1,color);
  line(x0,y1,x0,y0,color);  

}



void LEDPixels::setRange(unsigned int startLED, unsigned int endLED, unsigned int color )
{
  // set a linear range of LEDs. The color value must be created with the Color function (15 bit rgb)
  while(startLED <= endLED)
    Display[startLED++]=color;
}
// Set a LED, give it r,g,b
void LEDPixels::setLEDFast(unsigned int LED, byte rr, byte gg, byte bb)
{
  if(LED < NoOfLEDs)
    Display[LED] = color(bb,rr,gg);

}

// set an LED but just pass it a 15 bit color value
void LEDPixels::setLEDFast(unsigned int LED, unsigned int color)
{
  if(LED < NoOfLEDs)
    Display[LED] = color;
}

// Create a 15 bit color value from R,G,B
// Note for the small 10mm LEDs the colour sequence is B, R, G!!
unsigned int LEDPixels::color(unsigned char r,unsigned char g,unsigned char b)
{
  //Take the lowest 5 bits of each value and append them end to end
  return( ((unsigned int)b & 0x1F )<<10 | ((unsigned int)g & 0x1F)<<5 | (unsigned int)r & 0x1F);
}


void LEDPixels::show()
{
  // The interrupt routine will see this as re-send LED color data.
  SendMode = 0;
}

void LEDPixels::initialize(long microseconds, int * DisplayAddress,unsigned int LEDCount , char clkPin, char dPin )
{

  byte Counter;

  clockPin = clkPin;
  dataPin = dPin;
  Display = DisplayAddress;
  NoOfLEDs = LEDCount;

  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

                                        // Adjust as you please. Too slow makes LEDs flicker.
                                        // Too fast and the interrupt may chew into your processing speed!
    //Timer1.attachInterrupt( LedOut ) ;  // attaches routine to drive LEDs
    show();                             // Kick off display.


  TCCR1A = 0;                 // clear control register A 
  TCCR1B = _BV(WGM13);        // set mode as phase and frequency correct pwm, stop the timer

   if(microseconds > 0) setPeriod(microseconds);
  //isrCallback = isr;                                       // register the user's callback with the real ISR
  TIMSK1 = _BV(TOIE1);                                     // sets the timer overflow interrupt enable bit
  sei();                                                   // ensures that interrupts are globally enabled
  start();
}


void LEDPixels::setPeriod(long microseconds)
{
  long cycles = (F_CPU * microseconds) / 2000000;                                // the counter runs backwards after TOP, interrupt is at BOTTOM so divide microseconds by 2
  if(cycles < RESOLUTION)              clockSelectBits = _BV(CS10);              // no prescale, full xtal
  else if((cycles >>= 3) < RESOLUTION) clockSelectBits = _BV(CS11);              // prescale by /8
  else if((cycles >>= 3) < RESOLUTION) clockSelectBits = _BV(CS11) | _BV(CS10);  // prescale by /64
  else if((cycles >>= 2) < RESOLUTION) clockSelectBits = _BV(CS12);              // prescale by /256
  else if((cycles >>= 2) < RESOLUTION) clockSelectBits = _BV(CS12) | _BV(CS10);  // prescale by /1024
  else        cycles = RESOLUTION - 1, clockSelectBits = _BV(CS12) | _BV(CS10);  // request was out of bounds, set as maximum
  ICR1 = pwmPeriod = cycles;                                                     // ICR1 is TOP in p & f correct pwm mode
  TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));
  TCCR1B |= clockSelectBits;                                                     // reset clock select register
}


void LEDPixels::detachInterrupt()
{
  TIMSK1 &= ~_BV(TOIE1);                                   // clears the timer overflow interrupt enable bit 
}

void LEDPixels::start()
{
  TCCR1B |= clockSelectBits;
}

void LEDPixels::stop()
{
  TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));          // clears all clock selects bits
}

void LEDPixels::restart()
{
  TCNT1 = 0;
}

