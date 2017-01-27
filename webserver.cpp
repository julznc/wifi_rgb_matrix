
#include "webserver.h"
#include "rgbmatrix.h"

namespace web
{

static const char* ssid = "yusmeann_wifi";
static const char* password = "j03m05c15";

static RGBMatrix *_display = NULL;
static char _ready = 0;
static IPAddress _ip;

static const char *indexhtml = "<html>"
"<head>"
"<title>"
"WiFi RGB"
"</title>"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
"</head>"
"<style media=\"screen\" type=\"text/css\">"
".formbox{border:2px #CCC solid;padding:0.5em 1em;margin:0.5em 1em;}"
".textbox{width:75%;}"
"</style>"
"<body>"
"<h2>WiFi RGB Matrix</h2>"
"<form action=\"/text\" method=\"post\" class=\"formbox\">"
"Text: <input type=\"text\" name=\"text\" maxlength=\"256\" class=\"textbox\"></input><br/>"
"Color: <input type=\"color\" name=\"color\" value=\"#ffffff\"></input><br/>"
"<button type=\"submit\">Set</button>"
"</form>"
"<form action=\"/brightness\" method=\"post\" class=\"formbox\">"
"Brightness:"
"<input type=\"number\" min=\"0\" max=\"255\" value=\"18\" name=\"brightness\"required></input>"
"<button type=\"submit\">Set</button>"
"</form>"
"<form action=\"/bitmap\" method=\"post\" class=\"formbox\">"
"<input type=\"radio\" name=\"bitmap\" value=\"0\" onclick=\"this.form.submit();\">\"THANKS\"</input><br/><br/>"
"<input type=\"radio\" name=\"bitmap\" value=\"1\" onclick=\"this.form.submit();\">\"BABY ON CAR\"</input><br/><br/>"
"<input type=\"radio\" name=\"bitmap\" value=\"2\" onclick=\"this.form.submit();\">\"STOP\"</input><br/>"
"</form>"
"<form action=\"/animate\" method=\"post\" class=\"formbox\">"
"<input type=\"radio\" name=\"animate\" value=\"0\" onclick=\"this.form.submit();\">Random</input><br/>"
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
  if (server.arg("text").length())
    _display->setText(server.arg("text"));
  //Serial.println(server.arg("color"));
  if (server.arg("color").length())
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

void handleBitmap() {
  if (!server.hasArg("bitmap"))
    return handleFail("BAD ARGS");
  //Serial.println(server.arg("bitmap"));
  _display->showBitmap(server.arg("bitmap").toInt());
  handleRoot();
}

void handleAnimate() {
  if (!server.hasArg("animate"))
    return handleFail("BAD ARGS");
  //Serial.println(server.arg("animate"));
  _display->showAnimation(server.arg("animate").toInt());
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
  server.on("/bitmap", handleBitmap);
  server.on("/animate", handleAnimate);
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
      
      if (MDNS.begin("esp8266", _ip)) {
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

