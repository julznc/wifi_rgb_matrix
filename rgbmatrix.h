#ifndef _RGB_MATRIX_H
#define _RGB_MATRIX_H

#include <Adafruit_GFX.h>
#include <gfxfont.h>

#include <NeoPixelAnimator.h>
#include <NeoPixelBrightnessBus.h>
#include <NeoPixelBus.h>

// on esp8266 pin GPIO2
class RGBMatrix : public Adafruit_GFX, public NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod>
{
public:
  RGBMatrix(uint8_t w, uint8_t h);
  void init(void);

  virtual void drawPixel(int16_t x, int16_t y, uint16_t color);
  virtual void fillScreen(uint16_t color);

  void exec(void);
  void setText(const char *text);
  void setText(const String &text);
  void setTextHtmlColor(const String &htmlcolor);
  void showBitmap(uint8_t index);
  void showAnimation(uint8_t index);

private:
  NeoTopology<RowMajorAlternatingLayout> _topo;
  NeoPixelAnimator _animations;

  enum {
    MODE_TEXT,
    MODE_BITMAP,
    MODE_ANIMATE,
  } _mode;
  
  char _text_buff[256];
  uint8_t _bmp_idx;
  int _x;
  int _text_width;
  unsigned long _prev_ms;
  const unsigned long _period_ms;

  void _setupAnimation();

};

#endif
