#ifndef __GEN_TIE_H
#define __GEN_TIE_H



#define NUM_GEN_TIE_LEDS 9

int GEN_TIE_OFFSET = NUM_SIM_POWER_LEDS + SIM_POWER_OFFSET;

int GEN_TIE_LED_LIST[NUM_GEN_TIE_LEDS] = {0,1,2,3,4,5,6,7,8};

CRGB GEN_TIE_LEDS[NUM_GEN_TIE_LEDS];

void UpdateGenTieBacklightLEDS(int value){
  BackLighting::updateBacklight(value, GEN_TIE_LED_LIST,NUM_GEN_TIE_LEDS,GEN_TIE_LEDS);
  BackLighting::updateLCLEDS(NUM_GEN_TIE_LEDS,GEN_TIE_OFFSET,GEN_TIE_LEDS);
}


#endif