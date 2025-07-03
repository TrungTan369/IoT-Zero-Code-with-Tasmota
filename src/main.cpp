
#include "globals.h"

void setup() {
    Serial.begin(115200);
    Serial.println("Hello user");
    LittleFS.begin();
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
}

void loop() {
    Wifi_reconnect();
    reconnectMQTT();
}