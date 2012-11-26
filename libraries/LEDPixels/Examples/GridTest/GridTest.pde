#include <LEDPixels.h>

//Example usage of the LEDPixels library with a 5x5 grid of pixels.
//The grid must be arranged in a pattern as follows:
//00 09 10 19 20 
//01 08 11 18 21 
//02 07 12 17 22 
//03 06 13 16 23
//04 05 14 15 24 

// 2010 http://www.bliptronics.com
// http://code.google.com/p/arduino-rgb-pixels/

LEDPixels LP;      //Create an instance of the LED library.
int MyDisplay[25]; //Set up somewhere to store the colors for the LEDs.

void loop()
{
  
    int xx;
    
    // Set LEDs 0 to 24 to black.
    LP.setRange(0,24,LP.color(0,0,0));
    LP.show(); //Send out data to LEDs.
    
    // Display a pattern on the grid
    for(xx=0;xx<5;xx++)
    {
      LP.setPixel(0,xx,LP.color(0,31,0));
      LP.setPixel(1,4-xx,LP.color(0,0,31));
      LP.setPixel(2,xx,LP.color(0,31,0));
      LP.setPixel(3,4-xx,LP.color(0,0,31));
      LP.setPixel(4,xx,LP.color(0,31,0));

      LP.show();
      delay(200);
    }
    
    //Do some wipes of color on the grid.
    MoveLines(LP.color(31,0,0));  
    MoveLines(LP.color(31,31,0));  
    MoveLines(LP.color(0,31,0));  
    MoveLines(LP.color(0,31,31));  
    MoveLines(LP.color(0,0,31));  
    MoveLines(LP.color(31,0,31));  
    
    //Fade all LEDs up to white
    for(xx=0;xx<32;xx++)
    {
      LP.setRange(0,24,LP.color(xx,xx,xx));  
      LP.show();
      delay(30);
    }
    //FAde down from white.
    for(xx=31;xx>1;xx--)
    {
      LP.setRange(0,24,LP.color(xx,xx,xx));  
      LP.show();
      delay(30);
    }

    //Set all LEDs to random colours.
    for(xx=0;xx<25;xx++)
    {
      LP.setLEDFast(xx,LP.color(random(0,31),random(0,31),random(0,31) ) );  
    }
      LP.show();
      delay(2000);

    
  
}

//Set all LEDS and wait 1 second.
void All(unsigned int color)
{
    LP.setRange(0,25,color);  
    LP.show();
    delay(1000);
}


void MoveLines(int yy)
{
  //Draws 5 vertical lines in the requested color.
  //Then follow them with 5 black lines for a wipe effect.
  int xx;
      for(xx=0;xx<5;xx++)
        {
        LP.line(0,xx,4,xx,yy );
        LP.show();
        delay(50);
        }
   
      for(xx=0;xx<5;xx++)
        {
        LP.line(0,xx,4,xx,0 );
        LP.show();
        delay(50);
        }
}


void setup()
{
  //Initialize the LED driver. Pass the LED clock speed (lower is faster), pointer to display memory, the number of LEDs, clock pin (green wire), data pin (yellow wire)
  LP.initialize(25, &MyDisplay[0],60, 12, 11 );  //no of leds, address of display, clock (green), data (yellow)
  LP.setRange(0,24,LP.color(0,0,0));            //Set ALL our LEDs to black. Start, End, Color
  //Since we are  going to use the line and setPixel methods, the library needs to know the size of the grid.
  LP.gridWidth=5;
  LP.gridHeight=5;
  
}
