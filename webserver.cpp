
#include "webserver.h"
#include "rgbmatrix.h"

namespace web
{

// connect to a router
static const char *ssid = "yusmeann_wifi";
static const char *password = "j03m05c15";

// soft access point (as backup)
static const char *softAPssid = "rgb-matrix";
static const char *softAPpassword = "12345678";

static RGBMatrix *_display = NULL;
static char _ready = 0;
static IPAddress _ip;
static IPAddress _soft_ip;

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

void redirectToRoot(void)
{
  server.sendHeader("Location", "/", true);
  server.send ( 302, "text/plain", "");
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
  redirectToRoot();
}

void handleBrightness() {
  if (!server.hasArg("brightness"))
    return handleFail("BAD ARGS");
  //Serial.println(server.arg("brightness"));
  _display->SetBrightness(server.arg("brightness").toInt());
  redirectToRoot();
}

void handleBitmap() {
  if (!server.hasArg("bitmap"))
    return handleFail("BAD ARGS");
  //Serial.println(server.arg("bitmap"));
  _display->showBitmap(server.arg("bitmap").toInt());
  redirectToRoot();
}

void handleAnimate() {
  if (!server.hasArg("animate"))
    return handleFail("BAD ARGS");
  //Serial.println(server.arg("animate"));
  _display->showAnimation(server.arg("animate").toInt());
  redirectToRoot();
}

void handleNotFound(){
  server.send(404, "text/plain", "Not Found");
}

void init(void)
{
  WiFi.softAP(softAPssid, softAPpassword);
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

static int connect_timeout_count = 10*4; // seconds * (1/250ms)
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
    } else if (--connect_timeout_count < 0) {
      _soft_ip = WiFi.softAPIP();
      Serial.print("Soft AP: ");
      Serial.println(_soft_ip);
      String softAP_info = String("AP") + String(_soft_ip[2]) + "." + String(_soft_ip[3]);
      _display->setText(softAP_info);

      server.begin();
      Serial.println("HTTP server started");

      _ready = 1;
    }
    delay(250);
    return;
  }

  server.handleClient();
}

}

