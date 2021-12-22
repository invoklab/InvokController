/*
  Demo sketch for receiving Slider Data from Controller App
  Written by Thoby L. Noorhalim
  28 September 2021
*/

#include <InvokController.h>

// Controller Object Instantiation
Controller myController("websocket", 80, false);

void setup() {
  Serial.begin(115200);

  // Controller Setup
  myController.setHostname("Slider"); // mDNS
  myController.begin();
}

void loop() {

  if (myController.isDataArrived()){
    myController.setDataArrived(false); // Flush, reset flag
    Serial.printf("Slider State [%.1f] | [%.1f] | [%.1f] | [%.1f] | [%.1f] | [%.1f]\n",
    myController.slider.getSliderData(0), myController.slider.getSliderData(1), 
    myController.slider.getSliderData(2), myController.slider.getSliderData(3), 
    myController.slider.getSliderData(4), myController.slider.getSliderData(5)
    );
  }

  // Controller Loop
  myController.loop();
}