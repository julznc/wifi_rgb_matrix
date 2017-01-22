
#include "webserver.h"
#include "rgbmatrix.h"

namespace web
{

static const char* ssid = "yusmeann_wifi";
static const char* password = "j03m05c15";

static RGBMatrix *_display = NULL;
static char _ready = 0;
static IPAddress _ip;

static const char *indexhtml = ""
"<html>"
"<head>"
"<title>"
"WiFi RGB"
"</title>"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
"</head>"
"<body>"
"<h1>WiFi RGB Matrix</h1>"
"<form action=\"/text\" method=\"post\">"
"<p>Text:"
"<input type=\"text\" name=\"text\" required></input><br/>"
"Color:"
"<input type=\"color\" name=\"color\" value=\"#ffffff\"></input><br/>"
"<button type=\"submit\">Set</button></p>"
"</form>"
"<form action=\"/brightness\" method=\"post\">"
"<p>Brightness:"
"<input type=\"number\" min=\"0\" max=\"255\" name=\"brightness\"></input>"
"<button type=\"submit\">Set</button></p>"
"</form>"
"</body>"
"</html>";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", indexhtml);
}

void handleFail(String msg)
{
  server.sendHeader("Connection", "close");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(500, "text/plain", msg + "\r\n");
}

void handleText() {
  if (!server.hasArg("text") || !server.hasArg("color"))
    return handleFail("BAD ARGS");
  //Serial.println(server.arg("text"));
  _display->setText(server.arg("text"));
  //Serial.println(server.arg("color"));
  _display->setTextHtmlColor(server.arg("color"));
  handleRoot();
}

void handleBrightness() {
  if (!server.hasArg("brightness"))
    return handleFail("BAD ARGS");
  //Serial.println(server.arg("brightness"));
  _display->SetBrightness(server.arg("brightness").toInt());
  handleRoot();
}

void handleNotFound(){
  server.send(404, "text/plain", "Not Found");
}

void init(void)
{
  WiFi.begin(ssid, password);

  _ready = 0;
  _display = NULL;

  server.on("/", handleRoot);
  server.on("/text", handleText);
  server.on("/brightness", handleBrightness);
  server.onNotFound(handleNotFound);
  
}

void setDisplay(void *rgbmatrix)
{
  _display = (RGBMatrix *)rgbmatrix;
}

void exec(void)
{
  if (0==_ready) {
    // check for connection
    if (WL_CONNECTED == WiFi.status()) {
      _ip = WiFi.localIP();
      Serial.print("Connected to ");
      Serial.println(ssid);
      Serial.print("IP address: ");
      Serial.println(_ip);
      String ipstr = String(_ip[2]) + "." + String(_ip[3]);
      _display->setText(ipstr);
      
      if (MDNS.begin("esp8266")) {
        Serial.println("MDNS responder started");
      }

      server.begin();
      Serial.println("HTTP server started");

      _ready = 1;
      return;
    }
    delay(250);
    return;
  }

  server.handleClient();
}

}

