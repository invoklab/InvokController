/*
  Joystick.h - Library for storing and
  updating Joystick data.
  Created by Thoby L. Noorhalim.
  26 August 2021.
*/

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <ControllerData.h>
#include <string>
#include <vector>

using namespace std;

class Joystick : public ControllerData {
  public:
    // ---------- Constructor ----------
    Joystick();

    void updateData(vector<string> parsedData);
};

#endif