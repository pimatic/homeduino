#include <SerialCommand.h>
#include <Keypad.h>
#include <RFControl.h>

SerialCommand sCmd;

void on_hello();
void on_rf();
void unrecognized(const char *command);

void handle_rfcontrol();

void setup() {
	Serial.begin(9600);

	// Setup callbacks for SerialCommand commands
	sCmd.addCommand("HE", on_hello);
	sCmd.addCommand("RF", on_rf);    
	sCmd.setDefaultHandler(unrecognized);
	Serial.println("ready");
}

void loop() {
	// handle serial command
	sCmd.readSerial();
	// handle rf control receiving
	handle_rfcontrol();
}

void handle_rfcontrol() {
	if(RFControl::hasData()) {
    	unsigned int *timings;
    	unsigned int timings_size;
    	RFControl::getRaw(&timings, &timings_size);
    	unsigned int buckets[8];
    	RFControl::compressTimings(buckets, timings, timings_size);
    	Serial.print("RF receive ");
    	for(unsigned int i=0; i < 8; i++) {
      		Serial.print(buckets[i]);
      		Serial.write(' ');
    	}
    	Serial.write(' ');
    	for(unsigned int i=0; i < timings_size; i++) {
      		Serial.write('0' + timings[i]);
    	}
    	Serial.write('\n');
    	RFControl::continueReceiving();
  	}
}

void on_hello() {
	char *arg;
	Serial.print("hello ");
	arg = sCmd.next();
	if (arg != NULL) {
		Serial.println(arg);
	}
}

void on_rf() {
	char *arg;
	arg = sCmd.next();
	if(arg == NULL) {
		return;
	}
	if (strcmp(arg, "setup")) {
		arg = sCmd.next();
		if(arg == NULL) {
			return;
		}
		int interrupt_pin = atoi(arg);
		RFControl::startReceiving(interrupt_pin);
		Serial.write("RF receiving");
	}
}

// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command) {
	Serial.println("error unknown_command");
}
