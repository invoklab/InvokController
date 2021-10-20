/*
  Demo sketch for receiving Color Data from Controller App
  Written by Thoby L. Noorhalim
  4 September 2021
*/

#include <InvokController.h>

// Controller Object Instantiation
Controller myController("websocket");

void setup() {
  Serial.begin(115200);

  // Controller Setup
  myController.setHostname("Color Update"); // mDNS
  myController.begin();
  myController.printIP();
}

void loop() {

  if (myController.isDataArrived()){
    Serial.printf("R [%d] G [%d] B [%d] | H [%.1f] S[%.1f] V[%.1f]\n",
    myController.colorPicker.getR(), myController.colorPicker.getG(),
    myController.colorPicker.getB(), myController.colorPicker.getH(),
    myController.colorPicker.getS(), myController.colorPicker.getV());
    myController.setDataArrived(false); // Flush, reset flag
  }

  // Controller Loop
  myController.loop();
}