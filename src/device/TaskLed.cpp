#include "TaskLed.h"

volatile bool led_mode = 1;
LED_COLOR led_color;
void Led_Indicate_NO_WIFI(void *pvParameters) {
    while (1) {
        led_on();
        vTaskDelay(pdMS_TO_TICKS(1000));
        led_off();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
void Led_Indicate_NO_INTERNET(void *pvParameters) {
    while (1) {
        led_on();
        vTaskDelay(pdMS_TO_TICKS(250));
        led_off();
        vTaskDelay(pdMS_TO_TICKS(250));
    }
}
void initLed() {
    led_color = red;
    pinMode(LED_BUILTIN, OUTPUT);
}
void led_off() {
    digitalWrite(LED_BUILTIN, 0);
}
void led_on() {
    digitalWrite(LED_BUILTIN, 1);
}