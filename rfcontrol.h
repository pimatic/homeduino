#include <RFControl.h>

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
  char *arg;
  arg = sCmd.next();
  if(arg == NULL) {
    return;
  }
  if (strcmp(arg, "setup") == 0) {
    arg = sCmd.next();
    if(arg == NULL) {
      return;
    }
    int interrupt_pin = atoi(arg);
    RFControl::startReceiving(interrupt_pin);
    Serial.println("RF receiving");
  }
}


