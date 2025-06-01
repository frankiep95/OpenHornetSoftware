#ifndef __REWI_BACKLIGHT_H
#define __REWI_BACKLIGHT_H

#define NUM_REWI_LEDS 30

int REWI_OFFSET = NUM_HUD_PANEL_LEDS + HUD_PANEL_OFFSET;

int REWI_LED_LIST[NUM_REWI_LEDS-30] = {};

CRGB REWI_LEDS[NUM_REWI_LEDS];

void UpdateREWIBacklightLEDS(int value){
  BackLighting::updateBacklight(value, REWI_LED_LIST,NUM_REWI_LEDS-30,REWI_LEDS);
    BackLighting::updateUIPLEDS(NUM_REWI_LEDS,REWI_OFFSET,REWI_LEDS);
}

void onFireRightLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  REWI_LEDS[0] = CHSV(0,255,newValue);
  REWI_LEDS[1] = CHSV(0,255,newValue);
  REWI_LEDS[2] = CHSV(0,255,newValue);
  REWI_LEDS[3] = CHSV(0,255,newValue);
  BackLighting::updateUIPLEDS(NUM_REWI_LEDS,REWI_OFFSET,REWI_LEDS);
}DcsBios::IntegerBuffer fireRightLtBuffer(FA_18C_hornet_FIRE_RIGHT_LT, onFireRightLtChange);

void onFireApuLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  REWI_LEDS[4] = CHSV(0,255,newValue);
  REWI_LEDS[5] = CHSV(0,255,newValue);
  REWI_LEDS[6] = CHSV(0,255,newValue);
  REWI_LEDS[7] = CHSV(0,255,newValue);
  BackLighting::updateUIPLEDS(NUM_REWI_LEDS,REWI_OFFSET,REWI_LEDS);
}DcsBios::IntegerBuffer fireApuLtBuffer(FA_18C_hornet_FIRE_APU_LT, onFireApuLtChange);

void onRhAdvDispChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  REWI_LEDS[8] = CHSV(100,255,newValue);
  REWI_LEDS[9] = CHSV(100,255,newValue);
  BackLighting::updateUIPLEDS(NUM_REWI_LEDS,REWI_OFFSET,REWI_LEDS);
}DcsBios::IntegerBuffer rhAdvDispBuffer(FA_18C_hornet_RH_ADV_DISP, onRhAdvDispChange);

void onRhAdvRcdrOnChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  REWI_LEDS[10] = CHSV(100,255,newValue);
  REWI_LEDS[11] = CHSV(100,255,newValue);
  BackLighting::updateUIPLEDS(NUM_REWI_LEDS,REWI_OFFSET,REWI_LEDS);
}DcsBios::IntegerBuffer rhAdvRcdrOnBuffer(FA_18C_hornet_RH_ADV_RCDR_ON, onRhAdvRcdrOnChange);

void onRhAdvSpareRh1Change(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  REWI_LEDS[12] = CHSV(100,255,newValue);
  REWI_LEDS[13] = CHSV(100,255,newValue);
  BackLighting::updateUIPLEDS(NUM_REWI_LEDS,REWI_OFFSET,REWI_LEDS);
}DcsBios::IntegerBuffer rhAdvSpareRh1Buffer(FA_18C_hornet_RH_ADV_SPARE_RH1, onRhAdvSpareRh1Change);

void onRhAdvSpareRh2Change(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  REWI_LEDS[14] = CHSV(100,255,newValue);
  REWI_LEDS[15] = CHSV(100,255,newValue);
  BackLighting::updateUIPLEDS(NUM_REWI_LEDS,REWI_OFFSET,REWI_LEDS);
}DcsBios::IntegerBuffer rhAdvSpareRh2Buffer(FA_18C_hornet_RH_ADV_SPARE_RH2, onRhAdvSpareRh2Change);

void onRhAdvSpareRh3Change(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  REWI_LEDS[16] = CHSV(100,255,newValue);
  REWI_LEDS[17] = CHSV(100,255,newValue);
  BackLighting::updateUIPLEDS(NUM_REWI_LEDS,REWI_OFFSET,REWI_LEDS);
}DcsBios::IntegerBuffer rhAdvSpareRh3Buffer(FA_18C_hornet_RH_ADV_SPARE_RH3, onRhAdvSpareRh3Change);

void onRhAdvSpareRh4Change(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  REWI_LEDS[18] = CHSV(100,255,newValue);
  REWI_LEDS[19] = CHSV(100,255,newValue);
  BackLighting::updateUIPLEDS(NUM_REWI_LEDS,REWI_OFFSET,REWI_LEDS);
}DcsBios::IntegerBuffer rhAdvSpareRh4Buffer(FA_18C_hornet_RH_ADV_SPARE_RH4, onRhAdvSpareRh4Change);


void onRhAdvSamChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  REWI_LEDS[20] = CHSV(100,255,newValue);
  REWI_LEDS[21] = CHSV(100,255,newValue);
  BackLighting::updateUIPLEDS(NUM_REWI_LEDS,REWI_OFFSET,REWI_LEDS);
}DcsBios::IntegerBuffer rhAdvSamBuffer(FA_18C_hornet_RH_ADV_SAM, onRhAdvSamChange);

void onRhAdvSpareRh5Change(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  REWI_LEDS[22] = CHSV(100,255,newValue);
  REWI_LEDS[23] = CHSV(100,255,newValue);
  BackLighting::updateUIPLEDS(NUM_REWI_LEDS,REWI_OFFSET,REWI_LEDS);
}DcsBios::IntegerBuffer rhAdvSpareRh5Buffer(FA_18C_hornet_RH_ADV_SPARE_RH5, onRhAdvSpareRh5Change);


void onRhAdvAaaChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  REWI_LEDS[24] = CHSV(100,255,newValue);
  REWI_LEDS[25] = CHSV(100,255,newValue);
  BackLighting::updateUIPLEDS(NUM_REWI_LEDS,REWI_OFFSET,REWI_LEDS);
}DcsBios::IntegerBuffer rhAdvAaaBuffer(FA_18C_hornet_RH_ADV_AAA, onRhAdvAaaChange);

void onRhAdvAiChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  REWI_LEDS[26] = CHSV(100,255,newValue);
  REWI_LEDS[27] = CHSV(100,255,newValue);
  BackLighting::updateUIPLEDS(NUM_REWI_LEDS,REWI_OFFSET,REWI_LEDS);  
}DcsBios::IntegerBuffer rhAdvAiBuffer(FA_18C_hornet_RH_ADV_AI, onRhAdvAiChange);

void onRhAdvCwChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  REWI_LEDS[28] = CHSV(100,255,newValue);
  REWI_LEDS[29] = CHSV(100,255,newValue);
  BackLighting::updateUIPLEDS(NUM_REWI_LEDS,REWI_OFFSET,REWI_LEDS);
}DcsBios::IntegerBuffer rhAdvCwBuffer(FA_18C_hornet_RH_ADV_CW, onRhAdvCwChange);



#endif