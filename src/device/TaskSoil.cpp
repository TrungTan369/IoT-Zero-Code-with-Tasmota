#include "TaskSoil.h"

uint8_t soil;

void TaskSoil(void *pvParameters) {
    while (1) {
        soil = (analogRead(soil_pin) / 4095.0) * 100;
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void initSoil() {
    pinMode(soil_pin, INPUT);
    xTaskCreate(TaskSoil, "TaskSoil", 2048, NULL, 1, NULL);
}
