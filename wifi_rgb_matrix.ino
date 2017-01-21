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

  matrix.Begin();
  matrix.SetBrightness(8); // 0-255
  matrix.setTextWrap(false);
  matrix.setTextColor(0xFFFF);
  matrix.Show();

  web::begin();

  Serial.println("\nRunning...");

}

int x = 18;//matrix.width();

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {

    matrix.fillScreen(0);
    matrix.setCursor(x, 0);
    matrix.print(F("Julius love Mary Ann"));
    if(--x < -96) {
      x = matrix.width();
    }
    matrix.Show();

    previousMillis = currentMillis;

  }

  web::handle();

}
