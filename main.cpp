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
        friend class GenericRobot;
    public:
        // Get function
        int battlefieldCols() { return battlefieldCols_; }
        int battlefieldRows() { return battlefieldRows_; }
        int turns() { return totalTurns_; }
        int numOfRobots() { return numOfRobots_; }
        int currentTurn(){ return currentTurn_; }
        string getPlayer(int x, int y){return battlefield_[y][x];}
        vector <GenericRobot *> getAllRobots() const {return robots_;}
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
class ScoutBot : public SeeingRobot{
    private:
        int lookCount = 0;
        const int maxLooks = 3;

    public:
        ScoutBot(int x, int y, string name):Robot( x, y, name){}
        void actionLook(Battlefield* battlefield, int x, int y) override;
        void setRobotType(int type) override { robotType = SCOUT; }
        int getRobotType() const override { return SCOUT; }
};

class HideBot : public MovingRobot{
    private:
        int hideTurnsUsed = 0;
        const int maxHideTurns = 3;
        bool isHidden_ = false;

    public:
        HideBot(int x, int y, string name):Robot( x, y, name){}
        void actionMove(Battlefield* battlefield, int x, int y) override;
        bool isHidden() const { return isHidden_; }
        void setRobotType(int type) override { robotType = HIDE; }
        int getRobotType() const override { return HIDE; }
};

class JumpBot : public MovingRobot {
    private:
        int jumpsUsed = 0;
        const int maxJumps = 3;

    public:
        JumpBot(int x, int y, string name):Robot( x, y, name){}
        void actionMove(Battlefield* battlefield, int x, int y) override;
        void setRobotType(int type) override { robotType = JUMP; }
        int getRobotType() const override { return JUMP; }
};

class ThirtyShotBot : public ShootingRobot {
    public:
        ThirtyShotBot(int x, int y, string name):Robot( x, y, name){}
        void actionFire(Battlefield* battlefield, int x, int y) override { setShells(30); }
        void setRobotType(int type) override { robotType = THIRTYSHOT; }
        int getRobotType() const override { return THIRTYSHOT;}
};

class HealBot : public ShootingRobot {
    public:
        HealBot(int x, int y, string name):Robot( x, y, name){}
        void actionFire(Battlefield* battlefield, int x, int y) override;
        void setRobotType(int type) override { robotType = HEAL; }
        int getRobotType() const override { return HEAL; }
};

class BombBot : public ShootingRobot {
    private:
        int bombs = 1;
    public:
        BombBot(int x, int y, string name):Robot( x, y, name){}
        void actionFire(Battlefield* battlefield, int x, int y) override;
        void setRobotType(int type) override { robotType = BOMB; }
        int getRobotType() const override { return BOMB; }
};

class ReflectShotBot : public ShootingRobot {
    private:
        int reflect = 1;
        bool isReflect_ = false;
    public:
        ReflectShotBot(int x, int y, string name):Robot( x, y, name){}
        void actionFire(Battlefield* battlefield, int x, int y) override;
        bool isReflecting();
        void setRobotType(int type) override { robotType = REFLECTSHOT; }
        int getRobotType() const override { return REFLECTSHOT; }
 
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
        bool upgrade = false;
    public: 
        GenericRobot(string name, int x, int y) : Robot(x, y, name){
            robotId = robotIncrement; 
            robotIncrement++;
        }

        int getRobotID() const { return robotId; }
        void setRobotType(int type) override { robotType = type; } //setter
        int getRobotType() const override { return robotType; } //getter

/**********************************************************************
ActionFire()
**********************************************************************/
        virtual void actionFire(Battlefield* battlefield, int x, int y) override {
            
            //use get
            if(getShells() <= 0){
                cout << "Out of shells!" << endl;
                return;
            }

            //set
            setShells(getShells() - 1);
            
            int currentX = getRobotX();  // get current pos, center position like (0,0)
            int currentY = getRobotY(); 

            int lookX = currentX + x;
            int lookY = currentY + y;



            string targetRobotId = stoi(battlefield->battlefield_[lookY][lookX]);

            for (GenericRobot* robot : battlefield->robots_){
                        if (robot->getRobotID() == targetRobotId) {
                            targetRobotId = robot;
                            break;
                        }
            }

            HideBot* hiddenRobot = dynamic_cast<HideBot*>(targetRobot);
            if (hiddenRobot != nullptr && hiddenRobot->isHidden()){
                cout << "Shot missed. Robot is hidden." << endl;
                return;
            }

            ReflectShotBot* reflectBot = dynamic_cast<ReflectShotBot*>(targetRobot);
            if (reflectBot && reflectBot->isReflecting()) {
                cout << "Shot reflected." << endl;
                this->reduceLife(); // damage shooter

                if (!this->isAlive()){
                    cout << "Robot" << this->getRobotID() << " has been destroyed." << endl;
            }   
            }

            while (x != 0 || y!= 0){
                if (lookX >= 0 && lookX < battlefield->battlefieldRows() &&  //check if its in bound 
                lookY >= 0 && lookY < battlefield->battlefieldCols()) {
                    cout << "Out of bounds";
                    return;
                }

                
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
                        }
                        
                        incrementKills(); //increment kills for this robot
                        upgrade = true;
                        
                        if (getUpgradeCount() < MAX_UPGRADE){
                            int chosenUpgrade = getRobotType();
                            upgradeRobot(chosenUpgrade);
                        } else {
                            cout << "Max upgrade reached." << endl;
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
            else {
                int currentX = getRobotX();
                int currentY = getRobotY();

                int nextX = currentX + x;
                int nextY = currentY + y;

                if (nextX < 0 || nextX >= battlefield->battlefieldCols() || nextY < 0 || nextY >= battlefield->battlefieldRows()) {
                    cout << "Out of bounds." << endl; // check for bounds
                    return; 
                }

                // if (battlefield->battlefield_[nextY][nextX] != ""){ //checks if position is taken 
                //     cout << "place taken" << endl;
                //     return;
                // }

                battlefield->battlefield_[currentY][currentX] = "";

                battlefield->battlefield_[nextY][nextX] = to_string(robotId);

                // update positions
                setRobotX(nextX); 
                setRobotY(nextY);

                cout << "Robot " << getRobotID() << "move to position (" << nextX << ", " << nextY << ")" << endl;
            }
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

                
                    if((battlefield->battlefield_[lookY][lookX]) != ""){
                        int lookRobotId = stoi(battlefield->battlefield_[lookY][lookX]); // find the id of the robot currently in that position 
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
        virtual void actionThink(Battlefield* battlefield) override {
            actionRand(battlefield, x, y);

            if(robotUpgraded)
                robotUpgraded->actionThink(battlefield);
        }

/**********************************************************************
upgradeRobot()
**********************************************************************/
        void upgradeRobot(int upgradeType){
            if (upgradeCount >= MAX_UPGRADE) { 
                cout << "Max upgrade reached." ; 
                return; 
            }
            int x = getCurrentPlayer()->getRobotX();
            int y = getCurrentPlayer()->getRobotY();
            string name = getCurrentPlayer()->getRobotName();
            switch(upgradeType){
                case 1:
                    robotUpgraded = new ScoutBot(x, y, name);
                    break;
                case 2:
                    robotUpgraded = new TrackBot(x, y, name);
                    break;
                case 3:
                    robotUpgraded = new LongShotBot(x, y, name);
                    break;
                case 4:
                    robotUpgraded = new SemiAutoBot(x, y, name);
                    break;
                case 5:
                    robotUpgraded = new ThirtyShotBot(x, y, name);
                    break;
                case 6:
                    robotUpgraded = new JumpBot(x, y, name);
                    break;
                case 7:
                    robotUpgraded = new HideBot(x, y, name);
                    break;
                case 8:
                    robotUpgraded = new ReflectShotBot(x, y, name);
                    break;
                case 9:
                    robotUpgraded = new HealBot(x, y, name);
                    break;
                case 10:
                    robotUpgraded = new BombBot(x, y, name);
                    break;
                default: 
                    return;
            }

            upgradeCount++;
            upgrade = false;
        }

        bool toUpgrade() const {
            return upgradeCount < MAX_UPGRADE && upgrade; 
        }

        void ToGeneric(int upgradeType) {
            delete robotUpgraded;
            robotUpgraded = nullptr;
            robotType = GENERIC;
        }

        int getUpgradeCount() const {
            return upgradeCount; 
        }

/**********************************************************************
actionRand()
**********************************************************************/
        void actionRand(Battlefield* battlefield, int x, int y){

            random_device rd; 
            mt19937 gen(rd()); 
            uniform_int_distribution<> posDistr(0, 8);

            int directionMove = posDistr(gen);

            int currentX = getRobotX();
            int currentY = getRobotY();

            int moveX = 0, moveY = 0;

            switch(directionMove){
                case 0: moveX = -1; moveY = -1; break;  // topleft
                case 1: moveX =  0; moveY = -1; break;  // top
                case 2: moveX =  1; moveY = -1; break;  // topright
                case 3: moveX = -1; moveY =  0; break;  // left
                case 4: moveX =  1; moveY =  0; break;  // right
                case 5: moveX = -1; moveY =  1; break;  // bottomleft
                case 6: moveX =  0; moveY =  1; break;  // bottom
                case 7: moveX =  1; moveY =  1; break;  // bottomright
                case 8: moveX =  0; moveY =  0; break;  // stay in place
            }

            random_device rd2; 
            mt19937 gen(rd2()); 
            uniform_int_distribution<> actionDistr(0, 10); // define range
            
            actionThink(battlefield);
            actionLook(battlefield, 0, 0); 

            int randomInt = actionDistr(gen);

            if(randomInt % 2 == 0) { 
                actionMove(battlefield, moveX, moveY);
                actionFire(battlefield); 
            }

            else if(randomInt % 2 == 1){
            actionFire(battlefield);
            actionMove(battlefield, moveX, moveY);
            }
        }
};

int GenericRobot::robotIncrement = 1;

int main() {
    int option, x, y, choice, numOfKills;
    bool exitGame = false, invalidCoordinates;
    Battlefield* battlefield;
    GenericRobot* currentPlayer;
    battlefield->readFile("inputFile.txt");
    battlefield->placeRobots();

    do {
        currentPlayer = battlefield->getCurrentPlayer();

        battlefield->displayBattlefield(-5, -5);
        cout << "Player: " << currentPlayer()->getRobotName() << endl; 
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
                cout << "5. Fire a long shot (shoot up to 3 squares away from you)" << endl;
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
                    case 1: x = -1; y = 1; break;
                    case 2: x = 0; y = 1; break;
                    case 3: x = 1; y = 1; break;
                    case 4: x = -1; y = 0; break;
                    case 5: x = 0; y = 0; break;
                    case 6: x = 1; y = 0; break;
                    case 7: x = -1; y = -1; break;
                    case 8: x = 0; y = -1; break;
                    case 9: x = 1; y = -1; break;
                    default: x = 0; y = 0; break;
                }
                currentPlayer->actionLook(battlefield, x, y);
                break;
            case 3: // Fire (x,y)
                cout << "Choose where you want to shoot" << endl;
                cout << "1. UpLeft\n2. Up\n3. UpRight\n4. Left\n5. Right\n 6. DownLeft\n 7. Down\n 8. DownRight" << endl;
                cin  >> choice;
                switch(choice){
                    case 1: x = -1; y = 1; break;
                    case 2: x = 0; y = 1; break;
                    case 3: x = 1; y = 1; break;
                    case 4: x = -1; y = 0; break;
                    case 5: x = 1; y = 0; break;
                    case 6: x = -1; y = -1; break;
                    case 7: x = 0; y = -1; break;
                    case 8: x = 1; y = -1; break;
                    default: x = 0; y = 0; break;
                }
                numOfKills = currentPlayer->getKills();
                currentPlayer->actionFire(battlefield, x, y);
                if(numOfKills<currentPlayer->getKills() && currentPlayer->toUpgrade()){
                    cout << "Congratulations! You shoot a robot. Choose your upgrade: " << endl;
                    cout << "1. Scout Bot (see entire battlefield)\n2. Track Bot (plant tracker on another robot) \n3. ";
                    cout << "Long Shot Bot (shoot up to 3 squares away from you)\n4. Semi Auto Bot (each shot you fire shoots 3 consecutive shots)\n";
                    cout << "5. Thirty Shot Bot (get 30 shells but replaces old shells)\n6. Jump Bot (jump to anywhere on battlefield)\n";
                    cout << "7. Hide Bot (can't be seen or shot at by other robots)\n8. Reflect Shot Bot (if a robot shoots at you it will be reflected back at them)\n";
                    cout << "9. Heal Bot (gain 3 more lives)\n8. Bomb Bot (shoot all 8 neighbouring locations)\n";
                    cin >> choice;
                    switch(choice){
                        case 1: currentPlayer->upgradeRobot(SCOUT); break;
                        case 2: currentPlayer->upgradeRobot(TRACK); break;
                        case 3: currentPlayer->upgradeRobot(LONGSHOT); break;
                        case 4: currentPlayer->upgradeRobot(SEMIAUTO); break;
                        case 5: currentPlayer->upgradeRobot(THIRTYSHOT); break;
                        case 6: currentPlayer->upgradeRobot(JUMP); break;
                        case 7: currentPlayer->upgradeRobot(HIDE); break;
                        case 8: currentPlayer->upgradeRobot(REFLECTSHOT); break;
                        case 9: currentPlayer->upgradeRobot(HEAL); break;
                        case 10: currentPlayer->upgradeRobot(BOMB); break;
                    }
                }
                battlefield->nextTurn();
                break;
            case 4: // Move
                cout << "Choose where you want to move" << endl;
                cout << "1. UpLeft\n2. Up\n3. UpRight\n4. Left\n5. Right\n 6. DownLeft\n 7. Down\n 8. DownRight" << endl;
                cin  >> choice;
                switch(choice){
                    case 1: x = -1; y = 1; break;
                    case 2: x = 0; y = 1; break;
                    case 3: x = 1; y = 1; break;
                    case 4: x = -1; y = 0; break;
                    case 5: x = 1; y = 0; break;
                    case 6: x = -1; y = -1; break;
                    case 7: x = 0; y = -1; break;
                    case 8: x = 1; y = -1; break;
                    default: x = 0; y = 0; break;
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
                        numOfKills = currentPlayer->getKills();
                        currentPlayer->actionFire(battlefield, x, y);
                        if(numOfKills<currentPlayer->getKills() && currentPlayer->toUpgrade()){
                            cout << "Congratulations! You bomb a robot. Choose your upgrade: " << endl;
                            cout << "1. ScoutBot (see entire battlefield)\n2. TrackBot (plant tracker on another robot) \n3. ";
                            cout << "JumpBot (jump to anywhere on battlefield)\n4. Hide (can't be seen or shot at by other robots)\n" << endl;
                            cin >> choice;
                            switch(choice){
                                case 1: currentPlayer->upgradeRobot(SCOUT); break;
                                case 2: currentPlayer->upgradeRobot(TRACK); break;
                                case 3: currentPlayer->upgradeRobot(JUMP); break;
                                case 4: currentPlayer->upgradeRobot(HIDE); break;
                            }
                        }
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
                        numOfKills = currentPlayer->getKills();
                        currentPlayer->actionFire(battlefield, -5, -5);
                        if(numOfKills<currentPlayer->getKills() && currentPlayer->toUpgrade()){
                            cout << "Congratulations! You bomb a robot. Choose your upgrade: " << endl;
                            cout << "1. ScoutBot (see entire battlefield)\n2. TrackBot (plant tracker on another robot) \n3. ";
                            cout << "JumpBot (jump to anywhere on battlefield)\n4. Hide (can't be seen or shot at by other robots)\n" << endl;
                            cin >> choice;
                            switch(choice){
                                case 1: currentPlayer->upgradeRobot(SCOUT); break;
                                case 2: currentPlayer->upgradeRobot(TRACK); break;
                                case 3: currentPlayer->upgradeRobot(JUMP); break;
                                case 4: currentPlayer->upgradeRobot(HIDE); break;
                            }
                        }
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


/**********************************************************************
Upgraded Robot Functions
**********************************************************************/
void ScoutBot::actionLook(Battlefield* battlefield, int x, int y){
    if (lookCount < maxLooks) {
        battlefield->displayBattlefield(-10, -10);
        lookCount++;
    }
}

void HideBot::actionMove(Battlefield* battlefield, int x, int y){
    if (hideTurnsUsed < maxHideTurns) {
        isHidden_ = true;
        hideTurnsUsed++;
    }
}

void JumpBot::actionMove(Battlefield* battlefield, int x, int y){
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

void HealBot::actionFire(Battlefield* battlefield, int x, int y){
    addLife();
    addLife();
    addLife();
}

void BombBot::actionFire(Battlefield* battlefield, int x, int y){
    if(bombs){
        int cx = battlefield->getCurrentPlayer()->getRobotX();
        int cy = battlefield->getCurrentPlayer()->getRobotY();
        int tx, ty, targetRobotId;
        bool invalidCoordinates;
        string targetPosition;
        cout << "BombBot bombed surrounding squares!\n";

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue; // Skip self
                tx = cx + dx; 
                ty = cy + dy;
                invalidCoordinates = tx < 0 || tx >= battlefield->battlefieldCols() || ty < 0 || ty >= battlefield->battlefieldRows();
                cout << "Explosion at (" << tx << ", " << ty << ")\n";
                if(!invalidCoordinates){
                    targetPosition = battlefield->getPlayer(tx, ty);
                    if (!targetPosition.empty()) { //check if theres any robots at the location
                        targetRobotId = stoi(targetPosition);
                        GenericRobot* target = nullptr; 
                        
                        for (GenericRobot* robot : battlefield->getAllRobots()){
                            if (robot->getRobotID() == targetRobotId) {
                                target = robot;
                                break;
                            }
                        }

                        if (target) {
                            target->reduceLife();
                            if(!target->isAlive()){
                                cout << "Robot " << target->getRobotID() << "has been destroyed." << endl;
                            }
                            incrementKills(); //increment kills for this robot 
                        }
                    }                
                }
            }
        }
    }
    bombs--;
}

void ReflectShotBot::actionFire(Battlefield* battlefield, int x, int y){
    if(reflect>0)
        isReflect_ = true;
}

bool ReflectShotBot::isReflecting() {
    bool name = isReflect_;
    isReflect_ = false;
    reflect--;
    return name;
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






