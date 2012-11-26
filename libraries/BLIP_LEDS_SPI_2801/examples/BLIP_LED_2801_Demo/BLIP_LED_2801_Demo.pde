#include <BLIP_LEDS_SPI_WS2801.h>


/*Example sketch for driving WS2801 controlled RGB LEDs

  Bliptronics.com
  Ben Moyes 2009
  Use this as you wish, but please give credit, or at least buy some of my LEDs!

  Modified Jul 2011 by Ben Moyes and Andrew Tobolov to show off updated BLIP_LEDS_SPI_WS2801 Library

  Note, because this library uses the arduino's hardware SPI support, you MUST use the SPI 
  pins on your hardware - e.g. pins 11 and 13 on a Arduino pro mini or such. 
  Refer to the library for pins in use by your board type.

  Each LED holds a 24 bit RGB value.
  Note, you've only got limited memory on the Arduino, so you can only control 
  Several hundred LEDs on a normal arduino. Double that on a Duemilanove. 
  
  Refer to the accompanied README.txt file for further explanation on how to use our library and the
  functions used in this sketch*/


#define NUM_LEDS 224                        // Set the Number of LEDs in use here

void setup() 
{
  BL.setLeds(NUM_LEDS);                     // Initialisation functions
  BL.init();                                // SPI interrupt will now send out data to LEDs. This happens in the background, pretty fast.
  
  BL.gridHeight  = 32;                      // Grid dimensions for LINE and BOX effect functions are defined here. Also used for Spectrum Analyzer function.
  BL.gridWidth   = 7;
}

void loop() 
{
 
  unsigned int Counter, Counter2, Counter3;
  
  uint32_t color = 0xFF0000;
  for(int i=0;i<3;i++)                                  // An example of how pixels and their color values can be set 
  {  
  for(Counter=0; Counter < NUM_LEDS ; Counter++)
    {
     BL.setPixel(Counter,color);
     BL.show();
     delay(10);
    }
    color = color>>8;
  }
 

  for(int i=0;i<7;i++)                                // LINE Function Demo
  {
    BL.line(i,0,i,32,BL.color(255,255,255));          
    BL.show();
    delay(50);
    BL.line(i,0,i,32,BL.color(0,0,0));
  }
  
 for(int i=0;i<32;i++)
 {
    BL.line(0,i,6,i,BL.color(255,255,255));
    BL.show();
    delay(15);
    BL.line(0,i,6,i,BL.color(0,0,0));
 }

 
  BL.box(0,0,6,31,0xFFFFFF);                            //BOX Function Demo
  BL.show();
  delay(200);
  for(int i=0;i<NUM_LEDS;i++)BL.setPixel(i,0,0,0);
  BL.box(1,5,5,25,0xFFFFFF);
  BL.show();
  delay(200);
  for(int i=0;i<NUM_LEDS;i++)BL.setPixel(i,0,0,0);
  BL.box(2,10,4,20,0xFFFFFF);
  BL.show();
  delay(200);
  for(int i=0;i<NUM_LEDS;i++)BL.setPixel(i,0,0,0);
  
  
  
//      for(Counter=0; Counter < 768 ; Counter++)                             //Scrolling Rainbow Effect
//  {
// 
//    for(Counter2=0; Counter2 < NUM_LEDS; Counter2++)
//    {
//     BL.setPixel(Counter2, BL.Wheel((Counter2*2 + Counter)%768));
//      Counter3+=(768 / NUM_LEDS);
//    }    
//    BL.show();
//    delay(25);
//  }
  

}
  

