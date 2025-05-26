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
 * Bus Master for Lower Instrument Panel
 * 
 * @brief The following #define tells DCS-BIOS that this is a RS-485 slave device.
 * It also sets the address of this slave device. The slave address should be
 * between 1 and 126 and must be unique among all devices on the same bus.
 *
 * @bug Currently does not work with the Pro Micro (32U4), Fails to compile. 

   #define DCSBIOS_RS485_SLAVE 1 ///DCSBios RS485 Bus Address, once bug resolved move line below comment.
*/

//    FILE: RS485_simple_master.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: simple master
//     URL: https://github.com/RobTillaart/RS485

//  this is the code of a simple master  (needs simple slave)
//  it send one of 3 (single char) commands to the slave
//  '0' == set LED LOW
//  '1' == set LED HIGH
//  '2' == request status.
//
//  print debug messages SEND and RECV with data.
//  Note that one needs a 2nd Serial port for nice debugging.
//  (or an LCD screen whatever).

//    FILE: RS485_simple_master.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: simple master
//     URL: https://github.com/RobTillaart/RS485

//  this is the code of a simple master  (needs simple slave)
//  it send one of 3 (single char) commands to the slave
//  '0' == set LED LOW
//  '1' == set LED HIGH
//  '2' == request status.
//
//  print debug messages SEND and RECV with data.
//  Note that one needs a 2nd Serial port for nice debugging.
//  (or an LCD screen whatever).
#define DCSBIOS_DEFAULT_SERIAL
#include <DcsBios.h>
#include "Arduino.h"
#include "RS485.h"

const uint8_t sendPin = 5;
const uint8_t deviceID = 0;
uint8_t data[32];

RS485 muxBus(&Serial1, sendPin, deviceID);

// landing gear outputs
// DCSBios reads to save airplane state information.
// void onExtWowLeftChange(unsigned int newValue) {
//     sprintf((char*)data, "74d8 %d", newValue);
//     muxBus.send(1, data, strlen((char*)data));
//   } 
// DcsBios::IntegerBuffer extWowLeftBuffer(0x74d8, 0x0100, 8, onExtWowLeftChange);

// void onExtWowNoseChange(unsigned int newValue) {
//     sprintf((char*)data, "74d6 %d", newValue);
//     muxBus.send(1, data, strlen((char*)data));
//   } 
// DcsBios::IntegerBuffer extWowNoseBuffer(0x74d6, 0x4000, 14, onExtWowNoseChange);

// void onExtWowRightChange(unsigned int newValue) {
//     sprintf((char*)data, "74d6 %d", newValue);
//     muxBus.send(1, data, strlen((char*)data));
//   } 
// DcsBios::IntegerBuffer extWowRightBuffer(0x74d6, 0x8000, 15,onExtWowRightChange);

// void onGearDownlockOverrideBtnChange(unsigned int newValue) {
//     sprintf((char*)data, "747e %d", newValue);
//     muxBus.send(1, data, strlen((char*)data));
//   }
//  DcsBios::IntegerBuffer gearDownlockOverrideBtnBuffer(0x747e, 0x4000, 14, onGearDownlockOverrideBtnChange);


void onLandingGearHandleLtChange(unsigned int newValue) {
    sprintf((char*)data, "LGLT %d", newValue);
    muxBus.send(1, data, strlen((char*)data));
  }
  DcsBios::IntegerBuffer landingGearHandleLtBuffer(FA_18C_hornet_LANDING_GEAR_HANDLE_LT, onLandingGearHandleLtChange);




// unsigned int newValue = 0;
// unsigned int val2 = 0;
// unsigned int val3 = 0;

void setup() {
  pinMode(17, OUTPUT);
  Serial.begin(250000);
  Serial1.begin(250000);
  while (!Serial1) {}
  DcsBios::setup();

}
uint8_t ID;
uint8_t buffer[50];
uint8_t len;


void loop() {
  DcsBios::loop();

  if(muxBus.receive(ID,buffer,len)){
    buffer[len] = 0;
    Serial.println((char*) buffer);
  }
}

//  -- END OF FILE --
