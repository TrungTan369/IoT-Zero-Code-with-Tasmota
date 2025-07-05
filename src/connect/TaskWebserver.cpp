#include "TaskWebserver.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

String getSensorJson() {
    String json = "{";
    json += "\"temp\":" + String(10) + ",";
    json += "\"humi\":" + String(10) + ",";
    json += "\"soil\":" + String(10) + ",";
    json += "\"distance\":" + String(10) + ",";
    json += "\"light\":" + String(10) + ",";
    json += "\"mode\":" + String(led_mode ? 1 : 0);
    json += "}";
    return json;
}
bool saveWiFiToFS(const String &ssid, const String &password) {
    DynamicJsonDocument doc(256);
    doc["ssid"] = ssid;
    doc["password"] = password;

    File file = LittleFS.open("/wifi.json", "w");
    if (!file) {
        Serial.println("Failed to open wifi.json for writing");
        return false;
    }
    if (serializeJson(doc, file) == 0) {
        Serial.println("Failed to write to wifi.json");
        file.close();
        return false;
    }
    file.close();
    Serial.println("WiFi credentials saved to FS");
    return true;
}
void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
               void *arg, uint8_t *data, size_t len) {
    if (type == WS_EVT_CONNECT) {
        client->text(getSensorJson());
    } else if (type == WS_EVT_DATA) {
        AwsFrameInfo *info = (AwsFrameInfo *)arg;
        if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
            String msg = String((char *)data);
            if (msg == "get_data") {
                client->text(getSensorJson());
            } else if (msg.startsWith("mode_switch:")) {
                Serial.println("[WS] Nhận mode_switch: " + String(led_mode));
                led_mode = msg.substring(12).toInt();
                ws.textAll(getSensorJson());
            } else if (msg.startsWith("color:")) {
                String color = msg.substring(6);
                if (color == "red")
                    led_color = red;
                else if (color == "orange")
                    led_color = orange;
                else if (color == "yellow")
                    led_color = yellow;
                else if (color == "green")
                    led_color = green;
                else if (color == "blue")
                    led_color = blue;
                else if (color == "indigo")
                    led_color = indigo;
                else if (color == "purple")
                    led_color = purple;
                else if (color == "white")
                    led_color = white;
                else if (color == "black")
                    led_color = black;
            } else if (msg.startsWith("wifi:")) {
                DynamicJsonDocument doc(256);
                DeserializationError err = deserializeJson(doc, msg.substring(5));
                if (!err) {
                    ssid = doc["ssid"].as<String>();
                    password = doc["password"].as<String>();
                    saveWiFiToFS(ssid, password);
                    ESP.restart();
                }
            }
        }
    }
}

void handleRoot(AsyncWebServerRequest *request) {
    request->send(LittleFS, "/index.html", "text/html");
}

void setupOTA(AsyncWebServer &server) {
    server.on("/update", HTTP_POST, [](AsyncWebServerRequest *request) {
        bool shouldReboot = !Update.hasError();
        request->send(200, "text/html", shouldReboot ? "OK" : "FAIL");
        if (shouldReboot) {
            delay(1000);
            ESP.restart();
        } }, [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
        if (!index) {
            Update.begin(UPDATE_SIZE_UNKNOWN);
        }
        Update.write(data, len);
        if (final) {
            Update.end(true);
        } });
}
void initWebserver() {
    ws.onEvent(onWsEvent);
    server.addHandler(&ws);
    server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");
    server.begin();
    setupOTA(server);
    Serial.println("WebServer + WebSocket started");
}
