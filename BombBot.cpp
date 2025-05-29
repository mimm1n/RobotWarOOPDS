//*********************************************************   
// Program: BombBot.cpp   
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

#include "BombBot.h"
#include "GenericRobot.h"
#include "Battlefield.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

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

