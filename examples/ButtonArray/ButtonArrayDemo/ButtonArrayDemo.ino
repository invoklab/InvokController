/*
  Demo sketch for receiving Button State Data from Controller App
  Written by Thoby L. Noorhalim
  4 September 2021
*/

#include <InvokController.h>

// Controller Object Instantiation
Controller myController = Controller("websocket");

// Replace SSID and PASSWORD with your preffered WiFi Credentials
char* SSID = "SSID";
char* PASSWORD = "PASSWORD";

void setup() {
  Serial.begin(115200);

  // Controller Setup
  myController.setSSID(SSID);
  myController.setSSIDPassword(PASSWORD);
  myController.begin();
  myController.printIP();
}

void loop() {

  if (myController.isConnected()){
    Serial.printf("Button State [%s] | [%s] | [%s] | [%s] | [%s] | [%s] | [%s] | [%s] | [%s] | [%s] | [%s] | [%s]\n", 
    myController.buttonArray.getButtonArrayState(0) ? "1" : "0",
    myController.buttonArray.getButtonArrayState(1) ? "1" : "0",
    myController.buttonArray.getButtonArrayState(2) ? "1" : "0",
    myController.buttonArray.getButtonArrayState(3) ? "1" : "0",
    myController.buttonArray.getButtonArrayState(4) ? "1" : "0",
    myController.buttonArray.getButtonArrayState(5) ? "1" : "0",
    myController.buttonArray.getButtonArrayState(6) ? "1" : "0",
    myController.buttonArray.getButtonArrayState(7) ? "1" : "0",
    myController.buttonArray.getButtonArrayState(8) ? "1" : "0",
    myController.buttonArray.getButtonArrayState(9) ? "1" : "0",
    myController.buttonArray.getButtonArrayState(10) ? "1" : "0",
    myController.buttonArray.getButtonArrayState(11) ? "1" : "0");
  }

  // Controller Loop
  myController.loop();
}