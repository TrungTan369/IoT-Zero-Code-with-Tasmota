
#include "globals.h"

void setup() {
    Serial.begin(115200);
    Serial.println("Hello user");
    initWiFi();
    initWebserver();
    initMQTT();
    initDHT20();
    initLight();
    initSoil();
    initDistance();
    initFan();
    initRelay();
    initLed();
    initLCD1602();
    initFSM();
    if (!SPIFFS.begin(true)) {
        Serial.println("Mount failed");
    }
}

void loop() {
    Wifi_reconnect();
    reconnectMQTT();
}