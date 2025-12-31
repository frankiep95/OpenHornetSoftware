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
#define MUXADDRESS 4
#define DCSBIOS_MUX_SERIAL
#include "DcsBios.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

#include "2A4A1-RWR_CONTROL_PANEL.h"


#define M_AUTO A3
#define M_OFF A2
#define CP_NORM A1
#define CP_RAM 4
#define PITOT_ON A0
#define ENG_ON 15
#define ENG_TEST 6
#define BA_AUG 14
#define BA_ROFF 7
#define BA_OFF 16
#define BA_LOFF 8
#define TS_A A10
#define TC_A A9

#define PITOT_COIL 2
#define AUG_COIL 3

DcsBios::Switch3Pos ecsModeSw("ECS_MODE_SW",M_AUTO , M_OFF);

DcsBios::Switch3Pos cabinPressSw("CABIN_PRESS_SW", CP_RAM, CP_NORM);

DcsBios::Switch2Pos pitotHeatSw("PITOT_HEAT_SW", PITOT_ON);

DcsBios::Switch3Pos engAntiiceSw("ENG_ANTIICE_SW", ENG_ON, ENG_TEST);

DcsBios::Switch2Pos bleedAirPull("BLEED_AIR_PULL", BA_AUG,1);

const byte bleedAirKnobPins[4] = {DcsBios::PIN_NC, BA_ROFF, BA_OFF, BA_LOFF};
SwitchMultiPosDebounce bleedAirKnob("BLEED_AIR_KNOB", bleedAirKnobPins, 4);

DcsBios::Potentiometer cabinTemp("CABIN_TEMP", TC_A);

DcsBios::Potentiometer suitTemp("SUIT_TEMP", TS_A);




/**
* Arduino Setup Function
*
* Arduino standard Setup Function. Code who should be executed
* only once at the programm start, belongs in this function.
*/
void setup() {

pinMode(PITOT_COIL,OUTPUT);
pinMode(AUG_COIL,OUTPUT);
digitalWrite(PITOT_COIL,LOW);
digitalWrite(AUG_COIL,LOW);



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

  checkSwitches();

  bleedAirKnob.pollThisInput();
}

void checkSwitches(){
  if(DcsBios::CheckBus()){
    String add = DcsBios::getAddress();
    unsigned int value = DcsBios::getAmount();
    if(add == "PTOT"){
      outputDebounce(PITOT_COIL,value,500);
    }
    if(add == "AUGC"){
      outputDebounce(AUG_COIL,value,500);
    }
  }
}

void outputDebounce(uint8_t pin, unsigned int value, int delay ){
  bool blockUpdate = false;
  unsigned long elapsedTime = 0;

  if(!blockUpdate){
    elapsedTime  = millis();
    blockUpdate = true;
    digitalWrite(pin,value);
  }
  else{
    if ((millis-elapsedTime) > delay){
        blockUpdate = false;
    }
  }



}