#define NUM_OF_DATA 10
#define DATA_LENGTH 10

class ControllerData{
  private:
    double r = 0;
    double theta = 0;
    double x = 0;
    double y = 0;
    double intensity = 0;
  
  public:
    ControllerData();
    // ControllerData(char parsedData[NUM_OF_DATA][DATA_LENGTH]);
    void setR(char *r);
    void setTheta(char *theta);
    void setX(char *x);
    void setY(char *y);
    void setIntensity(char *intensity);

    double getR();
    double getTheta();
    double getX();
    double getY();
    double getIntensity();
};

ControllerData::ControllerData(){};

void ControllerData::setR(char *r){
  this->r = atof(r);
}

void ControllerData::setTheta(char *theta){
  this->theta = atof(theta);
}

void ControllerData::setX(char *x){
  this->x = atof(x);
}

void ControllerData::setY(char *y){
  this->y = atof(y);
}

void ControllerData::setIntensity(char *intensity){
  this->intensity = atof(intensity);
}



double ControllerData::getR(){
  return this->r;
}

double ControllerData::getTheta(){
  return this->theta;
}

double ControllerData::getX(){
  return this->x;
}

double ControllerData::getY(){
  return this->y;
}

double ControllerData::getIntensity(){
  return this->intensity;
}