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
 * @file OHSketchTemplate.ino
 * @author <Replace with author's name>
 * @date <MM.DD.YYYY>
 * @version u.0.0.1 (untested)
 * @copyright Copyright 2016-2024 OpenHornet. Licensed under the Apache License, Version 2.0.
 * @warning This sketch is based on a wiring diagram, and was not yet tested on hardware. (Remove this line once tested on hardware and in system.)
 * @brief <A short description of the PCB, will appear in the list of files.>
 *
 * @details This is the OpenHornet Sketch Template. It should be used as a starting point for every new sketch.
 * Please copy the whole OHSketchTemplate folder to start, and ensure the correct line in the Makefile is uncommented.
 * 
 *  * **Reference Designator:** <Replace with full reference designator.>
 *  * **Intended Board:** <Replace with the appropriate hardware, i.e. ABSIS ALE, ABSIS ALE w/ Relay Module, etc.>
 *  * **RS485 Bus Address:** <NA or RS485 Bus Address, i.e. 1, 2, 3, etc.>
 * 
 * ### Wiring diagram:
 * PIN | Function
 * --- | ---
 * 1   | function 1
 * 2   | function 2
 * 3   | function 3
 * 
 * @brief The following #define tells DCS-BIOS that this is a RS-485 slave device.
 * It also sets the address of this slave device. The slave address should be
 * between 1 and 126 and must be unique among all devices on the same bus.
 *
 * @bug Currently does not work with the Pro Micro (32U4), Fails to compile. 

   #define DCSBIOS_RS485_SLAVE 1 ///DCSBios RS485 Bus Address, once bug resolved move line below comment.
*/

/**
 * Check if we're on a Mega328 or Mega2560 and define the correct
 * serial interface
 * 
 */


#define MUXADDRESS 3
#define DCSBIOS_MUX_SERIAL
#include "DcsBios.h"
#ifdef __AVR__
#include <avr/power.h>
#endif



// Define pins for DCS-BIOS per interconnect diagram.
#define BRKP_M1 A3
#define BRKP_M2 2
#define BRKP_M3 A2
#define BRKP_M4 A1
#define BRKP_DIN 3
#define FIRE_SW1 6
#define FIRE_SW2 A0
#define BRKH_SECURE 15
#define BRKH_EMERG 6
#define BRKH_PARK 14

//Declare variables for custom non-DCS Bios logic
byte brakeState = 1;  ///< brakeState = 1:Park, 2:Emergency, or 0:Off

// DcsBios::Switch2Pos emergencyParkingBrakePull("EMERGENCY_PARKING_BRAKE_PULL", PIN);
// const byte emergencyParkingBrakeRotatePins[3] = {PIN_0, PIN_1, PIN_2};DcsBios::SwitchMultiPos emergencyParkingBrakeRotate("EMERGENCY_PARKING_BRAKE_ROTATE", emergencyParkingBrakeRotatePins, 3);

DcsBios::Switch3Pos fireTestSw("FIRE_TEST_SW", FIRE_SW1, FIRE_SW2);



void onHydIndBrakeChange(unsigned int newValue) {

}DcsBios::IntegerBuffer hydIndBrakeBuffer(FA_18C_hornet_HYD_IND_BRAKE, onHydIndBrakeChange);

/**
* Arduino Setup Function
*
* Arduino standard Setup Function. Code who should be executed
* only once at the programm start, belongs in this function.
*/
void setup() {

    // Run DCS Bios setup function
  DcsBios::setup();


}

/**
* Arduino Loop Function
*
* Arduino standard Loop Function. Code who should be executed
* over and over in a loop, belongs in this function.
*/
unsigned int value = 0;
void loop() {


check();
delay(1000);
  
  //Run DCS Bios loop function
  DcsBios::loop();
//  value = DcsBios::CheckBus("74b4");
  // Brake Handle Logic:
  // bool eBrkSwitchState = !digitalRead(BRKH_EMERG);  // read the emergency brake switch state
  // bool pBrkSwitchState = !digitalRead(BRKH_PARK);   // read the parking brake switch state

  // switch (brakeState) {                                           // brakeState = 1:Park, 2:Emergency, or 0:Off
  //   case 0:                                                       // brakeState == 0, brakes are off determine if pulled and which direction
  //     if (eBrkSwitchState) == 1 {                                 // Emerg brake switch state == 1, Brake handle pulled for emergency brake
  //       sendDcsBiosMessage("EMERGENCY_PARKING_BRAKE_PULL", "0");  // DcsBios message to pull handle
  //       brakeState = 2;                                           // Update brake state to emergency brakes applied
  //     }
  //     if (pBrkSwitchState) == 1 {                                   // Parking brake switch state == 1, brake handle pulled for parking brake
  //       sendDcsBiosMessage("EMERGENCY_PARKING_BRAKE_ROTATE", "1");  // Rotate parking brake handle to parking / vertical position
  //       delay(50);
  //       sendDcsBiosMessage("EMERGENCY_PARKING_BRAKE_PULL", "0");  // DcsBios message to pull handle
  //       brakeState = 1;                                           // Update brake state to parking brakes applied
  //     }
  //     break;
  //   case 1:                                                         // brakeState == 1, Parking brake on
  //     if (pBrkSwitchState) == 0 {                                   // Parking brake switch state == 0, brake handle pushed in
  //       sendDcsBiosMessage("EMERGENCY_PARKING_BRAKE_ROTATE", "2");  // DcsBios message to rotate the brake handle to the 'release' position (not modeled in the physical pit)
  //       delay(50);                                                  // delay for the animation to complete
  //       sendDcsBiosMessage("EMERGENCY_PARKING_BRAKE_PULL", "1");    // DcsBios message to push the brake handle in
  //       delay(50);                                                  // delay for the animation to complete
  //       sendDcsBiosMessage("EMERGENCY_PARKING_BRAKE_ROTATE", "0");  // DcsBios message to rotate the brake handle to the emergency / horizontal position
  //       brakeState = 0;                                             // Update brake state to off
  //     }
  //     break;
  //   case 2:                                                       // brakeState == 2, Emergency brake on
  //     if (eBrkSwitchState) == 0 {                                 // Emergency brake swtich state == 0, brake handle pushed in
  //       sendDcsBiosMessage("EMERGENCY_PARKING_BRAKE_PULL", "1");  // DcsBios message to push the brake handle in
  //       brakeState = 0;                                           // Update brake state to off
  //     }
  //     break;
  // }
}

void check(){

  
  if(digitalRead(FIRE_SW1)==1){
    Serial.println("FIRE 1 HIGH");
  }
  if(digitalRead(FIRE_SW1) == 0){
    Serial.println("FIRE 1 LOW");
  }
  if(digitalRead(FIRE_SW2) == 1){
    Serial.println("FIRE 2 HIGH");
  }
  if(digitalRead(FIRE_SW2) == 0){
    Serial.println("FIRE 2 LOW");
  }

    if(digitalRead(BRKH_SECURE) == 1){
    Serial.println("Brake secure HIGH");
  }
  if(digitalRead(BRKH_SECURE) == 0){
    Serial.println("Brake secure LOW");
  }

    if(digitalRead(BRKH_EMERG) == 1){
    Serial.println("BRKH_EMERG HIGH");
  }
  if(digitalRead(BRKH_EMERG) == 0){
    Serial.println("BRKH_EMERGe LOW");
  }

    if(digitalRead(BRKH_PARK) == 1){
    Serial.println("BRKH_PARK HIGH");
  }
  if(digitalRead(BRKH_PARK) == 0){
    Serial.println("BRKH_PARK LOW");
  }
}
