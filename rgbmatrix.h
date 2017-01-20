#ifndef _RGB_MATRIX_H
#define _RGB_MATRIX_H

#include <Adafruit_GFX.h>
#include <gfxfont.h>

#include <NeoPixelAnimator.h>
#include <NeoPixelBrightnessBus.h>
#include <NeoPixelBus.h>

// on esp8266 pin GPIO2
class RGBMatrix : public NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod>
{
public:
  RGBMatrix(uint8_t w, uint8_t h);
private:
  NeoTopology<RowMajorAlternatingLayout> _topo;
};

#endif
