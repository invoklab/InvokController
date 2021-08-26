/*
  ControllerData.h - Library for defining and storing
  raw values from string, sent by the app.
  Created by Thoby L. Noorhalim.
  26 August 2021.
*/

#ifndef CONTROLLER_DATA_H
#define CONTROLLER_DATA_H

#include <string>

#define NUM_OF_DATA 10

using namespace std;
class ControllerData{
  private:
    double r = 0.0;
    double theta = 0.0;
    double x = 0.0;
    double y = 0.0;
    double intensity = 0.0;
  
  public:
    // ---------- Constructor ----------
    ControllerData();

    // ---------- Setters ----------
    void setX(string x);
    void setY(string y);
    void setR(string r);
    void setTheta(string theta);
    void setIntensity(string intensity);

    // ---------- Getters ----------
    double getX();
    double getY();
    double getR();
    double getTheta();
    double getIntensity();
};

#endif