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

  if (myController.joystick.getIntensity() > 0 && myController.isConnected()){
    Serial.printf("Joystick intensity is %.1f\n", myController.joystick.getIntensity());
    Serial.printf("Joystick theta is %.1f\n", myController.joystick.getTheta());
  }

  // Controller Loop
  myController.loop();
}