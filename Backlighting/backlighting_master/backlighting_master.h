#ifndef __BACKLIGHTING_MASTER_H
#define __BACKLIGHTING_MASTER_H


#include <FastLED.h>
#include <DcsBios.h>
#include "Arduino.h"

#ifdef __AVR__
#include <avr/power.h>
#endif


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

#define LEFT_LIP_NUM_LEDS 96
#define LIP_NUM_LEDS 113
#define UIP_NUM_LEDS 191


CRGBArray<LEFT_LIP_NUM_LEDS> LEFT_LIP_LEDS;
CRGBArray<LIP_NUM_LEDS> LIP_LEDS;
CRGBArray<UIP_NUM_LEDS> UIP_LEDS;


typedef struct LedArrays_
{
  CRGB * values;
  int LED_COUNT;
} LedArrays_t;

namespace backlight{
int NUM_LEDS = 0;
}

namespace BackLighting{

void updateBacklight(unsigned int newValue, int * testleds, unsigned int ledCount, CRGB * theLEDS){
  int value = 0;
  value = map(newValue,0,65535,0,255);
  if(value < 70 && value >0){value = 70;}
  for(unsigned int a = 0; a < ledCount; a++){
    theLEDS[testleds[a]] = CHSV(GLOBAL_HUE,GLOBAL_SATURATION,value);
  }
}

void updateLeftLipLEDS(int numLEDS,int offset, CRGB * theLEDS){
  for(int a = 0;a < numLEDS; a++){
    LEFT_LIP_LEDS[a+ offset] = theLEDS[a];
  }
 FastLED.show();
}

void updateLipLEDS(int numLEDS,int offset, CRGB * theLEDS){
  for(int a = 0;a < numLEDS; a++){
    LIP_LEDS[a+ offset] = theLEDS[a];
  }
 FastLED.show();
}

void updateUIPLEDS(int numLEDS,int offset, CRGB * theLEDS){
  for(int a = 0;a < numLEDS; a++){
    UIP_LEDS[a+ offset] = theLEDS[a];
  }
 FastLED.show();
}

}

#include "IFEI_Backlight.h"
#include "Video_Recorder_Backlight.h"
#include "Station_Select_Backlight.h"
#include "Jett_Placard_Backlight.h"
#include "RWR_Control_Backlight.h"
#include "ECM_Dispense_Backlight.h"
#include "Cabin_Pressure_Backlight.h"
#include "Master_Arm_Backlight.h"
#include "LEWI_Backlight.h"
#include "Hud_Panel_Backlighting.h"
#include "REWI_Backlight.h"
#include "Spin_Recovery_Backlighting.h"

#endif