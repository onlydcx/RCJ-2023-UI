#include "Arduino.h"
#include <Wire.h>
#include <stdlib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>


Adafruit_ST7789 tft = Adafruit_ST7789(6, 8, 4);

float p = 3.1415926;

void clear() {
   tft.fillScreen(ST77XX_BLACK);
}

#define w tft.width()
#define h tft.height()

#define char_w 5
#define char_h 7

#define lb A10
#define cb A0
#define rb A1

byte data = 0;

void DataRequest() {
  Wire.write(digitalRead(lb));
}

void setup() {
   Wire.begin(8);
   Wire.onRequest(DataRequest);
   Serial.begin(9600);
   tft.init(135, 240);
   clear();
   tft.setRotation(3);
   tft.drawRect(0,h/2-30,60,60,ST7735_WHITE);
   tft.drawRect(w/2-30,h/2-30,60,60,ST7735_WHITE);
   tft.drawRect(w-60,h/2-30,60,60,ST7735_WHITE);
}

void loop() {
   if(digitalRead(lb)) {
      tft.fillRect(0,h/2-30,60,60,ST7735_RED);
   }
   else {
      tft.fillRect(0,h/2-30,60,60,ST7735_WHITE);
   }
   if(digitalRead(cb)) {
      tft.fillRect(w/2-30,h/2-30,60,60,ST7735_RED);
   }
   else {
      tft.fillRect(w/2-30,h/2-30,60,60,ST7735_WHITE);
   }
   if(digitalRead(rb)) {
      tft.fillRect(w-60,h/2-30,60,60,ST7735_RED);
   }
   else {
      tft.fillRect(w-60,h/2-30,60,60,ST7735_WHITE);
   }
}