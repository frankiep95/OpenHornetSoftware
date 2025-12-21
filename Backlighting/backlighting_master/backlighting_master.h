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
#define LC_NUM_LEDS 163


CRGBArray<LEFT_LIP_NUM_LEDS> LEFT_LIP_LEDS;
CRGBArray<LIP_NUM_LEDS> LIP_LEDS;
CRGBArray<UIP_NUM_LEDS> UIP_LEDS;
CRGBArray<LC_NUM_LEDS> LC_LEDS;


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

void updateLCLEDS(int numLEDS, int offset, CRGB * theLEDS){
  for(int a = 0; a < numLEDS; a++){
    LC_LEDS[a + offset] = theLEDS[a];
  }
  FastLED.show();
}

}
//LEFT LIP (LIP_CH1)
#include "IFEI_Backlight.h"
#include "Video_Recorder_Backlight.h"
#include "Station_Select_Backlight.h"
#include "Jett_Placard_Backlight.h"
//LIP (LIP_CH2)
#include "RWR_Control_Backlight.h"
#include "ECM_Dispense_Backlight.h"
#include "Cabin_Pressure_Backlight.h"
#include "Standby_Instruments_Backlight.h"
//UIP (CH1)
#include "Master_Arm_Backlight.h"
#include "LEWI_Backlight.h"
#include "Hud_Panel_Backlight.h"
#include "REWI_Backlight.h"
#include "Spin_Recovery_Backlight.h"
//LC (LC_CH1)
#include "Landing_Gear_backlight.h"
// #include "Select_Jett_backlight.h"
// #include "Fire_Test_Backlight.h"
// #include "Sim_Power_Backlight.h"
// #include "Gen_Tie_Backlight.h"
// #include "Ext_Lights_backlight.h"
// fuel panel leds 32


//LC (LC_CH2)
//apu leds 19
//fcs leds 22
// comm leds 109
//ant sel leds 17
//obogs leds 16
//hyd isol leds 24

//RC (RC_CH1)
//ldg checklist leds 24
// radalt leds 2
// hyd press leds 41
// caution panel leds 24
//av cool leds 13
// elec leds 24
// batt gauge leds 41
// defog panel leds 22

// RC (RC_CH2)
// ecs leds 63
// intr lt leds 65
// snsr leds 58
// sim control leds 61
// ky58 leds 79


#endif