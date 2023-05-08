/*
  Class definition for Motion.h library.
  Created by Thoby L. Noorhalim
  6 May 2023
*/

#include<Motion.h>

// ---------- Constructor ----------
Motion::Motion(){};

void Motion::updateData(std::vector<std::string> parsedData){
  setX(parsedData.at(1)); setY(parsedData.at(2));
  setR(parsedData.at(3)); setTheta(parsedData.at(4));
  setIntensity(parsedData.at(5));
}