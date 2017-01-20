#include "rgbmatrix.h"

RGBMatrix::RGBMatrix(uint8_t w, uint8_t h)
  : Adafruit_GFX(w, h), NeoPixelBus((uint16_t)(w*h)), _topo(w,h)
{
  
}

void RGBMatrix::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  RgbColor rgb((color&0xF800)>>8, (color&0x07E0)>>4, (color&0x001F)<<3);
  SetPixelColor(_topo.Map(x,y), rgb);
}

void RGBMatrix::fillScreen(uint16_t color)
{
  RgbColor rgb((color&0xF800)>>8, (color&0x07E0)>>4, (color&0x001F)<<3);
  ClearTo(rgb);
}

