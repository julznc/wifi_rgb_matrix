#include "rgbmatrix.h"

RGBMatrix::RGBMatrix(uint8_t w, uint8_t h)
  : Adafruit_GFX(w, h), NeoPixelBrightnessBus((uint16_t)(w*h)),
  _topo(w,h), _x(0), _text_width(0), _prev_ms(0), _period_ms(300)
{
  
}

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
    fillScreen(0);
    setCursor(_x, 0);
    print(_text_buff);
    
    if (_text_width > width()) { // need to scroll
      if((_text_width - (--_x)) < (width()>>1)) {
        _x = width();
      }
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
}

void RGBMatrix::setText(const String &text)
{
  setText(text.c_str());
}

