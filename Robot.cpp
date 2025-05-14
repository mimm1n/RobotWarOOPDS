#include "Robot.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

Robot(int robotX, int robotY, string name, string type){
    setRobotX(robotX);
    setRobotY(robotY);
    setRobotName(name);
    setRobotType(type);
}

virtual ~Robot(){}

void setRobotX(int x){
    robotX = x;
}

int getRobotX() const{
    return robotX;
}

void setRobotY(int y){
    robotY = y;
}

int getRobotY() const{
    return robotY;
}

void setRobotName(string name){
    robotName = name;
}

string getRobotName() const{
    return robotName;
}

void setRobotType(string type){
    robotType = type;
}

string getRobotType() const{
    return robotType;
}
