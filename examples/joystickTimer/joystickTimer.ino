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
  if (elapsedTime > 1000 && myController.joystick.getIntensity() > 0){
    Serial.printf("Joystick intensity is %.1f\n", myController.joystick.getIntensity());
    Serial.printf("Joystick theta is %.1f\n", myController.joystick.getTheta());
    elapsedTime = 0;
    nowTime = millis();
  }

  // Controller Loop
  myController.loop();
}