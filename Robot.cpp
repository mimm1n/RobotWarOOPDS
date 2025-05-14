#include "Robot.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

Robot::Robot(int robotX, int robotY, string name, string type){
    setRobotX(robotX);
    setRobotY(robotY);
    setRobotName(name);
    setRobotType(type);
}

// virtual ~Robot(){}

void Robot::setRobotX(int x){
    robotX = x;
}

int Robot::getRobotX() const{
    return robotX;
}

void Robot::setRobotY(int y){
    robotY = y;
}

int Robot::getRobotY() const{
    return robotY;
}

void Robot::setRobotName(string name){
    robotName = name;
}

string Robot::getRobotName() const{
    return robotName;
}

void Robot::setRobotType(string type){
    robotType = type;
}

string Robot::getRobotType() const{
    return robotType;
}
