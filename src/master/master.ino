#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include "uMQTTBroker.h"
#include "../../lib/src/stlpp.h"
#include "../../lib/src/stlpp.c"

const char* ssid = "traffic-light-poc";
const char* password = "traffic2019";
const char* mqtt_broker = "192.168.4.1";
void light1(STLPP* p);
class myMQTTBroker: public uMQTTBroker{
    public:
	virtual void onData(String topic, const char *data, uint32_t length){
	    char data_str[length+1];
	    os_memcpy(data_str, data, length);
	    data_str[length] = '\0';
	    Serial.println("received topic '"+topic+"' with data '"+(String)data_str+"'");
	    light1(makeSTLPP(data_str));
	}

};

myMQTTBroker myBroker;

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
  myBroker.publish("lights/1", serializeSTLPP(makeSTLPP(0, 1, EMPTY, RED))); 
}



void light1(STLPP* p){
    char* channel = "lights/1";
    if(p->s_id != 1)
	return;
    switch(p->c_state){
	case RED:
	    delay(2000);
	    p->n_state = RED_YELLOW;
	    break;
	case RED_YELLOW:
	    delay(1000);
	    p->n_state = GREEN;
	    break;
	case GREEN:
	    delay(4000);
	    p->n_state = GREEN_YELLOW;
	    break;
	case GREEN_YELLOW:
	    delay(1000);
	    p->n_state = RED;
	    break;
	default:
	    p->n_state = RED;
	    break;
    }
    Serial.println(serializeSTLPP(p));
    myBroker.publish(channel, serializeSTLPP(p));
}


int counter=0;

void loop() {
    myBroker.publish("lights/1", "0|1|7|1");
    delay(32000);
}

