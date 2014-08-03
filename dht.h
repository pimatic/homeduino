
#include <DHTlib.h>

dht DHT;

void dht_command() {
    char* arg = sCmd.next();
    if(arg == NULL) {
        return;
    }
    int dht_pin = atoi(arg);
    int chk = DHT.read22(dht_pin);

    switch (chk)
    {
    case DHTLIB_OK:
        Serial.print("DHT data ");
        Serial.print(dht_pin);
        Serial.write(' ');
        Serial.print(DHT.temperature, 1);
        Serial.write(' ');
        Serial.print(DHT.humidity, 1);
        break;
    case DHTLIB_ERROR_CHECKSUM:
        Serial.print("DHT checksum_error ");
        Serial.print(dht_pin);
        break;
    case DHTLIB_ERROR_TIMEOUT:
        Serial.print("DHT timeout_error ");
        Serial.print(dht_pin);
        break;
    default:
        Serial.print("DHT unknown_error ");
        Serial.print(dht_pin);
        break;
    }
}