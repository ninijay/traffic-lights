#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <GDBStub.h>
#include "../../lib/src/stlpp.h"
#include "../../lib/src/stlpp.c"
#define RED_LED D1 // Led in NodeMCU at pin GPIO16 (D0).
#define GREEN_LED D2
#define YELLOW_LED D7

const char* light = "lights/1";
const char* ssid="traffic-light-poc";
const char* password="traffic2019";
const char* mqtt_broker="192.168.4.1";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Received message [");
    Serial.print(topic);
    Serial.print("] ");
    char msg[length+1];
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
        msg[i] = (char)payload[i];
    }
    Serial.println();

    msg[length] = '\0';
    Serial.println(msg);
}

void setup() {
    pinMode(RED_LED, OUTPUT);    // LED pin as output.
    pinMode(GREEN_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    Serial.begin(115200);
    Serial.print("hello world");
    gdbstub_init();
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);

    // setup wifi
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // setup MQTT
    client.setServer(mqtt_broker, 1883);
    client.setCallback(callback);
}

void turn_green(){
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
}

void turn_yellow(){
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
}

void turn_red(){
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
}

void turn_light(STLPP *p){
    switch(p->n_state){
	case RED: 
	    turn_red();
	    break;
	case GREEN:
	    turn_green();
	    break;
	case RED_YELLOW:
	case GREEN_YELLOW:
	    turn_yellow();
	    break;
	default:
	    turn_red();
	    break;
    }
}


void reconnect() {
    while (!client.connected()) {
        Serial.print("Reconnecting...");
        if (!client.connect("ESP8266Client")) {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" retrying in 5 seconds");
            delay(5000);
        }
    }
    client.subscribe(light);
}

void loop() {
    turn_red();
    delay(1000);
    turn_green();
    delay(1000);
    turn_yellow();
    delay(1000);

    // test packet
    uint8_t x= 7;
    STLPP* p = makeSTLPP(x, x, RED, GREEN);
    Serial.println(serializeSTLPP(p));
    p = makeSTLPP(serializeSTLPP(p));
    Serial.println(serializeSTLPP(p));
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
}
