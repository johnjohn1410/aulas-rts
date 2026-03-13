#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void TaskHigh(void *pv) {

  Serial.println("[HIGH] prioridade = 1 - running");
  while(true){
    // Serial.println("[HIGH] prioridade = 1 - running");
    // vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void TaskLow(void *pv) {
   while(true){
    Serial.println("[LOW] prioridade = 1 - running");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void setup() {
  Serial.begin(115200);

  xTaskCreate(TaskLow, "Low", 2048, nullptr, 1, nullptr);
  xTaskCreate(TaskHigh, "High", 2048, nullptr, 2, nullptr);

}

void loop() {

}
