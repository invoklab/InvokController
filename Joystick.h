#include <ControllerData.h>

#define NUM_OF_DATA 10
#define DATA_LENGTH 10

class Joystick : public ControllerData {
  public:
    Joystick();

    void updateData(char parsedData[NUM_OF_DATA][DATA_LENGTH]);

};

Joystick::Joystick(){};

void Joystick::updateData(char parsedData[NUM_OF_DATA][DATA_LENGTH]){
  setX(parsedData[1]); setY(parsedData[2]);
  setR(parsedData[3]); setTheta(parsedData[4]);
  setIntensity(parsedData[5]);
  // Serial.println("theta is  " + String(getX()));
}