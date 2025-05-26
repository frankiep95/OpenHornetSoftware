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
// #define MUXADDRESS 5
// #define MUXPIN 2
#define DCSBIOS_DEFAULT_SERIAL
// #define MEGAMUX true 
#include <DcsBios.h>
#include "Arduino.h"
#include <OpenHornetGauge.h>

#ifdef __AVR__
#include <avr/power.h>
#endif


int ASCoil1 = 50;
int ASCoil2 = 52;
int ASCoil3 = 48;
int ASCoil4 = 46;
int ASZero = 54;
int AltCoil1 = 40;
int AltCoil2 = 44;
int AltCoil3 = 38;
int AltCoil4 = 42;
int AltZero = 55;
int VVCoil1 = 34;
int VVCoil2 = 36;
int VVCoil3 = 32;
int VVCoil4 = 30;
int VVZero = 56;
int RWRBright = A3;
int SARITest = 28;
int SARICageS2 = 22;
int SARIChA = 26;
int SARIChB = 24;
int AltChA = 12;
int AltChB = 13;


OpenHornetGauge Airspeed(ASCoil1,ASCoil2,ASCoil3,ASCoil4,ASZero);
OpenHornetGauge Altimeter(AltCoil1,AltCoil2,AltCoil3,AltCoil4,AltZero);
OpenHornetGauge VerticalVelocity(VVCoil1,VVCoil2,VVCoil3,VVCoil4,VVZero);

DcsBios::ActionButton saiCageToggle("SAI_CAGE", "TOGGLE", SARICageS2);
DcsBios::RotaryEncoder saiCage("SAI_CAGE", "DEC", "INC", SARIChA, SARIChB);
DcsBios::Switch2Pos saiTestBtn("SAI_TEST_BTN", SARITest);

DcsBios::Potentiometer rwrRwrIntesity("RWR_RWR_INTESITY", RWRBright);

DcsBios::RotaryEncoder stbyPressAlt("STBY_PRESS_ALT", "-3200", "+3200", AltChA, AltChB);



/**
* Arduino Setup Function
*
* Arduino standard Setup Function. Code who should be executed
* only once at the programm start, belongs in this function.
*/
void setup() {
  Airspeed.setOffset(0);
  Airspeed.setRotationDegrees(360);
  Airspeed.setMotorSpeed(1200);

  Altimeter.setOffset(0);
  Altimeter.setRotationDegrees(360);
  Altimeter.setMotorSpeed(1200);

  VerticalVelocity.setOffset(0);
  VerticalVelocity.setRotationDegrees(360);
  VerticalVelocity.setMotorSpeed(1200);

  Airspeed.home();
  Altimeter.home();
  VerticalVelocity.home();

  // Run DCS Bios setup function
  DcsBios::setup();


}


void onStbyAsiAirspeedChange(unsigned int newValue) {
  Airspeed.command(newValue);
  }
  DcsBios::IntegerBuffer stbyAsiAirspeedBuffer(FA_18C_hornet_STBY_ASI_AIRSPEED, onStbyAsiAirspeedChange);

  void onStbyAlt100FtPtrChange(unsigned int newValue) {
    Altimeter.command(newValue);
  }
  DcsBios::IntegerBuffer stbyAlt100FtPtrBuffer(FA_18C_hornet_STBY_ALT_100_FT_PTR, onStbyAlt100FtPtrChange);

  void onVsiChange(unsigned int newValue) {
     VerticalVelocity.command(newValue);
  }
  
  DcsBios::IntegerBuffer vsiBuffer(FA_18C_hornet_VSI, onVsiChange);



// keyAndValue_t values[];

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

  // DcsBios::CheckBus("");
  // keyAndValue_t data = {DcsBios::getAddress(),DcsBios::getAmount()};
  // if(data.key != ""){
  //   if(data.key == "74f0"){
  //     Airspeed.command(data.amount);
  //   }
  //   if(data.key == "74f4"){
  //     Altimeter.command(data.amount);
  //   }
  //   if(data.key == "7500"){
  //     VerticalVelocity.command(data.amount);
  //   }
  // }
  
  Airspeed.updatePos();
  Altimeter.updatePos();
  VerticalVelocity.updatePos();

}


