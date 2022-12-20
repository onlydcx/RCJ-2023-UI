#include "Arduino.h"

#include <stdlib.h>

#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_CS 6 
#define TFT_RST 4
#define TFT_DC 8

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

float p = 3.1415926;

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

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


void setup(void) {
  Serial.begin(9600);
  tft.init(135, 240);
  clear();
  tft.setRotation(3);
  tft.setTextSize(3);

  char str[] = "main.cpp";
  // testdrawtext(str,ST7735_WHITE);

  tft.drawRect(0,h/2-30,60,60,ST7735_WHITE);
  tft.drawRect(w/2-30,h/2-30,60,60,ST7735_WHITE);
  tft.drawRect(w-60,h/2-30,60,60,ST7735_WHITE);
  while(1) {
    
  }
}

String mode[] = {"Start","Kick","Dribbler","IMU","Ball","EEPROM"};

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
