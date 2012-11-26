Place the folder "BLIP_LEDS_SPI_2801" into your Arduino libraries folder, before starting the IDE.
Ensure that the following are contained within:-

BLIP_LEDS_SPI_2801.h
BLIP_LEDS_SPI_2801.cpp
BLIP_LEDS_SPI_DEMO>BLIP_LEDS_SPI_DEMO.pde (in the example folder)


This is an Arduino library for for driving WS2801 controlled RGB LED pixels.



Pick some up at http://www.bliptronics.com/

-------------------------------------------------------------------------------------------------------------
The following is an explanation of the functions used within a sketch to use our WS2801 controlled LED driver library 
-------------------------------------------------------------------------------------------------------------

#define	NUM_LEDS <number>

Simply define the number of LEDs used in your strip


	BL.setLeds (NUM_LEDS);      
	BL.init();

Initialisation functions. Wouldn't worry about them. They just need to be there.

                              

If LEDs are to be arranged in grid fashion the dimensions can be set to make use of LINE, BOX and Spectrum Analyser Functions. 
Eg.
	BL.gridHeight = 32;                        
	BL.gridWidth = 7;



Color selection of the LEDs is made by inputting a 24 bit value into  the  "BL.color" function.
The easiest method of doing this is by placing a value ranging from 0 to 255 in each of the red, green, blue positions like so:
Eg.
	BL.color(<red>,<green>,<blue>). 

    ie. BL.color(255,255,255);   producing white.

A 24 bit value can also be used:
Eg.
	BL.color(0xFFFFFF); 

To clear a color value BL.color(0,0,0); can be used.



To set a particular LED, the "BL.setPixel" function is used. The format is BL.setPixel(<LED position>, <24 bit color value>); 

Eg. 	BL.setPixel(0,255,255,255); 	will set the first led white

	BL.setPixel(0,0xFFFFFF); 	will do the same



"BL.show();"  displays or 'turns on' color data loaded in to each LED. 
NOTE: A delay function will often need to be used directly after a BL.show(); is called. The minimum amount of delay required will needed to be tested for in each implementation.



Our library allows the use of a LINE function, which will draw a line between 2 points in an array. Coordinates of the 2 points are required to enable this, and is implemented like so:

	BL.line(<X-position, Y position of first point>,<X position, Y position of 2nd point>,<24 bit color value>);

Eg. 
	BL.line(0,0,0,32,BL.color(255,255,255)); would result in a vertical white line, 32 LEDs long in the 			first column of an array

The coordinates are arranged such that the point X = 0, Y = 0 would be the TOP-LEFT of an array. Also, the columns are numbered from 0 to 1 less than the actual number of columns. ie. 7 columns are numbered from 0 to 6. Rows are numbered similarly.


The library also contains a BOX function. It is implemented in the same way as the LINE function only that a box is drawn from the given coordinates rather than a line.

 
