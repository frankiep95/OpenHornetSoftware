#include "backlighting_master.h"



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

FastLED LIP = FastLED::New();

int IFEIBackLightLEDS[75] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,56,57,60,62,64,65,67,70,71,74,87,88,89,90,91,92,93,94,95,96};

int LIP_LED_LIST[118] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117};

int UIP_LED_LIST[135] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,108,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134};

int globalHue = 100;
int globalSaturation = 255;

void onSjCtrChange(unsigned int newValue) {
    if(newValue > 0){newValue = 255;}

  int sjCtrLEDS[2] = {63,66};
  updateLEDS(newValue,sjCtrLEDS,2,100,255);

}
DcsBios::IntegerBuffer sjCtrBuffer(FA_18C_hornet_SJ_CTR, onSjCtrChange);

void onSjLiLtChange(unsigned int newValue) {
    if(newValue > 0){newValue = 255;}

  int sjLiLEDS[2] = {68,69};
  updateLEDS(newValue,sjLiLEDS,2,100,255);
}
DcsBios::IntegerBuffer sjLiLtBuffer(FA_18C_hornet_SJ_LI_LT, onSjLiLtChange);


void onSjLoChange(unsigned int newValue) { 
    if(newValue > 0){newValue = 255;}

int sjLoLEDS[2] ={72,73};
updateLEDS(newValue,sjLoLEDS,2,100,255);
}
DcsBios::IntegerBuffer sjLoBuffer(FA_18C_hornet_SJ_LO, onSjLoChange);



void onSjRiChange(unsigned int newValue) {
    if(newValue > 0){newValue = 255;}

  int sjRiLEDS[2] ={61,59};
  updateLEDS(newValue,sjRiLEDS,2,100,255);
}
DcsBios::IntegerBuffer sjRiBuffer(FA_18C_hornet_SJ_RI, onSjRiChange);



void onSjRoChange(unsigned int newValue) {
    if(newValue > 0){newValue = 255;}

 int sjRoLEDS[2] = {58,55};
 updateLEDS(newValue,sjRoLEDS,2,100,255);

}
DcsBios::IntegerBuffer sjRoBuffer(FA_18C_hornet_SJ_RO, onSjRoChange);

void onFlpLgNoseGearLtChange(unsigned int newValue) {
    if(newValue > 0){newValue = 100;}

int noseLtLEDS[2] = {75,86};
updateLEDS(newValue,noseLtLEDS,2,100,255);
}
DcsBios::IntegerBuffer flpLgNoseGearLtBuffer(FA_18C_hornet_FLP_LG_NOSE_GEAR_LT, onFlpLgNoseGearLtChange);


void onFlpLgRightGearLtChange(unsigned int newValue) {
      if(newValue > 0){newValue = 100;}
int rightGearLEDS[2] = {76,77};
updateLEDS(newValue,rightGearLEDS,2,100,255);
}
DcsBios::IntegerBuffer flpLgRightGearLtBuffer(FA_18C_hornet_FLP_LG_RIGHT_GEAR_LT, onFlpLgRightGearLtChange);




void onFlpLgLeftGearLtChange(unsigned int newValue) {
      if(newValue > 0){newValue = 100;}
int leftGearLEDS[2] = {78,79};
updateLEDS(newValue,leftGearLEDS,2,100,255);
}
DcsBios::IntegerBuffer flpLgLeftGearLtBuffer(FA_18C_hornet_FLP_LG_LEFT_GEAR_LT, onFlpLgLeftGearLtChange);



void onFlpLgHalfFlapsLtChange(unsigned int newValue) {
      if(newValue > 0){newValue = 100;}
int halfFlapLEDS[2] ={80,81};
updateLEDS(newValue,halfFlapLEDS,2,100,255);
}
DcsBios::IntegerBuffer flpLgHalfFlapsLtBuffer(FA_18C_hornet_FLP_LG_HALF_FLAPS_LT, onFlpLgHalfFlapsLtChange);


void onFlpLgFullFlapsLtChange(unsigned int newValue) {
      if(newValue > 0){newValue = 100;}
int fullFlapsLEDS[2] = {82,83};
updateLEDS(newValue,fullFlapsLEDS,2,100,255);
}
DcsBios::IntegerBuffer flpLgFullFlapsLtBuffer(FA_18C_hornet_FLP_LG_FULL_FLAPS_LT, onFlpLgFullFlapsLtChange);



void onFlpLgFlapsLtChange(unsigned int newValue) {
      if(newValue > 0){newValue = 100;}
int flapsLEDS[2] ={84,85};
updateLEDS(newValue,flapsLEDS,2,50,255);
}
DcsBios::IntegerBuffer flpLgFlapsLtBuffer(FA_18C_hornet_FLP_LG_FLAPS_LT, onFlpLgFlapsLtChange);

void onInstPnlDimmerChange(unsigned int newValue) {
updateBacklight(newValue,IFEIBackLightLEDS,74);
updateBacklight(newValue,LIP_LED_LIST,LIP_LEDS);
updateBacklight(newValue, UIP_LED_LIST,UIP_NUM_LEDS);
}
DcsBios::IntegerBuffer instPnlDimmerBuffer(FA_18C_hornet_INST_PNL_DIMMER, onInstPnlDimmerChange);


void setup() { 
  FastLED.addLeds<LED_TYPE, LIP_CH1,COLOUR_ORDER>(leds, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LIP_CH2,COLOUR_ORDER>(leds,LIP_LEDS);  
  FastLED.addLeds<LED_TYPE, UIP_CH2,COLOUR_ORDER>(uip_LEDS,UIP_NUM_LEDS);       
  FastLED.setDither(false);
  FastLED.show();

  DcsBios::setup();

}
void loop() {  
  DcsBios::loop();

}

//==================== Functions ===============================


void updateLEDS(unsigned int newValue, int * theleds, unsigned int ledCount, int  hue, int saturation){
  // if(newValue > 0){newValue = 255;}
  // int value = map(newValue,0,100,0,255);
  for(unsigned int a = 0; a < ledCount; a++){
    leds[theleds[a]] = CHSV(hue,saturation,newValue);
}
 FastLED.show();

}

void updateBacklight(unsigned int newValue, int * testleds, unsigned int ledCount){

   int value = map(newValue,0,65535,0,255);
   if(value < 70 && value >0){value = 70;}
  for(unsigned int a = 0; a < ledCount; a++){
   

     leds[testleds[a]] = CHSV(globalHue,globalSaturation,value);

}

 FastLED.show();

}


