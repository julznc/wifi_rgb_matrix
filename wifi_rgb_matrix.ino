/*
 * WS2812 RGB panel controlled by ESP8266 module (GPIO2 pin)
 */

#include "webserver.h"
#include "rgbmatrix.h"

// 8x36 matrix
const uint8_t PanelWidth = 36;
const uint8_t PanelHeight = 8;
RGBMatrix matrix(PanelWidth, PanelHeight);

unsigned long previousMillis = 0;
const long interval = 300; 

void setup() {
  Serial.begin(115200);
  while (!Serial); // wait for serial attach
  Serial.println("\nInitializing...");

  matrix.init();
  matrix.setText("yusmeann love marius");
  web::init();

  Serial.println("\nRunning...");
}

void loop() {
  matrix.exec();
  web::exec();
}
