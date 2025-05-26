#define DCSBIOS_MUX_SERIAL
#include <DcsBios.h>
#include "Arduino.h"


// DcsBios::ActionButton sjCtrToggle("SJ_CTR", "TOGGLE", A2);
// DcsBios::ActionButton sjLiToggle("SJ_LI", "TOGGLE", A3);
// DcsBios::ActionButton sjLoToggle("SJ_LO", "TOGGLE", 2);
// DcsBios::ActionButton sjRiToggle("SJ_RI", "TOGGLE", A1);
// DcsBios::ActionButton sjRoToggle("SJ_RO", "TOGGLE", A6);


// Define pins for DCS-BIOS per interconnect diagram.
#define LI_SW A3      ///< LI Switch
#define LO_SW 2      ///< LO Switch
#define CTR_SW A2    ///< CTR Switch
#define RI_SW A1     ///< RI Switch
#define RO_SW 4      ///< RO Switch
#define UP_SW 3      ///< UP Switch
#define DOWN_SW A0   ///< DOWN Switch
#define QTY_SW 15    ///< QTY Switch
#define ZONE_SW 6    ///< ZONE Switch
#define MODE_SW 14   ///< MODE Switch
#define ET_SW 7      ///< ET Switch
#define VR_MAN 16    ///< VR MAN
#define VR_AUTO 8    ///< VR Auto
#define VR_LDDI 10   ///< VR LDDI - Switch in SIM is 3 position
#define VR_A_IFEI 9  ///< VR IFEI Brightness

// Connect switches to DCS-BIOS
DcsBios::Potentiometer ifei("IFEI", VR_A_IFEI);
DcsBios::Switch3Pos modeSelectorSw("MODE_SELECTOR_SW", VR_AUTO, VR_MAN);

DcsBios::Switch2Pos ifeiDwnBtn("IFEI_DWN_BTN", DOWN_SW);
DcsBios::Switch2Pos ifeiEtBtn("IFEI_ET_BTN", ET_SW);
DcsBios::Switch2Pos ifeiModeBtn("IFEI_MODE_BTN", MODE_SW);
DcsBios::Switch2Pos ifeiQtyBtn("IFEI_QTY_BTN", QTY_SW);
DcsBios::Switch2Pos ifeiUpBtn("IFEI_UP_BTN", UP_SW);
DcsBios::Switch2Pos ifeiZoneBtn("IFEI_ZONE_BTN", ZONE_SW);

DcsBios::ActionButton sjCtrToggle("SJ_CTR", "TOGGLE", CTR_SW);
DcsBios::ActionButton sjLiToggle("SJ_LI", "TOGGLE", LI_SW);
DcsBios::ActionButton sjLoToggle("SJ_LO", "TOGGLE", LO_SW);
DcsBios::ActionButton sjRiToggle("SJ_RI", "TOGGLE", RI_SW);
DcsBios::ActionButton sjRoToggle("SJ_RO", "TOGGLE", RO_SW);


void setup()
{
DcsBios::setup();
}

void loop(){
  DcsBios::loop();

}