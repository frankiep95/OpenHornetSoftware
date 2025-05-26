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
 * @brief Controls the Master Arm Panel
 * @details
 * 
 *  * **Reference Designator:** 1A2
 *  * **Intended Board:** ABSIS ALE
 *  * **RS485 Bus Address:** 1
 * 
 * ### Wiring diagram:
 * PIN | Function
 * --- | ---
 * 3   | MSTR_ARM_SW
 * A3  | READY_SW
 * D2  | AA_SW
 * A2  | AG_SW
 * A1  | E_JETT_SW
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

#define DCSBIOS_MUX_SERIAL
#define MUXADDRESS 1
#include <DcsBios.h>
#include "Arduino.h"



#ifdef __AVR__
#include <avr/power.h>
#endif


// Define pins for DCS-BIOS per interconnect diagram.
#define MSTR_ARM_SW 3
#define READY_SW A3
#define AA_SW 2
#define AG_SW A2
#define E_JETT_SW A1



// Connect switches to DCS-BIOS
DcsBios::Switch2Pos masterArmSw("MASTER_ARM_SW", MSTR_ARM_SW);

DcsBios::Switch2Pos masterModeAa("MASTER_MODE_AA", AA_SW);

DcsBios::Switch2Pos masterModeAg("MASTER_MODE_AG", AG_SW);

DcsBios::Switch2Pos fireExtBtn("FIRE_EXT_BTN", READY_SW);

DcsBios::Switch2Pos emerJettBtn("EMER_JETT_BTN", E_JETT_SW);



/**
* Arduino Setup Function
*
* Arduino standard Setup Function. Code who should be executed
* only once at the programm start, belongs in this function.
*/
void setup() {
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
}

