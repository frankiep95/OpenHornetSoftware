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


#ifdef __AVR__
#include <avr/power.h>
#endif



// Define pins for DCS-BIOS per interconnect diagram.
#define PS_ON 8
#define PWR_OK 9
#define SIMPWR_PCPWR A3
#define SIMPWR_PCRESET A2
#define SIMPWR_MASTERON A1
#define SIMPWR_DISPON A0
#define SIMPWR_PFLT_MODE 15
#define SIMPWR_MAINT_MODE 14
#define EXT_ACC1 4
#define EXT_ACC2 5
#define EXT_ACC3 6
#define EXT_ACC4 7


/**
* Arduino Setup Function
*
* Arduino standard Setup Function. Code who should be executed
* only once at the programm start, belongs in this function.
*/
void setup() {
  pinMode(PS_ON, INPUT);
  pinMode(PWR_OK, INPUT);
  pinMode(SIMPWR_PCPWR, INPUT);
  pinMode(SIMPWR_PCRESET,INPUT);
  pinMode(SIMPWR_MASTERON,INPUT);
  pinMode(SIMPWR_DISPON,INPUT);
  pinMode(SIMPWR_PFLT_MODE,INPUT);
  pinMode(SIMPWR_MAINT_MODE,INPUT);
  pinMode(EXT_ACC1, OUTPUT);
  pinMode(EXT_ACC2, OUTPUT);
  pinMode(EXT_ACC3, OUTPUT);
  pinMode(EXT_ACC4, OUTPUT);
  digitalWrite(PS_ON,HIGH);
  digitalWrite(PWR_OK,HIGH);
  digitalWrite(SIMPWR_PCPWR,HIGH);
  digitalWrite(SIMPWR_PCRESET,HIGH);
  digitalWrite(SIMPWR_MASTERON,HIGH);
  digitalWrite(SIMPWR_DISPON,HIGH);
  digitalWrite(SIMPWR_PFLT_MODE,HIGH);
  digitalWrite(SIMPWR_MAINT_MODE,HIGH);
  digitalWrite(EXT_ACC1, LOW);
  digitalWrite(EXT_ACC2, LOW);
  digitalWrite(EXT_ACC3, LOW);
  digitalWrite(EXT_ACC4, LOW);



}

/**
* Arduino Loop Function
*
* Arduino standard Loop Function. Code who should be executed
* over and over in a loop, belongs in this function.
*/
void loop() {
  if(PWR_OK == 1 && SIMPWR_MASTERON == 1){
    digitalWrite(PS_ON, HIGH);
  }
  else{
    digitalWrite(PS_ON, LOW);
  }

  if(SIMPWR_DISPON == 1){
    digitalWrite(EXT_ACC3,HIGH);
  }
  else{
    digitalWrite(EXT_ACC3, LOW);
  }

}


