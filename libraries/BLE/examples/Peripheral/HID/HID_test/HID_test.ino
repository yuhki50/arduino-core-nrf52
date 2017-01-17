/* Copyright (c) Sandeep Mistry. All rights reserved.
   Licensed under the MIT license. See LICENSE file in the project root for full license information.
   Modified by Chiara Ruggeri <chiara@arduino.org>
   
   This example shows the use of the HID BLE library.
   Connect the board to the phone through the phone's bluetooth settings,
   open a serial terminal and type any characters.
*/

#include <BLEHIDPeripheral.h>
#include <BLEMouse.h>
#include <BLEKeyboard.h>
#include <BLEMultimedia.h>
#include <BLESystemControl.h>

BLEHIDPeripheral bleHID = BLEHIDPeripheral();
BLEMouse bleMouse;
BLEKeyboard bleKeyboard;
BLEMultimedia bleMultimedia;
BLESystemControl bleSystemControl;

void setup() {
  Serial.begin(9600);

  // clears bond data on every boot
  bleHID.clearBondStoreData();
  
  bleHID.setReportIdOffset(1);
  
  bleHID.setDeviceName("Arduino BLE HID");
//  bleHID.setAppearance(961);

  bleHID.setLocalName("HID");

  bleHID.addHID(bleMouse);
  bleHID.addHID(bleKeyboard);
  bleHID.addHID(bleMultimedia);
  bleHID.addHID(bleSystemControl);

  bleHID.begin();

  Serial.println(F("BLE HID"));
}

void loop() {
  BLECentral central = bleHID.central();

  if (central) {
    // central connected to peripheral
    Serial.print(F("Connected to central: "));
    Serial.println(central.address());

    while (bleHID.connected()) {
      if (Serial.available() > 0) {
        Serial.read();

        // comment out one of the following lines to try a different feature

        //bleMouse.move(100, 100, 0);
        //bleKeyboard.press(KEYCODE_A);
        bleMultimedia.write(MMKEY_VOL_UP);
        //bleSystemControl.write(SYSCTRLKEY_POWER);
      }
    }

    // central disconnected
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}
