#include "TaskLed.h"

void initLed() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(led_pin, OUTPUT);
}

void TaskLed(void *pvParameters) {
}

void led_off() {
    digitalWrite(LED_BUILTIN, 0);
}
void led_on() {
    digitalWrite(LED_BUILTIN, 1);
}