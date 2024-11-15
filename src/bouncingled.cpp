/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "d:/dev/particle/Neopixel_Ring_Bouncing_LED/src/bouncingled.ino"
// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>

void setup();
void loop();
#line 4 "d:/dev/particle/Neopixel_Ring_Bouncing_LED/src/bouncingled.ino"
SYSTEM_MODE(AUTOMATIC);

/* ======================= prototypes =============================== */

void set_next_index(uint8_t *index);
void set_color_index(uint8_t *index);



// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_COUNT 24
#define PIXEL_PIN D6
#define PIXEL_TYPE WS2812B

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
//               note: if not specified, D2 is selected for you.
// Parameter 3 = pixel type [ WS2812, WS2812B, WS2811, TM1803 ]
//               note: if not specified, WS2812B is selected for you.
//               note: RGB order is automatically applied to WS2811,
//                     WS2812/WS2812B/TM1803 is GRB order.
//
// 800 KHz bitstream 800 KHz bitstream (most NeoPixel products ...
//                         ... WS2812 (6-pin part)/WS2812B (4-pin part) )
//
// 400 KHz bitstream (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//                   (Radio Shack Tri-Color LED Strip - TM1803 driver
//                    NOTE: RS Tri-Color LED's are grouped in sets of 3)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

int led2 = D7;
uint8_t WAIT = 50;
uint8_t RED_VALUE = 10;
uint8_t GREEN_VALUE = 10;
uint8_t BLUE_VALUE = 10;

#define CW 0
#define CCW 1
int direction = CW;
struct RGB {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

#define NUM_COLORS 6
struct RGB led_color[NUM_COLORS] = {
    0, 0, BLUE_VALUE,
    0, GREEN_VALUE, 0,
    0, GREEN_VALUE, BLUE_VALUE,
    RED_VALUE, 0, 0,
    RED_VALUE, 0, BLUE_VALUE,
    RED_VALUE, GREEN_VALUE, 0
};

void setup() 
{
   strip.begin();
   strip.show(); // Initialize all pixels to 'off'
  
   pinMode(led2, OUTPUT);
}


void loop() 
{
   static uint8_t current_index = 0;
   static uint8_t color_index = 0;
   
   strip.setPixelColor(current_index, 0, 0, 0);
   set_next_index(&current_index);
   if (current_index == 0 || current_index == 23)
      set_color_index(&color_index);
   strip.setPixelColor(current_index, led_color[color_index].red, led_color[color_index].green, led_color[color_index].blue);
   strip.show();
   delay(WAIT);
   digitalWrite(led2, LOW);
}

void set_next_index(uint8_t *index)
{
    if (direction == CW)
    {
        if (*index == 23)
        {
            direction = CCW;
            *index = *index - 1;
            digitalWrite(led2, HIGH);
        }
        else 
        {
            *index = *index + 1;
        }
    }
    else
    {
        if (*index == 0)
        {
            direction = CW;
            *index = * index + 1;
            digitalWrite(led2, HIGH);
        }
        else
        {
            *index = *index - 1;
        }
    }
}

void set_color_index(uint8_t *index)
{
   //*index = ++(*index) % NUM_COLORS;
   *index = random(0,NUM_COLORS);
}
