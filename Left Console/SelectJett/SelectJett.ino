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
 * @file 4A3A1-SELECT_JETT_PANEL.ino
 * @author Arribe
 * @date 03.01.2024
 * @version 0.0.1
 * @copyright Copyright 2016-2024 OpenHornet. Licensed under the Apache License, Version 2.0.
 * @brief Controls the SELECT JETT panel.
 *
 * @details
 * 
 *  * **Reference Designator:** 4A3A1
 *  * **Intended Board:** ABSIS ALE w/ Relay Module
 *  * **RS485 Bus Address:** 2
 * 
 * ### Wiring diagram:
 * PIN | Function
 * --- | ---
 * A0  | Hook Bypass Switch
 * A1  | Launch Bar Switch
 * A2  | Flaps Switch Position 2
 * A3  | Flaps Switch Position 1
 * 2   | Launch Bar Mag Switch
 * 3   | Hook Bypass Mag Switch
 * 4   | Landing Taxi Light
 * 6   | Selector Jettision Position 1
 * 7   | Selector Jettision Position 3
 * 8   | Selector Jettision Position 8
 * 10  | Antiskid Switch
 * 14  | Selector Jettision Position 2
 * 15  | Selector Jettision Push
 * 16  | Selector Jettision Position 4
 * 
 * @brief The following #define tells DCS-BIOS that this is a RS-485 slave device.
 * It also sets the address of this slave device. The slave address should be
 * between 1 and 126 and must be unique among all devices on the same bus.
 *
 * @bug Currently does not work with the Pro Micro (32U4), Fails to compile. 
 *
//#define DCSBIOS_RS485_SLAVE 1 ///DCSBios RS485 Bus Address, once bug resolved move line below comment.
*/



#define MUXADDRESS 2
#define DCSBIOS_MUX_SERIAL
#include "DcsBios.h"

/**
* @brief Pilots may want the launch bar to automatically release when the throttles advance to MIL power.
* The sim's version of the F/A-18 does *NOT* have this feature.  The define allows setting it as desired, default is *false*.
*
*/


/**
* @brief Delay for Hook Bypass mag-switch auto-off when hook lever is lowered
*/
// #define HOOK_DELAY 3200

// Define pins for DCS-BIOS per interconnect diagram.
#define HOOKB_SW A0 ///< Hook Bypass Switch
#define LBAR_SW A1 ///< Launch Bar Switch
#define FLAPS_SW2 A2 ///< Flaps Switch Position 2
#define FLAPS_SW1 A3 ///< Flaps Switch Position 1
#define LBAR_RET 2    ///< Launch Bar Switch Mag
#define HOOK_FIELD 3  ///< Hook Bypass Switch Mag
#define LADG_SW 4 ///< Landing Taxi Light
#define SJET_SW1 6 ///< Selector Jettison Position 1
#define SJET_SW3 7 ///< Selector Jettison Position 3
#define SJET_SW5 8 ///< Selector Jettison Position 8
#define ASKID_SW 10 ///< Antiskid Switch
#define SJET_SW2 14 ///< Selector Jettison Position 2
#define SJET_PUSH 15 ///< Selector Jettison Push
#define SJET_SW4 16 ///< Selector Jettison Position 4

//Declare variables for custom non-DCSBios logic for mag-switches

// Connect switches to DCS-BIOS
DcsBios::Switch2Pos antiSkidSw("ANTI_SKID_SW", ASKID_SW,true);
DcsBios::Switch3Pos flapSw("FLAP_SW", FLAPS_SW1, FLAPS_SW2);
DcsBios::Switch2Pos hookBypassSw("HOOK_BYPASS_SW", HOOKB_SW);
DcsBios::Switch2Pos launchBarSw("LAUNCH_BAR_SW", LBAR_SW);
DcsBios::Switch2Pos ldgTaxiSw("LDG_TAXI_SW", LADG_SW,true);
DcsBios::Switch2Pos selJettBtn("SEL_JETT_BTN", SJET_PUSH);
const byte selJettKnobPins[5] = { SJET_SW5, SJET_SW4, SJET_SW3, SJET_SW2, SJET_SW1 };
DcsBios::SwitchMultiPos selJettKnob("SEL_JETT_KNOB", selJettKnobPins, 5);

// DCSBios reads to save airplane state information.

/**
* @brief DCSBios read back of Hook Bypass position.  If the Switch is turned off virtually in the sim, then turn off the hook bypass mag.
*/


/**
* @brief Need to save the hook lever state to test turning off the hook bypass mag-switch in the main loop.
*  
*/

/**
* @brief DCSBios read back of Hook Bypass position.  If the Switch is turned off virtually in the sim, then turn off the hook bypass mag.
  The Launch bar switch is only held down when there is weight-on-wheels.
*/


//Engine RPM needed for launch bar mag-switch


/**
* Arduino Setup Function
*
* Arduino standard Setup Function. Code who should be executed
* only once at the program start, belongs in this function.
*/
void setup() {

  // Run DCS Bios setup function
  DcsBios::setup();

  pinMode(LBAR_RET, OUTPUT);
  pinMode(HOOK_FIELD, OUTPUT);

  digitalWrite(LBAR_RET, LOW);
  digitalWrite(HOOK_FIELD, LOW);
}

/**
* Arduino Loop Function
*
* Arduino standard Loop Function. Code who should be executed
* over and over in a loop, belongs in this function.
*
*
*
*
*/
void loop() {

  //Run DCS Bios loop function
  DcsBios::loop();

  if(digitalRead(A1)){
    digitalWrite(LBAR_RET,HIGH);
  }

  if(digitalRead(A0)){
    digitalWrite(HOOK_FIELD,HIGH);
  }

  if(DcsBios::CheckBus()){   
    Serial.println("yes");
    String add = DcsBios::getAddress();
    unsigned int value = DcsBios::getAmount();
    if(add == "HOOK"){
      // Serial.println("hook");
      // Serial.println(value);
      digitalWrite(HOOK_FIELD,value);
    }
    if(add == "LNCH"){
      // Serial.println("launc");
      // Serial.println(value);
      digitalWrite(LBAR_RET,value);
    }    
    };

}





