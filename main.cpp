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
#include "Battlefield.h"
#include "ThinkingRobot.h"
#include "SeeingRobot.h"
#include "MovingRobot.h"
#include "ShootingRobot.h"

using namespace std;

class GenericRobot;
class HideBot;
class JumpBot;
class LongShotBot;
class SemiAutoBot;
class ThirtyShotBot;
class HealBot;
class BombBot;
class ReflectShotBot;
class ScoutBot;
class TrackBot;

int main() {
    ofstream outFile;
    Battlefield* battlefield = new Battlefield();
    battlefield->readFile("inputFile.txt");
    outFile.open("outputFile.txt");
    battlefield->placeRobots();
    Robot* currentPlayer = new GenericRobot(0,0,"test"), upgradedRobot = new GenericRobot(0, 0,"test");
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

        random_device rd;
        mt19937 gen(rd()), gen2(rd()), gen3(rd()), gen4(rd());

        uniform_int_distribution<> moveDistr(1, 4);
        int move = moveDistr(gen);

        uniform_int_distribution<> dirDistr(-1, 1);
        int x = dirDistr(gen2);
        int y = dirDistr(gen3);
        
        switch(move){
            case 1: // Think
                currentPlayer->actionThink(battlefield);
                cout << currentPlayer->getRobotName() << " is thinking" << endl;
                outFile << currentPlayer->getRobotName() << " is thinking" << endl;
                break;
            case 2: // Look
                currentPlayer->actionLook(battlefield, x, y);
                cout << currentPlayer->getRobotName() << " is looking" << endl;
                outFile << currentPlayer->getRobotName() << " is looking" << endl;
                break;
            case 3: // Fire
                kills = currentPlayer->getKills();
                currentPlayer->actionFire(battlefield, x, y);
                cout << currentPlayer->getRobotName() << " is shooting..." << endl;
                outFile << currentPlayer->getRobotName() << " is shooting..." << endl;

                if (kills < currentPlayer->getKills()){ // upgrade 
                    cout << currentPlayer->getRobotName() << " killed "; 
                    cout << battlefield->getPlayer(currentPlayer->getRobotX()+x,currentPlayer->getRobotY()+y) << "!" << endl;
                    outFile << currentPlayer->getRobotName() << " killed "; 
                    outFile << battlefield->getPlayer(currentPlayer->getRobotX()+x,currentPlayer->getRobotY()+y) << "!" << endl;

                    if (!currentPlayer->canUpgrade()) continue;

                    currentPlayerType = currentPlayer->getRobotType();
                    x = currentPlayer->getRobotX();
                    y = currentPlayer->getRobotY();
                    name = currentPlayer->getRobotName();

                    if (currentPlayerType == GENERIC){
                        uniform_int_distribution<> upgradeDistr(1, 10);
                        upgrade = upgradeDistr(gen4);
                        switch(upgrade){
                            case 1: upgradedRobot = new ScoutBot(x, y, name); break;
                            case 2: upgradedRobot = new TrackBot(x, y, name); break;
                            case 3: upgradedRobot = new LongShotBot(x, y, name); break;
                            case 4: upgradedRobot = new SemiAutoBot(x, y, name); break;
                            case 5: upgradedRobot = new ThirtyShotBot(x, y, name); break;
                            case 6: upgradedRobot = new JumpBot(x, y, name); break;
                            case 7: upgradedRobot = new HideBot(x, y, name); break;
                            case 8: upgradedRobot = new ReflectShotBot(x, y, name); break;
                            case 9: upgradedRobot = new HealBot(x, y, name); break;
                            case 10: upgradedRobot = new BombBot(x, y, name); break;
                        }
                    } else if (currentPlayerType == SCOUT || currentPlayerType == TRACK){
                        uniform_int_distribution<> upgradeDistr(1, 8);
                        upgrade = upgradeDistr(gen4);
                        switch(upgrade){
                            case 1: upgradedRobot = new LongShotBot(x, y, name); break;
                            case 2: upgradedRobot = new SemiAutoBot(x, y, name); break;
                            case 3: upgradedRobot = new ThirtyShotBot(x, y, name); break;
                            case 4: upgradedRobot = new JumpBot(x, y, name); break;
                            case 5: upgradedRobot = new HideBot(x, y, name); break;
                            case 6: upgradedRobot = new ReflectShotBot(x, y, name); break;
                            case 7: upgradedRobot = new HealBot(x, y, name); break;
                            case 8: upgradedRobot = new BombBot(x, y, name); break;
                        }
                    } else if (currentPlayerType == HIDE || currentPlayerType == JUMP){
                        uniform_int_distribution<> upgradeDistr(1, 8);
                        upgrade = upgradeDistr(gen4);
                        switch(upgrade){
                            case 1: upgradedRobot = new LongShotBot(x, y, name); break;
                            case 2: upgradedRobot = new SemiAutoBot(x, y, name); break;
                            case 3: upgradedRobot = new ThirtyShotBot(x, y, name); break;
                            case 4: upgradedRobot = new ScoutBot(x, y, name); break;
                            case 5: upgradedRobot = new TrackBot(x, y, name); break;
                            case 6: upgradedRobot = new ReflectShotBot(x, y, name); break;
                            case 7: upgradedRobot = new HealBot(x, y, name); break;
                            case 8: upgradedRobot = new BombBot(x, y, name); break;
                        }
                    } else {
                        uniform_int_distribution<> upgradeDistr(1, 4);
                        upgrade = upgradeDistr(gen4);
                        switch(upgrade){
                            case 1: upgradedRobot = new ScoutBot(x, y, name); break;
                            case 2: upgradedRobot = new TrackBot(x, y, name); break;
                            case 3: upgradedRobot = new JumpBot(x, y, name); break;
                            case 4: upgradedRobot = new HideBot(x, y, name); break;
                        }
                    }
                    upgradedRobot->addUpgrade(currentPlayer->getUpgradeCount());
                    upgradedRobot->setLives(currentPlayer->getLives());
                    upgradedRobot->setKills(currentPlayer->getKills());
                    upgradedRobot->setShells(currentPlayer->getShells());
                    // need to update in Battlefield the robot type

                    cout << currentPlayer->getRobotName() << " upgraded!" << endl;
                    outFile << currentPlayer->getRobotName() << " upgraded!" << endl;
                    delete upgradedRobot;
                    upgradedRobot = nullptr; 
                }
                break;
            case 4: // Move
                currentPlayer->actionMove(battlefield, x, y);
                break;
        }
        battlefield->nextTurn();
        delete currentPlayer;
        currentPlayer = nullptr;
    } while(!battlefield->getCurrentPlayer() && (battlefield->currentTurn() < battlefield->turns()));
    
    outFile.close();
    return 0;
}

class GenericRobot : public ShootingRobot, public MovingRobot, public SeeingRobot, public ThinkingRobot {
private:
    static int robotIncrement;
    int robotId;
    int upgradeCount = 0;
    const int MAX_UPGRADE = 3;
    Robot* robotUpgraded = nullptr;
    bool upgrade = false;

public:
    GenericRobot(std::string name, int x, int y);

    int getRobotID() const;
    void setRobotType(int type) override;
    int getRobotType() const override;

    void actionFire(Battlefield* battlefield, int x, int y) override;
    void actionMove(Battlefield* battlefield, int x, int y) override;
    void actionLook(Battlefield* battlefield, int x, int y) override;
    void actionThink(Battlefield* battlefield) override;
    void actionRand(Battlefield* battlefield);

    void upgradeRobot(Battlefield* battlefield, int upgradeType);
    bool toUpgrade() const;
    void ToGeneric(int upgradeType);
    int getUpgradeCount() const;
};

int GenericRobot::robotIncrement = 0;

GenericRobot::GenericRobot(string name, int x, int y) : Robot(x, y, name) {
    robotId = robotIncrement;
    robotIncrement++;
}

int GenericRobot::getRobotID() const { return robotId; }
void GenericRobot::setRobotType(int type) { robotType = type; }
int GenericRobot::getRobotType() const { return robotType; }

void GenericRobot::actionFire(Battlefield* battlefield, int x, int y) {
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
        cout << "Missed!" << endl;  //covers returns like an empty string or any invalid 
        return;
    }

    int targetRobotId = stoi(playerStr); //reuse 
    GenericRobot* targetRobot = nullptr;

    for (GenericRobot* robot : battlefield->robots_) {
        if (robot->getRobotID() == targetRobotId) {
            targetRobot = robot;
            break;
        }
    }

    if (!targetRobot) {
        cout << "Missed!" << endl;
        return;
    }

    if (HideBot* hidden = dynamic_cast<HideBot*>(targetRobot)) {
        if (hidden->isHidden()) {
            cout << "Shot missed. Robot is hidden." << endl;
            return;
        }
    }

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

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(1, 100);
    int hitChance = distr(gen);

    if (hitChance <= 70) {
        bool saveLife = targetRobot->isAlive();
        targetRobot->reduceLife();

        RobotType type = battlefield->findTargetRobot(targetRobot);

        if (type != GENERIC){
            bool remove = true; //remove when a robot got hit

            if (HideBot* hideBot = dynamic_cast<HideBot*>(targetRobot)) {
                if (hideBot->hidesLeft() > 0) {
                    remove = false; 
                } // dont remove if hides still more than 0
            }

            if (remove || !targetRobot->isAlive()){
                auto& list = battlefield->upgradedRobots_[type];
                list.erase(remove(list.begin(), list.end(), targetRobot), list.end()); 
            }
        }

        if (saveLife && !targetRobot->isAlive()) {
            cout << "Robot " << targetRobot->getRobotID() << " has been destroyed." << endl;
        }

        incrementKills();
        upgrade = true;

        if (getUpgradeCount() < MAX_UPGRADE) {
            int chosenUpgrade = getRobotType();
            upgradeRobot(battlefield, chosenUpgrade);
        } else {
            cout << "Max upgrade reached." << endl;
        }
    } else {
        cout << "Shot missed!" << endl;
    }
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

void GenericRobot::actionThink(Battlefield* battlefield) {
    actionRand(battlefield);
}

void GenericRobot::upgradeRobot(Battlefield* battlefield, int upgradeType) {
    if (upgradeCount >= MAX_UPGRADE) {
        cout << "Max upgrade reached.";
        return;
    }

    Robot* current = battlefield->getCurrentPlayer();
    if (!current) return;  //prevents dereferencing of nullptr

    int x = current->getRobotX();
    int y = current->getRobotY();
    string name = current->getRobotName();

    if (robotUpgraded) {
        delete robotUpgraded;
        robotUpgraded = nullptr;
    } //clear memory before new upgrade

    switch (upgradeType) {
        case 1: robotUpgraded = new ScoutBot(x, y, name); break;
        case 5: robotUpgraded = new ThirtyShotBot(x, y, name); break;
        case 6: robotUpgraded = new JumpBot(x, y, name); break;
        case 7: robotUpgraded = new HideBot(x, y, name); break;
        case 8: robotUpgraded = new ReflectShotBot(x, y, name); break;
        case 9: robotUpgraded = new HealBot(x, y, name); break;
        case 10: robotUpgraded = new BombBot(x, y, name); break;
        default: return;
    }

    battlefield->upgradedRobots_[upgradeType].push_back(this); // add to the upgraded robot list 
    upgradeCount++;
    upgrade = false;
}

bool GenericRobot::toUpgrade() const {
    return upgradeCount < MAX_UPGRADE && upgrade;
}

void GenericRobot::ToGeneric(int upgradeType) {
    delete robotUpgraded;
    robotUpgraded = nullptr;
    robotType = GENERIC;
}

int GenericRobot::getUpgradeCount() const {
    return upgradeCount;
}

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

class HideBot : public ShootingRobot, public MovingRobot, public SeeingRobot, public ThinkingRobot{
    private:
        int hideTurnsUsed = 0;
        const int MAX_HIDE_TURNS = 3;
        bool isHidden_ = false;

    public:
        HideBot(int x, int y, string name):MovingRobot(x, y, name){}
        void actionFire(Battlefield* battlefield, int x, int y) override;
        void actionMove(Battlefield* battlefield, int x, int y) override;
        void actionLook(Battlefield* battlefield, int x, int y) override;
        void actionThink(Battlefield* battlefield, int x, int y) override;
        void actionRand(Battlefield* battlefield);
        bool isHidden();
        int hidesLeft() const;
        void setRobotType(int type) override { robotType = HIDE; }
        int getRobotType() const override { return HIDE; }
};

//*********************************************************   
// Program: HideBot.cpp   
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

#include "HideBot.h"
#include "Battlefield.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

void HideBot::actionFire(Battlefield* battlefield, int x, int y){
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
        cout << "Missed!" << endl;  //covers returns like an empty string or any invalid 
        return;
    }

    int targetRobotId = stoi(playerStr); //reuse 
    GenericRobot* targetRobot = nullptr;

    for (GenericRobot* robot : battlefield->robots_) {
        if (robot->getRobotID() == targetRobotId) {
            targetRobot = robot;
            break;
        }
    }

    if (!targetRobot) {
        cout << "Missed!" << endl;
        return;
    }

    if (HideBot* hidden = dynamic_cast<HideBot*>(targetRobot)) {
        if (hidden->isHidden()) {
            cout << "Shot missed. Robot is hidden." << endl;
            return;
        }
    }

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

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(1, 100);
    int hitChance = distr(gen);

    if (hitChance <= 70) {
        bool saveLife = targetRobot->isAlive();
        targetRobot->reduceLife();

        RobotType type = battlefield->findTargetRobot(targetRobot);

        if (type != GENERIC){
            bool remove = true; //remove when a robot got hit

            if (HideBot* hideBot = dynamic_cast<HideBot*>(targetRobot)) {
                if (hideBot->hidesLeft() > 0) {
                    remove = false; 
                } // dont remove if hides still more than 0
            }

            if (remove || !targetRobot->isAlive()){
                auto& list = battlefield->upgradedRobots_[type];
                list.erase(remove(list.begin(), list.end(), targetRobot), list.end()); 
            }
        }

        if (saveLife && !targetRobot->isAlive()) {
            cout << "Robot " << targetRobot->getRobotID() << " has been destroyed." << endl;
        }

        incrementKills();
        upgrade = true;

        if (getUpgradeCount() < MAX_UPGRADE) {
            int chosenUpgrade = getRobotType();
            upgradeRobot(battlefield, chosenUpgrade);
        } else {
            cout << "Max upgrade reached." << endl;
        }
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


void HideBot::actionThink(Battlefield* battlefield, int x, int y){
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
