#ifndef __STATION_SELECT_BACKLIGHT_H
#define __STATION_SELECT_BACKLIGHT_H




#define NUM_STATION_SELECT_LEDS 32

int STATION_SELECT_OFFSET = VIDEO_RECORDER_OFFSET + NUM_VIDEO_RECORDER_LEDS;

int STATION_SELECT_LED_LIST[NUM_STATION_SELECT_LEDS -22]= {1,2,5,6,9,10,12,15,16,19};

CRGB STATION_SELECT_LEDS[NUM_STATION_SELECT_LEDS];


void UpdateStationSelectBacklightLEDS(int value){
  BackLighting::updateBacklight(value, STATION_SELECT_LED_LIST,NUM_STATION_SELECT_LEDS-22,STATION_SELECT_LEDS);
    BackLighting::updateLeftLipLEDS(NUM_STATION_SELECT_LEDS,STATION_SELECT_OFFSET,STATION_SELECT_LEDS);
}


void onSjCtrChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
// int sjCtrLEDS[2] = {63,66};
  STATION_SELECT_LEDS[8] = CHSV(100,255,newValue);
  STATION_SELECT_LEDS[11] = CHSV(100,255,newValue);
  BackLighting::updateLeftLipLEDS(NUM_STATION_SELECT_LEDS,STATION_SELECT_OFFSET,STATION_SELECT_LEDS);
}
DcsBios::IntegerBuffer sjCtrBuffer(FA_18C_hornet_SJ_CTR, onSjCtrChange);

void onSjLiLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  // int sjLiLEDS[2] = {68,69};
  STATION_SELECT_LEDS[13] = CHSV(100,255,newValue);
  STATION_SELECT_LEDS[14] = CHSV(100,255,newValue);
  BackLighting::updateLeftLipLEDS(NUM_STATION_SELECT_LEDS,STATION_SELECT_OFFSET,STATION_SELECT_LEDS);}
DcsBios::IntegerBuffer sjLiLtBuffer(FA_18C_hornet_SJ_LI_LT, onSjLiLtChange);


void onSjLoChange(unsigned int newValue) { 
  if(newValue > 0){newValue = 255;}
  // int sjLoLEDS[2] ={72,73};
  STATION_SELECT_LEDS[17] = CHSV(100,255,newValue);
  STATION_SELECT_LEDS[18] = CHSV(100,255,newValue);
  BackLighting::updateLeftLipLEDS(NUM_STATION_SELECT_LEDS,STATION_SELECT_OFFSET,STATION_SELECT_LEDS);}
DcsBios::IntegerBuffer sjLoBuffer(FA_18C_hornet_SJ_LO, onSjLoChange);



void onSjRiChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  // int sjRiLEDS[2] ={61,59};
  STATION_SELECT_LEDS[7] = CHSV(100,255,newValue);
  STATION_SELECT_LEDS[4] = CHSV(100,255,newValue);
  BackLighting::updateLeftLipLEDS(NUM_STATION_SELECT_LEDS,STATION_SELECT_OFFSET,STATION_SELECT_LEDS);}
DcsBios::IntegerBuffer sjRiBuffer(FA_18C_hornet_SJ_RI, onSjRiChange);



void onSjRoChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  //  int sjRoLEDS[2] = {58,55};
  STATION_SELECT_LEDS[0] = CHSV(100,255,newValue);
  STATION_SELECT_LEDS[3] = CHSV(100,255,newValue);
  BackLighting::updateLeftLipLEDS(NUM_STATION_SELECT_LEDS,STATION_SELECT_OFFSET,STATION_SELECT_LEDS);}
DcsBios::IntegerBuffer sjRoBuffer(FA_18C_hornet_SJ_RO, onSjRoChange);

void onFlpLgNoseGearLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 100;}
  // int noseLtLEDS[2] = {75,86};
  STATION_SELECT_LEDS[20] = CHSV(100,255,newValue);
  STATION_SELECT_LEDS[31] = CHSV(100,255,newValue);
  BackLighting::updateLeftLipLEDS(NUM_STATION_SELECT_LEDS,STATION_SELECT_OFFSET,STATION_SELECT_LEDS);}
DcsBios::IntegerBuffer flpLgNoseGearLtBuffer(FA_18C_hornet_FLP_LG_NOSE_GEAR_LT, onFlpLgNoseGearLtChange);


void onFlpLgRightGearLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 100;}
  // int rightGearLEDS[2] = {76,77};
  STATION_SELECT_LEDS[21] = CHSV(100,255,newValue);
  STATION_SELECT_LEDS[22] = CHSV(100,255,newValue);
  BackLighting::updateLeftLipLEDS(NUM_STATION_SELECT_LEDS,STATION_SELECT_OFFSET,STATION_SELECT_LEDS);}
DcsBios::IntegerBuffer flpLgRightGearLtBuffer(FA_18C_hornet_FLP_LG_RIGHT_GEAR_LT, onFlpLgRightGearLtChange);




void onFlpLgLeftGearLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 100;}
 // int leftGearLEDS[2] = {78,79};
  STATION_SELECT_LEDS[23] = CHSV(100,255,newValue);
  STATION_SELECT_LEDS[24] = CHSV(100,255,newValue);
  BackLighting::updateLeftLipLEDS(NUM_STATION_SELECT_LEDS,STATION_SELECT_OFFSET,STATION_SELECT_LEDS);}
DcsBios::IntegerBuffer flpLgLeftGearLtBuffer(FA_18C_hornet_FLP_LG_LEFT_GEAR_LT, onFlpLgLeftGearLtChange);



void onFlpLgHalfFlapsLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 100;}
  // int halfFlapLEDS[2] ={80,81};
  STATION_SELECT_LEDS[25] = CHSV(100,255,newValue);
  STATION_SELECT_LEDS[26] = CHSV(100,255,newValue);
  BackLighting::updateLeftLipLEDS(NUM_STATION_SELECT_LEDS,STATION_SELECT_OFFSET,STATION_SELECT_LEDS);}
DcsBios::IntegerBuffer flpLgHalfFlapsLtBuffer(FA_18C_hornet_FLP_LG_HALF_FLAPS_LT, onFlpLgHalfFlapsLtChange);


void onFlpLgFullFlapsLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 100;}
  // int fullFlapsLEDS[2] = {82,83};
  STATION_SELECT_LEDS[27] = CHSV(100,255,newValue);
  STATION_SELECT_LEDS[28] = CHSV(100,255,newValue);
  BackLighting::updateLeftLipLEDS(NUM_STATION_SELECT_LEDS,STATION_SELECT_OFFSET,STATION_SELECT_LEDS);}
DcsBios::IntegerBuffer flpLgFullFlapsLtBuffer(FA_18C_hornet_FLP_LG_FULL_FLAPS_LT, onFlpLgFullFlapsLtChange);



void onFlpLgFlapsLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 100;}
  // int flapsLEDS[2] ={84,85};
  STATION_SELECT_LEDS[29] = CHSV(60,255,newValue);
  STATION_SELECT_LEDS[30] = CHSV(60,255,newValue);
  BackLighting::updateLeftLipLEDS(NUM_STATION_SELECT_LEDS,STATION_SELECT_OFFSET,STATION_SELECT_LEDS);}
DcsBios::IntegerBuffer flpLgFlapsLtBuffer(FA_18C_hornet_FLP_LG_FLAPS_LT, onFlpLgFlapsLtChange);


#endif




