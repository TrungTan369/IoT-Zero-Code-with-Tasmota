#include "TaskSoil.h"

uint8_t soil;

void TaskSoil(void *pvParameters) {
    while (1) {
        soil = analogRead(soil_pin);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
void initSoil(){
    pinMode(soil_pin, INPUT);
    xTaskCreate(TaskSoil, "TaskSoil", 1024, NULL, 1, NULL);
}
