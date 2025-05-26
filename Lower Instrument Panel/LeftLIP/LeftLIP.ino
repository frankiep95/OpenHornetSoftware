/**************************************************************************************
 *        ____                   _    _                       _
 *       / __ \                 | |  | |                     | |
 *      | |  | |_ __   ___ _ __ | |__| | ___  _ __ _ __   ___| |_
 *      | |  | | '_ \ / _ \ '_ \|  __  |/ _ \| '__| '_ \ / _ \ __|
 *      | |__| | |_) |  __/ | | | |  | | (_) | |  | | | |  __/ |_
 *       \____/| .__/ \___|_| |_|_|  |_|\___/|_|  |_| |_|\___|\__|
 *             | |
 *             |_|
 *   ----------------------------------------------------------------------------------
 *   Copyright 2016-2024 OpenHornet
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *   ----------------------------------------------------------------------------------
 *   Note: All other portions of OpenHornet not within the 'OpenHornet-Software' 
 *   GitHub repository is released under the Creative Commons Attribution -
 *   Non-Commercial - Share Alike License. (CC BY-NC-SA 4.0)
 *   ----------------------------------------------------------------------------------
 *   This Project uses Doxygen as a documentation generator.
 *   Please use Doxygen capable comments.
 **************************************************************************************/

/**
 * @file LeftLIP.ino
 * @author Circuit
 * @date 11.09.2024
 * @version 0.0.1
 * @copyright Copyright 2016-2024 OpenHornet. Licensed under the Apache License, Version 2.0.
 * @brief Controls the RWR CONTROL panel.
 *
 * @details
 * 
 *  * **Reference Designator:** 2A2A1
 *  * **Intended Board:** ABSIS ALE
 *  * **RS485 Bus Address:** 1
 * 
 * ### Wiring diagram:
 * PIN | Function
 * --- | ---
 * A3  | LI_SW
 * 2   | LO_SW
 * A2  | CTR_SW
 * A1  | RI_SW
 * 4   | RO_SW
 * 3   | UP_SW
 * A0  | DOWN_SW
 * 15  | QTY_SW
 * 6   | ZONE_SW
 * 14  | MODE_SW
 * 7   | ET_SW
 * 16  | VR_MAN
 * 8   | VR_AUTO
 * 10  | VR_LDDI
 * 9   | VR_A_IFEI
 * 
 * 
 * 
 * @brief The following #define tells DCS-BIOS that this is a RS-485 slave device.
 * It also sets the address of this slave device. The slave address should be
 * between 1 and 126 and must be unique among all devices on the same bus.
 *
 * @bug Currently does not work with the Pro Micro (32U4), Fails to compile. 

   #define DCSBIOS_RS485_SLAVE 3 ///DCSBios RS485 Bus Address, once bug resolved move line below comment.
*/

#define MUXADDRESS 1
#define MUXPIN 5

#define DCSBIOS_MUX_SERIAL
#include <DcsBios.h>
#include "Arduino.h"


// DcsBios::ActionButton sjCtrToggle("SJ_CTR", "TOGGLE", A2);
// DcsBios::ActionButton sjLiToggle("SJ_LI", "TOGGLE", A3);
// DcsBios::ActionButton sjLoToggle("SJ_LO", "TOGGLE", 2);
// DcsBios::ActionButton sjRiToggle("SJ_RI", "TOGGLE", A1);
// DcsBios::ActionButton sjRoToggle("SJ_RO", "TOGGLE", A6);


// Define pins for DCS-BIOS per interconnect diagram.
#define LI_SW A3     ///< LI Switch
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


void setup() {
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
}