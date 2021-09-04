/*
  Class definition for ButtonArray.h library.
  Created by Thoby L. Noorhalim
  3 September 2021
*/

#include<ButtonArray.h>

// ---------- Constructor ----------
ButtonArray::ButtonArray(){};

void ButtonArray::updateData(vector<string> parsedData){
  setButtonArrayState(parsedData);
}