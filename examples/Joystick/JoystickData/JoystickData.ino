/*
  Demo sketch for receiving Joystick Control Data from Controller App
  Written by Thoby L. Noorhalim
  4 September 2021
*/

#include <InvokController.h>

// Controller Object Instantiation
Controller myController("websocket", 80, false);

void setup() {
  Serial.begin(115200);

  // Controller Setup
  myController.setHostname("Joystick"); // mDNS
  myController.begin();
}

void loop() {

  if (myController.isDataArrived()){
    Serial.printf("Intensity : [ %.1f ], Theta : [ %.1f ], State : [ %s ]\n", 
    myController.joystick.getIntensity(), myController.joystick.getTheta(),
    myController.joystick.getButtonState() ? "true" : "false");
    myController.setDataArrived(false); // Flush, reset flag
  }

  // Controller Loop
  myController.loop();
}