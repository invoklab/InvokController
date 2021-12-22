/*
  Demo sketch for receiving Joystick Control Data from Controller App,
  Printing the data periodically every second without blocking the program
  Written by Thoby L. Noorhalim
  4 September 2021
*/

#include <InvokController.h>

// Controller Object Instantiation
Controller myController("websocket", 80, false);

// Timer
double elapsedTime = 0;
double nowTime = 0;

void setup() {
  Serial.begin(115200);

  // Controller Setup
  myController.setHostname("Joystick"); // mDNS
  myController.begin();
}

void loop() {

  // Print data every second
  elapsedTime = millis() - nowTime;
  if (elapsedTime > 1000 && myController.isConnected()){
    Serial.printf("Intensity : [ %.1f ], Theta : [ %.1f ], State : [ %s ]\n", 
    myController.joystick.getIntensity(), myController.joystick.getTheta(),
    myController.joystick.getButtonState() ? "true" : "false");
    elapsedTime = 0;
    nowTime = millis();
  }

  // Controller Loop
  myController.loop();
}