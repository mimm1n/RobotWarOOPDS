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
// #include "Robot.h"
// #include "Battlefield.h"
// #include "ThinkingRobot.h"
// #include "SeeingRobot.h"
// #include "MovingRobot.h"
// #include "ShootingRobot.h"
using namespace std;

enum RobotType {GENERIC, SCOUT, TRACK, LONGSHOT, SEMIAUTO, THIRTYSHOT, JUMP, HIDE, REFLECTSHOT, HEAL, BOMB};

class Battlefield;
class GenericRobot;

class Robot{
    private:
        int robotX = -1, robotY = -1; // x and y coordinates of the robot (x,y)
        const int MAX_UPGRADES = 3;
        string robotName = ""; // The name of this robot        
    
    protected:
        int killCount = 0; // Number of robots this robot managed to destroy/kill
        int lives = 3; // Number of lives of this robot (initial is 3)
        int robotId = -1; // The ID of this robot
        int robotType = GENERIC; // This robot's type; Jump, Hide, etc.
        int upgradeCount = 0;

    public:
        Robot(int x, int y, string name); // Constructor
        virtual ~Robot(){} // Destructor
           // Set and get the x coordinate of this robot
        void setRobotID(int id); 
        int getRobotID() const;
        
        // Set and get the x coordinate of this robot
        void setRobotX(int x); 
        int getRobotX() const;

        // Set and get the y coordinate of this robot
        void setRobotY(int y);
        int getRobotY() const;

        // Get the name of this robot(fixed so can't set)
        string getRobotName() const;

        void addLife(); // Adds 1 life to the lives count 
        bool reduceLife(); // Reduces the lives count by 1
        int getLives() const; // Get this robot's lives count
        void setLives(int live);
        bool isAlive() const; // Checks if this robot's lives count is more than 0
        
        int getKills() const; // Get this robot's current kill count
        void setKills(int kills);
        void incrementKills(); // Adds 1 to the kill count

        int getUpgradeCount() const;
        bool canUpgrade() const;
        void addUpgrade(int currentUpgradeCount);

        virtual void actions(Battlefield* battlefield) = 0;

        // Set and get the robot's type
        virtual void setRobotType(int type) = 0;
        virtual int getRobotType() const = 0;
};

class SeeingRobot : virtual public Robot{
    public:
        virtual ~SeeingRobot(){}
        virtual void actionLook(Battlefield* battlefield, int x, int y) = 0;
};

class ShootingRobot : virtual public Robot{
    private:
        int shells = 10;
    public:
       virtual ~ShootingRobot(){}
        ShootingRobot(int x, int y, string name):Robot(x, y, name){}
        void setShells(int num) { shells = num; }
        int getShells() const { return shells; }
        virtual void actionFire(Battlefield* battlefield, int x, int y) = 0;
};

class ThinkingRobot : virtual public Robot{
    public:
        virtual ~ThinkingRobot(){}
        virtual void actionThink(Battlefield* battlefield) = 0;
};

class MovingRobot : virtual public Robot{
    public:
        virtual ~MovingRobot(){}
        MovingRobot(int x, int y, string name):Robot(x, y, name){}
        virtual void actionMove(Battlefield* battlefield, int x, int y) = 0;
};

class Battlefield {
    private:
        int battlefieldCols_ = -1; // variable to assign number of columns
        int battlefieldRows_ = -1; // variable to assign number of rows

        int totalTurns_ = -1; // variable to assign total turns
        int currentTurn_ = 1; 
        int currentPlayer = 0;
    

        int numOfRobots_ = -1; // variable to assign number of robots

        vector<Robot *> robots_; 
        vector<Robot *> upgradedRobots_[11];
        queue<Robot *> destroyedRobots_;
        queue<Robot *> waitingRobots_;  
        vector < vector <string> > battlefield_;
        friend class GenericRobot;
        
    public:
        // Get function
        int battlefieldCols();
        int battlefieldRows();
        int turns();
        int numOfRobots();
        int currentTurn();
        string getPlayer(int x, int y);
        vector <Robot *> getAllRobots() const;
        Robot* getCurrentPlayer() const;
        void robotUpgrade(Robot* upgradeRobot_);
        
        
        void readFile(string filename);
        void placeRobots();
        void displayBattlefield(int x, int y, vector<int> targets = {}) const;
        void respawnRobot(int x);
        void nextTurn();
        RobotType findTargetRobot(GenericRobot* target);
};

class GenericRobot : public ShootingRobot, public MovingRobot, public SeeingRobot, public ThinkingRobot {
private:

    static int robotIncrement;
    int robotId;
    int upgradeCount = 0;
    const int MAX_UPGRADE = 3;
    Robot* robotUpgraded = nullptr;
    bool upgrade = false;

public:
    GenericRobot(string name, int x, int y):Robot(x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){
    robotId = robotIncrement;
    robotIncrement++;
}

    //int getRobotID() const;
    void setRobotType(int type) override;
    int getRobotType() const override;

    virtual void actionFire(Battlefield* battlefield, int x, int y) override;
    virtual void actionMove(Battlefield* battlefield, int x, int y) override;
    virtual void actionLook(Battlefield* battlefield, int x, int y) override;
    virtual void actionThink(Battlefield* battlefield) override;
    void actionRand(Battlefield* battlefield);
    virtual void actions(Battlefield* battlefield) override;

    // void upgradeRobot(Battlefield* battlefield, int upgradeType);
    // bool toUpgrade() const;
    // void ToGeneric(int upgradeType);
    int getUpgradeCount() const;
};

class HideBot : public MovingRobot,public ShootingRobot, public SeeingRobot, public ThinkingRobot{
    private:
        int hideTurnsUsed = 0;
        const int MAX_HIDE_TURNS = 3;
        bool isHidden_ = false;

    public:
        HideBot(int x, int y, string name):Robot(x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){}
        void actionFire(Battlefield* battlefield, int x, int y) override;
        void actionMove(Battlefield* battlefield, int x, int y) override;
        void actionLook(Battlefield* battlefield, int x, int y) override;
        void actionThink(Battlefield* battlefield) override;
        void actionRand(Battlefield* battlefield);
        virtual void actions(Battlefield* battlefield) override;
        bool isHidden();
        int hidesLeft() const;
        void setRobotType(int type) override { robotType = HIDE; }
        int getRobotType() const override { return HIDE; }
};

class JumpBot : public MovingRobot,public ShootingRobot, public SeeingRobot, public ThinkingRobot {
    private:
        int jumpsUsed = 0;
        const int MAX_JUMPS = 3;

    public:
        JumpBot(int x, int y, string name):Robot(x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){}
        void actionMove(Battlefield* battlefield, int x, int y) override;
        void actionFire(Battlefield* battlefield, int x, int y) override;
        void actionLook(Battlefield* battlefield, int x, int y) override;
        void actionThink(Battlefield* battlefield) override;
        void actionRand(Battlefield* battlefield);
        virtual void actions(Battlefield* battlefield) override;
        void setRobotType(int type) override { robotType = JUMP; }
        int getRobotType() const override { return JUMP; }
};


class LongShotBot : public ShootingRobot , public MovingRobot, public SeeingRobot, public ThinkingRobot{
    public:
        LongShotBot(int x, int y, string name):Robot( x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){}
        void actionFire(Battlefield* battlefield, int x, int y) override;
        void actionMove(Battlefield* battlefield, int x, int y) override;
        void actionLook(Battlefield* battlefield, int x, int y) override;
        void actionThink(Battlefield* battlefield) override;
        void actionRand(Battlefield* battlefield);
        virtual void actions(Battlefield* battlefield) override;
        void setRobotType(int type) override { robotType = LONGSHOT; }
        int getRobotType() const override { return LONGSHOT;}
};

class SemiAutoBot : public ShootingRobot , public MovingRobot, public SeeingRobot, public ThinkingRobot {
    private:
        int shotsFired = 0;
        const int MAX_SHOTS_FIRED = 3;
    public:
        SemiAutoBot(int x, int y, string name):Robot( x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){}
        void actionFire(Battlefield* battlefield, int x, int y) override;
        void actionMove(Battlefield* battlefield, int x, int y) override;
        void actionLook(Battlefield* battlefield, int x, int y) override;
        void actionThink(Battlefield* battlefield) override;
        void actionRand(Battlefield* battlefield);
        virtual void actions(Battlefield* battlefield) override;
        void setRobotType(int type) override { robotType = SEMIAUTO; }
        int getRobotType() const override { return SEMIAUTO; }
};

class ThirtyShotBot : public ShootingRobot , public MovingRobot, public SeeingRobot, public ThinkingRobot {
    public:
        ThirtyShotBot(int x, int y, string name):Robot( x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){}
        void actionFire(Battlefield* battlefield, int x, int y) override;
        void actionMove(Battlefield* battlefield, int x, int y) override;
        void actionLook(Battlefield* battlefield, int x, int y) override;
        void actionThink(Battlefield* battlefield) override;
        void actionRand(Battlefield* battlefield);
        virtual void actions(Battlefield* battlefield) override;
        void setRobotType(int type) override { robotType = THIRTYSHOT; }
        int getRobotType() const override { return THIRTYSHOT;}
};


class HealBot : public ShootingRobot, public MovingRobot, public SeeingRobot, public ThinkingRobot {
    public:
        HealBot(int x, int y, string name):Robot( x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){}
        void actionFire(Battlefield* battlefield, int x, int y) override;
        void actionMove(Battlefield* battlefield, int x, int y) override;
        void actionLook(Battlefield* battlefield, int x, int y) override;
        void actionThink(Battlefield* battlefield) override;
        void actionRand (Battlefield* battlefield);
        virtual void actions(Battlefield* battlefield) override;
        void setRobotType(int type) override { robotType = HEAL; }
        int getRobotType() const override { return HEAL; }
};

class BombBot : public ShootingRobot, public MovingRobot, public SeeingRobot, public ThinkingRobot {
    private:
        int bombs = 1;
    public:
        BombBot(int x, int y, string name):Robot(x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){}
        void actionFire(Battlefield* battlefield, int x, int y) override;
        void actionMove(Battlefield* battlefield, int x, int y) override;
        void actionLook(Battlefield* battlefield, int x, int y) override;
        void actionThink(Battlefield* battlefield) override;
        void actionRand(Battlefield* battlefield);
        virtual void actions(Battlefield* battlefield) override;
        void setRobotType(int type) override { robotType = BOMB; }
        int getRobotType() const override { return BOMB; }
};

class ReflectShotBot : public ShootingRobot , public MovingRobot, public SeeingRobot, public ThinkingRobot{
    private:
        int reflect = 1;
        bool isReflect_ = false;
    public:
        ReflectShotBot(int x, int y, string name):Robot( x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){}
        void actionFire(Battlefield* battlefield, int x, int y) override;
        void actionMove(Battlefield* battlefield, int x, int y) override;
        void actionLook(Battlefield* battlefield, int x, int y) override;
        void actionThink(Battlefield* battlefield) override;
        virtual void actions(Battlefield* battlefield) override;
        bool isReflecting();
        void setRobotType(int type) override { robotType = REFLECTSHOT; }
        int getRobotType() const override { return REFLECTSHOT; }
 
};


class ScoutBot : public SeeingRobot , public MovingRobot, public ShootingRobot, public ThinkingRobot{
    private:
        int lookCount = 0;
        const int MAX_LOOKS = 3;

    public:
        ScoutBot(int x, int y, string name):Robot( x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){}
        void actionLook(Battlefield* battlefield, int x, int y) override;
        void actionFire(Battlefield* battlefield, int x, int y) override;
        void actionMove(Battlefield* battlefield, int x, int y) override;
        void actionThink(Battlefield* battlefield) override;
        void actionRand(Battlefield* battlefield);
        virtual void actions(Battlefield* battlefield) override;
        void setRobotType(int type) override { robotType = SCOUT; }
        int getRobotType() const override { return SCOUT; }
};

class TrackBot : public SeeingRobot  , public MovingRobot, public ShootingRobot, public ThinkingRobot {
    private:
        int trackersUsed = 0;
        const int MAX_TRACKERS = 3;
        vector<int> targets {};

    public:
        TrackBot(int x, int y, string name):Robot(x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){}
        void actionLook(Battlefield* battlefield, int x, int y) override;
        void actionFire(Battlefield* battlefield, int x, int y) override;
        void actionMove(Battlefield* battlefield, int x, int y) override;
        void actionThink(Battlefield* battlefield) override;
        void actionRand(Battlefield* Battlefield);
        virtual void actions(Battlefield* battlefield) override;
        vector<int> getTrackedTargets() { return targets; }
        void setRobotType(int type) override { robotType = TRACK; }
        int getRobotType() const override { return TRACK; }
};


int GenericRobot::robotIncrement = 0;

int main() {
    ofstream outFile;
    Battlefield* battlefield = new Battlefield();
    battlefield->readFile("inputFile.txt");
    outFile.open("outputFile.txt");
    battlefield->placeRobots();
    Robot* currentPlayer = new GenericRobot("test", 0,0);
    Robot* upgradedRobot = new GenericRobot("test", 0, 0);
    int move, x, y, kills, upgrade, currentPlayerType;
    string name;
    
    do {
        currentPlayer = battlefield->getCurrentPlayer();
        battlefield->displayBattlefield(-5,-5);
        //outFile << battlefield->displayBattlefield(-5,-5);
        cout << setw(22) << "Action Log" << endl;
        cout << "----------------------------------" << endl;
        outFile << setw(22) << "Action Log" << endl;
        outFile << "----------------------------------" << endl;
        currentPlayer->actions(battlefield);
        // random_device rd;
        // mt19937 gen(rd()), gen2(rd()), gen3(rd()), gen4(rd());

        // uniform_int_distribution<> moveDistr(1, 4);
        // int move = moveDistr(gen);

        // uniform_int_distribution<> dirDistr(-1, 1);
        // int x = dirDistr(gen2);
        // int y = dirDistr(gen3);
        
        // switch(move){
        //     case 1: // Think
        //         currentPlayer->actionThink(battlefield);
        //         cout << currentPlayer->getRobotName() << " is thinking" << endl;
        //         outFile << currentPlayer->getRobotName() << " is thinking" << endl;
        //         break;
        //     case 2: // Look
        //         currentPlayer->actionLook(battlefield, x, y);
        //         cout << currentPlayer->getRobotName() << " is looking" << endl;
        //         outFile << currentPlayer->getRobotName() << " is looking" << endl;
        //         break;
        //     case 3: // Fire
        //         kills = currentPlayer->getKills();
        //         currentPlayer->actionFire(battlefield, x, y);
        //         cout << currentPlayer->getRobotName() << " is shooting..." << endl;
        //         outFile << currentPlayer->getRobotName() << " is shooting..." << endl;

        //         if (kills < currentPlayer->getKills()){ // upgrade 
        //             cout << currentPlayer->getRobotName() << " killed "; 
        //             cout << battlefield->getPlayer(currentPlayer->getRobotX()+x,currentPlayer->getRobotY()+y) << "!" << endl;
        //             outFile << currentPlayer->getRobotName() << " killed "; 
        //             outFile << battlefield->getPlayer(currentPlayer->getRobotX()+x,currentPlayer->getRobotY()+y) << "!" << endl;

        //             if (!currentPlayer->canUpgrade()) continue;

        //             currentPlayerType = currentPlayer->getRobotType();
        //             x = currentPlayer->getRobotX();
        //             y = currentPlayer->getRobotY();
        //             name = currentPlayer->getRobotName();

        //             if (currentPlayerType == GENERIC){
        //                 uniform_int_distribution<> upgradeDistr(1, 10);
        //                 upgrade = upgradeDistr(gen4);
        //                 switch(upgrade){
        //                     case 1: upgradedRobot = new ScoutBot(x, y, name); break;
        //                     case 2: upgradedRobot = new TrackBot(x, y, name); break;
        //                     case 3: upgradedRobot = new LongShotBot(x, y, name); break;
        //                     case 4: upgradedRobot = new SemiAutoBot(x, y, name); break;
        //                     case 5: upgradedRobot = new ThirtyShotBot(x, y, name); break;
        //                     case 6: upgradedRobot = new JumpBot(x, y, name); break;
        //                     case 7: upgradedRobot = new HideBot(x, y, name); break;
        //                     case 8: upgradedRobot = new ReflectShotBot(x, y, name); break;
        //                     case 9: upgradedRobot = new HealBot(x, y, name); break;
        //                     case 10: upgradedRobot = new BombBot(x, y, name); break;
        //                 }
        //             } else if (currentPlayerType == SCOUT || currentPlayerType == TRACK){
        //                 uniform_int_distribution<> upgradeDistr(1, 8);
        //                 upgrade = upgradeDistr(gen4);
        //                 switch(upgrade){
        //                     case 1: upgradedRobot = new LongShotBot(x, y, name); break;
        //                     case 2: upgradedRobot = new SemiAutoBot(x, y, name); break;
        //                     case 3: upgradedRobot = new ThirtyShotBot(x, y, name); break;
        //                     case 4: upgradedRobot = new JumpBot(x, y, name); break;
        //                     case 5: upgradedRobot = new HideBot(x, y, name); break;
        //                     case 6: upgradedRobot = new ReflectShotBot(x, y, name); break;
        //                     case 7: upgradedRobot = new HealBot(x, y, name); break;
        //                     case 8: upgradedRobot = new BombBot(x, y, name); break;
        //                 }
        //             } else if (currentPlayerType == HIDE || currentPlayerType == JUMP){
        //                 uniform_int_distribution<> upgradeDistr(1, 8);
        //                 upgrade = upgradeDistr(gen4);
        //                 switch(upgrade){
        //                     case 1: upgradedRobot = new LongShotBot(x, y, name); break;
        //                     case 2: upgradedRobot = new SemiAutoBot(x, y, name); break;
        //                     case 3: upgradedRobot = new ThirtyShotBot(x, y, name); break;
        //                     case 4: upgradedRobot = new ScoutBot(x, y, name); break;
        //                     case 5: upgradedRobot = new TrackBot(x, y, name); break;
        //                     case 6: upgradedRobot = new ReflectShotBot(x, y, name); break;
        //                     case 7: upgradedRobot = new HealBot(x, y, name); break;
        //                     case 8: upgradedRobot = new BombBot(x, y, name); break;
        //                 }
        //             } else {
        //                 uniform_int_distribution<> upgradeDistr(1, 4);
        //                 upgrade = upgradeDistr(gen4);
        //                 switch(upgrade){
        //                     case 1: upgradedRobot = new ScoutBot(x, y, name); break;
        //                     case 2: upgradedRobot = new TrackBot(x, y, name); break;
        //                     case 3: upgradedRobot = new JumpBot(x, y, name); break;
        //                     case 4: upgradedRobot = new HideBot(x, y, name); break;
        //                 }
        //             }
        //             upgradedRobot->addUpgrade(currentPlayer->getUpgradeCount());
        //             upgradedRobot->setLives(currentPlayer->getLives());
        //             upgradedRobot->setKills(currentPlayer->getKills());
        //             upgradedRobot->setShells(currentPlayer->getShells());
        //             battlefield->robotUpgrade(upgradedRobot);

        //             cout << currentPlayer->getRobotName() << " upgraded!" << endl;
        //             outFile << currentPlayer->getRobotName() << " upgraded!" << endl;
        //             delete upgradedRobot;
        //             upgradedRobot = nullptr; 
        //         }
        //         break;
        //     case 4: // Move
        //         currentPlayer->actionMove(battlefield, x, y);
        //         break;
        // }
        battlefield->nextTurn();
        delete currentPlayer;
        currentPlayer = nullptr;
    } while(!battlefield->getCurrentPlayer() && (battlefield->currentTurn() < battlefield->turns()));
    
    outFile.close();
    return 0;
}

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
void Robot::setRobotID(int id){
    robotId = id;
}

int Robot::getRobotID() const{
    return robotId;
}/**********************************************************************
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
 * getUpgradeCount
 * task: gets the number of upgrades the robot has went through
 * @return upgradeCount - number of upgrades so far
 *********************************************************************/
int Robot::getUpgradeCount() const{
    return upgradeCount;
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
vector <Robot *> Battlefield::getAllRobots() const {
    return robots_;
}


/**********************************************************************
 * getCurrentPlayer
 * task: 
 * @return 
 *********************************************************************/
Robot* Battlefield::getCurrentPlayer() const {
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
            Robot* current = waitingRobots_.front();
            if (current->getRobotID() != died->getRobotID()){
                  waitingRobots_.pop();
                  waitingRobots_.push(current);
            }else
            {
            waitingRobots_.pop();}

        }

    if(!died->isAlive()){
        destroyedRobots_.push(died);
        return;
    }else{
        int newX = rand() % (battlefieldRows_);
        int newY = rand() % (battlefieldCols_);
        string name = died->getRobotName();

        GenericRobot* respawn = new GenericRobot(name, newX, newY);
        respawn->addUpgrade(died->getUpgradeCount()-1);
        respawn->setLives(died->getLives());
        respawn->setKills(died->getKills());
        // respawn->setShells(died->getShells());

        battlefield_[died->getRobotY()][died->getRobotX()] = ""; //clear the field
        battlefield_[newY][newX] = to_string(respawn->getRobotID());
        waitingRobots_.push(respawn);
        }
    
}

/**********************************************************************
 * nextTurn
 * task: 
 *********************************************************************/
void Battlefield::nextTurn(){
    currentTurn_++;
    Robot* front = waitingRobots_.front();
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

            Robot* current = waitingRobots_.front();
            if (current->getRobotID() != upgradeRobot_->getRobotID()){
                  waitingRobots_.pop();
                  waitingRobots_.push(current);
            }else
            {
            waitingRobots_.pop();
            waitingRobots_.push(upgradeRobot_);
            }
        }
        

   for (auto& robot : robots_) {

    if (robot->getRobotID() == upgradeRobot_->getRobotID()) {
        robot = upgradeRobot_;  // Replace pointer
        break;
    }
}

 }


// int GenericRobot::getRobotID() const { return robotId; }
void GenericRobot::setRobotType(int type) { robotType = type; }
int GenericRobot::getRobotType() const { return robotType; }

 void GenericRobot::actions(Battlefield* battlefield){
    actionRand(battlefield);
}

 void HideBot::actions(Battlefield* battlefield){
    actionRand(battlefield);
}

 void JumpBot::actions(Battlefield* battlefield){
    actionRand(battlefield);
}

 void LongShotBot::actions(Battlefield* battlefield){
    actionRand(battlefield);
}

 void SemiAutoBot::actions(Battlefield* battlefield){
    actionRand(battlefield);
}

 void ThirtyShotBot::actions(Battlefield* battlefield){
    actionRand(battlefield);
}

 void HealBot::actions(Battlefield* battlefield){
    actionRand(battlefield);
}

 void BombBot::actions(Battlefield* battlefield){
    actionRand(battlefield);
}

 void ReflectShotBot::actions(Battlefield* battlefield){
    // actionRand(battlefield);
}

 void ScoutBot::actions(Battlefield* battlefield){
    actionRand(battlefield);
}

 void TrackBot::actions(Battlefield* battlefield){
    actionRand(battlefield);
}

 void GenericRobot::actionFire(Battlefield* battlefield, int x, int y) {
    // if (getShells() <= 0) {
    //     cout << "Out of shells!" << endl;
    //     return;
    // }
    // setShells(getShells() - 1);

    // if (x == 0 && y == 0) {
    //     cout << "Cannot shoot at own position." << endl;
    //     return;
    // }

    // int currentX = getRobotX();
    // int currentY = getRobotY();
    // int lookX = currentX + x;
    // int lookY = currentY + y;

    // if (lookX < 0 || lookX >= battlefield->battlefieldCols() ||
    //     lookY < 0 || lookY >= battlefield->battlefieldRows()) {
    //     cout << "Out of bounds" << endl;
    //     return;
    // }

    // string playerStr = battlefield->getPlayer(lookX, lookY);
    // if (playerStr.empty() || !isdigit(playerStr[0])) {
    //     cout << "Missed!" << endl;  //covers returns like an empty string or any invalid 
    //     return;
    // }

    // int targetRobotId = stoi(playerStr); //reuse 
    // GenericRobot* targetRobot = nullptr;

    // for (Robot* robot : battlefield->robots_) {
    //     if (robot->getRobotID() == targetRobotId) {
    //         targetRobot = robot;
    //         break;
    //     }
    // }

    // if (!targetRobot) {
    //     cout << "Missed!" << endl;
    //     return;
    // }

    // if (HideBot* hidden = dynamic_cast<HideBot*>(targetRobot)) {
    //     if (hidden->isHidden()) {
    //         cout << "Shot missed. Robot is hidden." << endl;
    //         return;
    //     }
    // }

    // if (ReflectShotBot* reflect = dynamic_cast<ReflectShotBot*>(targetRobot)) {
    //     if (reflect->isReflecting()) {
    //         cout << "Shot reflected." << endl;
    //         reduceLife();
    //         if (!isAlive()) {
    //             cout << "Robot " << getRobotID() << " has been destroyed." << endl;
    //         }
    //         return;
    //     }
    // }

    // 70% chance to hit
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(1, 100);
    int hitChance = distr(gen);

    // if (hitChance <= 70) {
    //     bool saveLife = targetRobot->isAlive();
    //     targetRobot->reduceLife();

        // Special logic for HideBot (optional, add if needed)
        if (HideBot* hideBot = dynamic_cast<HideBot*>(targetRobot)) {
            if (hideBot->hidesLeft() > 0) {
                // Additional behavior if needed when hidesLeft > 0
            }
        }

    //     if (saveLife && !targetRobot->isAlive()) {
    //         cout << "Robot " << targetRobot->getRobotID() << " has been destroyed." << endl;
    //     }

    //     incrementKills();
    // } else {
    //     cout << "Shot missed!" << endl;
    // }
}

 void GenericRobot::actionMove(Battlefield* battlefield, int x, int y) {
    int currentX = getRobotX();
    int currentY = getRobotY();

    int nextX = currentX + x;
    int nextY = currentY + y;

    if (nextX < 0 || nextX >= battlefield->battlefieldCols() || nextY < 0 || nextY >= battlefield->battlefieldRows()) {
        cout << "Out of bounds." << endl;
        return;
    }

    battlefield->battlefield_[currentY][currentX] = "";
    battlefield->battlefield_[nextY][nextX] = to_string(robotId);

    setRobotX(nextX);
    setRobotY(nextY);

    cout << "Robot " << getRobotID() << " move to position (" << nextX << ", " << nextY << ")" << endl;
}

 void GenericRobot::actionLook(Battlefield* battlefield, int x, int y) {
    int currentX = getRobotX();
    int currentY = getRobotY();

    for (int dx = -1; dx <= 1; ++dx) {  //iterate 3x3 grid
        for (int dy = -1; dy <= 1; ++dy) {
            int lookX = currentX + dx;
            int lookY = currentY + dy;

            if (lookX >= 0 && lookX < battlefield->battlefieldCols() &&
                    lookY >= 0 && lookY < battlefield->battlefieldRows() &&
                !battlefield->battlefield_[lookY][lookX].empty()) {  //check if in bounds 
                
                int lookRobotId = stoi(battlefield->battlefield_[lookY][lookX]);
                GenericRobot* robotLooked = nullptr;
                
                //find robot corresponing to that ID 
                for (Robot* robot : battlefield->robots_) {
                    if (robot->getRobotID() == lookRobotId) {
                        robotLooked = robot;
                        break;
                    }
                }

                if (robotLooked) {
                cout << "Robot " << robotLooked->getRobotID() << " is at position (" 
                    << lookX << ", " << lookY << ")." << endl;
                    
            }
        }
    }
}
}

void GenericRobot::actionThink(Battlefield* battlefield) {
    actionRand(battlefield);
}

// void GenericRobot::upgradeRobot(Battlefield* battlefield, int upgradeType) {
//     if (upgradeCount >= MAX_UPGRADE) {
//         cout << "Max upgrade reached.";
//         return;
//     }

//     Robot* current = battlefield->getCurrentPlayer();
//     if (!current) return;  //prevents dereferencing of nullptr

//     int x = current->getRobotX();
//     int y = current->getRobotY();
//     string name = current->getRobotName();

//     if (robotUpgraded) {
//         delete robotUpgraded;
//         robotUpgraded = nullptr;
//     } //clear memory before new upgrade

//     switch (upgradeType) {
//         case 1: robotUpgraded = new ScoutBot(x, y, name); break;
//         case 5: robotUpgraded = new ThirtyShotBot(x, y, name); break;
//         case 6: robotUpgraded = new JumpBot(x, y, name); break;
//         case 7: robotUpgraded = new HideBot(x, y, name); break;
//         case 8: robotUpgraded = new ReflectShotBot(x, y, name); break;
//         case 9: robotUpgraded = new HealBot(x, y, name); break;
//         case 10: robotUpgraded = new BombBot(x, y, name); break;
//         default: return;
//     }

    
//     upgradeCount++;
//     upgrade = false;
// }

void GenericRobot::actionRand(Battlefield* battlefield) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> posDistr(0, 8);

    int directionMove = posDistr(gen);

    int currentX = getRobotX();
    int currentY = getRobotY();

    int moveX = 0, moveY = 0;

    switch (directionMove) {
        case 0: moveX = -1; moveY = -1; break;
        case 1: moveX =  0; moveY = -1; break;
        case 2: moveX =  1; moveY = -1; break;
        case 3: moveX = -1; moveY =  0; break;
        case 4: moveX =  1; moveY =  0; break;
        case 5: moveX = -1; moveY =  1; break;
        case 6: moveX =  0; moveY =  1; break;
        case 7: moveX =  1; moveY =  1; break;
        case 8: moveX =  0; moveY =  0; break;
    }

    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> actionDistr(0, 10);

    actionThink(battlefield);
    actionLook(battlefield, 0, 0);

    int randomInt = actionDistr(gen2);

    if (randomInt % 2 == 0) {
        actionMove(battlefield, moveX, moveY);
        actionFire(battlefield, moveX, moveY);
    } else {
        actionFire(battlefield, moveX, moveY);
        actionMove(battlefield, moveX, moveY);
    }
}

void HideBot::actionFire(Battlefield* battlefield, int x, int y) {
    if (getShells() <= 0) {
        cout << "Out of shells!" << endl;
        return;
    }
    setShells(getShells() - 1);

    if (x == 0 && y == 0) {
        cout << "Cannot shoot at own position." << endl;
        return;
    }

    int currentX = getRobotX();
    int currentY = getRobotY();
    int lookX = currentX + x;
    int lookY = currentY + y;

    if (lookX < 0 || lookX >= battlefield->battlefieldCols() ||
        lookY < 0 || lookY >= battlefield->battlefieldRows()) {
        cout << "Out of bounds" << endl;
        return;
    }

    string playerStr = battlefield->getPlayer(lookX, lookY);
    if (playerStr.empty() || !isdigit(playerStr[0])) {
        cout << "Missed!" << endl;
        return;
    }

    int targetRobotId = stoi(playerStr);
    Robot* targetRobot = nullptr;

    for (Robot* robot : battlefield->robots_) {
        if (robot->getRobotID() == targetRobotId) {
            targetRobot = robot;
            break;
        }
    }

    if (!targetRobot) {
        cout << "Missed!" << endl;
        return;
    }

    // Handle HideBot behavior
    if (HideBot* hidden = dynamic_cast<HideBot*>(targetRobot)) {
        if (hidden->isHidden()) {
            cout << "Shot missed. Robot is hidden." << endl;
            return;
        }
    }

    // Handle ReflectShotBot behavior
    if (ReflectShotBot* reflect = dynamic_cast<ReflectShotBot*>(targetRobot)) {
        if (reflect->isReflecting()) {
            cout << "Shot reflected." << endl;
            reduceLife();
            if (!isAlive()) {
                cout << "Robot " << getRobotID() << " has been destroyed." << endl;
            }
            return;
        }
    }

    // 70% chance to hit
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(1, 100);
    int hitChance = distr(gen);

    if (hitChance <= 70) {
        bool wasAlive = targetRobot->isAlive();
        targetRobot->reduceLife();

        // Special logic for HideBot (optional, add if needed)
        if (HideBot* hideBot = dynamic_cast<HideBot*>(targetRobot)) {
            if (hideBot->hidesLeft() > 0) {
                // Additional behavior if needed when hidesLeft > 0
            }
        }

        if (wasAlive && !targetRobot->isAlive()) {
            cout << "Robot " << targetRobot->getRobotID() << " has been destroyed." << endl;
        }

        incrementKills();
    } else {
        cout << "Shot missed!" << endl;
    }
}

void HideBot::actionMove(Battlefield* battlefield, int x, int y){
    if (hideTurnsUsed < MAX_HIDE_TURNS) {
        isHidden_ = true;
        hideTurnsUsed++;
    }
}

void HideBot::actionLook(Battlefield* battlefield, int x, int y){
    int currentX = getRobotX();
    int currentY = getRobotY();

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int lookX = currentX + dx;
            int lookY = currentY + dy;

            if (lookX >= 0 && lookX < battlefield->battlefieldCols() &&
                    lookY >= 0 && lookY < battlefield->battlefieldRows() &&
                !battlefield->battlefield_[lookY][lookX].empty()) {
                int lookRobotId = stoi(battlefield->battlefield_[lookY][lookX]);
                GenericRobot* robotLooked = nullptr;
                for (GenericRobot* robot : battlefield->robots_) {
                    if (robot->getRobotID() == lookRobotId) {
                        robotLooked = robot;
                        break;
                    }
                }
            }
        }
    }
}


void HideBot::actionThink(Battlefield* battlefield){
    actionRand(battlefield);
}

void HideBot::actionRand(Battlefield* battlefield){

        random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> posDistr(0, 8);

    int directionMove = posDistr(gen);

    int currentX = getRobotX();
    int currentY = getRobotY();

    int moveX = 0, moveY = 0;

    switch (directionMove) {
        case 0: moveX = -1; moveY = -1; break;
        case 1: moveX =  0; moveY = -1; break;
        case 2: moveX =  1; moveY = -1; break;
        case 3: moveX = -1; moveY =  0; break;
        case 4: moveX =  1; moveY =  0; break;
        case 5: moveX = -1; moveY =  1; break;
        case 6: moveX =  0; moveY =  1; break;
        case 7: moveX =  1; moveY =  1; break;
        case 8: moveX =  0; moveY =  0; break;
    }

    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> actionDistr(0, 10);

    actionThink(battlefield);
    actionLook(battlefield, 0, 0);

    int randomInt = actionDistr(gen2);

    if (randomInt % 2 == 0) {
        actionMove(battlefield, moveX, moveY);
        actionFire(battlefield, moveX, moveY);
    } else {
        actionFire(battlefield, moveX, moveY);
        actionMove(battlefield, moveX, moveY);
    }
}

bool HideBot::isHidden(){
    if (hideTurnsUsed >= MAX_HIDE_TURNS)
        isHidden_ = false;
    return isHidden_;
}

int HideBot::hidesLeft() const{ 
return MAX_HIDE_TURNS - hideTurnsUsed - 1;
}

void JumpBot::actionMove(Battlefield* battlefield, int x, int y){
    if (jumpsUsed < MAX_JUMPS) {
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

void JumpBot::actionThink(Battlefield* battlefield){
    actionRand(battlefield);
}

void JumpBot::actionRand(Battlefield* battlefield){

        random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> posDistr(0, 8);

    int directionMove = posDistr(gen);

    int currentX = getRobotX();
    int currentY = getRobotY();

    int moveX = 0, moveY = 0;

    switch (directionMove) {
        case 0: moveX = -1; moveY = -1; break;
        case 1: moveX =  0; moveY = -1; break;
        case 2: moveX =  1; moveY = -1; break;
        case 3: moveX = -1; moveY =  0; break;
        case 4: moveX =  1; moveY =  0; break;
        case 5: moveX = -1; moveY =  1; break;
        case 6: moveX =  0; moveY =  1; break;
        case 7: moveX =  1; moveY =  1; break;
        case 8: moveX =  0; moveY =  0; break;
    }

    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> actionDistr(0, 10);

    actionThink(battlefield);
    actionLook(battlefield, 0, 0);

    int randomInt = actionDistr(gen2);

    if (randomInt % 2 == 0) {
        actionMove(battlefield, moveX, moveY);
        actionFire(battlefield, moveX, moveY);
    } else {
        actionFire(battlefield, moveX, moveY);
        actionMove(battlefield, moveX, moveY);
    }
}


void LongShotBot::actionFire(Battlefield* battlefield, int x, int y){
    if (x < (getRobotX() - 4 ) || x > (getRobotX() + 4 ) || y < (getRobotY() - 4 ) || y > (getRobotY() + 4))
        return;
    
    if (getShells() <= 0) {
        cout << "No more shots left! " << getRobotName() << " has fired its maximum shells.\n";
        return;
    }

    if (battlefield->getPlayer(x, y) != ""){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distr(1, 100); // 1 to 100 randomiser

        int hitChance = distr(gen); 
        if (hitChance <= 70) {  // 70% chance 
            int targetRobotId = stoi(battlefield->getPlayer(x, y));
            GenericRobot* targetRobot = nullptr; 
            
            for (GenericRobot* robot : battlefield->getAllRobots()){
                if (robot->getRobotID() == targetRobotId) {
                    targetRobot = robot;
                    break;
                }
            }

            if (targetRobot->getRobotType() != HIDE && targetRobot->getRobotType() != REFLECTSHOT){
                targetRobot->reduceLife();
                if (!targetRobot->isAlive()){
                    cout << "Robot" << targetRobot->getRobotID() << "has been destroyed." << endl;
                }
                incrementKills(); //increment kills for this robot    
            } else if (targetRobot->getRobotType() == HIDE){
                targetRobot->reduceLife(); //??
            } else if (targetRobot->getRobotType() != REFLECTSHOT){
                reduceLife(); //??
            }
            delete targetRobot;
            targetRobot = nullptr;
        }
    }
}

void LongShotBot::actionThink(Battlefield* battlefield){
    actionRand(battlefield);
}

void LongShotBot::actionRand(Battlefield* battlefield){

        random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> posDistr(0, 8);

    int directionMove = posDistr(gen);

    int currentX = getRobotX();
    int currentY = getRobotY();

    int moveX = 0, moveY = 0;

    switch (directionMove) {
        case 0: moveX = -1; moveY = -1; break;
        case 1: moveX =  0; moveY = -1; break;
        case 2: moveX =  1; moveY = -1; break;
        case 3: moveX = -1; moveY =  0; break;
        case 4: moveX =  1; moveY =  0; break;
        case 5: moveX = -1; moveY =  1; break;
        case 6: moveX =  0; moveY =  1; break;
        case 7: moveX =  1; moveY =  1; break;
        case 8: moveX =  0; moveY =  0; break;
    }

    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> actionDistr(0, 10);

    actionThink(battlefield);
    actionLook(battlefield, 0, 0);

    int randomInt = actionDistr(gen2);

    if (randomInt % 2 == 0) {
        actionMove(battlefield, moveX, moveY);
        actionFire(battlefield, moveX, moveY);
    } else {
        actionFire(battlefield, moveX, moveY);
        actionMove(battlefield, moveX, moveY);
    }
}

void SemiAutoBot::actionFire(Battlefield* battlefield, int x, int y){
    int targetRobotId;
    GenericRobot* targetRobot = nullptr;

    while (shotsFired < MAX_SHOTS_FIRED && getShells() > 0){
        int targetX = getRobotX() + x;
        int targetY = getRobotY() + y;

        if(targetX < 0 || targetX >= battlefield->battlefieldCols() || targetY < 0 || targetY >= battlefield->battlefieldRows())
            return;

        if (battlefield->getPlayer(targetX, targetY) != ""){
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distr(1, 100); // 1 to 100 randomiser

            targetRobotId = stoi(battlefield->getPlayer(targetX, targetY)); 
            
            for (GenericRobot* robot : battlefield->getAllRobots()){
                if (robot->getRobotID() == targetRobotId) {
                    targetRobot = robot;
                    break;
                }
            }

            int hitChance = distr(gen); 
            if (hitChance <= 70) {  // 70% chance 
                if (targetRobot->getRobotType() != HIDE && targetRobot->getRobotType() != REFLECTSHOT){
                    targetRobot->reduceLife();
                    incrementKills();
                    if (!targetRobot->isAlive()){
                        cout << "Robot" << targetRobot->getRobotID() << "has been destroyed." << endl;
                        shotsFired = 1;
                        return;
                    }
                } else if (targetRobot->getRobotType() == HIDE){
                    targetRobot->reduceLife(); //??
                } else if (targetRobot->getRobotType() != REFLECTSHOT){
                    reduceLife(); //??
                }
            }
        }
        shotsFired++;
        setShells(getShells()-1);
    }
    shotsFired = 1;
    delete targetRobot;
    targetRobot = nullptr;
}
void SemiAutoBot::actionThink(Battlefield* battlefield){
    actionRand(battlefield);
}

void SemiAutoBot::actionRand(Battlefield* battlefield){

        random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> posDistr(0, 8);

    int directionMove = posDistr(gen);

    int currentX = getRobotX();
    int currentY = getRobotY();

    int moveX = 0, moveY = 0;

    switch (directionMove) {
        case 0: moveX = -1; moveY = -1; break;
        case 1: moveX =  0; moveY = -1; break;
        case 2: moveX =  1; moveY = -1; break;
        case 3: moveX = -1; moveY =  0; break;
        case 4: moveX =  1; moveY =  0; break;
        case 5: moveX = -1; moveY =  1; break;
        case 6: moveX =  0; moveY =  1; break;
        case 7: moveX =  1; moveY =  1; break;
        case 8: moveX =  0; moveY =  0; break;
    }

    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> actionDistr(0, 10);

    actionThink(battlefield);
    actionLook(battlefield, 0, 0);

    int randomInt = actionDistr(gen2);

    if (randomInt % 2 == 0) {
        actionMove(battlefield, moveX, moveY);
        actionFire(battlefield, moveX, moveY);
    } else {
        actionFire(battlefield, moveX, moveY);
        actionMove(battlefield, moveX, moveY);
    }
}


void ThirtyShotBot::actionFire(Battlefield* battlefield, int x, int y) { setShells(30); }

void ThirtyShotBot::actionThink(Battlefield* battlefield){
    actionRand(battlefield);
}

void ThirtyShotBot::actionRand(Battlefield* battlefield){

        random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> posDistr(0, 8);

    int directionMove = posDistr(gen);

    int currentX = getRobotX();
    int currentY = getRobotY();

    int moveX = 0, moveY = 0;

    switch (directionMove) {
        case 0: moveX = -1; moveY = -1; break;
        case 1: moveX =  0; moveY = -1; break;
        case 2: moveX =  1; moveY = -1; break;
        case 3: moveX = -1; moveY =  0; break;
        case 4: moveX =  1; moveY =  0; break;
        case 5: moveX = -1; moveY =  1; break;
        case 6: moveX =  0; moveY =  1; break;
        case 7: moveX =  1; moveY =  1; break;
        case 8: moveX =  0; moveY =  0; break;
    }

    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> actionDistr(0, 10);

    actionThink(battlefield);
    actionLook(battlefield, 0, 0);

    int randomInt = actionDistr(gen2);

    if (randomInt % 2 == 0) {
        actionMove(battlefield, moveX, moveY);
        actionFire(battlefield, moveX, moveY);
    } else {
        actionFire(battlefield, moveX, moveY);
        actionMove(battlefield, moveX, moveY);
    }
}


void HealBot::actionFire(Battlefield* battlefield, int x, int y){
    addLife();
    addLife();
    addLife();
} 
void HealBot::actionThink(Battlefield* battlefield){
    actionRand(battlefield);
}

void HealBot::actionRand(Battlefield* battlefield){

        random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> posDistr(0, 8);

    int directionMove = posDistr(gen);

    int currentX = getRobotX();
    int currentY = getRobotY();

    int moveX = 0, moveY = 0;

    switch (directionMove) {
        case 0: moveX = -1; moveY = -1; break;
        case 1: moveX =  0; moveY = -1; break;
        case 2: moveX =  1; moveY = -1; break;
        case 3: moveX = -1; moveY =  0; break;
        case 4: moveX =  1; moveY =  0; break;
        case 5: moveX = -1; moveY =  1; break;
        case 6: moveX =  0; moveY =  1; break;
        case 7: moveX =  1; moveY =  1; break;
        case 8: moveX =  0; moveY =  0; break;
    }

    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> actionDistr(0, 10);

    actionThink(battlefield);
    actionLook(battlefield, 0, 0);

    int randomInt = actionDistr(gen2);

    if (randomInt % 2 == 0) {
        actionMove(battlefield, moveX, moveY);
        actionFire(battlefield, moveX, moveY);
    } else {
        actionFire(battlefield, moveX, moveY);
        actionMove(battlefield, moveX, moveY);
    }
}


void BombBot::actionFire(Battlefield* battlefield, int x, int y){
    if(bombs){
        int cx = battlefield->getCurrentPlayer()->getRobotX();
        int cy = battlefield->getCurrentPlayer()->getRobotY();
        int tx, ty, targetRobotId;
        bool invalidCoordinates;
        string targetPosition;
        GenericRobot* target = nullptr;        
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
                        
                        for (GenericRobot* robot : battlefield->getAllRobots()){
                            if (robot->getRobotID() == targetRobotId) {
                                target = robot;
                                break;
                            }
                        }

                        if (target) {
                            target->reduceLife();
                            if(!target->isAlive())
                                cout << "Robot " << target->getRobotID() << "has been destroyed." << endl;
                            incrementKills(); //increment kills for this robot 
                        }
                    }                
                }
            }
        }
    }
    bombs--;
}

void BombBot::actionThink(Battlefield* battlefield){
    actionRand(battlefield);
}

void BombBot::actionRand(Battlefield* battlefield){

        random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> posDistr(0, 8);

    int directionMove = posDistr(gen);

    int currentX = getRobotX();
    int currentY = getRobotY();

    int moveX = 0, moveY = 0;

    switch (directionMove) {
        case 0: moveX = -1; moveY = -1; break;
        case 1: moveX =  0; moveY = -1; break;
        case 2: moveX =  1; moveY = -1; break;
        case 3: moveX = -1; moveY =  0; break;
        case 4: moveX =  1; moveY =  0; break;
        case 5: moveX = -1; moveY =  1; break;
        case 6: moveX =  0; moveY =  1; break;
        case 7: moveX =  1; moveY =  1; break;
        case 8: moveX =  0; moveY =  0; break;
    }

    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> actionDistr(0, 10);

    actionThink(battlefield);
    actionLook(battlefield, 0, 0);

    int randomInt = actionDistr(gen2);

    if (randomInt % 2 == 0) {
        actionMove(battlefield, moveX, moveY);
        actionFire(battlefield, moveX, moveY);
    } else {
        actionFire(battlefield, moveX, moveY);
        actionMove(battlefield, moveX, moveY);
    }
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


void ScoutBot::actionLook(Battlefield* battlefield, int x, int y){
    if (lookCount < MAX_LOOKS) {
        battlefield->displayBattlefield(-10, -10);
        lookCount++;
    }
}
void ScoutBot::actionThink(Battlefield* battlefield){
    actionRand(battlefield);
}

void ScoutBot::actionRand(Battlefield* battlefield){

        random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> posDistr(0, 8);

    int directionMove = posDistr(gen);

    int currentX = getRobotX();
    int currentY = getRobotY();

    int moveX = 0, moveY = 0;

    switch (directionMove) {
        case 0: moveX = -1; moveY = -1; break;
        case 1: moveX =  0; moveY = -1; break;
        case 2: moveX =  1; moveY = -1; break;
        case 3: moveX = -1; moveY =  0; break;
        case 4: moveX =  1; moveY =  0; break;
        case 5: moveX = -1; moveY =  1; break;
        case 6: moveX =  0; moveY =  1; break;
        case 7: moveX =  1; moveY =  1; break;
        case 8: moveX =  0; moveY =  0; break;
    }

    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> actionDistr(0, 10);

    actionThink(battlefield);
    actionLook(battlefield, 0, 0);

    int randomInt = actionDistr(gen2);

    if (randomInt % 2 == 0) {
        actionMove(battlefield, moveX, moveY);
        actionFire(battlefield, moveX, moveY);
    } else {
        actionFire(battlefield, moveX, moveY);
        actionMove(battlefield, moveX, moveY);
    }
}


void TrackBot::actionLook(Battlefield* battlefield, int x, int y){
    if (trackersUsed > MAX_TRACKERS)
        return;

    int targetRobotId = stoi(battlefield->getPlayer(x, y));
    targets.push_back(targetRobotId);
    trackersUsed++;
}
void TrackBot::actionThink(Battlefield* battlefield){
    actionRand(battlefield);
}

void TrackBot::actionRand(Battlefield* battlefield){

        random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> posDistr(0, 8);

    int directionMove = posDistr(gen);

    int currentX = getRobotX();
    int currentY = getRobotY();

    int moveX = 0, moveY = 0;

    switch (directionMove) {
        case 0: moveX = -1; moveY = -1; break;
        case 1: moveX =  0; moveY = -1; break;
        case 2: moveX =  1; moveY = -1; break;
        case 3: moveX = -1; moveY =  0; break;
        case 4: moveX =  1; moveY =  0; break;
        case 5: moveX = -1; moveY =  1; break;
        case 6: moveX =  0; moveY =  1; break;
        case 7: moveX =  1; moveY =  1; break;
        case 8: moveX =  0; moveY =  0; break;
    }

    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> actionDistr(0, 10);

    actionThink(battlefield);
    actionLook(battlefield, 0, 0);

    int randomInt = actionDistr(gen2);

    if (randomInt % 2 == 0) {
        actionMove(battlefield, moveX, moveY);
        actionFire(battlefield, moveX, moveY);
    } else {
        actionFire(battlefield, moveX, moveY);
        actionMove(battlefield, moveX, moveY);
    }
}


