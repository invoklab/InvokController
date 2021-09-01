/*
  ColorData.h - Library for defining and storing
  raw values from string, sent by the app.
  Created by Thoby L. Noorhalim.
  1 September 2021.
*/

#ifndef COLOR_DATA_H
#define COLOR_DATA_H

#include <string>

#define NUM_OF_DATA 10

using namespace std;
class ColorData{
  private:
    int a = 0;
    int r = 0;
    int g = 0;
    int b = 0;
    double h = 0.0;
    double s = 0.0;
    double v = 0.0;
  
  public:
    // ---------- Constructor ----------
    ColorData();

    // ---------- Setters ----------
    void setA(string a);
    void setR(string r);
    void setG(string g);
    void setB(string b);
    void setH(string h);
    void setS(string s);
    void setV(string v);


    // ---------- Getters ----------
    int getA();
    int getR();
    int getG();
    int getB();
    double getH();
    double getS();
    double getV();
};

#endif