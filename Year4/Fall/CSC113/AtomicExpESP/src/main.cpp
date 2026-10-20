#include <Arduino.h>

const BaseType_t cpu_core_0 = 0;
const BaseType_t cpu_core_1 = 1;
const size_t MESSAGE_SIZE = 64; //64 byte msg size 

// Handle for the queue
QueueHandle_t integerQueue;

// Task 1: Sends data to the queue
void taskSend(void *parameter) {
  char valueToSend[MESSAGE_SIZE] = {};
  size_t length = 0;
  while (1) {
    while (Serial.available() > 0) {
      char incoming = Serial.read();
      if (incoming == '\n') {
        valueToSend[length] = '\0';
        // Send the string to the back of the queue with 10 ms max wait time
        if (xQueueSend(integerQueue, valueToSend, pdMS_TO_TICKS(10)) != pdPASS) {
          Serial.println("Queue is full or timed out!");
        } else {
          Serial.print("Sent: ");
          Serial.println(valueToSend);
        }
        length = 0;
      } else if (incoming != '\r' && length < MESSAGE_SIZE - 1) {
        valueToSend[length++] = incoming;
      }
    }
    vTaskDelay(pdMS_TO_TICKS(10)); // Wait 10 milliseconds
  }
}

// Task 2: Receives data from the queue
void taskReceive(void *parameter) {
  char receivedValue[MESSAGE_SIZE] = {};
  while (1) {
    // Wait to receive data from the queue
    if (xQueueReceive(integerQueue, receivedValue, pdMS_TO_TICKS(2000)) == pdPASS) {
      Serial.print("  --> Received: ");
      Serial.println(receivedValue);
    } else {
      Serial.println("  --> Timed out waiting for queue item!");
    }
  }
}

void setup() {
  Serial.begin(9600);
  vTaskDelay(pdMS_TO_TICKS(1000));
  Serial.println("\n--- FreeRTOS xQueueCreate Example ---");

  // Create queue: length of 5 messages, each message is 64 bytes
  integerQueue = xQueueCreate(5, MESSAGE_SIZE);

  if (integerQueue == NULL) {
    Serial.println("Error: Failed to create integerQueue!");
  } else {
    // Create producer task
    xTaskCreatePinnedToCore(
      taskSend,         // Task function
      "Task Send",      // Task name
      1024,             // Stack size (bytes)
      NULL,             // Parameter
      1,                // Priority
      NULL,             // Task handle
      cpu_core_0           // Core
    );

    // Create consumer task
    xTaskCreatePinnedToCore(
      taskReceive,      // Task function
      "Task Receive",   // Task name
      1024,             // Stack size (bytes)
      NULL,             // Parameter
      1,                // Priority
      NULL,             // Task handle
      cpu_core_1           // Core
    );
  }
}

void loop() {
  // Empty. FreeRTOS tasks handle everything.
}
