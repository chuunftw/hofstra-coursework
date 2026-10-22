#include <Arduino.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define LED_SERVICE_UUID                "9d6d44f6-4486-4018-b987-34e490568646"
#define LED_CHARACTERISTIC_UUID         "04a23f1d-24a9-450a-9418-43a02eec06ab"

BLECharacteristic *pCharacteristic;
void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLEDevice::init("Rchen");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(LED_SERVICE_UUID);
  /*BLECharacteristic * */
  pCharacteristic = pService->createCharacteristic(
                                         LED_CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setValue("Initial value");
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(LED_SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

int i = 0;

void loop() 
{
  if(i++%10==0)
  {
    String str = "value is: " + String(i);
    pCharacteristic->setValue(str.c_str());
  }

  std::string res = pCharacteristic->getValue();
  Serial.println(res.c_str());
      
  delay(1000);
}
