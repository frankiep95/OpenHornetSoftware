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
#define MUXADDRESS 5
#define DCSBIOS_MUX_SERIAL
#include "DcsBios.h"
#ifdef __AVR__
#include <avr/power.h>
#endif


#define APU_SW1 15
#define APU_LAMP 6
#define CRANK_SW1 14
#define CRANK_SW2 7
#define FCS_CH1 16
#define FCS_CH2 8
#define LCSPDBRK 10
#define LCLBAR 9
#define APU_COIL 2
#define CRANK_COIL 3


DcsBios::Switch2Pos apuControlSw("APU_CONTROL_SW", APU_SW1);

DcsBios::Switch3Pos engineCrankSw("ENGINE_CRANK_SW", CRANK_SW2, CRANK_SW1);

DcsBios::Switch2Pos cbFcsChan1("CB_FCS_CHAN1", FCS_CH1);
DcsBios::Switch2Pos cbFcsChan2("CB_FCS_CHAN2", FCS_CH2);
DcsBios::Switch2Pos cbLaunchBar("CB_LAUNCH_BAR", LCLBAR);
DcsBios::Switch2Pos cbSpdBrk("CB_SPD_BRK", LCSPDBRK);

/**
* Arduino Setup Function
*
* Arduino standard Setup Function. Code who should be executed
* only once at the programm start, belongs in this function.
*/
void setup() {

pinMode(APU_COIL,OUTPUT);
pinMode(CRANK_COIL,OUTPUT);
pinMode(APU_LAMP,OUTPUT);
digitalWrite(APU_COIL,LOW);
digitalWrite(CRANK_COIL,LOW);
digitalWrite(APU_LAMP,LOW);


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


}

void checkSwitches(){
  if(DcsBios::CheckBus()){
    String add = DcsBios::getAddress();
    unsigned int value = DcsBios::getAmount();
    if(add == "APU1"){
      outputDebounce(APU_COIL,value,100);

      if(value == 0){
         outputDebounce(CRANK_COIL,LOW,100); // also kill the crank switches
      }
    }
    if(add == "CRNK"){
      if(value == 1){
        outputDebounce(CRANK_COIL,LOW,100);    
      }
      if(value == 0 || value == 2){
        outputDebounce(CRANK_COIL,HIGH,100);
      }
    }
    if(add == "APLT"){
      digitalWrite(APU_LAMP,value);
      if(value == 0){
         outputDebounce(CRANK_COIL,LOW,100); // also kill the crank switches
         outputDebounce(APU_COIL,LOW,100); // kill the APU
      }         
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