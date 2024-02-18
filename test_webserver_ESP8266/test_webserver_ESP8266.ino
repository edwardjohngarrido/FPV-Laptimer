/*
FPV Laptimer build by Edward John Garrido
*/
//Import required libraries.
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <LittleFS.h>

//ESP8266 OR ESP32 Asynchronous Web Server's SSID and Password
const char* ssid = "testwebserver";
const char* password = "123456789";

//create asyncwebserver object on port 80
AsyncWebServer server(80);

String processor(const String& var){
  Serial.println(var);
  return String();
  }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //Inititalize LittleFS
  if(!LittleFS.begin()){
    Serial.println("An Error has occured while mounting LittleFS");
    return;
    }

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
    request->send(LittleFS, "/index.html", String(), false, processor);
  });

  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/style.css", "text/css");
    });

  // Start server
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}
