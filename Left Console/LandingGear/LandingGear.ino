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
 * @file 4A2A1-LDG_GEAR_PANEL.ino
 * @author Arribe
 * @date 2/28/2024
 * @version 0.0.3
 * @copyright Copyright 2016-2024 OpenHornet. Licensed under the Apache License, Version 2.0.
 * @brief Controls the LDG GEAR panel.
 *
 * @details
 * 
 *  * **Reference Designator:** 4A2A1
 *  * **Intended Board:** ABSIS ALE /w Relay Module
 *  * **RS485 Bus Address:** 1
 * 
 * ### Wiring diagram:
 * PIN | Function
 * --- | ---
 * A1  | Landing Gear Emergency Rotate and Pull
 * A2  | Landing Gear Down Lock Override Button
 * A3  | Landing Gear Warning Silence Button
 * 2   | Landing Gear Down Lock Solenoid
 * 3   | Landing Gear Limit Switch (handle raise / lower)
 * 4   | Landing Gear Lollipop LED
 *
 *
 * @brief The following #define tells DCS-BIOS that this is a RS-485 slave device.
 * It also sets the address of this slave device. The slave address should be
 * between 1 and 126 and must be unique among all devices on the same bus.
 *
 * @bug Currently does not work with the Pro Micro (32U4), Fails to compile. 
 *
 // #define DCSBIOS_RS485_SLAVE 1
*/

/**
 * Check if we're on a Mega328 or Mega2560 and define the correct
 * serial interface
 */

#define MUXADDRESS 1
#define DCSBIOS_MUX_SERIAL
#include "DcsBios.h"


#ifdef __AVR__
#include <avr/power.h>
#endif






// Define pins for DCS-BIOS per interconnect diagram.
#define LG_EMERG 3 ///< Landing Gear Emergency Rotate and Pull
#define LG_ORIDE 4 ///< Landing Gear Down Lock Override Button
#define LG_WARN A6 ///< Landing Gear Warning Silence Button
#define LG_LEVER_SOLENOID 2 ///< Landing Gear Down Lock Solenoid
#define LG_LIMIT A1 ///< Landing Gear Limit Switch (handle raise / lower)
#define LG_LED A2 ///< Landing Gear Lollipop LED

//Declare variables for down lock logic
bool wowLeft = true;           ///< Initializing weight-on-wheel value for cold/ground start.
bool wowRight = true;          ///< Initializing weight-on-wheel value for cold/ground start.
bool wowNose = true;           ///< Initializing weight-on-wheel value for cold/ground start.
bool downLockOverride = false; ///< Initializing value for down lock override to not pressed.

// Connect switches to DCS-BIOS 
DcsBios::Switch2Pos emergencyGearRotate("EMERGENCY_GEAR_ROTATE", LG_EMERG);
DcsBios::Switch2Pos gearDownlockOverrideBtn("GEAR_DOWNLOCK_OVERRIDE_BTN", LG_ORIDE);
DcsBios::Switch2Pos gearLever("GEAR_LEVER", LG_LIMIT,true);
DcsBios::Switch2Pos gearSilenceBtn("GEAR_SILENCE_BTN", LG_WARN);





/**
* Arduino Setup Function
*
* Code that should be executed only once at the program start, belongs in this function.
*/
void setup() {

  // Run DCS Bios setup function
  DcsBios::setup();

  // pinMode(LG_LEVER_SOLENOID, OUTPUT);
  // digitalWrite(LG_LEVER_SOLENOID, LOW);  //initialize solenoid to off
  pinMode(LG_LED,OUTPUT);
  digitalWrite(LG_LED, LOW);
}

/**
* Arduino Loop Function
*
* Arduino standard Loop Function. Code who should be executed
* over and over in a loop, belongs in this function.
*/

	typedef struct keyAndValue_
	{
		String key;
		unsigned int amount;
	} keyAndValue_t;


void loop() {

  //Run DCS Bios loop function
  DcsBios::loop();

  DcsBios::CheckBus("");

  keyAndValue_t data = {DcsBios::getAddress(),DcsBios::getAmount()};
  if(data.key != ""){
    if(data.key == "LGLT"){
      digitalWrite(LG_LED,data.amount);
    }
  }

/**
* ### Landing Gear Down Lock Logic
*  -# If landing gear handle in down position and lock override pushed, then activate solenoid to **unlock** handle. \n
*  -# If landing gear handle in down position and NO weight on wheels, then activate solenoid to **unlock** handle. \n
*  -# IF landing gear handle is down and there is weight on at least one wheel, then turn off solenoid to **lock** handle down. \n
*  -# If landing gear handle is up turn off solenoid, handle cannot physically be locked in up position. \n
*  \n
* @remark Digital reads of switch state will allow the landing gear handle to operate using the downlock override button
* without needing to have the sim running.
*/
  // if (digitalRead(LG_LIMIT) == 1) {                              //Switch closed, gear handle is down
  //   if (downLockOverride == true || !digitalRead(LG_ORIDE) == true) {  // Override switched pushed virtually in sim or physically in pit, turn on solenoid to unlock gear handle.
  //     digitalWrite(LG_LEVER_SOLENOID, HIGH);
  //   } else if (wowLeft == wowRight == wowNose == false) {  //No weight on any wheel, turn on solenoid to unlock the gear handle
  //     digitalWrite(LG_LEVER_SOLENOID, HIGH);
  //   } else {  // gear handle is down and there is weight on at least one wheel, turn off solenoid to lock the handle down.
  //     digitalWrite(LG_LEVER_SOLENOID, LOW);
  //   }
  // } else {  //gear handle up, turn off solenoid
  //   digitalWrite(LG_LEVER_SOLENOID, LOW);
  // }
}