#include <Arduino.h>
#include <Wire.h>
#include <Bounce2.h>
#include <Adafruit_NeoPixel.h>
#include <DHT.h>
#include "pins.h"

//If we are in arvdebug environment, then include necessary headers
//and define DEBUGMSG macro to use avr-stub's debug_message since
//Serial() is unavailable in this environment
#ifdef AVRDEBUG
#include "avr8-stub.h"
//#include "app_api.h" // only needed with flash breakpoints
#define DEBUGMSG(m) debug_message(m)
//If we are not in avrdebug, then define DEBUGMSG macro to 
//use Serial.print();
#else
#define DEBUGMSG(m) Serial.print(m)
#endif
#define BOARD_LED 13
volatile int pixcount = 30;
#ifdef STRIP_RGBW
Adafruit_NeoPixel lightPixels(NEOPIXEL1_COUNT, NEOPIXEL1, NEO_RGBW + NEO_KHZ800);
#else
Adafruit_NeoPixel lightPixels(NEOPIXEL1_COUNT, NEOPIXEL1);
#endif
Adafruit_NeoPixel statusPixels(NEOPIXEL2_COUNT, NEOPIXEL2);

uint32_t cold=lightPixels.Color(0,0,128,0);
bool justBooted = true;
volatile int delaytime = 100;
volatile int bytecolor=1;
void setup () {
#ifdef AVRDEBUG
    debug_init();
#endif
#ifndef AVRDEBUG
    Serial.begin(9600);
#endif
    lightPixels.begin();
    lightPixels.show(); //All pixels off
    statusPixels.begin();
    statusPixels.show(); //All pixels off
    pinMode (BOARD_LED, OUTPUT);
};
void loop () {
    if (justBooted) {
        justBooted = false;
        DEBUGMSG("Starting\n");
    }
    lightPixels.fill(cold, 1, pixcount);
//    lightPixels.setPixelColor(1, 0, 0, 0, 128);
//    lightPixels.setPixelColor(2, 0, 0, bytecolor, 0);
//    lightPixels.setPixelColor(3, 0, bytecolor, 0, 0);
//    lightPixels.setPixelColor(4, bytecolor, 0, 0, 0);
    statusPixels.setPixelColor(2, 0, 0, bytecolor);
    statusPixels.setPixelColor(3, 0, bytecolor, 0);
    statusPixels.setPixelColor(4, bytecolor, 0, 0);
    bytecolor=(bytecolor + 1) % 128;
    //DEBUGMSG(char(bytecolor));
    lightPixels.show();
    statusPixels.show();
    digitalWrite (BOARD_LED, HIGH);
    DEBUGMSG("On\n");
    delay (delaytime);
    digitalWrite (BOARD_LED, LOW);
    DEBUGMSG("Off\n");
    delay (delaytime);
}
