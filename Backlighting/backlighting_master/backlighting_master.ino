

#include "backlighting_master.h"
#include "IFEI_Backlight.h"
#include "Video_Recorder_Backlight.h"
#include "Station_Select_Backlight.h"

/*
1:master arm leds 29 ready 1-4 master mode 26-29
2:lewi 30 fire 1-4 master caution 5-8 go/nogo
3:hud 49
4: rewi 30
5: spin recv 52  spin 30 33

*/






#define NUM_LEDS     96       // Set it to the number of LEDs you have connected.

#define UIP_NUM_LEDS 135
#define LIP_LEDS    118
#define BRIGHTNESS   25      // LED Brightness 0 = Off, 255 = 100%.
#define SOLID_SPEED  1000     // How long each solid colour is held in ms.
#define CHASE_SPEED  100      // How fast the chase goes in ms

// CRGB leds[NUM_LEDS];
CRGBArray<NUM_LEDS> leds;
CRGBArray<UIP_NUM_LEDS> uip_LEDS;

// FastLED LIP = FastLED::New();

// int IFEIBackLightLEDS[75] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,56,57,60,62,64,65,67,70,71,74,87,88,89,90,91,92,93,94,95,96};

int LIP_LED_LIST[118] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117};

int UIP_LED_LIST[135] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,108,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134};



void onInstPnlDimmerChange(unsigned int newValue) {
updateBacklight(newValue,IFEI_LED_LIST,NUM_IFEI_LEDS);
updateBacklight(newValue,VIDEO_RECORDER_LED_LIST,NUM_VIDEO_RECORDER_LEDS);
updateBacklight(newValue,STATION_SELECT_LED_LIST,NUM_STATION_SELECT_LEDS);
// updateBacklight(newValue,LIP_LED_LIST,LIP_LEDS);
// updateBacklight(newValue, UIP_LED_LIST,UIP_NUM_LEDS);
}
DcsBios::IntegerBuffer instPnlDimmerBuffer(FA_18C_hornet_INST_PNL_DIMMER, onInstPnlDimmerChange);


void setup() { 
  FastLED.addLeds<LED_TYPE, LIP_CH1,COLOUR_ORDER>(IFEI_LEDS,NUM_IFEI_LEDS);
  FastLED.addLeds<LED_TYPE, LIP_CH1,COLOUR_ORDER>(VIDEO_RECORDER_LEDS,NUM_VIDEO_RECORDER_LEDS);
  FastLED.addLeds<LED_TYPE, LIP_CH1,COLOUR_ORDER>(STATION_SELECT_LEDS,NUM_STATION_SELECT_LEDS);
  // FastLED.addLeds<LED_TYPE, LIP_CH1,COLOUR_ORDER>(leds, NUM_LEDS);
  // FastLED.addLeds<LED_TYPE, LIP_CH2,COLOUR_ORDER>(leds,LIP_LEDS);  
  // FastLED.addLeds<LED_TYPE, UIP_CH2,COLOUR_ORDER>(uip_LEDS,UIP_NUM_LEDS);       
  FastLED.setDither(false);
  FastLED.show();



  DcsBios::setup();

}
void loop() {  
  DcsBios::loop();

}

//==================== Functions ===============================





void updateBacklight(unsigned int newValue, int * testleds, unsigned int ledCount){

   int value = map(newValue,0,65535,0,255);
   if(value < 70 && value >0){value = 70;}
  for(unsigned int a = 0; a < ledCount; a++){
   

     leds[testleds[a]] = CHSV(GLOBAL_HUE,GLOBAL_SATURATION,value);

}

 FastLED.show();

}


