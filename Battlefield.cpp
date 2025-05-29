//*********************************************************   
// Program: Battlefield.cpp   
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

#include "Battlefield.h"
#include "Robot.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <queue>
#include "GenericRobot.h"
using namespace std;

/**********************************************************************
 * battlefieldCols
 * task: 
 * @return battlefieldCols_ - 
 *********************************************************************/
int Battlefield::battlefieldCols(){ 
    return battlefieldCols_; 
}

/**********************************************************************
 * battlefieldRows
 * task: 
 * @return battlefieldRows_ - 
 *********************************************************************/
int Battlefield::battlefieldRows(){
    return battlefieldRows_;
}

/**********************************************************************
 * turns
 * task: 
 * @return totalTurns_ - 
 *********************************************************************/
int Battlefield::turns(){
    return totalTurns_;
}

/**********************************************************************
 * numOfRobots
 * task: 
 * @return numOfRobots_ - 
 *********************************************************************/
int Battlefield::numOfRobots(){
    return numOfRobots_; 
}

/**********************************************************************
 * currentTurn
 * task: 
 * @return currentTurn_ - 
 *********************************************************************/
int Battlefield::currentTurn(){
    return currentTurn_; 
}

/**********************************************************************
 * getPlayer
 * task: 
 * @param x -
 *        y -
 * @return  
 *********************************************************************/
string Battlefield::getPlayer(int x, int y){
    return battlefield_[y][x];
}

/**********************************************************************
 * getAllRobots
 * task: 
 * @return robots_ - 
 *********************************************************************/
vector <GenericRobot *> Battlefield::getAllRobots() const {
    return robots_;
}

/**********************************************************************
 * getAllRobotId
 * task: 
 * @return allRobotId - 
 *********************************************************************/
vector <int> Battlefield::getAllRobotId() const {
    return allRobotId;
}

/**********************************************************************
 * getCurrentPlayer
 * task: 
 * @return 
 *********************************************************************/
GenericRobot* Battlefield::getCurrentPlayer() const {
    return waitingRobots_.front();
}

/**********************************************************************
 * readFile
 * task: 
 * @param filename - 
 *********************************************************************/
void Battlefield::readFile(string filename) {

    ifstream infile(filename);
    string line;

    //find matrix
    getline(infile, line); //read first line
    size_t pos1 = line.find(":");
    if (pos1 != string::npos){
        string numStr = line.substr(pos1+2);
        stringstream ss(numStr);
        string colstr, rowstr;
        ss >> rowstr >> colstr;
        battlefieldRows_ = stoi(rowstr);
        battlefieldCols_ = stoi(colstr);
    }

    battlefield_ = vector<vector<string>>(battlefieldRows_+ 1, vector<string>(battlefieldCols_+ 1, "")); //2D vector for rows and columns

    //find total turn
    getline(infile, line); //read second line
    size_t pos2 = line.find(":");
    if (pos2 != string::npos){
        string numStr2 = line.substr(pos2+2);
        totalTurns_ = stoi(numStr2);
    }
    
    //find total robot
    getline(infile, line);// read the third line
    size_t pos3 = line.find(":");
    if (pos3 != string::npos){
        string numStr3 = line.substr(pos3+2);
        numOfRobots_ = stoi(numStr3);
    }

    cout << battlefieldCols_ << " " << battlefieldRows_ << " " << totalTurns_ << " " << numOfRobots_ << endl;

    //find robot name and position
    for (int i = 0; i < numOfRobots_; i++) {
        getline(infile, line);
        istringstream robotLine(line);
        string name, xStr, yStr;
        int x, y;
        robotLine >> name >> yStr >> xStr;
        if (xStr == "random" && yStr == "random"){
            x = rand() % (battlefieldRows_);
            y = rand() % (battlefieldCols_);
            cout << x << y << endl;
        } else {
            x = stoi(xStr);
            y = stoi(yStr);
        }
        robots_.push_back(new GenericRobot(name,x,y));
    }
}

/**********************************************************************
 * placeRobots
 * task: 
 *********************************************************************/
void Battlefield::placeRobots(){
    for(int i=0;i<battlefield_.size(); i++){
        for (int j=0; j<battlefield_[i].size(); j++){
            battlefield_[i][j]="";
        }
    }

    for (int i=0;i<robots_.size(); i++){
        int y = robots_[i]->getRobotY();
        int x = robots_[i]->getRobotX();

        if(y < battlefield_.size() && x < battlefield_[0].size()){
            battlefield_[y][x]= to_string(robots_[i]->getRobotID());
        } else {
            cout << "Error message: Invalid location for the robot " << robots_[i]->getRobotName() << endl;
            exit(1);
        }
        
        waitingRobots_.push(robots_[i]);
 
    }

};

/**********************************************************************
 * displayBattlefield
 * task: Displays the battlefield and any needed players
 * x and y are the center of the nine square grid when looking
 * when x = -10 and y = -10, all robots displayed on field (scoutBot)
 * when x = -5 and y = -5 only current player's position displayed
 * @param x - the x coordinate of the nine square
 *        y - the y coordinate of the nine square
 *********************************************************************/
void Battlefield::displayBattlefield(int x, int y, vector <int> targets ) const{
    cout << "Display Battlefield";
    cout << endl << "    ";

    for (int j=0; j< battlefield_[0].size();j++)
        cout << "   " << right << setfill('0') << setw(2) << j << "";
    cout << endl;

    for (int i=0; i< battlefield_.size();i++){
        cout << "     ";
        for (int j = 0; j < battlefield_[i].size(); j++)
            cout << "+----";
        cout << "+" << endl;
        cout << "   " << right << setfill('0') << setw(2) << i;

        for (int j = 0;j <battlefield_[0].size(); j++){
            if(battlefield_[i][j] == ""){
                cout << "|" << "    ";
            } else { //placesRobot
                if(x == -10  && y == -10){ //scout  
                    cout << "|" << "GR";
                    cout << "0";   
                    cout << battlefield_[i][j];
                }else {
                    if (stoi(battlefield_[i][j]) == getCurrentPlayer()->getRobotID()){ //general
                        cout << "|" << "GR";
                        cout << "0";   
                        cout << battlefield_[i][j];
                    }

                    if(y == i-1 || y == i || y == i+1 || x == j-1 || x == j || x == j+1){ //look
                        cout << "|" << "GR";
                        cout << "0";   
                        cout << battlefield_[i][j];
                    }
                }
            }
        }
        cout << "|" << endl;
    }
    cout << "     ";
    for (int j = 0;j<battlefield_[0].size();j++)
        cout << "+----";
    cout << "+" << endl;

}

/**********************************************************************
 * respawnRobot
 * task: 
 * @param index - 
 *********************************************************************/
void Battlefield::respawnRobot(int index){

    Robot* died = robots_[index];
    int size = waitingRobots_.size();

        for(int i = 0; i<size;i++){
            Robot* current = waitingRobots_.front()
            if (current->getRobotId() != died->getRobotId()){
                  waitingRobots_.pop();
                  waitingRobots_.push(current);
            }else{
            waitingRobots_.pop();}

        }

    if(!died->isAlive()){
        destroyedRobots_.push(died);
        return;
    }else{
        int newX = rand() % (battlefieldRows_);
        int newY = rand() % (battlefieldCols_);

        GenericRobot* respawn = new GenericRobot(name, newX, newY);
        respawn->addUpgrade(died->getUpgradeCount()-1);
        respawn->setLives(died->getLives());
        respawn->setKills(died->getKills());
        respawn->setShells(died->getShells());

        battlefield_[died->getRobotY()][died->getRobotX()] = ""; //clear the field
        battlefield_[newY][newX] = to_string(respawn->getRobotId());
        waitingRobots_.push(respawn);
        }
    
}

/**********************************************************************
 * nextTurn
 * task: 
 *********************************************************************/
void Battlefield::nextTurn(){
    currentTurn_++;
    GenericRobot* front = waitingRobots_.front();
    waitingRobots_.pop();
    waitingRobots_.push(front);
}

RobotType Battlefield::findTargetRobot(GenericRobot* target) {
    for (int i = 0; i <= BOMB; ++i) {
        for (Robot* robot : upgradedRobots_[i]) {
            if (robot == target) {
                return static_cast<RobotType>(i);
            }
        }
    }
    return GENERIC;
}

/**********************************************************************
 * robotUpgrade
 * task: 
 *********************************************************************/
 void Battlefield::robotUpgrade(Robot* upgradeRobot_){
    int size = waitingRobots_.size();

        for(int i = 0; i<size;i++){
            Robot* current = waitingRobots_.front()
            if (current->getRobotId() != upgradeRobot_->getRobotId()){
                  waitingRobots_.pop();
                  waitingRobots_.push(current);
            }else{
            waitingRobots_.pop();
            waitingRobots_.push(upgradeRobot_)
            }
        }
        

   for (auto& robot : robots_) {

    if (robot->getRobotId() == upgradeRobot_->getRobotId()) {
        robot = upgradeRobot_;  // Replace pointer
        break;
    }
}

 }