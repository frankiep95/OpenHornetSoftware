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
unsigned int pst1;
unsigned int pst2;
unsigned int pst3;
unsigned int pst1Old;
unsigned int pst2Old;
unsigned int pst3Old;
unsigned int alt10K;
unsigned int alt10KOld;
unsigned int alt1K;
unsigned int alt1KOld;

RS485 muxBus(&Serial1, sendPin, deviceID);



void onInstPnlDimmerChange(unsigned int newValue) {
    sprintf((char*)data, "7546 %d", newValue);
    muxBus.send(2, data, strlen((char*)data));
    muxBus.send(5,data,strlen((char*)data));
}
DcsBios::IntegerBuffer instPnlDimmerBuffer(FA_18C_hornet_INST_PNL_DIMMER, onInstPnlDimmerChange);

void onPressureAltChange(unsigned int newValue) {
   sprintf((char*)data, "7514 %d", newValue);
   muxBus.send(4,data,strlen((char*)data));
}
DcsBios::IntegerBuffer pressureAltBuffer(FA_18C_hornet_PRESSURE_ALT, onPressureAltChange);

void onStbyAlt100FtPtrChange(unsigned int newValue) {
      sprintf((char*)data, "74f4 %d", newValue);
    muxBus.send(5, data, strlen((char*)data));
}
DcsBios::IntegerBuffer stbyAlt100FtPtrBuffer(FA_18C_hornet_STBY_ALT_100_FT_PTR, onStbyAlt100FtPtrChange);

void onStbyAsiAirspeedChange(unsigned int newValue) {
    sprintf((char*)data, "74f0 %d", newValue);
    muxBus.send(5, data, strlen((char*)data));
}
DcsBios::IntegerBuffer stbyAsiAirspeedBuffer(FA_18C_hornet_STBY_ASI_AIRSPEED, onStbyAsiAirspeedChange);


void onVsiChange(unsigned int newValue) {
    sprintf((char*)data, "7500 %d", newValue);
    muxBus.send(5, data, strlen((char*)data));
}
DcsBios::IntegerBuffer vsiBuffer(FA_18C_hornet_VSI, onVsiChange);

void onStbyPressSet0Change(unsigned int value) {
  unsigned int adjustedValue = value + 3277;
  int newValue = adjustedValue/6553;
  pst1 = newValue;
}
DcsBios::IntegerBuffer stbyPressSet0Buffer(FA_18C_hornet_STBY_PRESS_SET_0, onStbyPressSet0Change);

void onStbyPressSet1Change(unsigned int value) {
  unsigned int adjustedValue = value + 3277;
  int newValue = adjustedValue/6553;
  pst2 = newValue;
}
DcsBios::IntegerBuffer stbyPressSet1Buffer(FA_18C_hornet_STBY_PRESS_SET_1, onStbyPressSet1Change);

void onStbyPressSet2Change(unsigned int newValue) {

  switch(newValue){
    case 26214:
      pst3 = 28;
      break;
    case 39321:
      pst3 = 29;
      break;
    case 52428:
      pst3 = 30;
      break;
    case 65535:
      pst3 = 31;
      break;
  }

}
DcsBios::IntegerBuffer stbyPressSet2Buffer(FA_18C_hornet_STBY_PRESS_SET_2, onStbyPressSet2Change);

void onStbyAlt10000FtCntChange(unsigned int value) {
  unsigned int adjustedValue = value + 3277;
  int newValue = adjustedValue/6553;
  alt10K = newValue;
}
DcsBios::IntegerBuffer stbyAlt10000FtCntBuffer(FA_18C_hornet_STBY_ALT_10000_FT_CNT, onStbyAlt10000FtCntChange);

void onStbyAlt1000FtCntChange(unsigned int value) {
  unsigned int adjustedValue = value + 3277;
  int newValue = adjustedValue/6553;
  alt1K = newValue;
}
DcsBios::IntegerBuffer stbyAlt1000FtCntBuffer(FA_18C_hornet_STBY_ALT_1000_FT_CNT, onStbyAlt1000FtCntChange);

unsigned int newValue = 0;
unsigned int val2 = 0;
unsigned int val3 = 0;
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
  updateBaro();
  updateAlt();

  if(muxBus.receive(ID,buffer,len)){
    buffer[len] = 0;
    Serial.println((char*) buffer);
  }
}

void updateBaro(){

  if((pst1 != pst1Old) || (pst2 != pst2Old) || (pst3 != pst3Old)){

    int fullValue = (pst3 * 100) + (pst2 * 10) + pst1;

    sprintf((char*)data, "BARO %d", fullValue);
    muxBus.send(5, data, strlen((char*)data));

    pst1Old = pst1;
    pst2Old = pst2;
    pst3Old = pst3;

  }
}

void updateAlt(){

  if((alt10K != alt10KOld) || (alt1K != alt1KOld)){

    int fullValue = (alt10K * 10) + alt1K;

    sprintf((char*)data, "BALT %d", fullValue);
    muxBus.send(5, data, strlen((char*)data));
    alt10KOld = alt10K;
    alt1KOld = alt1K;
  }

}

//  -- END OF FILE --
