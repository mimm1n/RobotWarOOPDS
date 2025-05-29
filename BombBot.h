//*********************************************************   
// Program:BombBot.h   
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

#ifndef BOMBBOT_H
#define BOMBBOT_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "ShootingRobot.h"
#include "GenericRobot.h"
#include "Battlefield.h"

using namespace std;

class ShootingRobot;

class BombBot : public ShootingRobot {
    private:
        int bombs = 1;
    public:
        BombBot(int x, int y, string name):Robot(x, y, name){}
        void actionFire(Battlefield* battlefield, int x, int y) override;
        void setRobotType(int type) override { robotType = BOMB; }
        int getRobotType() const override { return BOMB; }
};
#endif