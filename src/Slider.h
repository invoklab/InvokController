/*
  Slider.h - Library for storing and
  updating Slider data.
  Created by Thoby L. Noorhalim.
  28 September 2021.
*/

#ifndef SLIDER_H
#define SLIDER_H

#include <string>
#include <vector>

using namespace std;

class Slider {
  private:
    double sliderData[6] = {0.0};

  public:
    // ---------- Constructor ----------
    Slider();

    void updateData(vector<string> parsedData);
    double getSliderData(int whichSlider);
};

#endif