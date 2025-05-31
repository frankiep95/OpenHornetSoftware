#ifndef __LEWI_BACKLIGHT_H
#define __LEWI_BACKLIGHT_H

#define NUM_LEWI_LEDS 30

int LEWI_OFFSET = NUM_MASTER_ARM_LEDS;

int LEWI_LED_LIST[NUM_LEWI_LEDS-30] = {};

CRGB LEWI_LEDS[NUM_LEWI_LEDS];

void UpdateLEWIBacklightLEDS(int value){
  BackLighting::updateBacklight(value, LEWI_LED_LIST,NUM_LEWI_LEDS-30,LEWI_LEDS);
    BackLighting::updateUIPLEDS(NUM_LEWI_LEDS,LEWI_OFFSET,LEWI_LEDS);
}

void onFireLeftLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  LEWI_LEDS[0] = CHSV(0,255,newValue);
  LEWI_LEDS[1] = CHSV(0,255,newValue);
  LEWI_LEDS[2] = CHSV(0,255,newValue);
  LEWI_LEDS[3] = CHSV(0,255,newValue);
  BackLighting::updateUIPLEDS(NUM_LEWI_LEDS,LEWI_OFFSET,LEWI_LEDS);
}DcsBios::IntegerBuffer fireLeftLtBuffer(FA_18C_hornet_FIRE_LEFT_LT, onFireLeftLtChange);

void onMasterCautionLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  LEWI_LEDS[4] = CHSV(45,255,newValue);
  LEWI_LEDS[5] = CHSV(45,255,newValue);
  LEWI_LEDS[6] = CHSV(45,255,newValue);
  LEWI_LEDS[7] = CHSV(45,255,newValue);
  BackLighting::updateUIPLEDS(NUM_LEWI_LEDS,LEWI_OFFSET,LEWI_LEDS);
}DcsBios::IntegerBuffer masterCautionLtBuffer(FA_18C_hornet_MASTER_CAUTION_LT, onMasterCautionLtChange);

void onLhAdvGoChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  LEWI_LEDS[8] = CHSV(100,255,newValue);
  LEWI_LEDS[9] = CHSV(100,255,newValue);
  BackLighting::updateUIPLEDS(NUM_LEWI_LEDS,LEWI_OFFSET,LEWI_LEDS);
}DcsBios::IntegerBuffer lhAdvGoBuffer(FA_18C_hornet_LH_ADV_GO, onLhAdvGoChange);

void onLhAdvNoGoChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  LEWI_LEDS[10] = CHSV(45,255,newValue);
  LEWI_LEDS[11] = CHSV(45,255,newValue);
  BackLighting::updateUIPLEDS(NUM_LEWI_LEDS,LEWI_OFFSET,LEWI_LEDS);
}DcsBios::IntegerBuffer lhAdvNoGoBuffer(FA_18C_hornet_LH_ADV_NO_GO, onLhAdvNoGoChange);

void onLhAdvRBleedChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  LEWI_LEDS[12] = CHSV(0,255,newValue);
  LEWI_LEDS[13] = CHSV(0,255,newValue);
  BackLighting::updateUIPLEDS(NUM_LEWI_LEDS,LEWI_OFFSET,LEWI_LEDS);
}DcsBios::IntegerBuffer lhAdvRBleedBuffer(FA_18C_hornet_LH_ADV_R_BLEED, onLhAdvRBleedChange);

void onLhAdvLBleedChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  LEWI_LEDS[14] = CHSV(0,255,newValue);
  LEWI_LEDS[15] = CHSV(0,255,newValue);
  BackLighting::updateUIPLEDS(NUM_LEWI_LEDS,LEWI_OFFSET,LEWI_LEDS);
}DcsBios::IntegerBuffer lhAdvLBleedBuffer(FA_18C_hornet_LH_ADV_L_BLEED, onLhAdvLBleedChange);

void onLhAdvSpdBrkChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  LEWI_LEDS[16] = CHSV(100,255,newValue);
  LEWI_LEDS[17] = CHSV(100,255,newValue);
  BackLighting::updateUIPLEDS(NUM_LEWI_LEDS,LEWI_OFFSET,LEWI_LEDS);
}DcsBios::IntegerBuffer lhAdvSpdBrkBuffer(FA_18C_hornet_LH_ADV_SPD_BRK, onLhAdvSpdBrkChange);

void onLhAdvStbyChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  LEWI_LEDS[18] = CHSV(100,255,newValue);
  LEWI_LEDS[19] = CHSV(100,255,newValue);
  BackLighting::updateUIPLEDS(NUM_LEWI_LEDS,LEWI_OFFSET,LEWI_LEDS);
}DcsBios::IntegerBuffer lhAdvStbyBuffer(FA_18C_hornet_LH_ADV_STBY, onLhAdvStbyChange);

void onLhAdvRecChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  LEWI_LEDS[20] = CHSV(100,255,newValue);
  LEWI_LEDS[21] = CHSV(100,255,newValue);
  BackLighting::updateUIPLEDS(NUM_LEWI_LEDS,LEWI_OFFSET,LEWI_LEDS);
}DcsBios::IntegerBuffer lhAdvRecBuffer(FA_18C_hornet_LH_ADV_REC, onLhAdvRecChange);

void onLhAdvLBarGreenChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  LEWI_LEDS[22] = CHSV(100,255,newValue);
  LEWI_LEDS[23] = CHSV(100,255,newValue);
  BackLighting::updateUIPLEDS(NUM_LEWI_LEDS,LEWI_OFFSET,LEWI_LEDS);
}DcsBios::IntegerBuffer lhAdvLBarGreenBuffer(FA_18C_hornet_LH_ADV_L_BAR_GREEN, onLhAdvLBarGreenChange);

void onLhAdvLBarRedChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  LEWI_LEDS[24] = CHSV(0,255,newValue);
  LEWI_LEDS[25] = CHSV(0,255,newValue);
  BackLighting::updateUIPLEDS(NUM_LEWI_LEDS,LEWI_OFFSET,LEWI_LEDS);
}DcsBios::IntegerBuffer lhAdvLBarRedBuffer(FA_18C_hornet_LH_ADV_L_BAR_RED, onLhAdvLBarRedChange);

void onLhAdvXmitChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  LEWI_LEDS[26] = CHSV(100,255,newValue);
  LEWI_LEDS[27] = CHSV(100,255,newValue);
  BackLighting::updateUIPLEDS(NUM_LEWI_LEDS,LEWI_OFFSET,LEWI_LEDS);
}DcsBios::IntegerBuffer lhAdvXmitBuffer(FA_18C_hornet_LH_ADV_XMIT, onLhAdvXmitChange);

void onLhAdvAspjOhChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  LEWI_LEDS[28] = CHSV(45,255,newValue);
  LEWI_LEDS[29] = CHSV(45,255,newValue);
  BackLighting::updateUIPLEDS(NUM_LEWI_LEDS,LEWI_OFFSET,LEWI_LEDS);
}DcsBios::IntegerBuffer lhAdvAspjOhBuffer(FA_18C_hornet_LH_ADV_ASPJ_OH, onLhAdvAspjOhChange);


#endif