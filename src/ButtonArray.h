/*
  ButtonArray.h - Library for storing and
  updating Button Array data.
  Created by Thoby L. Noorhalim.
  3 September 2021.
*/

#ifndef BUTTON_ARRAY_H
#define BUTTON_ARRAY_H

#include <ControllerData.h>
#include <string>
#include <vector>

using namespace std;

class ButtonArray : public ControllerData {
  public:
    // ---------- Constructor ----------
    ButtonArray();

    void updateData(vector<string> parsedData);
};

#endif