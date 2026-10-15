#include <Arduino.h>

const int LED_PIN = 2;

// Shared mutex keeps the two tasks from mixing their Serial messages
SemaphoreHandle_t xSerialSemaphore;

// Repeats a count up and down based on the task label
void vTaskCode( void * pvParameters )
{
  // Read the task label and choose its direction and pause length
  const char *param = (const char *)pvParameters;
  bool countDown = false;
  int roundDelayMs = 4000;

  if (strcmp(param, "Count down") == 0)
  {
    countDown = true;
    roundDelayMs = 8000;
  }

  int round = 0;
  // Keep this task running continuously
  while(true)
  {
    // Wait for the mutex before printing a complete round
    if ( xSemaphoreTake( xSerialSemaphore, portMAX_DELAY ) == pdTRUE )
    {
      if (countDown == false)
      {
        digitalWrite(LED_PIN, HIGH);
      }

      round = round + 1;
      Serial.println("Begin protected code section");
      Serial.print(param);
      Serial.print(" - round ");
      Serial.println(round);
      for(int i=0;i<9;i++)
      {
        if (countDown)
        {
          Serial.print(8 - i);
        }
        else
        {
          Serial.print(i);
        }
        Serial.print(" ");
      }
      Serial.println("\nEnd protected code section");

      xSemaphoreGive( xSerialSemaphore ); // Let the other task use Serial
    }
    if (countDown == false)
    {
      // Keep the LED on for another half-second, then turn it off
      vTaskDelay(pdMS_TO_TICKS(500));
      digitalWrite(LED_PIN, LOW);
    }
    // Pause this task without holding the mutex
    vTaskDelay(pdMS_TO_TICKS(roundDelayMs));

  }
}

#define STACK_SIZE_BYTES 4096

// Initializes Serial and the LED, creates the mutex, and starts both tasks once
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);


  if ( xSerialSemaphore == NULL )
  {
    xSerialSemaphore = xSemaphoreCreateMutex();
  }

  if (xSerialSemaphore == NULL)
  {
    Serial.println("Startup failed: could not create the Serial mutex.");
    return;
  }

  Serial.println("begin task....");
  Serial.println("Ryan's concurrency demo: two counting tasks");
  Serial.println("Count up: LED flash, then 4-second rest. Count down: 8-second rest.");
  // Hold the mutex until startup checks are complete.
  xSemaphoreTake(xSerialSemaphore, portMAX_DELAY);
  TaskHandle_t xHandle1 = NULL;
  BaseType_t task1Result = xTaskCreate( vTaskCode, "MyTask1", STACK_SIZE_BYTES, (void *)"Count up", tskIDLE_PRIORITY + 1, &xHandle1 );
  TaskHandle_t xHandle2 = NULL;
  BaseType_t task2Result = xTaskCreate( vTaskCode, "MyTask2", STACK_SIZE_BYTES, (void *)"Count down", tskIDLE_PRIORITY + 1, &xHandle2 );

  // Stop any created task if both tasks could not be started
  if (task1Result != pdPASS || task2Result != pdPASS)
  {
    if (task1Result == pdPASS)
    {
      vTaskDelete(xHandle1);
    }
    if (task2Result == pdPASS)
    {
      vTaskDelete(xHandle2);
    }
    Serial.println("Startup failed: could not create both counting tasks.");
  }
  xSemaphoreGive(xSerialSemaphore);

}

// Waits while the two FreeRTOS tasks do the counting and LED work
void loop() {
  delay(1000);
}
