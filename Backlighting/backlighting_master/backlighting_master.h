#define DCSBIOS_DEFAULT_SERIAL

#include <FastLED.h>
#include <DcsBios.h>
#include "Arduino.h"


//backlight channels
#define LIP_CH1 13      
#define LIP_CH2 12
#define UIP_CH1 11
#define UIP_CH2 10 
#define LC_CH1 9
#define LC_CH2 8
#define RC_CH1 7
#define RC_CH2 6




#define LED_TYPE     WS2812B  // OPENHORNET backlighting LEDs are WS2812B
#define COLOUR_ORDER GRB      // OPENHORNET backlighting LEDs are GRB (green, red, blue)