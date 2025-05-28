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

#define GLOBAL_HUE 100
#define GLOBAL_SATURATION 255


#define LED_TYPE     WS2812B  // OPENHORNET backlighting LEDs are WS2812B
#define COLOUR_ORDER GRB      // OPENHORNET backlighting LEDs are GRB (green, red, blue)
// namespace backlight{

// void updateLEDS(unsigned int newValue, int * theleds, unsigned int ledCount, int  hue, int saturation, CRGBArray<>  & theLEDS){
//   for(unsigned int a = 0; a < ledCount; a++){
//     theLEDS[theleds[a]] = CHSV(hue,saturation,newValue);
// }
//  FastLED.show();

// }
// }