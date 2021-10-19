/*
  Class definition for ColorData.h library.
  Created by Thoby L. Noorhalim
  1 September 2021
*/

#include <ColorData.h>

// Constructor
ColorData::ColorData(){};

// ---------- Setters ----------
void ColorData::setA(std::string a){
  this->a = stoi(a);
}

void ColorData::setR(std::string r){
  this->r = stoi(r);
}

void ColorData::setG(std::string g){
  this->g = stoi(g);
}

void ColorData::setB(std::string b){
  this->b = stoi(b);
}

void ColorData::setH(std::string h){
  this->h = stod(h);
}

void ColorData::setS(std::string s){
  this->s = stod(s);
}

void ColorData::setV(std::string v){
  this->v = stod(v);
}


// ---------- Getters ----------
int ColorData::getA(){
  return this->a;
}

int ColorData::getR(){
  return this->r;
}

int ColorData::getG(){
  return this->g;
}

int ColorData::getB(){
  return this->b;
}

double ColorData::getH(){
  return this->h;
}

double ColorData::getS(){
  return this->s;
}

double ColorData::getV(){
  return this->v;
}