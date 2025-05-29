//*********************************************************   
// Program: Robot.cpp   
// Course: CCP6124 OOPDS  
// Lecture Class: TC2L 
// Tutorial Class: TT7L 
// Trimester: 2510 
// Member_1: 243UC24665 | NOR ALIYAH SYAHIRAH BINTI MUHD HASSANAL | NOR.ALIYAH.SYAHIRAH@student.mmu.edu.my | 0146202605 
// Member_2: 243UC246KQ | KHAYRIN SOFIYA BINTI JAMEL | KHAYRIN.SOFIYA.JAMEL@student.mmu.edu.my | 0193320041 
// Member_3: 243UC247CJ | AIMI BINTI MOHD FAIZAL | AIMI.MOHD.FAIZAL@student.mmu.edu.my | 0139071648 
// Member_4: 241UC24199 | AMIRUL IHTISYAM BIN IDRUS | AMIRUL.IHTISYAM.IDRUS@student.mmu.edu.my | 0194090095	  
//********************************************************* 
// Task Distribution 
// Member_1:   
// Member_2:   
// Member_3:   
// Member_4: 
// ******************************************************** 

#include "Robot.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

/**********************************************************************
 * Robot (constructor)
 * task: Constructs a robot object by assigning it's x and y 
 *       coordinates, its name, and its type 
 * @param x - x coordinate
 *        y - y coordinate
 *        name - robot's name
 *********************************************************************/
Robot::Robot(int x, int y, string name){
    setRobotX(x);
    setRobotY(y);
    robotName = name;
}

/**********************************************************************
 * setRobotX
 * task: sets the x coordinate of the robot
 * @param x - x coordinate
 *********************************************************************/
void Robot::setRobotX(int x){
    robotX = x;
}

/**********************************************************************
 * getRobotX
 * task: gets the x coordinate of the robot
 * @return robotX - x coordinate of the robot
 *********************************************************************/
int Robot::getRobotX() const{
    return robotX;
}

/**********************************************************************
 * setRobotY
 * task: sets the y coordinate of the robot
 * @param y - y coordinate
 *********************************************************************/
void Robot::setRobotY(int y){
    robotY = y;
}

/**********************************************************************
 * getRobotY
 * task: gets the y coordinate of the robot
 * @return robotY - y coordinate of the robot
 *********************************************************************/
int Robot::getRobotY() const{
    return robotY;
}

/**********************************************************************
 * getRobotName
 * task: gets the name of the robot
 * @return robotName - name of the robot
 *********************************************************************/
string Robot::getRobotName() const{
    return robotName;
}

/**********************************************************************
 * addLife
 * task: Increases the lives count by 1
 *********************************************************************/
void Robot::addLife(){
    lives++;
}

/**********************************************************************
 * reduceLife
 * task: Decreases the lives count by 1 if the robot isAlive
 * @return true if robot is alive after decreasing the lives count 
 *         by 1, false if robot dead/destroyed
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
 * @return lives - number of lives of the robot 
 *********************************************************************/
int Robot::getLives() const{
    return lives;
}

/**********************************************************************
 * setLives
 * task: sets the lives count
 * @param live - live count
 *********************************************************************/
void Robot::setLives(int live){
    lives = live;
}

/**********************************************************************
 * isAlive
 * task: Checks if the lives count is greater than 0
 * @return true if the lives count is greater than 0
 *********************************************************************/
bool Robot::isAlive() const{
    if(lives<=0){
        cout << "Robot" << robotName << "is dead!";
        return false;
    }
    return true;
}

/**********************************************************************
 * getKills
 * task: gets the number of kills the robot has
 * @return killCount - number of kills so far
 *********************************************************************/
int Robot::getKills() const{
    return killCount;
}

/**********************************************************************
 * setKills
 * task: sets the kill count
 * @param kills - kill count
 *********************************************************************/
void Robot::setKills(int kills){
    killCount = kills;
}

/**********************************************************************
 * incrementKills
 * task: Increases the kill count by 1
 * @return killCount - number of kills so far
 *********************************************************************/
void Robot::incrementKills(){
    killCount++;
}

/**********************************************************************
 * canUpgrade
 * task: Checks if the upgrade count is lesser than max upgrades
 * @return true if it hasn't reached max upgrades
 *********************************************************************/
bool Robot::canUpgrade() const{
    if(upgradeCount < MAX_UPGRADES){
        return true;
    }
    return false;
}

/**********************************************************************
 * incrementKills
 * task: Increases the kill count by 1
 * @return killCount - number of kills so far
 *********************************************************************/
void Robot::addUpgrade(int currentUpgradeCount){
    upgradeCount = currentUpgradeCount + 1;
}