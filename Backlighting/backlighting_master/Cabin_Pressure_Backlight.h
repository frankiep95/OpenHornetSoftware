#ifndef __CABIN_PRESSURE_BACKLIGHT_H
#define __CABIN_PRESSURE_BACKLIGHT_H

#define NUM_CABIN_PRESSURE_LEDS 2

int CABIN_PRESSURE_OFFSET = ECM_DISPENSE_OFFSET + NUM_ECM_DISPENSE_LEDS;

int CABIN_PRESSURE_LED_LIST[NUM_CABIN_PRESSURE_LEDS] = {0,1};

CRGB CABIN_PRESSURE_LEDS[NUM_CABIN_PRESSURE_LEDS];

void UpdateCabinPressureBacklightLEDS(int value){
  BackLighting::updateBacklight(value, CABIN_PRESSURE_LED_LIST,NUM_CABIN_PRESSURE_LEDS,CABIN_PRESSURE_LEDS);
  BackLighting::updateLipLEDS(NUM_CABIN_PRESSURE_LEDS,CABIN_PRESSURE_OFFSET,CABIN_PRESSURE_LEDS);
}



#endif