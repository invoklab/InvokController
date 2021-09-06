/*
  Class definition for ControllerData.h library.
  Created by Thoby L. Noorhalim
  26 August 2021
*/

#include <ControllerData.h>

// ---------- Constructor ----------
ControllerData::ControllerData(){};

// ---------- Setters ----------
void ControllerData::setX(string x){
  this->x = stod(x);
}

void ControllerData::setY(string y){
  this->y = stod(y);
}

void ControllerData::setR(string r){
  this->r = stod(r);
}

void ControllerData::setTheta(string theta){
  this->theta = stod(theta);
}

void ControllerData::setIntensity(string intensity){
  this->intensity = stod(intensity);
}

void ControllerData::setButtonState(string state){
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


