
#define DCSBIOS_DEFAULT_SERIAL
#include "backlighting_master.h"


void onInstPnlDimmerChange(unsigned int newValue) {
  UpdateIFEIBacklightLEDS(newValue);
  UpdateVideoRecorderBacklightLEDS(newValue);
  UpdateStationSelectBacklightLEDS(newValue);
  UpdateJettPlacardBacklightLEDS(newValue);
  UpdateECMDispenseBacklightLEDS(newValue);
  UpdateRWRControlBacklightLEDS(newValue);
  UpdateCabinPressureBacklightLEDS(newValue);
  UpdateMasterArmBacklightLEDS(newValue);
  UpdateHudPanelBacklightLEDS(newValue);
  UpdateSpinRecoveryBacklightLEDS(newValue);
}
DcsBios::IntegerBuffer instPnlDimmerBuffer(FA_18C_hornet_INST_PNL_DIMMER, onInstPnlDimmerChange);


void setup() { 
  Serial.begin(115200);

  FastLED.addLeds<LED_TYPE, LIP_CH1,COLOUR_ORDER>(LEFT_LIP_LEDS, LEFT_LIP_NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LIP_CH2,COLOUR_ORDER>(LIP_LEDS,LIP_NUM_LEDS);  
  FastLED.addLeds<LED_TYPE, UIP_CH1,COLOUR_ORDER>(UIP_LEDS,UIP_NUM_LEDS);       
  FastLED.setDither(false);
  FastLED.clearData();
  FastLED.show();
  DcsBios::setup();

// onInstPnlDimmerChange(40000);
// onFireRightLtChange(1);
// onFireApuLtChange(1);

}
void loop() {  
  DcsBios::loop();
}



