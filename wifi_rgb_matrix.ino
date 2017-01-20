/*
 * WS2812 RGB panel controlled by ESP8266 module (GPIO2 pin)
 */
 
#include "rgbmatrix.h"

// 8x36 matrix
const uint8_t PanelWidth = 36;
const uint8_t PanelHeight = 8;
RGBMatrix matrix(PanelWidth, PanelHeight);

void setup() {
  Serial.begin(115200);
  while (!Serial); // wait for serial attach
  Serial.println("\nInitializing...");
  
  matrix.Begin();
  matrix.Show();

  Serial.println("\nRunning...");

}

void loop() {
  // put your main code here, to run repeatedly:

}
