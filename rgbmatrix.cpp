#include "rgbmatrix.h"

RGBMatrix::RGBMatrix(uint8_t w, uint8_t h)
  : Adafruit_GFX(w, h), NeoPixelBrightnessBus((uint16_t)(w*h)),
  _topo(w,h), _animations((uint16_t)(w*h), NEO_MILLISECONDS),
  _mode(MODE_TEXT), _bmp_idx(0),
  _x(0),_text_width(0),
  _prev_ms(0), _period_ms(250)
{
  
}

const uint32_t bmp_THANKS[] = {
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
  0x00000000, 0x00FFFF00, 0x00FFFF00, 0x00FFFF00, 0x00FFFF00, 0x00000000, 0x00000000, 0x000000FF, 0x00000000, 0x00000000, 0x00000000, 0x000000FF, 0x00000000, 0x00000000, 0x00FFFF00, 0x00FFFF00, 0x00FFFF00, 0x00FFFF00, 0x00000000, 0x00000000, 0x000000FF, 0x000000FF, 0x000000FF, 0x00000000, 0x00000000, 0x00FFFF00, 0x00000000, 0x00000000, 0x00000000, 0x00FFFF00, 0x00000000, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF, 
  0x00000000, 0x00000000, 0x002A00D4, 0x00000000, 0x00000000, 0x00000000, 0x00D5FF2B, 0x00000000, 0x00000000, 0x00000000, 0x00D5FF2B, 0x00000000, 0x002A00D4, 0x00000000, 0x00000000, 0x00000000, 0x002A00D4, 0x00000000, 0x00D5FF2B, 0x00000000, 0x00000000, 0x00000000, 0x00D5FF2B, 0x00000000, 0x002A00D4, 0x00000000, 0x00000000, 0x00000000, 0x002A00D4, 0x00000000, 0x00D5FF2B, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00AAFF55, 0x00000000, 0x00000000, 0x005500AA, 0x00000000, 0x00000000, 0x005500AA, 0x00000000, 0x00AAFF55, 0x00000000, 0x00000000, 0x00000000, 0x00AAFF55, 0x00000000, 0x005500AA, 0x00000000, 0x00000000, 0x00000000, 0x005500AA, 0x00000000, 0x00AAFF55, 0x00000000, 0x00000000, 0x00000000, 0x00AAFF55, 0x00000000, 0x00000000, 0x00000000, 0x005500AA, 0x00000000, 0x00000000, 
  0x00000000, 0x00000000, 0x007F007F, 0x00000000, 0x00000000, 0x00000000, 0x0080FF80, 0x0080FF80, 0x0080FF80, 0x0080FF80, 0x0080FF80, 0x00000000, 0x007F007F, 0x007F007F, 0x007F007F, 0x007F007F, 0x007F007F, 0x00000000, 0x0080FF80, 0x00000000, 0x00000000, 0x00000000, 0x0080FF80, 0x00000000, 0x007F007F, 0x007F007F, 0x007F007F, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0080FF80, 0x0080FF80, 0x0080FF80, 0x00000000, 0x00000000, 
  0x00000000, 0x0055FFAA, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00AA0055, 0x00000000, 0x00000000, 0x00AA0055, 0x00000000, 0x0055FFAA, 0x00000000, 0x00000000, 0x00000000, 0x0055FFAA, 0x00000000, 0x00AA0055, 0x00000000, 0x00000000, 0x00000000, 0x00AA0055, 0x00000000, 0x0055FFAA, 0x00000000, 0x00000000, 0x00000000, 0x0055FFAA, 0x00000000, 0x00000000, 0x00000000, 0x00AA0055, 0x00000000, 0x00000000, 
  0x00000000, 0x00000000, 0x00D4002A, 0x00000000, 0x00000000, 0x00000000, 0x002BFFD5, 0x00000000, 0x00000000, 0x00000000, 0x002BFFD5, 0x00000000, 0x00D4002A, 0x00000000, 0x00000000, 0x00000000, 0x00D4002A, 0x00000000, 0x002BFFD5, 0x00000000, 0x00000000, 0x00000000, 0x002BFFD5, 0x00000000, 0x00D4002A, 0x00000000, 0x00000000, 0x00000000, 0x00D4002A, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x002BFFD5, 0x00000000, 
  0x00000000, 0x00000000, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x0000FFFF, 0x00000000, 0x00000000, 0x00000000, 0x0000FFFF, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x0000FFFF, 0x00000000, 0x00000000, 0x00000000, 0x0000FFFF, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 
};

const uint32_t bmp_STOP[] = {
  0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00FF0000, 0x00FF0000, 0x00FF0000, 0x00000000, 0x00FF0000, 0x00FF0000, 0x00FF0000, 0x00FF0000, 0x00FF0000, 0x00000000, 0x00000000, 0x00FF0000, 0x00FF0000, 0x00FF0000, 0x00000000, 0x00000000, 0x00FF0000, 0x00FF0000, 0x00FF0000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 
  0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00FF0000, 0x00000000, 0x00000000, 0x00FF0000, 0x00FF0000, 0x00000000, 0x00000000, 
  0x00000000, 0x00000000, 0x00FF0000, 0x00FF0000, 0x00000000, 0x00000000, 0x00FF0000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00FF0000, 0x00FF0000, 0x00FF0000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00FF0000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
  0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
  0x00000000, 0x00000000, 0x00FF0000, 0x00FF0000, 0x00FF0000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00FF0000, 0x00FF0000, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0000, 0x00FF0000, 0x00FF0000, 0x00FF0000, 0x00000000, 0x00000000, 0x00000000, 
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
};

const uint32_t bmp_BABYONCAR[] = {
  0x00FF0080, 0x00FF0080, 0x00FF0080, 0x00000000, 0x00000000, 0x00000000, 0x0098FF98, 0x00000000, 0x00000000, 0x00FF0080, 0x00FF0080, 0x00FF0080, 0x00000000, 0x0098FF98, 0x00000000, 0x00000000, 0x00000000, 0x0098FF98, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0098FF98, 0x00000000, 0x00000000, 0x00000000, 0x0098FF98, 0x00FF0080, 0x00000000, 0x00000000, 0x00FF0080, 0x00000000, 0x0098FF98, 0x00000000, 0x0098FF98, 0x00000000, 0x00FF0080, 0x00000000, 0x00000000, 0x00FF0080, 
  0x00FF0080, 0x00000000, 0x00000000, 0x00FF0080, 0x0098FF98, 0x00000000, 0x00000000, 0x00000000, 0x0098FF98, 0x00FF0080, 0x00000000, 0x00000000, 0x00FF0080, 0x0098FF98, 0x00000000, 0x00000000, 0x00000000, 0x0098FF98, 0x00FF0000, 0x00FF0000, 0x00FF0000, 0x0000FF40, 0x0000FF40, 0x00000F00, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
  0x00000000, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x00000000, 0x00FF0080, 0x00FF0080, 0x00000000, 0x000080C0, 0x000080C0, 0x000080C0, 0x00000000, 0x0000FF40, 0x00000000, 0x0000FF40, 0x00FF0000, 0x00000000, 0x00FF0000, 0x00000000, 0x0098FF98, 0x00000000, 0x0098FF98, 0x00000000, 0x00000000, 0x00FF0080, 0x00FF0080, 0x00FF0080, 0x0098FF98, 0x0098FF98, 0x0098FF98, 0x0098FF98, 0x0098FF98, 0x00000000, 0x00FF0080, 0x00FF0080, 0x00FF0080, 
  0x00FF0080, 0x00000000, 0x00000000, 0x00FF0080, 0x0098FF98, 0x00000000, 0x00000000, 0x00000000, 0x0098FF98, 0x00FF0080, 0x00000000, 0x00000000, 0x00FF0080, 0x00000000, 0x00000000, 0x0098FF98, 0x00000000, 0x00000000, 0x00FF0000, 0x00000000, 0x00FF0000, 0x0000FF40, 0x00000000, 0x0000FF40, 0x000080C0, 0x00000000, 0x00000000, 0x00000000, 0x00FF0080, 0x00000000, 0x00000000, 0x00FF0080, 0x0000FFFF, 0x00000000, 0x00000000, 0x0000FFFF, 
  0x00000000, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x00FF0080, 0x00FF0080, 0x00FF0080, 0x00FF0080, 0x00000000, 0x00000000, 0x00000000, 0x000080C0, 0x0000FF40, 0x00000000, 0x0000FF40, 0x00FF0000, 0x00FF0000, 0x00FF0000, 0x00000000, 0x00000000, 0x0098FF98, 0x00000000, 0x00000000, 0x00FF0080, 0x00000000, 0x00000000, 0x00FF0080, 0x0098FF98, 0x00000000, 0x00000000, 0x00000000, 0x0098FF98, 0x00FF0080, 0x00000000, 0x00000000, 0x00FF0080, 
  0x00FF0080, 0x00FF0080, 0x00FF0080, 0x00000000, 0x0098FF98, 0x00000000, 0x00000000, 0x00000000, 0x0098FF98, 0x00FF0080, 0x00FF0080, 0x00FF0080, 0x00000000, 0x00000000, 0x00000000, 0x0098FF98, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000080C0, 0x00000000, 0x00000000, 0x00000000, 0x00FF0080, 0x00000000, 0x00000000, 0x00FF0080, 0x0000FFFF, 0x00000000, 0x0000FFFF, 0x00000000, 
  0x0000FFFF, 0x00000000, 0x00000000, 0x0000FFFF, 0x00FF0080, 0x00000000, 0x00000000, 0x00FF0080, 0x000080C0, 0x000080C0, 0x000080C0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
};

const uint32_t bmp_PREGGYONCAR[] = {
  0x00FF0080, 0x00FF0080, 0x00FF0080, 0x00000000, 0x00FFFF00, 0x00FFFF00, 0x00FFFF00, 0x00000000, 0x00FF0080, 0x00FF0080, 0x00FF0080, 0x00FF0080, 0x00000000, 0x00FFFF00, 0x00FFFF00, 0x00000000, 0x00000000, 0x00FF0080, 0x00FF0080, 0x00000000, 0x00FFFF00, 0x00000000, 0x00000000, 0x00000000, 0x00FFFF00, 0x00000000, 0x00000000, 0x00FF0000, 0x00FF0000, 0x00FF0000, 0x00000000, 0x0000FF00, 0x0000FF00, 0x0000FF00, 0x00000000, 0x00000000, 
  0x00000000, 0x00000000, 0x0000FF00, 0x00000000, 0x0000FF00, 0x00000000, 0x00FF0000, 0x00000000, 0x00FF0000, 0x00000000, 0x00000000, 0x00FFFF00, 0x00000000, 0x00000000, 0x00000000, 0x00FFFF00, 0x00FF0080, 0x00000000, 0x00000000, 0x00FF0080, 0x00FFFF00, 0x00000000, 0x00000000, 0x00FFFF00, 0x00000000, 0x00000000, 0x00000000, 0x00FF0080, 0x00FFFF00, 0x00000000, 0x00000000, 0x00FFFF00, 0x00FF0080, 0x00000000, 0x00000000, 0x00FF0080, 
  0x00FF0080, 0x00000000, 0x00000000, 0x00FF0080, 0x00FFFF00, 0x00000000, 0x00000000, 0x00FFFF00, 0x00FF0080, 0x00000000, 0x00000000, 0x00000000, 0x00FFFF00, 0x00000000, 0x00000000, 0x00000000, 0x00FF0080, 0x00000000, 0x00000000, 0x00000000, 0x00FFFF00, 0x00000000, 0x00000000, 0x00000000, 0x00FFFF00, 0x00000000, 0x00000000, 0x00FF0000, 0x00FF0000, 0x00FF0000, 0x00000000, 0x0000FF00, 0x00000000, 0x0000FF00, 0x00000000, 0x00000000, 
  0x00000000, 0x00FF8040, 0x00FF8040, 0x00FF8040, 0x00000000, 0x000080FF, 0x000080FF, 0x00000000, 0x00FF80FF, 0x00FF80FF, 0x00FF80FF, 0x00000000, 0x00FFFF00, 0x00000000, 0x00FFFF00, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00FF0080, 0x00000000, 0x00000000, 0x00000000, 0x00FFFF00, 0x00000000, 0x00FF0080, 0x00FF0080, 0x00FF0080, 0x00000000, 0x00FFFF00, 0x00FFFF00, 0x00FFFF00, 0x00000000, 0x00FF0080, 0x00FF0080, 0x00FF0080, 
  0x00FF0080, 0x00000000, 0x00000000, 0x00000000, 0x00FFFF00, 0x00000000, 0x00FFFF00, 0x00000000, 0x00FF0080, 0x00000000, 0x00000000, 0x00000000, 0x00FFFF00, 0x00000000, 0x00FFFF00, 0x00FFFF00, 0x00FF0080, 0x00000000, 0x00FF0080, 0x00FF0080, 0x00000000, 0x00000000, 0x00FFFF00, 0x00000000, 0x00FF80FF, 0x00000000, 0x00000000, 0x00000000, 0x000080FF, 0x00000000, 0x00000000, 0x000080FF, 0x00FF8040, 0x00000000, 0x00000000, 0x00FF8040, 
  0x00000000, 0x00FF8040, 0x00FF8040, 0x00FF8040, 0x000080FF, 0x000080FF, 0x000080FF, 0x000080FF, 0x00000000, 0x00000000, 0x00000000, 0x00FF80FF, 0x00000000, 0x00FFFF00, 0x00000000, 0x00000000, 0x00FF0080, 0x00000000, 0x00000000, 0x00FF0080, 0x00FFFF00, 0x00000000, 0x00000000, 0x00FFFF00, 0x00000000, 0x00000000, 0x00000000, 0x00FF0080, 0x00FFFF00, 0x00000000, 0x00000000, 0x00FFFF00, 0x00000000, 0x00000000, 0x00000000, 0x00FF0080, 
  0x00FF0080, 0x00000000, 0x00000000, 0x00000000, 0x00FFFF00, 0x00000000, 0x00000000, 0x00FFFF00, 0x00FF0080, 0x00000000, 0x00000000, 0x00000000, 0x00FFFF00, 0x00000000, 0x00000000, 0x00FFFF00, 0x00FF0080, 0x00000000, 0x00000000, 0x00FF0080, 0x00000000, 0x00000000, 0x00FFFF00, 0x00000000, 0x00FF80FF, 0x00000000, 0x00000000, 0x00000000, 0x000080FF, 0x00000000, 0x00000000, 0x000080FF, 0x00FF8040, 0x00000000, 0x00FF8040, 0x00000000, 
  0x00FF8040, 0x00000000, 0x00000000, 0x00FF8040, 0x000080FF, 0x00000000, 0x00000000, 0x000080FF, 0x00FF80FF, 0x00FF80FF, 0x00FF80FF, 0x00000000, 0x00000000, 0x00FFFF00, 0x00000000, 0x00000000, 0x00000000, 0x00FF0080, 0x00FF0080, 0x00000000, 0x00000000, 0x00FFFF00, 0x00FFFF00, 0x00000000, 0x00FF0080, 0x00FF0080, 0x00FF0080, 0x00FF0080, 0x00FFFF00, 0x00000000, 0x00000000, 0x00FFFF00, 0x00000000, 0x00000000, 0x00000000, 0x00FF0080, 
};

const uint32_t *bmp_arrays[] = {
  bmp_THANKS, bmp_STOP, bmp_BABYONCAR, bmp_PREGGYONCAR
};

void RGBMatrix::init(void)
{
  memset(_text_buff, 0, sizeof(_text_buff));

  Begin();
  SetBrightness(18); // 0-255
  setTextWrap(false);
  setTextColor(0xFFFF);
  Show();
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

void RGBMatrix::exec(void)
{
  unsigned long curr_ms = millis();
  if (curr_ms - _prev_ms >= _period_ms)
  {
    switch(_mode)
    {
    case MODE_TEXT:
      fillScreen(0);
      setCursor(_x, 0);
      print(_text_buff);
      
      if (_text_width > width()) { // need to scroll
        if((_text_width + (--_x)) < (width()>>1)) {
          //Serial.println("reset");
          _x = width() >> 1;
        }
      }
      break;
    case MODE_BITMAP:
      for (uint16_t pixel=0; pixel<PixelsSize(); pixel++) {
        SetPixelColor(pixel, HtmlColor(bmp_arrays[_bmp_idx][pixel]));
      }
      break;
    case MODE_ANIMATE:
      if (_animations.IsAnimating()) {
        _animations.UpdateAnimations();
      } else {
        _setupAnimation();
      }
      break;
    }
    Show();

    _prev_ms = curr_ms;
  }
}

void RGBMatrix::setText(const char *text)
{
  strncpy(_text_buff, text, sizeof(_text_buff)-1);
  _text_width = strlen(text);
  if (_text_width > 1) {
    _text_width *= (5+1);
  } else {
    _text_width *= 5;
  }

  if (_text_width > width()) { // need to scroll
    //Serial.println("need to scroll");
    _x = width() >> 1;
  } else { // show at center
    //Serial.println("show at center");
    _x = (width()-_text_width) >> 1;
  }
  _mode = MODE_TEXT;
}

void RGBMatrix::setText(const String &text)
{
  setText(text.c_str());
}

void RGBMatrix::setTextHtmlColor(const String &htmlcolor)
{
  HtmlColor color;
  color.Parse<HtmlColorNames>(htmlcolor.c_str());
  RgbColor rgb( color );
  uint16_t r = (rgb.R & 0xF8) << 8;
  uint16_t g = (rgb.G & 0xFC) << 4;
  uint16_t b = (rgb.B & 0xF8) >> 3;
  setTextColor(r|g|b);
}

void RGBMatrix::showBitmap(uint8_t index)
{
  _bmp_idx = index;
  _mode = MODE_BITMAP;
}

void RGBMatrix::_setupAnimation()
{
  for (uint16_t pixel = 0; pixel < PixelsSize(); pixel++)
  {
    const uint8_t peak = 128;
    RgbColor originalColor = GetPixelColor(pixel);
    RgbColor targetColor = RgbColor(random(peak), random(peak), random(peak));

    AnimUpdateCallback animUpdate = [=](const AnimationParam& param)
    {
      float progress = NeoEase::QuadraticInOut(param.progress);
      RgbColor updatedColor = RgbColor::LinearBlend(originalColor, targetColor, progress);
      SetPixelColor(pixel, updatedColor);
    };
    _animations.StartAnimation(pixel, random(100, 800), animUpdate);
  }
}

void RGBMatrix::showAnimation(uint8_t index)
{
  (void)index; // random animation only for now
  _mode = MODE_ANIMATE;
}

