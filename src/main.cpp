
#include "globals.h"

void setup() {
    Serial.begin(115200);
    initWebserver();
    initMQTT();
    initDHT20();
    initLight();
    initSoil();
    initDistance();
}

void loop() {
    if (!Wifi_reconnect()) {
        return;
    }
    reconnectMQTT();
}