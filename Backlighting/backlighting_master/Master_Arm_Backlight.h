#ifndef __MASTER_ARM_BACKLIGHT_H
#define __MASTER_ARM_BACKLIGHT_H

#define NUM_MASTER_ARM_LEDS 29

int MASTER_ARM_OFFSET = 0;

int MASTER_ARM_LED_LIST[NUM_MASTER_ARM_LEDS-8] = {4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};

CRGB MASTER_ARM_LEDS[NUM_MASTER_ARM_LEDS];

void UpdateMasterArmBacklightLEDS(int value){
  BackLighting::updateBacklight(value, MASTER_ARM_LED_LIST,NUM_MASTER_ARM_LEDS-8,MASTER_ARM_LEDS);
    BackLighting::updateUIPLEDS(NUM_MASTER_ARM_LEDS,MASTER_ARM_OFFSET,MASTER_ARM_LEDS);
}

void onMcReadyChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  MASTER_ARM_LEDS[0] = CHSV(45,255,newValue);
  MASTER_ARM_LEDS[1] = CHSV(45,255,newValue);
  BackLighting::updateUIPLEDS(NUM_MASTER_ARM_LEDS,MASTER_ARM_OFFSET,MASTER_ARM_LEDS);
}DcsBios::IntegerBuffer mcReadyBuffer(FA_18C_hornet_MC_READY, onMcReadyChange);

void onMcDischChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  MASTER_ARM_LEDS[2] = CHSV(100,255,newValue);
  MASTER_ARM_LEDS[3] = CHSV(100,255,newValue);
  BackLighting::updateUIPLEDS(NUM_MASTER_ARM_LEDS,MASTER_ARM_OFFSET,MASTER_ARM_LEDS);
}DcsBios::IntegerBuffer mcDischBuffer(FA_18C_hornet_MC_DISCH, onMcDischChange);

void onMasterModeAaLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  MASTER_ARM_LEDS[27] = CHSV(100,255,newValue);
  MASTER_ARM_LEDS[28] = CHSV(100,255,newValue);
  BackLighting::updateUIPLEDS(NUM_MASTER_ARM_LEDS,MASTER_ARM_OFFSET,MASTER_ARM_LEDS);
}DcsBios::IntegerBuffer masterModeAaLtBuffer(FA_18C_hornet_MASTER_MODE_AA_LT, onMasterModeAaLtChange);

void onMasterModeAgLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  MASTER_ARM_LEDS[25] = CHSV(100,255,newValue);
  MASTER_ARM_LEDS[26] = CHSV(100,255,newValue);
  BackLighting::updateUIPLEDS(NUM_MASTER_ARM_LEDS,MASTER_ARM_OFFSET,MASTER_ARM_LEDS);
}DcsBios::IntegerBuffer masterModeAgLtBuffer(FA_18C_hornet_MASTER_MODE_AG_LT, onMasterModeAgLtChange);



#endif