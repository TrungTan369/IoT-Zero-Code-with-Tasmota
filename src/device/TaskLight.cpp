#include "TaskLight.h"

uint8_t light = 0;

void TaskLight(void *pvParameters){
    while(1){
        light = analogRead(light_sensor_pin);
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

void initLight(){
    pinMode(light_sensor_pin, INPUT);
    xTaskCreate(TaskLight, "TaskLight", 1024, NULL, 1, NULL);
}