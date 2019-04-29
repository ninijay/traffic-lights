#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// Replace with your network credentials
const char* ssid = "traffic-light-poc";
const char* password = "traffic2019";


void setup(void){
  Serial.begin(115200);
  WiFi.softAP(ssid, password); //begin WiFi access point

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
}

void loop(void){
}
