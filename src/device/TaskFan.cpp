#include "TaskFan.h"

void TaskFan(void *pvParameters) {
    while (1) {
        digitalWrite(fan_pin, 1);
        Serial.println("Fan on");
        vTaskDelay(pdMS_TO_TICKS(1000));
        digitalWrite(fan_pin, 0);
        Serial.println("Fan off");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
void initFan() {
    pinMode(fan_pin, OUTPUT);
    xTaskCreate(TaskFan, "TaskFan", 2048, NULL, 1, NULL);
}