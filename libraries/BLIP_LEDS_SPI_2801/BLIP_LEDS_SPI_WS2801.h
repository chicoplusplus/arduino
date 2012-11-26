#ifndef __INC_SPIRGB_H
#define __INC_SPIRGB_H
#include <HardwareSerial.h>
#include <WProgram.h>
#include "string.h"
#include <avr/pgmspace.h>

/******************************************************************************
 * A class for controlling a shift-register based LED decoder WS2801 controller 
   chip
 ******************************************************************************/

class CBLIP_LEDS_SPI { 
public:
  
  void setup_hardware_spi();
  
  int m_nLeds;
  unsigned char m_nDirty;
  unsigned long m_nCounter;
  unsigned char *m_pData;
  unsigned char *m_pDataEnd;
  unsigned int NUM_LEDS;
  unsigned char *getRGBData() { return m_pData; }
  
  
  void setLeds(int nLeds) 
  { 
    m_nLeds = nLeds * 3; 
    m_nCounter = 0; 
    m_nDirty = 0; 
    m_pData = (unsigned char*)malloc(m_nLeds); 
    memset(m_pData,0,m_nLeds); 
    m_pDataEnd = m_pData + m_nLeds; 
    NUM_LEDS = nLeds; 
  }

  void init();
  void start();
  void stop();
 
  void setRange(unsigned int startLED, unsigned int endLED, uint32_t color);
  void show();
  
  
  /******************************************************************************
 * LED EFFECTS
 ******************************************************************************/
                                                                                
  unsigned int Wheel(byte WheelPos);
   
  void setLED(unsigned int LED, byte rr, byte gg, byte bb);
  void setPixel(unsigned int LED, uint32_t color);
  void setPixel(int x, int y, uint32_t color);
  void setPixel(unsigned int LED, byte rr, byte gg, byte bb);
      
  unsigned int Translate(byte x, byte y);
  void box(byte x0, byte y0, byte x1, byte y1, uint32_t color);
  void swap(int * a, int * b);
  void line(int x0,  int y0, int x1, int y1, uint32_t color);

  uint32_t color(unsigned char r, unsigned char g, unsigned char b);
  unsigned int gridHeight;
  unsigned int gridWidth;
  
  
};

extern CBLIP_LEDS_SPI BL;

#endif

