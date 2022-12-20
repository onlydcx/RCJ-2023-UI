#include "Arduino.h"
#include <Wire.h>

#define SLAVE_ADDRESS 0x01
#define SLAVE_REGISTER_1 0x00
#define SLAVE_REGISTER_2 0x01

uint8_t registerIndex = 0;
uint8_t data[2] = {0, 1};

void receiveEvent() {
  while(Wire.available() > 0){
    registerIndex = Wire.read();
  }
}

void requestEvent() {
  Wire.write(data[registerIndex]);
}

void setup() {
Wire.begin(0x01);
Wire.onReceive(receiveEvent);
Wire.onRequest(requestEvent);
}

void loop() {
// delay(100);
}