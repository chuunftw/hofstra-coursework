#include <Arduino.h>
#include <driver/rtc_io.h>
#include <esp_sleep.h>

// Adapted from Pranav Cherukupalli's public-domain deep-sleep timer example.
// Connect a normally open pushbutton between GPIO 33 and GND.
constexpr gpio_num_t BUTTON_PIN = GPIO_NUM_33;
RTC_DATA_ATTR int bootCount = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.printf("Boot number: %d\n", ++bootCount);

  const esp_sleep_wakeup_cause_t wakeupReason = esp_sleep_get_wakeup_cause();
  if (wakeupReason == ESP_SLEEP_WAKEUP_EXT0) {
    Serial.println("Wakeup caused by pushbutton");
  } else {
    Serial.printf("Wakeup reason: %d\n", static_cast<int>(wakeupReason));
  }

  // The RTC pull-up keeps GPIO 33 high during deep sleep until the button is pressed.
  rtc_gpio_init(BUTTON_PIN);
  rtc_gpio_set_direction(BUTTON_PIN, RTC_GPIO_MODE_INPUT_ONLY);
  rtc_gpio_pulldown_dis(BUTTON_PIN);
  rtc_gpio_pullup_en(BUTTON_PIN);
  if (esp_sleep_enable_ext0_wakeup(BUTTON_PIN, LOW) != ESP_OK) {
    Serial.println("Could not configure pushbutton wakeup");
    return;
  }

  // Wait for release so a held button does not immediately wake the ESP32 again.
  do {
    while (rtc_gpio_get_level(BUTTON_PIN) == LOW) {
      delay(10);
    }
    delay(30);
  } while (rtc_gpio_get_level(BUTTON_PIN) == LOW);

  Serial.println("Going to deep sleep. Press the button to wake.");
  Serial.flush();
  esp_deep_sleep_start();
}

void loop() {}
