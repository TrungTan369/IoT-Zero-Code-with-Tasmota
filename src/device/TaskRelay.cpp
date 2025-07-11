#include "TaskRelay.h"

void TaskRelay(void *pvParameters) {
    while (1) {
        digitalWrite(relay_pin, 1);
        vTaskDelay(pdMS_TO_TICKS(1000));
        digitalWrite(relay_pin, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void initRelay() {
    pinMode(relay_pin, OUTPUT);
    xTaskCreate(TaskRelay, "TaskRelay", 2048, NULL, 1, NULL);
}