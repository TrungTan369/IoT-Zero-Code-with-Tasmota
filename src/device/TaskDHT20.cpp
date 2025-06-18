#include "TaskDHT20.h"

DHT20 dht20;

void TaskDHT20(void *pvParameters) {
    while (true) {
        if (dht20.read() == DHT20_OK) {
            float t = dht20.getTemperature();
            float h = dht20.getHumidity();
            publishData("temp", String(t));
            publishData("humi", String(h));
            Serial.print("temp: ");
            Serial.print(t);
            Serial.print("\t humi: ");
            Serial.println(h);
        } else {
            Serial.println("Failed to read DHT20 sensor.");
        }
        vTaskDelay(delay_time / portTICK_PERIOD_MS);
    }
}

void initDHT20() {
    Wire.begin(SDA, SCL);
    dht20.begin();
    xTaskCreate(
        TaskDHT20,    // Function to implement the task
        "TaskDHT20",  // Name of the task
        4096,         // Stack size in words
        NULL,         // Task input parameter
        1,            // Priority of the task
        NULL          // Task handle
    );
}