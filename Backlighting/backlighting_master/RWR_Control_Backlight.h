#ifndef __RWR_CONTROL_BACKLIGHT_H
#define __RWR_CONTROL_BACKLIGHT_H

#define NUM_RWR_CONTROL_LEDS 33

int RWR_CONTROL_OFFSET = 0;

int RWR_CONTROL_LED_LIST[NUM_RWR_CONTROL_LEDS -18] = {0,1,2,3,4,5,6,23,26,27,28,29,30,31,32};

CRGB RWR_CONTROL_LEDS[NUM_RWR_CONTROL_LEDS];

void UpdateRWRControlBacklightLEDS(int value){
  BackLighting::updateBacklight(value, RWR_CONTROL_LED_LIST,NUM_RWR_CONTROL_LEDS-18,RWR_CONTROL_LEDS);
  BackLighting::updateLipLEDS(NUM_RWR_CONTROL_LEDS,RWR_CONTROL_OFFSET,RWR_CONTROL_LEDS);
}

void onRwrBitLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  RWR_CONTROL_LEDS[7] = CHSV(100,255,newValue);
  RWR_CONTROL_LEDS[10] = CHSV(100,255,newValue);
  BackLighting::updateLipLEDS(NUM_RWR_CONTROL_LEDS,RWR_CONTROL_OFFSET,RWR_CONTROL_LEDS);
}DcsBios::IntegerBuffer rwrBitLtBuffer(FA_18C_hornet_RWR_BIT_LT, onRwrBitLtChange);

void onRwrFailLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  RWR_CONTROL_LEDS[8] = CHSV(100,255,newValue);
  RWR_CONTROL_LEDS[9] = CHSV(100,255,newValue);
  BackLighting::updateLipLEDS(NUM_RWR_CONTROL_LEDS,RWR_CONTROL_OFFSET,RWR_CONTROL_LEDS);
}DcsBios::IntegerBuffer rwrFailLtBuffer(FA_18C_hornet_RWR_FAIL_LT, onRwrFailLtChange);

void onRwrEnableLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  RWR_CONTROL_LEDS[12] = CHSV(100,255,newValue);
  RWR_CONTROL_LEDS[13] = CHSV(100,255,newValue);
  BackLighting::updateLipLEDS(NUM_RWR_CONTROL_LEDS,RWR_CONTROL_OFFSET,RWR_CONTROL_LEDS);
}DcsBios::IntegerBuffer rwrEnableLtBuffer(FA_18C_hornet_RWR_ENABLE_LT, onRwrEnableLtChange);

void onRwrOffsetLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  RWR_CONTROL_LEDS[11] = CHSV(100,255,newValue);
  RWR_CONTROL_LEDS[14] = CHSV(100,255,newValue);
  BackLighting::updateLipLEDS(NUM_RWR_CONTROL_LEDS,RWR_CONTROL_OFFSET,RWR_CONTROL_LEDS);
}DcsBios::IntegerBuffer rwrOffsetLtBuffer(FA_18C_hornet_RWR_OFFSET_LT, onRwrOffsetLtChange);

void onRwrSpecialLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  RWR_CONTROL_LEDS[15] = CHSV(100,255,newValue);
  RWR_CONTROL_LEDS[18] = CHSV(100,255,newValue);
  BackLighting::updateLipLEDS(NUM_RWR_CONTROL_LEDS,RWR_CONTROL_OFFSET,RWR_CONTROL_LEDS);
}DcsBios::IntegerBuffer rwrSpecialLtBuffer(FA_18C_hornet_RWR_SPECIAL_LT, onRwrSpecialLtChange);

void onRwrSpecialEnLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  RWR_CONTROL_LEDS[16] = CHSV(100,255,newValue);
  RWR_CONTROL_LEDS[17] = CHSV(100,255,newValue);
  BackLighting::updateLipLEDS(NUM_RWR_CONTROL_LEDS,RWR_CONTROL_OFFSET,RWR_CONTROL_LEDS);
}DcsBios::IntegerBuffer rwrSpecialEnLtBuffer(FA_18C_hornet_RWR_SPECIAL_EN_LT, onRwrSpecialEnLtChange);

void onRwrDisplayLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  RWR_CONTROL_LEDS[19] = CHSV(100,255,newValue);
  RWR_CONTROL_LEDS[22] = CHSV(100,255,newValue);
  BackLighting::updateLipLEDS(NUM_RWR_CONTROL_LEDS,RWR_CONTROL_OFFSET,RWR_CONTROL_LEDS);
}DcsBios::IntegerBuffer rwrDisplayLtBuffer(FA_18C_hornet_RWR_DISPLAY_LT, onRwrDisplayLtChange);

void onRwrLimitLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  RWR_CONTROL_LEDS[20] = CHSV(100,255,newValue);
  RWR_CONTROL_LEDS[21] = CHSV(100,255,newValue);
  BackLighting::updateLipLEDS(NUM_RWR_CONTROL_LEDS,RWR_CONTROL_OFFSET,RWR_CONTROL_LEDS);
}DcsBios::IntegerBuffer rwrLimitLtBuffer(FA_18C_hornet_RWR_LIMIT_LT, onRwrLimitLtChange);

void onRwrLowerLtChange(unsigned int newValue) {
  if(newValue > 0){newValue = 255;}
  RWR_CONTROL_LEDS[24] = CHSV(100,255,newValue);
  RWR_CONTROL_LEDS[25] = CHSV(100,255,newValue);
  BackLighting::updateLipLEDS(NUM_RWR_CONTROL_LEDS,RWR_CONTROL_OFFSET,RWR_CONTROL_LEDS);
}DcsBios::IntegerBuffer rwrLowerLtBuffer(FA_18C_hornet_RWR_LOWER_LT, onRwrLowerLtChange);


#endif