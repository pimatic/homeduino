#include <RFControl.h>

void rfcontrol_command_send();
void rfcontrol_command_receive();

void rfcontrol_setup() {

}

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
      Serial.write(' ');
      for(unsigned int i=0; i < timings_size; i++) {
          Serial.write('0' + timings[i]);
      }
      Serial.write('\n');
      RFControl::continueReceiving();
    }
}

void rfcontrol_command() {
  char* arg = sCmd.next();
  if(arg == NULL) {
    return;
  }
  if (strcmp(arg, "send") == 0) {
    rfcontrol_command_send();
  } else if (strcmp(arg, "receive") == 0) {
    rfcontrol_command_receive();
  }
}

void rfcontrol_command_receive() {
  char* arg = sCmd.next();
  if(arg == NULL) {
    return;
  }
  int interrupt_pin = atoi(arg);
  RFControl::startReceiving(interrupt_pin);
  Serial.println("RF receiving");
}


void rfcontrol_command_send() {
  char* arg = sCmd.next();
  if(arg == NULL) {
    return;
  }
  int transmitter_pin = atoi(arg);

  // read pulse lengths
  unsigned int buckets[8];
  for(unsigned int i = 0; i < 8; i++) {
    arg = sCmd.next();
    if(arg == NULL) {
      return;
    }
    buckets[i] = atoi(arg);
  }
  //read pulse sequence
  arg = sCmd.next();
  if(arg == NULL) {
    return;
  }
  unsigned int timings_size = strlen(arg);
  unsigned int timings[timings_size];
  for(unsigned int i = 0; i < timings_size; i++) {
    unsigned int index = arg[i] - '0';
    timings[i] = buckets[index];
  }
  RFControl::sendByTimings(transmitter_pin, timings, timings_size);
  Serial.println("RF send");
}