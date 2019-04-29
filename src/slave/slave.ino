#include <GDBStub.h>
#define RED_LED 5 // Led in NodeMCU at pin GPIO16 (D0).
#define GREEN_LED 4
#define YELLOW_LED 12

void setup() {
pinMode(RED_LED, OUTPUT);    // LED pin as output.
pinMode(GREEN_LED, OUTPUT);
pinMode(YELLOW_LED, OUTPUT);
Serial.begin(115200);
Serial.print("hello world");
gdbstub_init();
}

void turn_color(int on, int off[]){
    // turn off LEDs
    for(int i=0; i < (sizeof(off)/sizeof(int)); i++){
	digitalWrite(off[i], LOW);
    }
    digitalWrite(on, HIGH);
}


void loop() {
    int red_on[] = { GREEN_LED, YELLOW_LED };
    int green_on[] = { RED_LED, YELLOW_LED};
    int yellow_on[] = { RED_LED, GREEN_LED};
    turn_color(RED_LED, red_on);
    delay(1000);
    turn_color(GREEN_LED, green_on);
    delay(1000);
    turn_color(YELLOW_LED, yellow_on);
    delay(1000);
}
