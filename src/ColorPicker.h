/*
  ColorPicker.h - Library for storing and
  updating Color data.
  Created by Thoby L. Noorhalim.
  1 September 2021.
*/

#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <ColorData.h>
#include <string>
#include <vector>

using namespace std;

class ColorPicker : public ColorData {
  public:
    // ---------- Constructor ----------
    ColorPicker();

    void updateData(vector<string> parsedData);
};

#endif