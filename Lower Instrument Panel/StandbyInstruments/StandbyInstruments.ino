

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
#define MUXPIN 2
#define DCSBIOS_MUX_SERIAL
#define MEGAMUX true 
#include <DcsBios.h>
#include "Arduino.h"
#include <OpenHornetGauge.h>
#include <MultiMap.h>              // by Rob Tillart
#include <FastLED.h>
#include <SPI.h>
#include <Wire.h>
extern "C" {
#include "utility/twi.h"           // from Wire library, so we can do bus scanning
}
#include <U8g2lib.h>  

#ifdef __AVR__
#include <avr/power.h>
#endif


#define ASCoil1 50
#define ASCoil2  52
#define ASCoil3  48
#define ASCoil4  46
#define ASZero  54
#define AltCoil1  40
#define AltCoil2  44
#define AltCoil3  38
#define AltCoil4  42
#define AltZero  55
#define VVCoil1  34
#define VVCoil2  36
#define VVCoil3  32
#define VVCoil4  30
#define VVZero  56
#define RWRBright  A3
#define SARITest  28
#define SARICageS2  22
#define SARIChA  26
#define SARIChB  24
#define AltChA  12
#define AltChB  13
#define backLight 11


// OLED ALTIMETER CONFIGURATION
#define TCAADDR 0x70

/**
 * @brief Selects a specific channel on the TCA9548A I2C multiplexer
 * @param i Channel number to select (0-7)
 * @see This function is called by setup() and updateBARO() and updateALT() functions
 */
void tcaselect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

#define BARO_OLED_Port 0
#define ALT_OLED_Port 1

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2_BARO(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2_ALT(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

String BaroOnes = "2";
String BaroTens = "9";
String BaroHundreds = "9";
String BaroThousands = "2";
bool BaroUpdated = true; 

String Alt1000s = "0";
String LastAlt1000s = "";
String Alt10000s = "0";
String LastAlt10000s = "";
bool AltUpdated = true;


OpenHornetGauge Airspeed(ASCoil1,ASCoil2,ASCoil3,ASCoil4,ASZero);
OpenHornetGauge Altimeter(AltCoil1,AltCoil2,AltCoil3,AltCoil4,AltZero);
OpenHornetGauge VerticalVelocity(VVCoil1,VVCoil2,VVCoil3,VVCoil4,VVZero);

DcsBios::ActionButton saiCageToggle("SAI_CAGE", "TOGGLE", SARICageS2);
DcsBios::RotaryEncoder saiSet("SAI_SET", "-320", "+320", SARIChA, SARIChB);
DcsBios::Switch2Pos saiTestBtn("SAI_TEST_BTN", SARITest);

DcsBios::Potentiometer rwrRwrIntesity("RWR_RWR_INTESITY", RWRBright);

DcsBios::RotaryEncoder stbyPressAlt("STBY_PRESS_ALT", "-1600", "+1600", AltChA, AltChB);


// ALTIMETER CONFIGURATION TO DCS
/**
 * @brief Updates the barometric pressure display on the OLED screen
 * @param strnewValue String containing the new barometric pressure value to display
 * @see This function is called by buildBAROString() and setup() functions
 */
void updateBARO(String strnewValue) {
  const char* newValue = strnewValue.c_str();
  tcaselect(BARO_OLED_Port);
  u8g2_BARO.setFontMode(0);
  u8g2_BARO.setDrawColor(0);
  u8g2_BARO.drawBox(0, 0, 128, 32);
  u8g2_BARO.setDrawColor(1);
  u8g2_BARO.setFontDirection(2);
  u8g2_BARO.drawStr(115, 0, newValue);
  u8g2_BARO.sendBuffer();
}

/**
 * @brief Builds and displays the complete barometric pressure string from individual digits
 * @see This function is called by loop() function when BaroUpdated is true
 */
void buildBAROString() {
  updateBARO(BaroThousands + BaroHundreds + BaroTens + BaroOnes);
  BaroUpdated = false;
}

/**
 * @brief Updates the altitude display on the OLED screen with ten-thousands and thousands digits
 * @param strTenThousands String containing the ten-thousands digit of altitude
 * @param strThousands String containing the thousands digit of altitude
 * @see This function is called by loop() function when AltUpdated is true
 */
void updateALT(String strTenThousands, String strThousands) {
  if (strTenThousands == LastAlt10000s && strThousands == LastAlt1000s) {
    return;
  }

  const char* newTenThousandsValue = strTenThousands.c_str();
  const char* newThousandsValue = strThousands.c_str();

  int End_X_Pos = 46;
  int End_Y_Pos = 28;
  int Start_Y_Pos = 13;
  int Start_X_Pos = 27;
  int Box_Width = 20;

  tcaselect(ALT_OLED_Port);
  u8g2_ALT.setFontMode(0);
  u8g2_ALT.setDrawColor(0);
  u8g2_ALT.drawBox(0, 0, 128, 32);
  u8g2_ALT.setDrawColor(1);

  if (strTenThousands == "0") {
    u8g2_ALT.drawBox(Start_X_Pos, 13, Box_Width, 20);
    u8g2_ALT.setDrawColor(0);

    u8g2_ALT.drawLine(Start_X_Pos, Start_Y_Pos, End_X_Pos, 32);
    u8g2_ALT.drawLine(Start_X_Pos, Start_Y_Pos + 1, End_X_Pos - 1, 32);
    u8g2_ALT.drawLine(Start_X_Pos, Start_Y_Pos + 2, End_X_Pos - 2, 32);
    u8g2_ALT.drawLine(Start_X_Pos, Start_Y_Pos + 3, End_X_Pos - 3, 32);
    u8g2_ALT.drawLine(Start_X_Pos, Start_Y_Pos + 4, End_X_Pos - 4, 32);
    u8g2_ALT.drawLine(Start_X_Pos, Start_Y_Pos + 5, End_X_Pos - 5, 32);
    u8g2_ALT.drawLine(Start_X_Pos, Start_Y_Pos + 6, End_X_Pos - 6, 32);

    u8g2_ALT.drawLine(Start_X_Pos, Start_Y_Pos + 11, End_X_Pos - 11, 32);
    u8g2_ALT.drawLine(Start_X_Pos, Start_Y_Pos + 12, End_X_Pos - 12, 32);
    u8g2_ALT.drawLine(Start_X_Pos, Start_Y_Pos + 13, End_X_Pos - 13, 32);
    u8g2_ALT.drawLine(Start_X_Pos, Start_Y_Pos + 14, End_X_Pos - 14, 32);
    u8g2_ALT.drawLine(Start_X_Pos, Start_Y_Pos + 15, End_X_Pos - 15, 32);

    u8g2_ALT.drawLine(Start_X_Pos + 4, Start_Y_Pos, Start_X_Pos + Box_Width, End_Y_Pos + 1);
    u8g2_ALT.drawLine(Start_X_Pos + 5, Start_Y_Pos, Start_X_Pos + Box_Width, End_Y_Pos);
    u8g2_ALT.drawLine(Start_X_Pos + 6, Start_Y_Pos, Start_X_Pos + Box_Width, End_Y_Pos - 1);
    u8g2_ALT.drawLine(Start_X_Pos + 7, Start_Y_Pos, Start_X_Pos + Box_Width, End_Y_Pos - 2);
    u8g2_ALT.drawLine(Start_X_Pos + 8, Start_Y_Pos, Start_X_Pos + Box_Width, End_Y_Pos - 3);
    u8g2_ALT.drawLine(Start_X_Pos + 9, Start_Y_Pos, Start_X_Pos + Box_Width, End_Y_Pos - 4);
    u8g2_ALT.drawLine(Start_X_Pos + 10, Start_Y_Pos, Start_X_Pos + Box_Width, End_Y_Pos - 5);

    u8g2_ALT.drawLine(Start_X_Pos + 15, Start_Y_Pos, Start_X_Pos + Box_Width, End_Y_Pos - 10);
    u8g2_ALT.drawLine(Start_X_Pos + 16, Start_Y_Pos, Start_X_Pos + Box_Width, End_Y_Pos - 11);
    u8g2_ALT.drawLine(Start_X_Pos + 17, Start_Y_Pos, Start_X_Pos + Box_Width, End_Y_Pos - 12);
    u8g2_ALT.drawLine(Start_X_Pos + 18, Start_Y_Pos, Start_X_Pos + Box_Width, End_Y_Pos - 13);
    u8g2_ALT.drawLine(Start_X_Pos + 19, Start_Y_Pos, Start_X_Pos + Box_Width, End_Y_Pos - 14);

    u8g2_ALT.setDrawColor(1);

  } else {
    u8g2_ALT.drawStr(32, 32, newTenThousandsValue);
  }
  u8g2_ALT.drawStr(65, 32, newThousandsValue);
  u8g2_ALT.sendBuffer();

  LastAlt10000s = strTenThousands;
  LastAlt1000s = strThousands;

  AltUpdated = false;
}




/**
* Arduino Setup Function
*
* Arduino standard Setup Function. Code who should be executed
* only once at the programm start, belongs in this function.
*/
void setup() {


  //OLEDS ALTIMETER SETUP
  Wire.begin();  
  for (uint8_t t = 0; t < 8; t++) {
    tcaselect(t);

    for (uint8_t addr = 0; addr <= 127; addr++) {
      //if (addr == TCAADDR) continue;

      uint8_t data;
      if (!twi_writeTo(addr, &data, 0, 1, 1)) {
        // Had to comment out these debugging messages as they created a conflict with the IRQ definition in DCS BIOS
      }
    }
  }

  tcaselect(BARO_OLED_Port);
  u8g2_BARO.begin();
  u8g2_BARO.clearBuffer();
  u8g2_BARO.setFont(u8g2_font_fub14_tr);
  u8g2_BARO.sendBuffer();

  tcaselect(ALT_OLED_Port);
  u8g2_ALT.begin();
  u8g2_ALT.clearBuffer();
  u8g2_ALT.setFont(u8g2_font_fub20_tr);
  u8g2_ALT.sendBuffer();

  updateALT("0", "0");
  updateBARO("2992");



  Airspeed.setOffset(0);
  Airspeed.setRotationDegrees(360);
  Airspeed.setMotorSpeed(1200);

  Altimeter.setOffset(0);
  Altimeter.setRotationDegrees(360);
  Altimeter.setMotorSpeed(1200);

  VerticalVelocity.setOffset(0);
  VerticalVelocity.setRotationDegrees(360);
  VerticalVelocity.setMotorSpeed(1200);

  // Airspeed.home();
  // Altimeter.home();
  // VerticalVelocity.home();

  // Run DCS Bios setup function
  DcsBios::setup();


}
// keyAndValue_t values[];

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


  // Airspeed.updatePos();
  // Altimeter.updatePos();
  // VerticalVelocity.updatePos();

  
  //UPDATE THE OLEDS EVERY 100 MS TO AVOID LAG WITH STEPPERS
  static unsigned long lastOLEDUpdate = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - lastOLEDUpdate >= 100) { //EVERY 100 MS
    lastOLEDUpdate = currentMillis;

    if (BaroUpdated == true) buildBAROString();
    if (AltUpdated == true) updateALT(Alt10000s, Alt1000s);
  }
}

void checkSwitches(){
  if(DcsBios::CheckBus()){
    String add = DcsBios::getAddress();
    unsigned int value = DcsBios::getAmount();
    if(add == "74f0"){
      Airspeed.command(value);
    }
    if(add == "74f4"){
      Altimeter.command(value);
    }
    if(add == "7500"){
      VerticalVelocity.command(value); 
    }

    if(add == "BARO"){
      BaroOnes = String(value).substring(3,4);
      BaroTens = String(value).substring(2,3);
      BaroHundreds = String(value).substring(1,2);
      BaroThousands = String(value).substring(0,1);
      BaroUpdated = true;
    }
    if(add == "BALT"){
      Serial.println("Balt");
      Alt1000s = String(value).substring(1,2);
      Alt10000s = String(value).substring(0,1);
      AltUpdated = true;
    }
  }
}
