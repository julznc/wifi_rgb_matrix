
#include "webserver.h"

namespace web
{

static const char* ssid = "yusmeann_wifi";
static const char* password = "j03m05c15";

ESP8266WebServer server(80);

void begin(void)
{
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
  
}

}

