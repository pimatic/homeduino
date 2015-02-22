#include <SerialCommand.h>
#include <OneWire.h>
#include <DallasTemperature.h>

void argument_error();

SerialCommand sCmd;

#include "rfcontrol.h"
#ifdef KEYPAD_ENABLED
#include "keypad.h"
#endif
#include "ping.h"
#include "dht.h"


void digital_read_command();
void digital_write_command();
void analog_read_command();
void analog_write_command();
void reset_command();
void pin_mode_command();
void unrecognized(const char *command);
void dst_command();

OneWire oneWire(99);                 // Setup a oneWire instance - use dummy pin here
DallasTemperature sensors(&oneWire);

void setup() {
	sensors.begin();

	Serial.begin(115200);
	// Setup callbacks for SerialCommand commands
	sCmd.addCommand("DR", digital_read_command);
	sCmd.addCommand("DW", digital_write_command);
	sCmd.addCommand("AR", analog_read_command);
	sCmd.addCommand("AW", analog_write_command);
	sCmd.addCommand("PM", pin_mode_command);
	sCmd.addCommand("RF", rfcontrol_command);    
	sCmd.addCommand("PING", ping_command);
	sCmd.addCommand("DHT", dht_command);
	sCmd.addCommand("DST", dst_command);
	sCmd.addCommand("RESET", reset_command);
#ifdef KEYPAD_ENABLED
	sCmd.addCommand("K", keypad_command);
#endif
	sCmd.setDefaultHandler(unrecognized);
	Serial.print("ready\r\n");
}

void loop() {
	// handle serial command
	sCmd.readSerial();
	// handle rf control receiving
	rfcontrol_loop();
  #ifdef KEYPAD_ENABLED
	// handle keypad keypress
	keypad_loop();
  #endif
}

void digital_read_command() {
	char* arg = sCmd.next();
  	if(arg == NULL) {
  		argument_error();
    	return;
  	}
  	int pin = atoi(arg);
  	int val = digitalRead(pin);
  	Serial.print("ACK ");
  	Serial.write('0' + val);
  	Serial.print("\r\n");
}

void analog_read_command() {
	char* arg = sCmd.next();
  	if(arg == NULL) {
  		argument_error();
    	return;
  	}
  	int pin = atoi(arg);
  	int val = analogRead(pin);
  	Serial.print("ACK ");
  	Serial.print(val);
  	Serial.print("\r\n");
}

void digital_write_command() {
	char* arg = sCmd.next();
  	if(arg == NULL) {
  		argument_error();
    	return;
  	}
  	int pin = atoi(arg);
  	arg = sCmd.next();
  	if(arg == NULL) {
  		argument_error();
    	return;
  	}
  	int val = atoi(arg);
  	digitalWrite(pin, val);
  	Serial.print("ACK\r\n");
}

void analog_write_command() {
	char* arg = sCmd.next();
  	if(arg == NULL) {
  		argument_error();
    	return;
  	}
  	int pin = atoi(arg);
  	arg = sCmd.next();
  	if(arg == NULL) {
  		argument_error();
    	return;
  	}
  	int val = atoi(arg);
  	analogWrite(pin, val);
  	Serial.print("ACK\r\n");
}

void pin_mode_command() {
	char* arg = sCmd.next();
  	if(arg == NULL) {
  		argument_error();
    	return;
  	}
  	int pin = atoi(arg);
  	arg = sCmd.next();
  	if(arg == NULL) {
  		argument_error();
    	return;
  	}
  	// INPUT 0x0
	// OUTPUT 0x1
  	int mode = atoi(arg);
  	pinMode(pin, mode);
    Serial.print("ACK\r\n");	
}

void reset_command() {
  RFControl::stopReceiving();
  Serial.print("ready\r\n");
}

void argument_error() {
	Serial.print("ERR argument_error\r\n");
}
// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command) {
	Serial.print("ERR unknown_command\r\n");
}

void dst_command(){

  // param1 is oneWire_pin
  char* arg = sCmd.next();
  if (arg == NULL) {
    argument_error();
    return;
  }
  int oneWire_pin = atoi(arg);

  // param2 is sensor_number
  arg = sCmd.next();
  if (arg == NULL) {
    argument_error();
    return;
  }
  int sensor_number = atoi(arg);

  // param3 is precision
  arg = sCmd.next();
  if (arg == NULL) {
    argument_error();
    return;
  }
  int precision = atoi(arg);

  //-----------------

  OneWire oneWire(oneWire_pin);                // Setup a oneWire instance - use real pin
  DallasTemperature sensors(&oneWire);         // Pass our oneWire reference to Dallas Temperature
  sensors.begin();                             // Start up temp sensor
  sensors.setResolution(precision);            // 9 bit is better, aprox. 100ms to data adquire
                                               // 12 bit is high precision: 0.06 deg C, but slow (750ms)
                                               
  sensors.requestTemperatures(); 
  double temp = sensors.getTempCByIndex(sensor_number); 

  //-----
  // response without check errors would be:
  //  Serial.print("ACK ");
  //  Serial.print(temp, 1);
  //  Serial.print("\r\n");
  //-----
  // response with check errors and address sensor:
  int numberOfDevices = sensors.getDeviceCount();
  if (numberOfDevices == 0) {
    Serial.print("ERR No devices connected to the oneWire_pin\r\n");
  } else if (sensor_number + 1 > numberOfDevices) {
    Serial.print("ERR Error sensor_number\r\n");
  } else if (precision < 9 or precision > 12) {
    Serial.print("ERR Error precision\r\n");
  } else if (temp == DEVICE_DISCONNECTED) {   // DEVICE_DISCONNECTED = -127.00
    Serial.print("ERR Error device disconnected\r\n");
  } else {
    Serial.print("ACK ");
    Serial.print(temp, 1);
    //*(2)
    Serial.print(" ");
    //Serial.print(" ---- sensor_number=");
    Serial.print(sensor_number);
    Serial.print(" ");
    //Serial.print(" sensor_address=");
    DeviceAddress sensor_address;
    sensors.getAddress(sensor_address, sensor_number);
    for (uint8_t i = 0; i < 8; i++)
    {
      if (sensor_address[i] < 16) Serial.print("0");
      Serial.print(sensor_address[i], HEX);
    }
    //*(2)
    Serial.print("\r\n");
  }
  //-----
}


