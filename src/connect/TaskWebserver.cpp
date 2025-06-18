
#include "TaskWebserver.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void notifyClients() {
    String json = "{";
    json += "\"temp\":" + String(temp) + ",";
    json += "\"humi\":" + String(humi) + ",";
    json += "\"soil\":" + String(soil) + ",";
    json += "\"distance\":" + String(distance) + ",";
    json += "\"light\":" + String(light);
    json += "}";

    ws.textAll(json);
}

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
               AwsEventType type, void *arg, uint8_t *data, size_t len) {
    if (type == WS_EVT_CONNECT) {
        Serial.println("WebSocket client connected");
    } else if (type == WS_EVT_DISCONNECT) {
        Serial.println("WebSocket client disconnected");
    }
}

void initWebserver() {
    ws.onEvent(onWsEvent);
    server.addHandler(&ws);

    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

    server.begin();
}

void TaskWebServer(void *pvParameters) {
    while (1) {
        notifyClients();
        vTaskDelay(pdMS_TO_TICKS(1000));  // Gửi mỗi 1 giây
    }
}
