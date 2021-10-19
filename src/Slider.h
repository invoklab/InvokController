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


class Slider {
  private:
    double sliderData[6] = {0.0};

  public:
    // ---------- Constructor ----------
    Slider();

    void updateData(std::vector<std::string> parsedData);
    double getSliderData(int whichSlider);
};

#endif