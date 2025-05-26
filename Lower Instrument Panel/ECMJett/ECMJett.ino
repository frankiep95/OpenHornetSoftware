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
 *  * **Reference Designator:** 2A5A1
 *  * **Intended Board:** ABSIS ALE
 *  * **RS485 Bus Address:** 4
 * 
 * ### Wiring diagram:
 * PIN | Function
 * --- | ---
 * 15  | ECM_JETT_SW
 * 6   | ECM_STBY
 * 14  | ECM_BIT
 * 7   | ECM_REC
 * 16  | ECM_XMIT
 * 8   | DISP_BYPASS
 * 10  | DISP_OFF
 * 9   | AUXR_ENBL
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
/**
 * Check if we're on a Mega328 or Mega2560 and define the correct
 * serial interface
 * 
 */
// #define DCSBIOS_DEFAULT_SERIAL
#define DCSBIOS_MUX_SERIAL
#define MUXADDRESS 4
#include <DcsBios.h>
#include "Arduino.h"
#include <OpenHornetGauge.h>


#ifdef __AVR__
#include <avr/power.h>
#endif

#include "2A4A1-RWR_CONTROL_PANEL.h"

// Define pins for DCS-BIOS per interconnect diagram.
#define ECM_JETT_SW 15
#define ECM_STBY 6
#define ECM_BIT 14
#define ECM_REC 7
#define ECM_XMIT 16
#define DISP_BYPASS 8
#define DISP_OFF 10
#define AUXR_OFF 9

int coil1 = 21;
int coil2 = 2;
int coil3 = 20;
int coil4 = 19;
int zero = 3;

OpenHornetGauge cabinPressure(coil1,coil2,coil3,coil4,zero);

// Connect switches to DCS-BIOS
DcsBios::Switch2Pos cmsdJetSelBtn("CMSD_JET_SEL_BTN", ECM_JETT_SW);

const byte ecmModeSwPins[5] = { DcsBios::PIN_NC, ECM_STBY, ECM_BIT, ECM_REC, ECM_XMIT };
SwitchMultiPosDebounce ecmModeSw("ECM_MODE_SW", ecmModeSwPins, 5, false, 100);

DcsBios::Switch3Pos cmsdDispenseSw("CMSD_DISPENSE_SW", DISP_BYPASS, DISP_OFF);

DcsBios::Switch2Pos auxRelSw("AUX_REL_SW", AUXR_OFF);


// DcsBios::busTools cabinPressureValue("7514");

/**
* Arduino Setup Function
*
* Arduino standard Setup Function. Code who should be executed
* only once at the programm start, belongs in this function.
*/
void setup() {
  cabinPressure.setOffset(900);
  cabinPressure.setRotationDegrees(315);
  cabinPressure.setMotorSpeed(1200);
  cabinPressure.home();
  // Run DCS Bios setup function
  DcsBios::setup();
}

/**
* Arduino Loop Function
*
* Arduino standard Loop Function. Code who should be executed
* over and over in a loop, belongs in this function.
*/


void loop() {
  //Run DCS Bios loop function
  DcsBios::loop();
  
  cabinPressure.command(DcsBios::CheckBus("7514"));
  cabinPressure.updatePos();
  
  ecmModeSw.pollThisInput();
}

