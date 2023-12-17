#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <WebServer.h>
 
WebServer server(80);
const int led = 13;

void handleRoot() {
  Serial.println("handle root called");
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp32!");
  digitalWrite(led, 0);
}

void handleCMD() {
  digitalWrite(led, 1);
  delay(1000);
  Serial.println("handle cmd called");
  server.send(200, "text/plain", "hello from esp32!");
  digitalWrite(led, 0);
}

void setup() {
    pinMode(led, OUTPUT);
    digitalWrite(led, 0);
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    // it is a good practice to make sure your code sets wifi mode how you want it.
 
    // put your setup code here, to run once:
    Serial.begin(115200);
    
    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;

 
    bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
    res = wm.autoConnect("AutoConnectAP","password"); // password protected ap
    // wm.resetSettings();
 
    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");

        server.on("/", handleRoot);
        server.on("/cmd", HTTP_POST, handleCMD);
        server.begin();
        Serial.println("HTTP server started");
    }
 
}
 
void loop() {
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks  
}
