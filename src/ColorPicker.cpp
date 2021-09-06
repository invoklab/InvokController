/*
  Class definition for ColorPicker.h library.
  Created by Thoby L. Noorhalim
  1 September 2021
*/

#include<ColorPicker.h>

// ---------- Constructor ----------
ColorPicker::ColorPicker(){};

void ColorPicker::updateData(vector<string> parsedData){
  setA(parsedData.at(1)); setR(parsedData.at(2));
  setG(parsedData.at(3)); setB(parsedData.at(4));
  setH(parsedData.at(5)); setS(parsedData.at(6));
  setV(parsedData.at(6));
}