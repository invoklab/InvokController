/*
  Class definition for Joystick.h library.
  Created by Thoby L. Noorhalim
  26 August 2021
*/

#include<Joystick.h>

// ---------- Constructor ----------
Joystick::Joystick(){};

void Joystick::updateData(vector<string> parsedData){
  setX(parsedData.at(1)); setY(parsedData.at(2));
  setR(parsedData.at(3)); setTheta(parsedData.at(4));
  setIntensity(parsedData.at(5));
  setButtonState(parsedData.at(6));
}