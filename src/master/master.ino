#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include "uMQTTBroker.h"
#include "../../lib/src/stlpp.h"
#include "../../lib/src/stlpp.c"

const char* ssid = "traffic-light-poc";
const char* password = "traffic2019";
const char* mqtt_broker = "192.168.4.1";

uMQTTBroker myBroker;

void setup(void){
  Serial.begin(115200);
  WiFi.softAP(ssid, password); //begin WiFi access point

  Serial.println(WiFi.localIP());
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  myBroker.init();
  myBroker.subscribe("#");
}

int counter=0;

void loop(void){
    myBroker.publish("lights/1", serializeSTLPP(makeSTLPP(0, 1, EMPTY, RED))); 
    Serial.println("send message");
    delay(1000);
}
