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
                state = FSM_SOIL;
                break;
            case FSM_SOIL:
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("SOIL: ");
                lcd.print(soil);
                state = FSM_DHT20;
                break;
            case FSM_ERROR:
                // Xử lý lỗi nếu cần
                break;
            default:
                break;
        }
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void fsm_init() {
    state = FSM_DHT20;
    xTaskCreate(fsm_handle, "fsm_handle", 1024, NULL, 1, NULL);
}