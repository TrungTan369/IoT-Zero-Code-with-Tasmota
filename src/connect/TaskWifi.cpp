#include "TaskWifi.h"

constexpr char AP_SSID[] = "ESP32_CONFIG";
constexpr char AP_PASSWORD[] = "87654321";

String ssid = "";
String password = "";
TaskHandle_t Task_Led_Indicate_NO_WIFI_Handle = NULL;
TaskHandle_t Task_Led_Indicate_NO_INTERNET_Handle = NULL;

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
    Serial.println("Connecting to WiFi ...");
    if (loadWiFiFromFS()) {
        WiFi.begin(ssid, password);
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Connected to AP");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }
}

void initWiFi() {
    pinMode(BOOT_BUTTON, INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);
    WiFi.mode(WIFI_STA);
    setup_STA();
}
void Wifi_reconnect() {
    const wl_status_t status = WiFi.status();
    // hold time out 3s -> off sta mode on ap mode
    if (digitalRead(BOOT_BUTTON) == 0) {
        uint32_t timepress = millis();
        while (digitalRead(BOOT_BUTTON) == 0) {
            if (millis() - timepress >= 3000) {
                Serial.println("Vào chế độ cấu hình AP");
                WiFi.disconnect(true);
                WiFi.mode(WIFI_AP);
                setup_AP();
                initWebserver();  // mở websocket để user vào config
                return;
            }
            delay(10);
        }
    }
    // ---------- NO WIFI
    if (status != WL_CONNECTED) {
        Serial.println("NO WIFI");
        if (Task_Led_Indicate_NO_WIFI_Handle == NULL) {
            xTaskCreate(
                Led_Indicate_NO_WIFI,
                "Led_Indicate_NO_WIFI",
                2048,
                NULL,
                1,
                &Task_Led_Indicate_NO_WIFI_Handle);
        }
        setup_STA();
    } else {
        if (Task_Led_Indicate_NO_WIFI_Handle != NULL) {
            vTaskDelete(Task_Led_Indicate_NO_WIFI_Handle);
            Task_Led_Indicate_NO_WIFI_Handle = NULL;
        }
    }
    // ------- STILL WIFI BUT NO INTERNET
    if (status == WL_CONNECTED && !client.connected()) {
        Serial.println("NO INTERNET");
        if (Task_Led_Indicate_NO_INTERNET_Handle == NULL) {
            xTaskCreate(
                Led_Indicate_NO_INTERNET,
                "Led_Indicate_NO_INTERNET",
                2048,
                NULL,
                1,
                &Task_Led_Indicate_NO_INTERNET_Handle);
        }
    } else {
        if (Task_Led_Indicate_NO_INTERNET_Handle != NULL) {
            vTaskDelete(Task_Led_Indicate_NO_INTERNET_Handle);
            Task_Led_Indicate_NO_INTERNET_Handle = NULL;
        }
    }
}
