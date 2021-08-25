#ifndef CONTROLLER_DATA_H
#define CONTROLLER_DATA_H

#include <string>

#define NUM_OF_DATA 10

using namespace std;
class ControllerData{
  private:
    double r = 0;
    double theta = 0;
    double x = 0;
    double y = 0;
    double intensity = 0;
  
  public:
    ControllerData();
    void setR(string r);
    void setTheta(string theta);
    void setX(string x);
    void setY(string y);
    void setIntensity(string intensity);

    double getR();
    double getTheta();
    double getX();
    double getY();
    double getIntensity();
};

ControllerData::ControllerData(){};

void ControllerData::setR(string r){
  this->r = stod(r);
}

void ControllerData::setTheta(string theta){
  this->theta = stod(theta);
}

void ControllerData::setX(string x){
  this->x = stod(x);
}

void ControllerData::setY(string y){
  this->y = stod(y);
}

void ControllerData::setIntensity(string intensity){
  this->intensity = stod(intensity);
}

double ControllerData::getR(){
  return this->r;
}

double ControllerData::getTheta(){
  return this->theta;
}

double ControllerData::getX(){
  return this->x;
}

double ControllerData::getY(){
  return this->y;
}

double ControllerData::getIntensity(){
  return this->intensity;
}

#endif