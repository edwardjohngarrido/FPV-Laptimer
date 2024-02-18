#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "testwebserver";
const char* password = "123456789";

//create asyncwebserver object on port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
  <!DOCTYPE HTML><html>
  <h1>HELLO WORLD</h1>
  <h1>Android 1.8 IDE</h1>
  </html>
)rawliteral";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Start server
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}
