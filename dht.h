
#include <DHTlib.h>

dht DHT;

void dht_command() {
    char* arg = sCmd.next();
    if(arg == NULL) {
        return;
    }
    int dht_type = atoi(arg);
    arg = sCmd.next();
    if(arg == NULL) {
        return;
    }
    int dht_pin = atoi(arg);

    // just the dht 11 sensor read function is different
    int chk;
    if (dht_type == 11) {
        chk = DHT.read11(dht_pin);
    } else {
        chk = DHT.read(dht_pin);
    }

    switch (chk) {
        case DHTLIB_OK:
            Serial.print("DHT data ");
            Serial.print(dht_pin);
            Serial.write(' ');
            Serial.print(DHT.temperature, 1);
            Serial.write(' ');
            Serial.print(DHT.humidity, 1);
            Serial.write('\n');
            break;
        case DHTLIB_ERROR_CHECKSUM:
            Serial.print("DHT checksum_error ");
            Serial.print(dht_pin);
            Serial.write('\n');
            break;
        case DHTLIB_ERROR_TIMEOUT:
            Serial.print("DHT timeout_error ");
            Serial.print(dht_pin);
            Serial.write('\n');
            break;
        default:
            Serial.print("DHT unknown_error ");
            Serial.print(dht_pin);
            Serial.write('\n');
            break;
    }
}