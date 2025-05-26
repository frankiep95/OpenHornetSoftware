#define DCSBIOS_DEFAULT_SERIAL

#include <FastLED.h>
#include <DcsBios.h>
#include "Arduino.h"

#define DATA_PIN     13       // What data pin are the LEDs conencted to? BL#1 = 13, BL#2 = 12, BL#3 = 11 etc.
#define LED_TYPE     WS2812B  // OPENHORNET backlighting LEDs are WS2812B
#define COLOUR_ORDER GRB      // OPENHORNET backlighting LEDs are GRB (green, red, blue)
#define NUM_LEDS     96       // Set it to the number of LEDs you have connected.
#define BRIGHTNESS   25      // LED Brightness 0 = Off, 255 = 100%.
#define SOLID_SPEED  1000     // How long each solid colour is held in ms.
#define CHASE_SPEED  100      // How fast the chase goes in ms

CRGB leds[NUM_LEDS];

int IFEIBackLightLEDS[74] = {0,1,2,11,12,13,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,56,57,60,62,64,65,67,70,71,74,87,88,89,90,91,92,93,94,95,96};


void onSjCtrChange(unsigned int newValue) {
  int sjCtrLEDS[2] = {63,66};
  updateLEDS(newValue,sjCtrLEDS,2,CRGB::Green,CRGB::Black);

}
DcsBios::IntegerBuffer sjCtrBuffer(FA_18C_hornet_SJ_CTR, onSjCtrChange);

void onSjLiLtChange(unsigned int newValue) {
  int sjLiLEDS[2] = {68,69};
  updateLEDS(newValue,sjLiLEDS,2,CRGB::Green,CRGB::Black);
}
DcsBios::IntegerBuffer sjLiLtBuffer(FA_18C_hornet_SJ_LI_LT, onSjLiLtChange);


void onSjLoChange(unsigned int newValue) { 
int sjLoLEDS[2] ={72,73};
updateLEDS(newValue,sjLoLEDS,2,CRGB::Green,CRGB::Black);
}
DcsBios::IntegerBuffer sjLoBuffer(FA_18C_hornet_SJ_LO, onSjLoChange);



void onSjRiChange(unsigned int newValue) {
  int sjRiLEDS[2] ={61,59};
  updateLEDS(newValue,sjRiLEDS,2,CRGB::Green,CRGB::Black);
}
DcsBios::IntegerBuffer sjRiBuffer(FA_18C_hornet_SJ_RI, onSjRiChange);



void onSjRoChange(unsigned int newValue) {
 int sjRoLEDS[2] = {58,55};
 updateLEDS(newValue,sjRoLEDS,2,CRGB::Green,CRGB::Black);

}
DcsBios::IntegerBuffer sjRoBuffer(FA_18C_hornet_SJ_RO, onSjRoChange);

void onFlpLgNoseGearLtChange(unsigned int newValue) {
int noseLtLEDS[2] = {75,86};
updateLEDS(newValue,noseLtLEDS,2,CRGB::Green,CRGB::Black);
}
DcsBios::IntegerBuffer flpLgNoseGearLtBuffer(FA_18C_hornet_FLP_LG_NOSE_GEAR_LT, onFlpLgNoseGearLtChange);


void onFlpLgRightGearLtChange(unsigned int newValue) {
int rightGearLEDS[2] = {76,77};
updateLEDS(newValue,rightGearLEDS,2,CRGB::Green,CRGB::Black);
}
DcsBios::IntegerBuffer flpLgRightGearLtBuffer(FA_18C_hornet_FLP_LG_RIGHT_GEAR_LT, onFlpLgRightGearLtChange);




void onFlpLgLeftGearLtChange(unsigned int newValue) {
int leftGearLEDS[2] = {78,79};
updateLEDS(newValue,leftGearLEDS,2,CRGB::Green,CRGB::Black);
}
DcsBios::IntegerBuffer flpLgLeftGearLtBuffer(FA_18C_hornet_FLP_LG_LEFT_GEAR_LT, onFlpLgLeftGearLtChange);



void onFlpLgHalfFlapsLtChange(unsigned int newValue) {
int halfFlapLEDS[2] ={80,81};
updateLEDS(newValue,halfFlapLEDS,2,CRGB::Green,CRGB::Black);
}
DcsBios::IntegerBuffer flpLgHalfFlapsLtBuffer(FA_18C_hornet_FLP_LG_HALF_FLAPS_LT, onFlpLgHalfFlapsLtChange);


void onFlpLgFullFlapsLtChange(unsigned int newValue) {
int fullFlapsLEDS[2] = {82,83};
updateLEDS(newValue,fullFlapsLEDS,2,CRGB::Green,CRGB::Black);
}
DcsBios::IntegerBuffer flpLgFullFlapsLtBuffer(FA_18C_hornet_FLP_LG_FULL_FLAPS_LT, onFlpLgFullFlapsLtChange);



void onFlpLgFlapsLtChange(unsigned int newValue) {
int flapsLEDS[2] ={84,85};
updateLEDS(newValue,flapsLEDS,2,CRGB::Yellow,CRGB::Black);
}
DcsBios::IntegerBuffer flpLgFlapsLtBuffer(FA_18C_hornet_FLP_LG_FLAPS_LT, onFlpLgFlapsLtChange);

void onInstPnlDimmerChange(unsigned int newValue) {
updateBacklight(newValue,IFEIBackLightLEDS,74,CRGB::Green,CRGB::Black);

}
DcsBios::IntegerBuffer instPnlDimmerBuffer(FA_18C_hornet_INST_PNL_DIMMER, onInstPnlDimmerChange);


void setup() { 
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOUR_ORDER>(leds, NUM_LEDS);         
  FastLED.setDither(false);
  FastLED.setBrightness(BRIGHTNESS);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();

  DcsBios::setup();

}
void loop() {  
  DcsBios::loop();
}

//==================== Functions ===============================


void updateLEDS(unsigned int newValue, int * theleds, unsigned int ledCount,unsigned int  OnValue, int offValue){
  for(unsigned int a = 0; a < ledCount; a++){
  if(newValue == 1){
     leds[theleds[a]] = OnValue;
  }
  if(newValue == 0){
    leds[theleds[a]] = offValue;
  }
}
 FastLED.show();

}

void updateBacklight(unsigned int newValue, int * testleds, unsigned int ledCount,unsigned int  OnValue, int offValue){
  for(unsigned int a = 0; a < ledCount; a++){
  if(newValue > 7000){
     leds[testleds[a]] = OnValue;
  }
  if(newValue <= 7000 ){
    leds[testleds[a]] = offValue;
  }
}
FastLED.setBrightness(map(newValue,0,65535,0,255));
 FastLED.show();

}


