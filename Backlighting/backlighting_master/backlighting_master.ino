
#define DCSBIOS_DEFAULT_SERIAL
#include "backlighting_master.h"


unsigned int instrumentValue = 0;
unsigned int consoleValue = 0;
unsigned int oldConsole = 0;
unsigned int oldInstrument =0;


void onInstPnlDimmerChange(unsigned int newValue) {
  instrumentValue = newValue;
}
DcsBios::IntegerBuffer instPnlDimmerBuffer(FA_18C_hornet_INST_PNL_DIMMER, onInstPnlDimmerChange);


void onConsolesDimmerChange(unsigned int newValue) {
  consoleValue = newValue;
}DcsBios::IntegerBuffer consolesDimmerBuffer(FA_18C_hornet_CONSOLES_DIMMER, onConsolesDimmerChange);

void setup() { 
  Serial.begin(115200);

  FastLED.addLeds<LED_TYPE, LIP_CH1,COLOUR_ORDER>(LEFT_LIP_LEDS, LEFT_LIP_NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LIP_CH2,COLOUR_ORDER>(LIP_LEDS,LIP_NUM_LEDS);  
  FastLED.addLeds<LED_TYPE, UIP_CH1,COLOUR_ORDER>(UIP_LEDS,UIP_NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LC_CH1,COLOUR_ORDER>(LC_LEDS,LC_NUM_LEDS);       
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
  updateInstruments(0);
  // updateConsoles(0);
}

unsigned long instrumentStartTime = 0;
bool instrumentUpdate = false;
void updateInstruments(int delayTime) {

  if ((instrumentValue != oldInstrument)) {
    if (instrumentUpdate == false) {
      instrumentStartTime = millis();
      instrumentUpdate = true;
    }
    if (instrumentUpdate && (millis() - instrumentStartTime >= delayTime)) {
      UpdateIFEIBacklightLEDS(instrumentValue);
      UpdateVideoRecorderBacklightLEDS(instrumentValue);
      UpdateStationSelectBacklightLEDS(instrumentValue);
      UpdateJettPlacardBacklightLEDS(instrumentValue);
      UpdateECMDispenseBacklightLEDS(instrumentValue);
      UpdateRWRControlBacklightLEDS(instrumentValue);
      UpdateCabinPressureBacklightLEDS(instrumentValue);
      UpdateMasterArmBacklightLEDS(instrumentValue);
      UpdateHudPanelBacklightLEDS(instrumentValue);
      UpdateSpinRecoveryBacklightLEDS(instrumentValue);
      oldInstrument = instrumentValue;
      instrumentUpdate = false;
    }
  }
}

unsigned long consoleStartTime = 0;
bool consoleUpdate = false;
void updateConsoles(int delayTime) {
  if ((consoleValue != oldConsole) ) {

    if (consoleUpdate == false) {
      consoleStartTime = millis();
      consoleUpdate = true;
    }
    if (consoleUpdate && (millis() - consoleStartTime >= delayTime)) {
      UpdateLandingGearBacklightLEDS(consoleValue);
      // UpdateSelectJettBacklightLEDS(newValue);
      // UpdateFireTestBacklightLEDS(newValue);
      // UpdateSimPowerBacklightLEDS(newValue);
      // UpdateGenTieBacklightLEDS(newValue);
      // UpdateExtLightsBacklightLEDS(newValue);

      oldConsole = consoleValue;
      consoleUpdate = false;
    }
  }
}



