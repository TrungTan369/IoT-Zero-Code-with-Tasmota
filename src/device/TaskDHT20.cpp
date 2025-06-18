#include "TaskDHT20.h"

DHT20 dht20;
float temp;
float humi;
void TaskDHT20(void *pvParameters) {
    while (true) {
        if (dht20.read() == DHT20_OK) {
            temp = dht20.getTemperature();
            humi = dht20.getHumidity();
            publishData("temp", String(temp));
            publishData("humi", String(humi));
            Serial.print("temp: ");
            Serial.print(temp);
            Serial.print("\t humi: ");
            Serial.println(humi);
        } else {
            Serial.println("Failed to read DHT20 sensor.");
        }
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}

void initDHT20() {
    Wire.begin(SDA, SCL);
    dht20.begin();
    xTaskCreate(TaskDHT20, "TaskDHT20", 4096, NULL, 1, NULL);
}