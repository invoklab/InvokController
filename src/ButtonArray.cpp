/*
  Class definition for ButtonArray.h library.
  Created by Thoby L. Noorhalim
  3 September 2021
*/

#include<ButtonArray.h>

// ---------- Constructor ----------
ButtonArray::ButtonArray(){};

void ButtonArray::updateData(std::vector<std::string> parsedData){
  setButtonArrayState(parsedData);
}

void ButtonArray::setButtonArrayState(std::vector<std::string> state){
  for(size_t i = 0; i < sizeof(this->buttonArrayState); i++){
    if(state[i+1].compare("1") == 0){
      this->buttonArrayState[i] = true;
    } else {
      this->buttonArrayState[i] = false;
    }
  }
}

bool ButtonArray::getButtonArrayState(int button){
  return this->buttonArrayState[button];
}
