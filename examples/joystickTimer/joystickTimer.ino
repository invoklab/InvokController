#include <InvokController.h>

// Controller Object Instantiation
Controller myController = Controller("websocket");

// Timer
double elapsedTime = 0;
double nowTime = 0;

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