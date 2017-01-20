/*
 * WS2812 RGB panel controlled by ESP8266 module
 */
#include <NeoPixelAnimator.h>
#include <NeoPixelBrightnessBus.h>
#include <NeoPixelBus.h>

// 8x36 matrix
const uint8_t PanelWidth = 36;
const uint8_t PanelHeight = 8;
const uint16_t PixelCount = PanelWidth * PanelHeight;
NeoTopology<RowMajorAlternatingLayout> topo(PanelWidth, PanelHeight);

// on esp8266 pin GPIO2
NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(PixelCount);

void setup() {
  Serial.begin(115200);
  while (!Serial); // wait for serial attach
  Serial.println("\nInitializing...");
  
  strip.Begin();
  strip.Show();

  Serial.println("\nRunning...");

}

void loop() {
  // put your main code here, to run repeatedly:

}
