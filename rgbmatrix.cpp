#include "rgbmatrix.h"

RGBMatrix::RGBMatrix(uint8_t w, uint8_t h)
  : NeoPixelBus((uint16_t)(w*h)), _topo(w,h)
{
  
}

