#include <Arduino.h>
#include <Wire.h>
#include <Bounce2.h>
#include <Adafruit_NeoPixel.h>
#include <DHT.h>
#include "pins.h"
#define PIXEL_PIN 10
#define PIXEL_COUNT 60

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

//If we are using an RGBW strip, then set PIXELCOLOR macro to use
//all args and create the proper object for RGBW
#ifdef STRIP_RGBW
#define PIXELCOLOR(n, r, g, b, w) strip.setPixelColor(n, r, g, b, w);
//Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_RGBW + NEO_KHZ800);
//IF using a "normal" RGB strip, then the PIXELCOLOR macro to
//ignore the 5th (white) argument. Also create an object for RGB
#else
#define PIXELCOLOR(n, r, g, b, w) strip.setPixelColor(n, r, g, b);
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN);
#endif

bool justBooted = true;
volatile int delaytime = 500;
void setup () {
#ifdef AVRDEBUG
    debug_init();
#endif
#ifndef AVRDEBUG
    Serial.begin(9600);
#endif
    strip.begin();
    strip.show(); //All pixels off
    pinMode (BOARD_LED, OUTPUT);
};
void loop () {
    if (justBooted) {
        justBooted = false;
        DEBUGMSG("Starting\n");
    }
    //strip.setPixelColor(6, 0, 0, 0, 128);
    //strip.setPixelColor(8, 0, 0, 128, 0);
    //strip.setPixelColor(10, 0, 128, 0, 0);
    //strip.setPixelColor(12, 128, 0, 0, 0);
    PIXELCOLOR(6, 0, 0, 0, 128);
    PIXELCOLOR(8, 0, 0, 128, 0);
    PIXELCOLOR(10, 0, 128, 0, 0);
    PIXELCOLOR(12, 128, 0, 0, 0);
    strip.show();
    digitalWrite (BOARD_LED, HIGH);
    DEBUGMSG("On\n");
    delay (delaytime);
    digitalWrite (BOARD_LED, LOW);
    DEBUGMSG("Off\n");
    delay (delaytime);
}
