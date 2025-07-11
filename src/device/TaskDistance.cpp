#include "TaskDistance.h"

uint8_t distance;

void TaskDistance(void *pvParameters) {
    while (1) {
        digitalWrite(trig, LOW);
        vTaskDelay(pdMS_TO_TICKS(2));
        digitalWrite(trig, HIGH);
        vTaskDelay(pdMS_TO_TICKS(10));
        digitalWrite(trig, LOW);
        long duration = pulseIn(echo, HIGH);
        if (duration > 0) {
            distance = int(duration / 2 / 29.412);
        } else {
            distance = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

void initDistance() {
    pinMode(echo, INPUT);
    pinMode(trig, OUTPUT);
    xTaskCreate(TaskDistance, "TaskDistance", 2048, NULL, 1, NULL);
}