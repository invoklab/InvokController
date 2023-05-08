/*
  Motion.h - Library for storing and
  updating Motion data.
  Created by Thoby L. Noorhalim.
  6 May 2023.
*/

#ifndef MOTION_H
#define MOTION_H

#include <ControllerData.h>
#include <string>
#include <vector>

class Motion : public ControllerData {
  public:
    // ---------- Constructor ----------
    Motion();

    void updateData(std::vector<std::string> parsedData);
};

#endif