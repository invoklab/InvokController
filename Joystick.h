#include <ControllerData.h>
#include <string>

#define NUM_OF_DATA 10
#define DATA_LENGTH 10

using namespace std;

class Joystick : public ControllerData {
  public:
    Joystick();

    void updateData(vector<string> parsedData);

};

Joystick::Joystick(){};

void Joystick::updateData(vector<string> parsedData){
  setX(parsedData.at(1)); setY(parsedData.at(2));
  setR(parsedData.at(3)); setTheta(parsedData.at(4));
  setIntensity(parsedData.at(5));
  // Serial.println("theta is  " + String(getX()));
}