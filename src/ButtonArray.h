/*
  ButtonArray.h - Library for storing and
  updating Button Array data.
  Created by Thoby L. Noorhalim.
  3 September 2021.
*/

#ifndef BUTTON_ARRAY_H
#define BUTTON_ARRAY_H

#include <string>
#include <vector>

class ButtonArray {
  private:
    bool buttonArrayState[12] = {0};
  public:
    // ---------- Constructor ----------
    ButtonArray();

    void updateData(std::vector<std::string> parsedData);
    void setButtonArrayState(std::vector<std::string> state);
    bool getButtonArrayState(int button);
};

#endif