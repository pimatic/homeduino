
#include <DHTlib.h>

dht DHT;

void dht_command() {
    char* arg = sCmd.next();
    if(arg == NULL) {
        argument_error();
        return;
    }
    int dht_type = atoi(arg);
    arg = sCmd.next();
    if(arg == NULL) {
        argument_error();
        return;
    }
    int dht_pin = atoi(arg);

    int chk;
    // just the dht 11 sensor read function is different
    if (dht_type == 11) {
        chk = DHT.read11(dht_pin);
    } else {
        chk = DHT.read(dht_pin);
    }

    switch (chk) {
        case DHTLIB_OK:
            Serial.print("ACK ");
            Serial.print(DHT.temperature, 1);
            Serial.write(' ');
            Serial.print(DHT.humidity, 1);
            Serial.print("\r\n");
            break;
        case DHTLIB_ERROR_CHECKSUM:
            Serial.print("ERR checksum_error\r\n");
            break;
        case DHTLIB_ERROR_TIMEOUT:
            Serial.print("ERR timeout_error\r\n");
            break;
        default:
            Serial.print("ERR unknown_error\r\n");
            break;
    }
}