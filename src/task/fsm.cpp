#include "fsm.h"

FSMState state;

void fsm_handle(void *pvParameters) {
    while (1) {
        switch (state) {
            case FSM_DHT20:
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Temp: ");
                lcd.print(temp);
                lcd.setCursor(0, 1);
                lcd.print("Humi: ");
                lcd.print(humi);
                state = FSM_SOIL_LIGHT;
                break;
            case FSM_SOIL_LIGHT:
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("SOIL: ");
                lcd.print(soil);
                lcd.setCursor(0, 1);
                lcd.print("LIGHT: ");
                lcd.print(light);
                state = FSM_DISTANCE;
                break;
            case FSM_DISTANCE:
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("DISTANCE: ");
                lcd.print(distance);
                state = FSM_DHT20;
                break;
            default:
                break;
        }
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void initFSM() {
    state = FSM_DHT20;
    xTaskCreate(fsm_handle, "fsm_handle", 4096, NULL, 1, NULL);
}