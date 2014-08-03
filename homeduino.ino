#include <SerialCommand.h>

SerialCommand sCmd;

#include "rfcontrol.h"
#include "keypad.h"
#include "ping.h"
#include "dht.h"

void unrecognized(const char *command);

void setup() {
	Serial.begin(9600);
	// Setup rfcontrol
	rfcontrol_setup();
	// Setup keypad
	keypad_setup();
	// Setup callbacks for SerialCommand commands
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

// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command) {
	Serial.println("error unknown_command");
}
