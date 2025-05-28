#define NUM_STATION_SELECT_LEDS 32

int STATION_SELECT_LED_LIST[NUM_STATION_SELECT_LEDS -8]= {1,2,5,7,9,10,12,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};

CRGBArray<NUM_STATION_SELECT_LEDS> STATION_SELECT_LEDS;


void onSjCtrChange(unsigned int newValue) {
    if(newValue > 0){newValue = 255;}

  // int sjCtrLEDS[2] = {63,66};
  // updateLEDS(newValue,sjCtrLEDS,2,GLOBAL_HUE,255);
      STATION_SELECT_LEDS[8] = CHSV(100,255,newValue);
    STATION_SELECT_LEDS[11] = CHSV(100,255,newValue);
      FastLED.show();

}
DcsBios::IntegerBuffer sjCtrBuffer(FA_18C_hornet_SJ_CTR, onSjCtrChange);

void onSjLiLtChange(unsigned int newValue) {
    if(newValue > 0){newValue = 255;}

    // int sjLiLEDS[2] = {68,69};
    STATION_SELECT_LEDS[13] = CHSV(100,255,newValue);
    STATION_SELECT_LEDS[14] = CHSV(100,255,newValue);
  // backlight::updateLEDS(newValue,sjLiLEDS,2,GLOBAL_HUE,255,STATION_SELECT_LEDS);
  FastLED.show();
}
DcsBios::IntegerBuffer sjLiLtBuffer(FA_18C_hornet_SJ_LI_LT, onSjLiLtChange);


// void onSjLoChange(unsigned int newValue) { 
//     if(newValue > 0){newValue = 255;}

// int sjLoLEDS[2] ={72,73};
// updateLEDS(newValue,sjLoLEDS,2,GLOBAL_HUE,255);
// }
// DcsBios::IntegerBuffer sjLoBuffer(FA_18C_hornet_SJ_LO, onSjLoChange);



void onSjRiChange(unsigned int newValue) {
    if(newValue > 0){newValue = 255;}

  // int sjRiLEDS[2] ={61,59};
  // updateLEDS(newValue,sjRiLEDS,2,100,255);
      STATION_SELECT_LEDS[4] = CHSV(100,255,newValue);
    STATION_SELECT_LEDS[6] = CHSV(100,255,newValue);
      FastLED.show();
}
DcsBios::IntegerBuffer sjRiBuffer(FA_18C_hornet_SJ_RI, onSjRiChange);



void onSjRoChange(unsigned int newValue) {
    if(newValue > 0){newValue = 255;}

//  int sjRoLEDS[2] = {58,55};
//  updateLEDS(newValue,sjRoLEDS,2,GLOBAL_HUE,255);
    STATION_SELECT_LEDS[0] = CHSV(100,255,newValue);
    STATION_SELECT_LEDS[3] = CHSV(100,255,newValue);
      FastLED.show();

}
DcsBios::IntegerBuffer sjRoBuffer(FA_18C_hornet_SJ_RO, onSjRoChange);

// void onFlpLgNoseGearLtChange(unsigned int newValue) {
//     if(newValue > 0){newValue = 100;}

// int noseLtLEDS[2] = {75,86};
// updateLEDS(newValue,noseLtLEDS,2,GLOBAL_HUE,255);
// }
// DcsBios::IntegerBuffer flpLgNoseGearLtBuffer(FA_18C_hornet_FLP_LG_NOSE_GEAR_LT, onFlpLgNoseGearLtChange);


// void onFlpLgRightGearLtChange(unsigned int newValue) {
//       if(newValue > 0){newValue = 100;}
// int rightGearLEDS[2] = {76,77};
// updateLEDS(newValue,rightGearLEDS,2,GLOBAL_HUE,255);
// }
// DcsBios::IntegerBuffer flpLgRightGearLtBuffer(FA_18C_hornet_FLP_LG_RIGHT_GEAR_LT, onFlpLgRightGearLtChange);




// void onFlpLgLeftGearLtChange(unsigned int newValue) {
//       if(newValue > 0){newValue = 100;}
// int leftGearLEDS[2] = {78,79};
// updateLEDS(newValue,leftGearLEDS,2,GLOBAL_HUE,255);
// }
// DcsBios::IntegerBuffer flpLgLeftGearLtBuffer(FA_18C_hornet_FLP_LG_LEFT_GEAR_LT, onFlpLgLeftGearLtChange);



// void onFlpLgHalfFlapsLtChange(unsigned int newValue) {
//       if(newValue > 0){newValue = 100;}
// int halfFlapLEDS[2] ={80,81};
// updateLEDS(newValue,halfFlapLEDS,2,GLOBAL_HUE,255);
// }
// DcsBios::IntegerBuffer flpLgHalfFlapsLtBuffer(FA_18C_hornet_FLP_LG_HALF_FLAPS_LT, onFlpLgHalfFlapsLtChange);


// void onFlpLgFullFlapsLtChange(unsigned int newValue) {
//       if(newValue > 0){newValue = 100;}
// int fullFlapsLEDS[2] = {82,83};
// updateLEDS(newValue,fullFlapsLEDS,2,GLOBAL_HUE,255);
// }
// DcsBios::IntegerBuffer flpLgFullFlapsLtBuffer(FA_18C_hornet_FLP_LG_FULL_FLAPS_LT, onFlpLgFullFlapsLtChange);



// void onFlpLgFlapsLtChange(unsigned int newValue) {
//       if(newValue > 0){newValue = 100;}
// int flapsLEDS[2] ={84,85};
// updateLEDS(newValue,flapsLEDS,2,50,255);
// }
// DcsBios::IntegerBuffer flpLgFlapsLtBuffer(FA_18C_hornet_FLP_LG_FLAPS_LT, onFlpLgFlapsLtChange);







//Functions

// void updateLEDS(unsigned int newValue, int * theleds, unsigned int ledCount, int  hue, int saturation){
//   for(unsigned int a = 0; a < ledCount; a++){
//     STATION_SELECT_LEDS[theleds[a]] = CHSV(hue,saturation,newValue);
// }
// //  FastLED.show();

// }