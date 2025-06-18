#include "TaskDistance.h"

uint8_t distance;


void TaskDistance(void *pvParameters) {
    while (1) {
        digitalWrite(trig, LOW);
        vTaskDelay(pdMS_TO_TICKS(2));
        digitalWrite(trig, HIGH);
        vTaskDelay(pdMS_TO_TICKS(10));
        digitalWrite(trig, LOW);

        long duration = pulseIn(echo, HIGH, 30000);
        distance = duration * 0.034 / 2;
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void initDistance() {
    pinMode(echo, INPUT);
    pinMode(trig, OUTPUT);

    xTaskCreate(TaskDistance, "TaskDistance", 1025, NULL, 1, NULL);
}