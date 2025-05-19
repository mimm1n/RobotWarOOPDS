/**********|**********|**********|
Program: Robot.cpp
Course: OOPDS
Trimester: 2510
Name: Aliyah, Khayrin, Aimi, Amirul
ID: 243UC24665 , 243UC246KQ , 243UC247CJ, 241UC24199
Lecture Section: TC2L
Tutorial Section: TT7L
Email: NOR.ALIYAH.SYAHIRAH@student.mmu.edu.my, KHAYRIN.SOFIYA.JAMEL@student.mmu.edu.my, AIMI.MOHD.FAIZAL@student.mmu.edu.my, AMIRUL.IHTISYAM.IDRUS@student.mmu.edu.my
Phone: 0146202605, 0193320041, 0139071648, 0194090095
**********|**********|**********/

#include "Robot.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

Robot::Robot(int x, int y, string name, string type){
    setRobotX(x);
    setRobotY(y);
    robotName = name;
    setRobotType(type);
}

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

string Robot::getRobotName() const{
    return robotName;
}

void Robot::setRobotType(string type){
    robotType = type;
}

string Robot::getRobotType() const{
    return robotType;
}

bool Robot::addLife(){
    return lives++;
}

bool Robot::reduceLife(){
    if(lives>0)
        return lives--;
    return false;
}

int Robot::getLives() const{
    return lives;
}

bool Robot::isAlive() const{
    return lives>0;
}

bool Robot::incrementKills(){
    return killCount++;
}

