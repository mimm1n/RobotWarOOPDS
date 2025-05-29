//*********************************************************   
// Program: LongShotBot.cpp   
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

#include "LongShotBot.h"
#include "ShootingRobot.h"
#include "GenericRobot.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

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

void LongShotBot::actionThink(Battlefield* battlefield, int x, int y){
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

