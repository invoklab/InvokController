/*
  Demo sketch for receiving Motion Control Data from Controller App
  Written by Thoby L. Noorhalim
  6 May 2023
*/

#include <InvokController.h>

// Controller Object Instantiation
Controller myController("websocket", 80, false);

void setup() {
  Serial.begin(115200);

  // Controller Setup
  myController.setHostname("Motion"); // mDNS
  myController.begin();
}

void loop() {

  if (myController.isDataArrived()){
    Serial.printf("Intensity : [ %.1f ], Theta : [ %.1f ]\n", 
    myController.motion.getIntensity(), myController.motion.getTheta(),
    myController.setDataArrived(false); // Flush, reset flag
  }

  // Controller Loop
  myController.loop();
}