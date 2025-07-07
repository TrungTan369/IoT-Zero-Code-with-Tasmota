#include "globals.h"

void setup() {
    Serial.begin(115200);
    Serial.println("Hello user");
    LittleFS.begin();
    initWiFi();
    initMQTT();
}

void loop() {
    Wifi_reconnect();
    reconnectMQTT();
    delay(500);
}