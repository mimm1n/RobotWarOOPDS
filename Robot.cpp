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

/**********************************************************************
 * Robot (constructor)
 * task: Constructs a robot object by assigning it's x and y 
 *       coordinates, its name, and its type 
 * data in: x - x coordinate
 *          y - y coordinate
 *          name - robot's name
 *          type - robot's type
 *********************************************************************/
Robot::Robot(int x, int y, string name, string type){
    setRobotX(x);
    setRobotY(y);
    robotName = name;
    setRobotType(type);
}

/**********************************************************************
 * setRobotX
 * task: sets the x coordinate of the robot
 * data in: x - x coordinate
 *********************************************************************/
void Robot::setRobotX(int x){
    robotX = x;
}

/**********************************************************************
 * getRobotX
 * task: gets the x coordinate of the robot
 * data out: robotX - x coordinate of the robot
 *********************************************************************/
int Robot::getRobotX() const{
    return robotX;
}

/**********************************************************************
 * setRobotY
 * task: sets the y coordinate of the robot
 * data in: y - y coordinate
 *********************************************************************/
void Robot::setRobotY(int y){
    robotY = y;
}

/**********************************************************************
 * getRobotY
 * task: gets the y coordinate of the robot
 * data out: robotY - y coordinate of the robot
 *********************************************************************/
int Robot::getRobotY() const{
    return robotY;
}

/**********************************************************************
 * getRobotName
 * task: gets the name of the robot
 * data out: robotName - name of the robot
 *********************************************************************/
string Robot::getRobotName() const{
    return robotName;
}

/**********************************************************************
 * setRobotType
 * task: sets the robot's type
 * data in: type - type of robot
 *********************************************************************/
void Robot::setRobotType(string type){
    robotType = type;
}

/**********************************************************************
 * getRobotType
 * task: gets the type of the robot
 * data out: robotType - type of the robot
 *********************************************************************/
string Robot::getRobotType() const{
    return robotType;
}

/**********************************************************************
 * addLife
 * task: Increases the lives count by 1
 * data out: lives - number of lives the robot has 
 *********************************************************************/
int Robot::addLife(){
    return lives++;
}

/**********************************************************************
 * reduceLife
 * task: Decreases the lives count by 1 if the robot isAlive
 * data out: true if robot is alive after decreasing the lives count 
 *           by 1, false if robot dead/destroyed in the first place
 *********************************************************************/
bool Robot::reduceLife(){
    if(isAlive()){
        lives--;
        return isAlive();
    }
    return false;
}

/**********************************************************************
 * getLives
 * task: gets the number of lives the robot has left
 * data out: lives - number of lives of the robot 
 *********************************************************************/
int Robot::getLives() const{
    return lives;
}

/**********************************************************************
 * isAlive
 * task: Checks if the lives count is greater than 0
 * data out: true if the lives count is greater than 0
 *********************************************************************/
bool Robot::isAlive() const{
    if(lives<=0){
        cout << "Robot" << robotName << "is dead!"
        return false;
    }
    return true;
}

/**********************************************************************
 * incrementKills
 * task: Increases the kill count by 1
 * data out: killCount - number of kills so far
 *********************************************************************/
int Robot::incrementKills(){
    return killCount++;
}

