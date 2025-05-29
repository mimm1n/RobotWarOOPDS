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
