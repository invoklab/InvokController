/*
  Class definition for ControllerData.h library.
  Created by Thoby L. Noorhalim
  26 August 2021
*/

#include <ControllerData.h>

// ---------- Constructor ----------
ControllerData::ControllerData(){};

// ---------- Setters ----------
void ControllerData::setX(std::string x){
  this->x = stod(x);
}

void ControllerData::setY(std::string y){
  this->y = stod(y);
}

void ControllerData::setR(std::string r){
  this->r = stod(r);
}

void ControllerData::setTheta(std::string theta){
  this->theta = stod(theta);
}

void ControllerData::setIntensity(std::string intensity){
  this->intensity = stod(intensity);
}

void ControllerData::setButtonState(std::string state){
  if(state.compare("true") == 0){
    this->buttonState = true;
  } else {
    this->buttonState = false;
  }
}



// ---------- Getters ----------
double ControllerData::getX(){
  return this->x;
}

double ControllerData::getY(){
  return this->y;
}

double ControllerData::getR(){
  return this->r;
}

double ControllerData::getTheta(){
  return this->theta;
}

double ControllerData::getIntensity(){
  return this->intensity;
}

bool ControllerData::getButtonState(){
  return this->buttonState;
}


