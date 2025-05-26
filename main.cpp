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

/**********************************************************************
CLASS DEFINTIONS
**********************************************************************/

class GenericRobot;

/**********************************************************************
Battlefield Class 
**********************************************************************/
class Battlefield {
    private:
        int battlefieldCols_ = -1; // variable to assign number of columns
        int battlefieldRows_ = -1; // variable to assign number of rows

        int totalTurns_ = -1; // variable to assign total turns
        int currentTurn_ = 1; 
        int currentPlayer = 0;
    

        int numOfRobots_ = -1; // variable to assign number of robots

        vector<GenericRobot *> robots_; 
        queue<GenericRobot *> destroyedRobots_;
        queue<GenericRobot *> waitingRobots_;  

        vector<vector<string>> battlefield_;

    public:
        // Get function
        int battlefieldCols() { return battlefieldCols_; }
        int battlefieldRows() { return battlefieldRows_; }
        int turns() { return totalTurns_; }
        int numOfRobots() { return numOfRobots_; }
        int currentTurn(){ return currentTurn_; }
        string getPlayer(int x, int y){return battlefield_[y][x];}
        vector <GenericRobot *> getAllRobot() const {return robots_;}
        GenericRobot* getCurrentPlayer() const { return waitingRobots_.front(); }
        
        
        void readFile(string filename);
        void placeRobots();
        void displayBattlefield(int x, int y) const;
        void respawnRobot(int x);
        void nextTurn();
};

/**********************************************************************
Robot Action Classes 
**********************************************************************/
class ThinkingRobot : virtual public Robot{
    public:
        ThinkingRobot(){}
        virtual void actionThink(Battlefield* battlefield) = 0;
};

class SeeingRobot : virtual public Robot{
    public:
        SeeingRobot(){}
        virtual void actionLook(Battlefield* battlefield,int x, int y) = 0;
};

class MovingRobot : virtual public Robot{
    public:
        MovingRobot(){}
        virtual void actionMove(Battlefield* battlefield, int x, int y) = 0;
};

class ShootingRobot : virtual public Robot{
    private:
        int shells = 10;
    public:
        ShootingRobot(){}
        void setShells(int num) { shells = num; }
        int getShells() const { return shells; }
        virtual void actionFire(Battlefield* battlefield, int x, int y) = 0;
};

/**********************************************************************
Upgraded Robot Classes 
**********************************************************************/
class ThirtyShotBot : public ShootingRobot {
    public:
        void actionFire(Battlefield* battlefield, int x, int y) override { setShells(30); }
        void setRobotType(int type) override { robotType = THIRTYSHOT; }
        int getRobotType() const override { return THIRTYSHOT;}
};

class JumpBot : public MovingRobot {
    private:
        int jumpsUsed = 0;
        const int maxJumps = 3;

    public:
        void actionMove(Battlefield* battlefield, int x, int y) override {
            if (jumpsUsed < maxJumps) {
                string targetPosition = battlefield->getPlayer(x, y);
                if (targetPosition.empty()) { //check if theres any robots at the location
                    setRobotX(x);
                    setRobotY(y);
                    jumpsUsed++;
                } else {
                    cout << "Invalid location! There might be a robot there." << endl;
                }
            }
        }
        void setRobotType(int type) override { robotType = JUMP; }
        int getRobotType() const override { return JUMP; }
};

class HealBot : public ShootingRobot {
    public:
        void actionFire(Battlefield* battlefield, int x, int y) override {
            addLife();
            addLife();
            addLife();
        }
        void setRobotType(int type) override { robotType = HEAL; }
        int getRobotType() const override { return HEAL; }
};

class ScoutBot : public SeeingRobot{
    private:
        int lookCount = 0;
        const int maxLooks = 3;

    public:
        void actionLook(Battlefield* battlefield, int x, int y) override {
            if (lookCount < maxLooks) {
                battlefield->displayBattlefield(-10, -10);
                lookCount++;
            }
        }
        void setRobotType(int type) override { robotType=SCOUT; }
        int getRobotType() const override { return SCOUT; }
};

class HideBot : public MovingRobot{
    private:
        int hideTurnsUsed = 0;
        const int maxHideTurns = 3;
        bool isHidden_ = false;

    public:
        void actionMove(Battlefield* battlefield, int x, int y) override {
            if (hideTurnsUsed < maxHideTurns) {
            isHidden_ = true;
            hideTurnsUsed++;
            }
        }
        bool isHidden() const{
            return isHidden_;
        }
};

/**********************************************************************
Generic Robot Class 
**********************************************************************/
class GenericRobot : public ShootingRobot, public MovingRobot, 
        public SeeingRobot, public ThinkingRobot{
    private: 
        static int robotIncrement;
        int upgradeCount = 0; 
        const int MAX_UPGRADE = 3; 
        Robot* robotUpgraded = nullptr; 
    public: 
        GenericRobot(string name, int x, int y) : Robot(x, y, name){
            robotId = robotIncrement; 
            robotIncrement++;
        }

        int getRobotID() const { return robotId; }

        //setter
        void setRobotType(int type) override {
            robotType = type;
        }

        //getter
        int getRobotType() const override { return robotType; }

/**********************************************************************
ActionFire()
**********************************************************************/
        virtual void actionFire(Battlefield* battlefield, int x, int y) override {
            int currentX = getRobotX();  // get current pos, center position like (0,0)
            int currentY = getRobotY(); 

            int lookX = currentX + x;
            int lookY = currentY + y;

            if (robotUpgraded && dynamic_cast<HideBot*>(robotUpgraded) && static_cast<HideBot*>(robotUpgraded)->isHidden()){
                cout << "Shot missed. Robot is hidden." << endl;
                return;
            }

            while (x != 0 || y!= 0){
                if (lookX >= 0 && lookX < battlefield->battlefieldRows() &&  //check if its in bound 
                lookY >= 0 && lookY < battlefield->battlefieldCols()) {
                    cout << "Out of bounds";
                    return;
                }

                string targetRobot = battlefield->getPlayer(lookX, lookY);
                if (targetRobot.empty()) { //check if theres any robots at the location
                    cout << "Missed!"; //no robot, miss
                    return;
                }

                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<> distr(1, 100); // 1 to 100 randomiser

                int hitChance = distr(gen); 
                if (hitChance <= 70) {  // 70% chance 
                    int targetRobotId = stoi(targetRobot);
                    GenericRobot* targetRobot = nullptr; 
                    
                    for (GenericRobot* robot : battlefield->robots_){
                        if (robot->getRobotID() == targetRobotId) {
                            targetRobot = robot;
                            break;
                        }
                    }

                    if (targetRobot) {
                        targetRobot->reduceLife();
                        if(!targetRobot->isAlive()){
                            cout << "Robot" << targetRobot->getRobotID() << "has been destroyed." << endl;
                            incrementKills(); //increment kills for this robot 
                        }
                            
                    }
                }

                cout << "Cannot shoot at own position." << endl; 
            }
        }

/**********************************************************************
actionMove()
**********************************************************************/
        virtual void actionMove(Battlefield* battlefield, int x, int y) override {
            if(robotUpgraded)
                robotUpgraded->actionMove(battlefield, x, y);
        }

/**********************************************************************
actionLook()
**********************************************************************/
        virtual void actionLook(Battlefield* battlefield, int x, int y) override {
            if(robotUpgraded)
                robotUpgraded->actionLook(battlefield, -10, -10);

            int currentX = getRobotX();  // get current pos, center position like (0,0)
            int currentY = getRobotY(); 

            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int lookX = currentX + dx;
                    int lookY = currentY + dy;

                
                    if(battlefield->getPlayer(lookX, lookY) != ""){
                        int lookRobotId = stoi(battlefield->getPlayer(lookX, lookY)); // find the id of the robot currently in that position 
                        GenericRobot* robotLooked = nullptr;
                        for (GenericRobot* robot : battlefield->robots_){
                            if (robot->getRobotID() == lookRobotId) {
                                robotLooked = robot; 
                                break;
                            }
                        }
                    }  
                }
            }
        }
/**********************************************************************
actionThink()
**********************************************************************/
        virtual void actionThink(Battlefield* battlefield)override {
            actionRand(battlefield);

            if(robotUpgraded)
                robotUpgraded->actionThink(battlefield);
        }

        void upgradeRobot(int upgradeType){
            if (upgradeCount >= MAX_UPGRADE) { 
                cout << "Max upgrade reached." ; 
                return; 
            }

            switch(upgradeType){
                case 1:
                    robotUpgraded = new ScoutBot();
                    break;
                case 2:
                    robotUpgraded = new TrackBot();
                    break;
                case 3:
                    robotUpgraded = new LongShotBot();
                    break;
                case 4:
                    robotUpgraded = new SemiAutoBot();
                    break;
                case 5:
                    robotUpgraded = new ThirtyShotBot();
                    break;
                case 6:
                    robotUpgraded = new JumpBot();
                    break;
                case 7:
                    robotUpgraded = new HideBot();
                    break;
                case 8:
                    robotUpgraded = new ReflectShotBot();
                    break;
                case 9:
                    robotUpgraded = new HealBot();
                    break;
                case 10:
                    robotUpgraded = new BombBot();
                    break;
                default: 
                    return;
            }

            upgradeCount++;
        }

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
    int option, x, y, choice;
    bool exitGame = false, invalidCoordinates;
    Battlefield* battlefield;
    GenericRobot* currentPlayer;
    battlefield->readFile("inputFile.txt");
    battlefield->placeRobots();

    do {
        currentPlayer = battlefield->getCurrentPlayer();

        battlefield->displayBattlefield(-5, -5);
        cout << "Player: " << currentPlayer->getRobotName << endl; 
        cout << "What would you like to do?" << endl;
        cout << "1. Think" << endl;
        cout << "2. Look (x,y)" << endl;
        cout << "3. Fire (x,y)" << endl;
        cout << "4. Move" << endl;
        if (currentPlayer->getRobotType() != -1){
            if (currentPlayer->getRobotType() == SCOUT)
                cout << "5. Scout (see entire battlefield)" << endl;
            else if (currentPlayer->getRobotType() == TRACK)
                cout << "5. Track (plant tracker on another robot)" << endl;
            else if (currentPlayer->getRobotType() == LONGSHOT)
                cout << "5. Fire a long shot (see entire battlefield)" << endl;
            else if (currentPlayer->getRobotType() == SEMIAUTO)
                cout << "You have the SemiAuto upgrade! Each shot you fire shoots 3 consecutive shots." << endl;
            else if (currentPlayer->getRobotType() == JUMP)
                cout << "5. Jump (x,y)" << endl;
            else if (currentPlayer->getRobotType() == HIDE)
                cout << "5. Hide (can't be seen or shot at by other robots)" << endl;
            else if (currentPlayer->getRobotType() == REFLECTSHOT)
                cout << "You have the ReflectShot upgrade! If a robot shoots at you in the new few turns, it will be reflected back at them! >:) " << endl;
            else if (currentPlayer->getRobotType() == HEAL)
                cout << "You have the Heal upgrade! You have a total of " << currentPlayer->getLives() << " lives left." << endl;
            else if (currentPlayer->getRobotType() == BOMB)
                cout << "5. Bomb (shoot all 8 neighbouring locations)" << endl;
        }
        cout << "To quit the game enter any key other than the above options" << endl;
        cout << "Enter your next move option: ";
        cin >> option;

        switch(option){
            case 1: // Think
                currentPlayer->actionThink(battlefield);
                battlefield->nextTurn();
                break;
            case 2: // Look (x,y)
                cout << "Choose where you want to look" << endl;
                cout << "1. UpLeft\n2. Up\n3. UpRight\n4. Left\n5. Center\n 6. Right\n 7. DownLeft\n 8. Down\n 9. DownRight" << endl;
                cin  >> choice;
                switch(choice){
                    case 1: 
                        x = -1, y = 1;
                        break;
                    case 2:
                        x = 0, y = 1;
                        break;
                    case 3:
                        x = 1, y = 1;
                        break;
                    case 4:
                        x = -1, y = 0;
                        break;
                    case 5:
                        x = 0, y = 0;
                        break;
                    case 6:
                        x = 1, y = 0;
                        break;
                    case 7:
                        x = -1, y = -1;
                        break;
                    case 8:
                        x = 0, y = -1;
                        break;
                    case 9:
                        x = 1, y = -1;
                        break;
                    default:
                        x = 0, y = 0;
                        break;
                }
                currentPlayer->actionLook(battlefield, x, y);
                break;
            case 3: // Fire (x,y)
                cout << "Choose where you want to shoot" << endl;
                cout << "1. UpLeft\n2. Up\n3. UpRight\n4. Left\n5. Right\n 6. DownLeft\n 7. Down\n 8. DownRight" << endl;
                cin  >> choice;
                switch(choice){
                    case 1: 
                        x = -1, y = 1;
                        break;
                    case 2:
                        x = 0, y = 1;
                        break;
                    case 3:
                        x = 1, y = 1;
                        break;
                    case 4:
                        x = -1, y = 0;
                        break;
                    case 5:
                        x = 1, y = 0;
                        break;
                    case 6:
                        x = -1, y = -1;
                        break;
                    case 7:
                        x = 0, y = -1;
                        break;
                    case 8:
                        x = 1, y = -1;
                        break;
                    default:
                        x = 0, y = 0;
                        break;
                }
                currentPlayer->actionFire(battlefield, x, y);
                battlefield->nextTurn();
                break;
            case 4: // Move
                cout << "Choose where you want to move" << endl;
                cout << "1. UpLeft\n2. Up\n3. UpRight\n4. Left\n5. Right\n 6. DownLeft\n 7. Down\n 8. DownRight" << endl;
                cin  >> choice;
                switch(choice){
                    case 1: 
                        x = -1, y = 1;
                        break;
                    case 2:
                        x = 0, y = 1;
                        break;
                    case 3:
                        x = 1, y = 1;
                        break;
                    case 4:
                        x = -1, y = 0;
                        break;
                    case 5:
                        x = 1, y = 0;
                        break;
                    case 6:
                        x = -1, y = -1;
                        break;
                    case 7:
                        x = 0, y = -1;
                        break;
                    case 8:
                        x = 1, y = -1;
                        break;
                    default:
                        x = 0, y = 0;
                        break;
                }
                currentPlayer->actionMove(battlefield, x, y);
                battlefield->nextTurn();
                break;
            case 5: // Upgrades if upgraded robot, quit game if not 
                if(currentPlayer->getRobotType() != -1){ 
                    if (currentPlayer->getRobotType() == SCOUT){
                        currentPlayer->actionLook(battlefield, -10, -10);
                    } else if (currentPlayer->getRobotType() == TRACK){
                        // how to deploy this?? 
                        currentPlayer->actionLook(battlefield, x, y);
                    } else if (currentPlayer->getRobotType() == LONGSHOT){
                        bool tooLongShot;
                        do {
                            cout << "LongShot Upgrade allows you to shoot up to three squares away from you !" << endl;
                            cout << "Enter the x and y coordinate of the location you want to shoot at: (separated by a space)" << endl;
                            cin >> x >> y;
                            invalidCoordinates = x < 0 || x >= battlefield->battlefieldCols() || y < 0 || y >= battlefield->battlefieldRows();
                            tooLongShot = x < (currentPlayer->getRobotX() - 4 ) || x > (currentPlayer->getRobotX() + 4 ) || y < (currentPlayer->getRobotY() - 4 ) || y > (currentPlayer->getRobotY() + 4);
                            if (invalidCoordinates || tooLongShot)
                                cout << "Invalid location entered!" << endl;
                        } while (invalidCoordinates || tooLongShot);
                        currentPlayer->actionFire(battlefield, x, y);
                        battlefield->nextTurn();
                    } else if (currentPlayer->getRobotType() == JUMP){
                        do {
                            cout << "Enter the x and y coordinate of the location you want to jump to: (separated by a space)" << endl;
                            cin >> x >> y;
                            invalidCoordinates = x < 0 || x >= battlefield->battlefieldCols() || y < 0 || y >= battlefield->battlefieldRows();
                            if (invalidCoordinates)
                                cout << "Invalid location entered!" << endl;
                        } while (invalidCoordinates);
                        currentPlayer->actionMove(battlefield, x, y);
                        battlefield->nextTurn();
                    } else if (currentPlayer->getRobotType() == HIDE){
                        // how to deploy this?? 
                        currentPlayer->actionMove(battlefield, x, y);
                        battlefield->nextTurn();
                    } else if (currentPlayer->getRobotType() == BOMB){
                        currentPlayer->actionFire(battlefield, -5, -5);
                        battlefield->nextTurn();
                    }
                } else {
                    exitGame = true;
                }
                break;
            default: // Quit game
                exitGame = true;
                break;
        }
    } while(!exitGame && (battlefield->currentTurn() < battlefield->turns()));
    
    return 0;
}

// do{
//     cout << endl << endl;
//     battlefield.displayBattlefield();
//     cout << "Turn " << battlefield.currentTurn() << ":" << endl;
//     battlefield.nextTurn();

// }while(battlefield.currentTurn() != battlefield.turns());


/**********************************************************************
FUNCTION DEFINTIONS
**********************************************************************/

/**********************************************************************
Battlefield Functions
**********************************************************************/
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
        // if(!robots_[i]->isAlive()){respawnRobot(i);}
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
void Battlefield::displayBattlefield(int x, int y) const{
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
                    if (battlefield_[i][j] == getCurrentPlayer()->getRobotID()){ //general
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

void Battlefield::respawnRobot(int index){
    GenericRobot* destroyed = robots_[index];
    destroyedRobots_.push(destroyed);
    int oldX = destroyed -> getRobotX();
    int oldY = destroyed -> getRobotY();
    battlefield_[oldY][oldX] = ""; //clear the field

    GenericRobot* waiting = destroyedRobots_.front();
    waitingRobots_.push(waiting);
    destroyedRobots_.pop();
    if(!waitingRobots_.empty()){
        GenericRobot* respawn = waitingRobots_.front();
        waitingRobots_.pop();

        int newX = rand() % (battlefieldRows_);
        int newY = rand() % (battlefieldCols_);

        respawn->setRobotX(newX);
        respawn->setRobotY(newY);
        battlefield_[newY][newX]=to_string(respawn->getRobotID());
    }
}

void Battlefield::nextTurn(){
    currentTurn_++;
    GenericRobot* front = waitingRobots_.front();
    waitingRobots_.pop();
    waitingRobots_.push(front);
}



// class TrackBot : public SeeingRobot {
// private:
//     int trackersUsed = 0;
//     const int maxTrackers = 3;
//     vector <int> targets;
// public:
//     void actionLook(Battlefield* battlefield, int x, int y) override {
//         if (trackersUsed < maxTrackers) {
//                string target = battlefield->battlefield_[y][x];
//                 if (!target.empty()) { //check if theres any robots at the location
//                 setRobotX(x);
//                 setRobotY(y);
// // Robot* target = battlefield->selectEnemyToTrack();
// // if (target) {
// //     battlefield->trackEnemy(target, this);
// //     trackersUsed++;
// }
//         }
//     }
// };

class LongShotBot : public ShootingRobot {
public:
    void actionFire(Battlefield* battlefield) override {
        int targetX, targetY;
        if (battlefield->getTargetWithinRange(this, 3, targetX, targetY)) {
battlefield->fireAt(targetX, targetY);
        }
    }
};

class SemiAutoBot : public ShootingRobot {
public:
    void actionFire(Battlefield* battlefield) override {
        int targetX, targetY;
        if (battlefield->getTarget(this, targetX, targetY)) {
for (int i = 0; i < 3; ++i) {
    battlefield->fireAt(targetX, targetY); // 3 shells
}
        }
    }
};
                // random_device rd;
                // mt19937 gen(rd());
                // uniform_int_distribution<> distr(1, 100); // 1 to 100 randomiser

                // int hitChance = distr(gen); 
                // if (hitChance <= 70) {  // 70% chance 
                //     int targetRobotId = stoi(targetRobot);
                //     GenericRobot* targetRobot = nullptr; 
                    
                //     for (GenericRobot* robot : battlefield->robots_){
                //         if (robot->getRobotID() == targetRobotId) {
                //             targetRobot = robot;
                //             break;
                //         }
                //     }

                //     if (targetRobot) {
                //         targetRobot->reduceLife();
                //         if(!targetRobot->isAlive()){
                //             cout << "Robot" << targetRobot->getRobotID() << "has been destroyed." << endl;
                //             incrementKills(); //increment kills for this robot 
                //         }
                            
                //     }
                // }


      class BombBot : public ShootingRobot {
public:
    void actionFire(Battlefield* battlefield, int x, int y) override {

        int cx = battlefield->getCurrentPlayer()->getRobotX();
        int cy = battlefield->getCurrentPlayer()->getRobotY();
        int tx, ty;
        bool invalidCoordinates;
        string target;
        cout << "BombBot bombed surrounding squares!\n";

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue; // Skip self
                tx = cx + dx; 
                ty = cy + dy;
                invalidCoordinates = tx < 0 || tx >= battlefield->battlefieldCols() || ty < 0 || ty >= battlefield->battlefieldRows();
                cout << "Explosion at (" << tx << ", " << ty << ")\n";
                if(!invalidCoordinates){
                   target = battlefield->getPlayer(tx, ty);
                   if (!target.empty()) { //check if theres any robots at the location
                
                } 
                }
                
            }
        }
    }
};




// class ReflectShotBot : public ThinkingRobot {
// public:
//     void actionThink(Battlefield* battlefield) override {
//         // Passive ability: no action needed unless attacked
//     }

//     void onHit(Robot* attacker, Battlefield* battlefield) {
//         if (attacker) {
// cout << "ReflectShotBot reflects the shot back to attacker!\n";
// battlefield->fireAt(attacker->getX(), attacker->getY());
//         }
//     }
// };



