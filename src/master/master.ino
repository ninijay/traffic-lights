#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include "uMQTTBroker.h"

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
    myBroker.publish("controller/counter", (String)counter++);
    Serial.println("send message");
    delay(1000);
    char* data=(char*)malloc(256);
    data="test\0";
    Serial.println(data);
    myBroker.onData("controller/counter", data, 256);
    Serial.println(data);
}
