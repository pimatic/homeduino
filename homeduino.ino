#include <SerialCommand.h>

SerialCommand sCmd;

#include "rfcontrol.h"
#include "keypad.h"
#include "ping.h"
#include "dht.h"

void digital_read_command();
void digital_write_command();
void analog_read_command();
void analog_write_command();
void pin_mode_command();
void unrecognized(const char *command);

void setup() {
	Serial.begin(9600);
	// Setup rfcontrol
	rfcontrol_setup();
	// Setup keypad
	keypad_setup();
	// Setup callbacks for SerialCommand commands
	sCmd.addCommand("DR", digital_read_command);
	sCmd.addCommand("DW", digital_write_command);
	sCmd.addCommand("AR", analog_read_command);
	sCmd.addCommand("AW", analog_write_command);
	sCmd.addCommand("PM", pin_mode_command);
	sCmd.addCommand("RF", rfcontrol_command);    
	sCmd.addCommand("PING", ping_command);
	sCmd.addCommand("DHT", dht_command);
	sCmd.setDefaultHandler(unrecognized);
	Serial.println("ready");
}

void loop() {
	// handle serial command
	sCmd.readSerial();
	// handle rf control receiving
	rfcontrol_loop();
	// handle keypad keypress
	keypad_loop();
}

void digital_read_command() {
	char* arg = sCmd.next();
  	if(arg == NULL) {
    	return;
  	}
  	int pin = atoi(arg);
  	int val = digitalRead(pin);
  	Serial.print("DR ");
  	Serial.write('0' + val);
  	Serial.write('\n');
}

void analog_read_command() {
	char* arg = sCmd.next();
  	if(arg == NULL) {
    	return;
  	}
  	int pin = atoi(arg);
  	int val = digitalRead(pin);
  	Serial.print("DR ");
  	Serial.print(val);
  	Serial.write('\n');
}

void digital_write_command() {
	char* arg = sCmd.next();
  	if(arg == NULL) {
    	return;
  	}
  	int pin = atoi(arg);
  	arg = sCmd.next();
  	if(arg == NULL) {
    	return;
  	}
  	int val = atoi(arg);
  	digitalWrite(pin, val);
  	Serial.print("DW\n");
}

void analog_write_command() {
	char* arg = sCmd.next();
  	if(arg == NULL) {
    	return;
  	}
  	int pin = atoi(arg);
  	arg = sCmd.next();
  	if(arg == NULL) {
    	return;
  	}
  	int val = atoi(arg);
  	analogWrite(pin, val);
  	Serial.print("AW\n");
}

void pin_mode_command() {
	char* arg = sCmd.next();
  	if(arg == NULL) {
    	return;
  	}
  	int pin = atoi(arg);
  	arg = sCmd.next();
  	if(arg == NULL) {
    	return;
  	}
  	// INPUT 0x0
	// OUTPUT 0x1
  	int mode = atoi(arg);
  	pinMode(pin, mode);
    Serial.print("PM\n");	
}


// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command) {
	Serial.println("error unknown_command");
}
