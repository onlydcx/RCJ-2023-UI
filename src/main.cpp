#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define w tft.width()
#define h tft.height()

Adafruit_ST7789 tft = Adafruit_ST7789(6, 8, 4);

byte data = 0;

int buttons[4] = {11,10,18,19};

bool isPush(int pin) {
   if (digitalRead(buttons[pin-1])) {
      while (digitalRead(buttons[pin-1])) {
         if (!digitalRead(buttons[pin-1])) {
            break;
         }
      }
      return 1;
   }
   else {
      return 0;
   }
}

word RGB(byte R, byte G, byte B) {
   return (((R & 0xF8) << 8) | ((G & 0xFC) << 3) | (B >> 3));
}

void clear() {
   tft.fillScreen(RGB(0,0,0));
}

void DataRequest() {
  Wire.write(data);
}

void setup() {
   Serial.begin(9600);
   for(int i = 0; i < 4; i++) {
      pinMode(buttons[i],INPUT);
   }
   Wire.begin(8);
   Wire.onRequest(DataRequest);
   tft.init(135, 240);
   clear();
   tft.setRotation(3);
   tft.setTextSize(3);
   tft.setCursor(80,30);
   tft.print("Main");
   tft.drawLine(0,83,w,83,RGB(0,0,255));
   tft.drawTriangle(30,110,60,95,60,125,RGB(0,255,255));
   tft.drawTriangle((w-30),110,(w-60),95,(w-60),125,RGB(0,255,255));
}

String mode[] = {
   "main","speed","ball","gyro","line"
};

int len = sizeof(mode) / sizeof(int), nav = 1;

void loop() {
   if(isPush(4)) {
      if(nav < len) {
         nav++;
         clear();
         tft.setTextSize(3);
         tft.setCursor(80,30);
         tft.print(mode[nav]);
         tft.drawLine(0,83,w,83,RGB(0,0,255));
         tft.drawTriangle(30,110,60,95,60,125,RGB(0,255,255));
         tft.drawTriangle((w-30),110,(w-60),95,(w-60),125,RGB(0,255,255));
      }
   }
   if(isPush(2)) {
      if(nav > len) {
         nav--;
         clear();
         tft.setTextSize(3);
         tft.setCursor(80,30);
         tft.print(mode[nav]);
         tft.drawLine(0,83,w,83,RGB(0,0,255));
         tft.drawTriangle(30,110,60,95,60,125,RGB(0,255,255));
         tft.drawTriangle((w-30),110,(w-60),95,(w-60),125,RGB(0,255,255));
      }
   }
}