
#include "globals.h"

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("CC");
    initDHT20();
    initMQTT();
    // InitWebserver();
}

void loop() {
    // if (!Wifi_reconnect()) {
    //     return;
    // }
    //reconnectMQTT();
}