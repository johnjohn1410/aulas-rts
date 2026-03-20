#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

QueueHandle_t q;

void Producer(void *pv) {
  int v = 0;
  while (true) {
    if (xQueueSend(q, &v, pdMS_TO_TICKS(50)) == pdPASS) {
      v++;
      Serial.printf("[Producer] data sent = %d\n", v);
    } else {
      Serial.println("[Producer] failed to send data");
    }
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void Consumer(void *pv) {
  int v;
  while (true) {
    if (xQueueReceive(q, &v, portMAX_DELAY) == pdPASS) {
      Serial.printf("[Consumer] data sent = %d\n", v);
    }
  }
}

void setup() {
  Serial.begin(115200);

  q = xQueueCreate(1, sizeof(int)); //FIFO com 1 item contendo um int
  if (!q) {
    Serial.println("Falha ao criar fila!");
    while (true) {}
  }

  xTaskCreate(Producer, "Producer", 2048, nullptr, 1, nullptr);
  xTaskCreate(Consumer, "Consumer", 2048, nullptr, 1, nullptr);
}

void loop() {}