//*********************************************************   
// Program: main.cpp   
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

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <random>
#include "Robot.h"
using namespace std;

class GenericRobot;

/**********************************************************************
Battlefield Class 
 *********************************************************************/
class Battlefield {
private:
  int battlefieldCols_ = -1; // variable to assign number of columns
  int battlefieldRows_ = -1; // variable to assign number of rows

  int totalTurns_ = -1; // variable to assign total turns
  int currentTurn_ = 0; //??

  int numOfRobots_ = -1; // variable to assign number of robots

vector<GenericRobot *> robots_; 
// queue<Robot *> destroyedRobots_;
// queue<Robot *> waitingRobots_;  

vector<vector<string>> battlefield_;

public:
  // Get function
  int battlefieldCols() { return battlefieldCols_; }
  int battlefieldRows() { return battlefieldRows_; }
  int turn() { return totalTurns_; }
  int numOfRobots() { return numOfRobots_; }
  
  void readFile(string filename);
  void placeRobots();
  void displayBattlefield() const;
  void respawnRobot();
};

/**********************************************************************
Robot Action Classes 
 *********************************************************************/
class ThinkingRobot : virtual public Robot{
    public:
        ThinkingRobot(){}
        virtual void actionThink(Battlefield* battlefield) = 0;
        
};

class SeeingRobot : virtual public Robot{
    public:
        SeeingRobot(){}
        virtual void actionLook(Battlefield* battlefield) = 0;
};

class MovingRobot : virtual public Robot{
    public:
        MovingRobot(){}
        // virtual void setLocation(int x, int y);
        virtual void actionMove(Battlefield* battlefield) = 0;
};

class ShootingRobot : virtual public Robot{
    private:
        int shells = 10;
    public:
        ShootingRobot(){}
        void setShells(int num);
        int getShells() const;
        // virtual void setLocation(int x, int y);
        virtual void actionFire(Battlefield* battlefield) = 0;
};


/**********************************************************************
Generic Robot Class 
 *********************************************************************/
class GenericRobot : public ShootingRobot, public MovingRobot, 
                    public SeeingRobot, public ThinkingRobot{
    private: 
        static int robotIncrement;
    public: 
        GenericRobot(string name, int x, int y) : Robot(x, y, name){
            robotId = robotIncrement; 
            robotIncrement++;
        }

        int getRobotID() const { return robotId; }

        //setter
        void setRobotType(int RobotType) override {
            robotType = RobotType;
        }

        //getter
        int getRobotType() const override { return RobotType; }

        virtual void actionFire(Battlefield* battlefield) override {
            // ShootingRobot::actionShoot(battlefield); 
        }
        virtual void actionMove(Battlefield* battlefield) override {}
        virtual void actionLook(Battlefield* battlefield) override {}
        virtual void actionThink(Battlefield* battlefield)override {}
        void actionRand(Battlefield* battlefield){
            random_device rd; 
            mt19937 gen(rd()); 
            uniform_int_distribution<> distr(0, 10); // define range

            actionThink(battlefield);
            actionLook(battlefield); 

            int randomInt = distr(gen);

            if(randomInt % 2 == 0) { 
                actionMove(battlefield);
                actionFire(battlefield); 
            }

        else if(randomInt % 2 == 1){
            actionFire(battlefield);
            actionMove(battlefield); 
        }
    }
};

    int GenericRobot::robotIncrement = 0;

int main() {
    cout << "Hello World!" << endl;
    Battlefield battlefield;
    battlefield.readFile("inputFile.txt");
    battlefield.placeRobots();
    battlefield.displayBattlefield();
    

    return 0;
}

/**********************************************************************
Function Definitions
 *********************************************************************/
// void ThinkingRobot::setLocation(int x, int y){
//     setRobotX(x);
//     setRobotY(y);
// }

// // void SeeingRobot::setLocation(int x, int y){
// //     setRobotX(x);
// //     setRobotY(y);
// // }

// void MovingRobot::setLocation(int x, int y){
//     setRobotX(x);
//     setRobotY(y);
// }

// void ShootingRobot::setLocation(int x, int y){
//     setRobotX(x);
//     setRobotY(y);
// }

void ShootingRobot::setShells(int num){
    shells = num;
}

int ShootingRobot::getShells() const{
    return shells;
}


/**********************************************************************
Battlefield Functions
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

    }else{
      x = stoi(xStr);
      y = stoi(yStr);
    }
robots_.push_back(new GenericRobot(name,x,y));
}
}

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

    battlefield_[y][x]=robots_[i]->getRobotID();
    cout << robots_[i]->getRobotID();

    }

    else{
      cout << "Error message: Invalid location for the robot " << robots_[i]->getRobotName() << endl;
      exit(1);
    }
  }
};

void Battlefield::displayBattlefield() const{
  cout << "Display Battlefield";
  cout << endl << "    ";
  for (int j=0; j< battlefield_[0].size();j++){
    cout << "   " << right << setfill('0') << setw(2) << j << "";
  }
  cout << endl;
 for (int i=0; i< battlefield_.size();i++){
    cout << "     ";
    for (int j = 0; j < battlefield_[i].size(); j++)
    cout << "+----";
  cout << "+" << endl;
  cout << "   " << right << setfill('0') << setw(2) << i;
  for (int j = 0;j <battlefield_[0].size(); j++)
  {
    if(battlefield_[i][j] == "")
    {
      cout << "|" << "    ";
    }
    else
    {
      cout << "|" << left << setfill(' ') << setw(10) << battlefield_[i][j];
    }
  }
  cout << "|" << endl;
  }
  cout << "     ";
  for (int j = 0;j<battlefield_[0].size();j++)
  cout << "+----";
  cout << "+" << endl;
}

// void Battlefield::respawnRobot(){

//     GenericRobot* current = new GenericRobot(name, x, y);
//     if(current->getLives()<= 3 && current->getLives != 0)
//     {
//     destroyedRobots_.push_back(current);
//     if(!GenericRobot){
//     Robot* destroyed = destroyedRobots_.front(); // retrieve first element in destroyedRobots_ queue
//     destroyedRobot_.pop_front(); // remove first element in destroyedRobot_ queue
//     waitingRobots_.push_back(destroyed); //put the removed destroyedRobot_ in waitingRobots
//     Robot* enter = waitingRobots_front();
//     }
//     } 

// }

// class ScoutBot : public SeeingRobot {
// private:
//     int lookCount = 0;
//     const int maxLooks = 3;

// public:
//     void actionLook(Battlefield* battlefield) override {
//         if (lookCount < maxLooks) {
//             // Logic to scan the entire battlefield
//             battlefield->scanEntireField(this);
//             lookCount++;
//         }
//     }
// };

// class TrackBot : public SeeingRobot {
// private:
//     int trackersUsed = 0;
//     const int maxTrackers = 3;

// public:
//     void actionLook(Battlefield* battlefield) override {
//         if (trackersUsed < maxTrackers) {
//             Robot* target = battlefield->selectEnemyToTrack();
//             if (target) {
//                 battlefield->trackEnemy(target, this);
//                 trackersUsed++;
//             }
//         }
//     }
// };
// class LongShotBot : public ShootingRobot {
// public:
//     void actionFire(Battlefield* battlefield) override {
//         int targetX, targetY;
//         if (battlefield->getTargetWithinRange(this, 3, targetX, targetY)) {
//             battlefield->fireAt(targetX, targetY);
//         }
//     }
// };
// class SemiAutoBot : public ShootingRobot {
// public:
//     void actionFire(Battlefield* battlefield) override {
//         int targetX, targetY;
//         if (battlefield->getTarget(this, targetX, targetY)) {
//             for (int i = 0; i < 3; ++i) {
//                 battlefield->fireAt(targetX, targetY); // 3 shells
//             }
//         }
//     }
// };
// class ThirtyShotBot : public ShootingRobot {
// private:
//     int ammo = 0;

// public:
//     void actionFire(Battlefield* battlefield) override {
//         ammo = 30; // Reload
//     }
// };
// class HideBot : public ThinkingRobot {
// private:
//     int hideTurnsUsed = 0;
//     const int maxHideTurns = 3;
//     bool isHidden = false;

// public:
//     void actionThink(Battlefield* battlefield) override {
//         if (hideTurnsUsed < maxHideTurns) {
//             isHidden = true;
//             hideTurnsUsed++;
//             battlefield->setHidden(this, true);
//         }
//     }
// };
// class JumpBot : public MovingRobot {
// private:
//     int jumpsUsed = 0;
//     const int maxJumps = 3;

// public:
//     void actionMove(Battlefield* battlefield) override {
//         if (jumpsUsed < maxJumps) {
//             int newX, newY;
//             battlefield->getRandomLocation(newX, newY);
//             setLocation(newX, newY);
//             jumpsUsed++;
//         }
//     }
// };



