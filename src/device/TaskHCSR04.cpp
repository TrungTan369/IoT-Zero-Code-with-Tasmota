#include "TaskHCSR04.h"

HCSR04Sensor hcsr04;

void getValueHCSR04() {
    double *distances = hcsr04.measureDistanceCm();
    Serial.println(String(*distances) + " cm");
    publishData("Distance", String(*distances));
}

void TaskHCSR04(void *pvParameters) {
    while (true) {
        getValueHCSR04();
        vTaskDelay(delay_time / portTICK_PERIOD_MS);
    }
}

void initHCSR04() {
    hcsr04.begin(MY_TRIG, MY_ECHO);
    xTaskCreate(
        TaskHCSR04,    // Function to implement the task
        "TaskHCSR04",  // Name of the task
        8192,          // Stack size in words
        NULL,          // Task input parameter
        1,             // Priority of the task
        NULL           // Task handle
    );
}