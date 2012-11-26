#include <BLIP_LEDS_SPI_WS2801.h>

//Example to control RGB LED Modules with Spectrum Analyzer
//Bliptronics.com
//Ben Moyes 2010
//Modified Jul 2011:- Ben Moyes/Andrew Tobolov
//Use this as you wish, but please give credit, or at least buy some of my LEDs!
//
   
//  PIN Connection COLOR CODE
//  RED:    5V
//  BLUE:   GND
//  GREEN:  PIN 13  CLOCK
//  YELLOW: PIN 11  DATA

//For spectrum analyzer shield, these three pins are used.
//You can move pins 4 and 5, but you must cut the trace on the shield and re-route from the 2 jumpers. 

int spectrumReset=5;
int spectrumStrobe=4;
int spectrumAnalog=0;  //0 for left channel, 1 for right.

//This holds the 15 bit RGB values for each LED.
//You'll need one for each LED, we're using 25 LEDs here.
//Note you've only got limited memory, so you can only control 
//Several hundred LEDs on a normal arduino. Double that on a Duemilanove.

#define WIDTH 7                  //Width of our grid.
#define HEIGHT 32                //Height of our grid.
#define NUM_LEDS WIDTH * HEIGHT  // Set the number of LEDs in use here

// Spectrum analyzer read values will be kept here.
int Spectrum[7];

void setup() {
    
//Initialize the "BLIP_LEDS_SPI" library.
   
  BL.setLeds(NUM_LEDS);
  BL.init();
  BL.gridHeight=HEIGHT;      // defines rhe grid dimensions
  BL.gridWidth=WIDTH;
 
  spectrum_init();          //init the spectrum analyzer hardware.  
}

void loop() 
{
 
  unsigned int xx,yy,zz,rr,gg,bb; 
  int aa,bbb;
  int buff[32];




  //for(xx=0;xx<2000;xx++)
 while(1)
  {
    showSpectrum();
    BL.show();
    delay(4);
  }


  while(0)
  {

   normalizeSpectrum();  
  for(zz=HEIGHT-1;zz>0;zz--)
  {
    buff[zz]=buff[zz-1];
    BL.line(0,zz,6,zz,BL.Wheel(buff[zz]*8));
  }

    buff[0] = Spectrum[0];
  
    //BL.line(0,0,6,0,0);
    BL.show();
    delay(15);
 }
    
//    for(xx=0;xx<7;xx++)
//    {
//      normalizeSpectrum();
//      aa=Spectrum[0];
//      if (aa>31)
//        aa=20;
//      BL.line(0,31-aa,6,aa, BL.color(0,0,255));
//      BL.show();
//
//      delay(50-aa);
//      BL.line(0,31-aa,6,aa, BL.color(0,0,0));
//    }
  
  rr=0;
  gg=0;
  bb=0;
  for(xx=0;xx<1000;xx++)
  {
    normalizeSpectrum();
    //BL.setRange(0,NUM_LEDS-1,BL.color(Spectrum[0]*4,Spectrum[3]*4,Spectrum[6]*4));
    if((Spectrum[0] > rr) && rr)
      rr=Spectrum[0];
      else 
      rr--;
  
    if (rr > 31)
      rr=31;

    if(Spectrum[3] > gg)
      gg+=2;
      else 
      gg--;
  
    if (gg > 31)
      gg=31;
  

    if (bb > 31)
      bb=31;
    if(Spectrum[6] > bb)
      bb+=2;
      else 
      bb--;
  
    if (bb > 31)
      bb=31;
  
  
    BL.line(0,31-rr,6,31-rr,BL.color(255,0,0));
    BL.line(0,31-gg,6,31-gg,BL.color(0,255,0));
    BL.line(0,31-bb,6,31-bb,BL.color(0,0,255));
  
   

//    BL.setPixel(random(0,NUM_LEDS),BL.color(Spectrum[0]*4,0,0));
//  BL.setPixel(random(0,NUM_LEDS),BL.color(0,Spectrum[3]*4,0));
//    BL.setPixel(random(0,NUM_LEDS),BL.color(0,0,Spectrum[6]*4));

    BL.show();
    delay(10);
    BL.line(0,31-rr,6,31-rr,BL.color(0,0,0));
    BL.line(0,31-gg,6,31-gg,BL.color(0,0,0));
    BL.line(0,31-bb,6,31-bb,BL.color(0,0,0));
    
     //zz=zz-1;  
  }




  BL.setRange(0,223,BL.color(128,128,128));
  BL.show();
  delay(250);
  
  BL.setRange(0,223,BL.color(128,0,0));
  BL.show();
  delay(250);
  
  BL.setRange(0,223,BL.color(0,128,0));
  BL.show();
  delay(250);
  BL.setRange(0,223,BL.color(0,0,128));
  BL.show();
  delay(250);
  
  
  for(yy=1;yy<32;yy++)
  {
   // showSpectrum();
    BL.line(0,31-yy,6,yy,BL.color(255,255,255));
    BL.show();
    delay(20);
    BL.line(0,31-yy,6,yy,BL.color(0,0,0));
  }
  
  for(xx=1;xx<7;xx++)
  {
    //showSpectrum();
    BL.line(xx,0,6-xx,31,BL.color(255,255,255));
    BL.show();
    delay(20);
    BL.line(xx,0,6-xx,31,BL.color(0,0,0));
  }

 
 
}

//***********************************************************************************
//***********************************************************************************

void spectrum_init()
{
    //Setup pins to drive the spectrum analyzer. 
  pinMode(spectrumReset, OUTPUT);
  pinMode(spectrumStrobe, OUTPUT);

  //Init spectrum analyzer
  digitalWrite(spectrumStrobe,LOW);
    delay(1);
  digitalWrite(spectrumReset,HIGH);
    delay(1);
  digitalWrite(spectrumStrobe,HIGH);
    delay(1);
  digitalWrite(spectrumStrobe,LOW);
    delay(1);
  digitalWrite(spectrumReset,LOW);
    delay(5);
  // Reading the analyzer now will read the lowest frequency.
  
  BL.show();                             //Write out display to LEDs
}


// Read 7 band equalizer.
void readSpectrum()
{
 
  byte Band;
  for(Band=0;Band <7; Band++)
  {
    Spectrum[Band] = (analogRead(spectrumAnalog) + analogRead(spectrumAnalog) ) >>1; //Read twice and take the average by dividing by 2
    digitalWrite(spectrumStrobe,HIGH);
    digitalWrite(spectrumStrobe,LOW);     
  }
}



void normalizeSpectrum()
{
 
  static unsigned int  Divisor = 20, ChangeTimer=0, scaledLevel; //, ReminderDivisor,
  byte Band, BarSize, MaxLevel;
  
  readSpectrum();
  
  MaxLevel=0;
  for(Band=0;Band<7;Band++)
  {
     scaledLevel = Spectrum[Band]/Divisor;	//Bands are read in as 10 bit values. Scale them down to be 0 - 5
     Spectrum[Band]=scaledLevel;
     if (scaledLevel > MaxLevel)  //Check if this value is the largest so far.
       MaxLevel = scaledLevel;    
  }
  
  //Is the level off the chart!?? If so, increase the divisor to make it small next read.
  if (MaxLevel >= (BL.gridHeight)+1)
  {
    Divisor=Divisor+1;
    ChangeTimer=0;
  }
  else //If the level is too low, make divisor smaller, increase the levels on next read! - but only if divisor is not too small. If too small we sample too much noise!
    if(MaxLevel < 20)
    {
      if(Divisor > 25)
        if(ChangeTimer++ > 20)
        {
          Divisor--;
          ChangeTimer=0;
        }
    }
    else
    {
      ChangeTimer=0; 
    }
  
  
}


void showSpectrum()
{
  //Not I don;t use any floating point numbers - all integers to keep it zippy. 
   normalizeSpectrum();
   byte Band, BarSize;
   static unsigned int  Divisor = 20, ChangeTimer=0; //, ReminderDivisor,
   unsigned int works, Remainder;
  
  
        
  for(Band=0;Band<BL.gridWidth;Band++)  //We only graph the lowest 5 bands here, there is 2 more unused! //ALTERED
    {
    //If value is 0, we don't show anything on graph               
       for(BarSize=1;BarSize <=BL.gridHeight; BarSize++)  
          {            
            if(Spectrum[Band] > BarSize) BL.setPixel(BL.Translate(Band,32-BarSize),255,0,0); //BL.Wheel(Band*10));//below the level
            else if ( Spectrum[Band] == BarSize) BL.setPixel(BL.Translate(Band,32-BarSize),0,0,31);//at the level
            else BL.setPixel(BL.Translate(Band,BL.gridHeight-BarSize),0,0,0); //Above the level
          }
    }
  }




 
    
