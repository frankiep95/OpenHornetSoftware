#define DCSBIOS_DEFAULT_SERIAL

#include <FastLED.h>
#include <DcsBios.h>
#include "Arduino.h"

#define NUM_IFEI_LEDS 39

int IFEI_LED_LIST[NUM_IFEI_LEDS] = {};

CRGBArray<NUM_IFEI_LEDS> IFEI_LEDS;