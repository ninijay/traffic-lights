#include <GDBStub.h>
#include "../../lib/src/stlpp.h"
#define RED_LED D1 // Led in NodeMCU at pin GPIO16 (D0).
#define GREEN_LED D2
#define YELLOW_LED D7

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

void loop() {
    int red_on[] = { GREEN_LED, YELLOW_LED };
    int green_on[] = { RED_LED, YELLOW_LED};
    int yellow_on[] = { RED_LED, GREEN_LED};
    turn_red();
    delay(1000);
    turn_green();
    delay(1000);
    turn_yellow();
    delay(1000);
}
