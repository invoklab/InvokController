/*
  ControllerData.h - Library for defining and storing
  raw values from string, sent by the app.
  Created by Thoby L. Noorhalim.
  26 August 2021.
*/

#ifndef CONTROLLER_DATA_H
#define CONTROLLER_DATA_H

#include <string>
#include <vector>

class ControllerData{
  private:
    double r = 0.0;
    double theta = 0.0;
    double x = 0.0;
    double y = 0.0;
    double intensity = 0.0;
    bool buttonState = false;


  public:
    // ---------- Constructor ----------
    ControllerData();

    // ---------- Setters ----------
    void setX(std::string x);
    void setY(std::string y);
    void setR(std::string r);
    void setTheta(std::string theta);
    void setIntensity(std::string intensity);
    void setButtonState(std::string state);
    

    // ---------- Getters ----------
    double getX();
    double getY();
    double getR();
    double getTheta();
    double getIntensity();
    bool getButtonState();
    
};

#endif