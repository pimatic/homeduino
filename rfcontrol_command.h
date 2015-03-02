#include <RFControl.h>


int interrupt_pin = -1;

void rfcontrol_command_send();
void rfcontrol_command_receive();

void rfcontrol_loop() {
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
      for(unsigned int i=0; i < timings_size; i++) {
          Serial.write('0' + timings[i]);
      }
      Serial.print("\r\n");
      RFControl::continueReceiving();
    }
}

void rfcontrol_command() {
  char* arg = sCmd.next();
  if(arg == NULL) {
    argument_error();
    return;
  }
  if (strcmp(arg, "send") == 0) {
    rfcontrol_command_send();
  } else if (strcmp(arg, "receive") == 0) {
    rfcontrol_command_receive();
  } else {
    argument_error();
  }
}

void rfcontrol_command_receive() {
  char* arg = sCmd.next();
  if(arg == NULL) {
    argument_error();
    return;
  }
  interrupt_pin = atoi(arg);
  RFControl::startReceiving(interrupt_pin);
  Serial.print("ACK\r\n");
}


void rfcontrol_command_send() {
  char* arg = sCmd.next();
  if(arg == NULL) {
    argument_error();
    return;
  }
  int transmitter_pin = atoi(arg);

  arg = sCmd.next();
  if(arg == NULL) {
    argument_error();
    return;
  }
  int repeats = atoi(arg);

  // read pulse lengths
  unsigned int buckets[8];
  for(unsigned int i = 0; i < 8; i++) {
    arg = sCmd.next();
    if(arg == NULL) {
      argument_error();
      return;
    }
    buckets[i] = atoi(arg); 
  }
  //read pulse sequence
  arg = sCmd.next();
  if(arg == NULL) {
    argument_error();
    return;
  }
  RFControl::sendByCompressedTimings(transmitter_pin, buckets, arg, repeats);
  Serial.print("ACK\r\n");
}
