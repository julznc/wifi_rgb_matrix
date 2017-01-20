#include "rgbmatrix.h"

RGBMatrix::RGBMatrix(uint8_t w, uint8_t h)
  : Adafruit_GFX(w, h), NeoPixelBus((uint16_t)(w*h)), _topo(w,h)
{
  
}

void RGBMatrix::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  SetPixelColor(_topo.Map(x,y), color);
}

