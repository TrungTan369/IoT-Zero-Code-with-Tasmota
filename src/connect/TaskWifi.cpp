#include "TaskWifi.h"

constexpr char AP_SSID[] = "ESP32_CONFIG";
constexpr char AP_PASSWORD[] = "87654321";

String ssid = "";
String password = "";
TaskHandle_t TaskLedBlinkHandle = NULL;
bool loadWiFiFromFS() {
    if (!LittleFS.begin()) {
        Serial.println("Failed to mount LittleFS");
        return false;
    }
    if (!LittleFS.exists("/wifi.json")) {
        Serial.println("wifi.json does not exist");
        return false;
    }
    File file = LittleFS.open("/wifi.json", "r");
    if (!file) {
        Serial.println("Failed to open wifi.json for reading");
        return false;
    }
    DynamicJsonDocument doc(256);
    DeserializationError error = deserializeJson(doc, file);
    file.close();
    if (error) {
        Serial.println("Failed to parse wifi.json");
        return false;
    }
    ssid = doc["ssid"].as<String>();
    password = doc["password"].as<String>();
    Serial.println("WiFi credentials loaded from FS");
    return true;
}

void setup_AP() {
    WiFi.softAP(AP_SSID, AP_PASSWORD);
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());
}
void setup_STA() {
    Serial.println("Connecting to AP ...");
    if (loadWiFiFromFS()) {
        WiFi.begin(ssid, password);
    }
    if (TaskLedBlinkHandle == NULL) {
        xTaskCreate(TaskLedBlink, "TaskLedBlink", 2048, NULL, 1, &TaskLedBlinkHandle);
    }
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    if (TaskLedBlinkHandle != NULL) {
        vTaskDelete(TaskLedBlinkHandle);
        TaskLedBlinkHandle = NULL;
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Connected to AP");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }
}
void initWiFi() {
    WiFi.mode(WIFI_AP_STA);
    setup_AP();
    setup_STA();
}
bool Wifi_reconnect() {
    const wl_status_t status = WiFi.status();
    if (status == WL_CONNECTED) {
        return true;
    }
    setup_STA();
    return true;
}