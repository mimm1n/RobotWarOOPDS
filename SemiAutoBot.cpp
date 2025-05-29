//*********************************************************   
// Program: SemiAutoBot.cpp   
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

#include "SemiAutoBot.h"
#include "Battlefield.h"
#include "GenericRobot.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

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