/*
  Demo sketch for Controller app serial monitor
  Written by Thoby L. Noorhalim
  13 October 2021
*/

#include <InvokController.h>

// Timer
double elapsedTime = 0;
double capturedTime = 0;

int variable = 0;

// Controller Object Instantiation
Controller myController("websocket", 80, false);

void setup() {
  Serial.begin(115200);

  // Controller Setup
  myController.setHostname("Serial Monitor"); // mDNS
  myController.begin();
}

void loop() {

  // Print data every 3 second
  elapsedTime = millis() - capturedTime;
  if (elapsedTime > 3000 && myController.isConnected()){
    myController.print("Hello " + to_string(variable));
    variable++;
    elapsedTime = 0;
    capturedTime = millis();
  }

  if(!myController.getIncomingCommand().empty()){
    Serial.printf("Command from client %s\n", myController.getIncomingCommand().c_str());
    // Flush incoming command
    myController.setIncomingCommand("");
  }

  // Controller Loop
  myController.loop();
}