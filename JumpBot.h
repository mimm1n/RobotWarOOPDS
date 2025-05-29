//*********************************************************   
// Program: JumpBot.h   
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

#ifndef JUMPBOT_H
#define JUMPBOT_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "Robot.h"
#include "Battlefield.h"
#include "MovingRobot.h"

using namespace std;

class JumpBot : public MovingRobot {
    private:
        int jumpsUsed = 0;
        const int MAX_JUMPS = 3;

    public:
        JumpBot(int x, int y, string name):Robot(x, y, name), MovingRobot( x, y, name){}
        void actionMove(Battlefield* battlefield, int x, int y) override;
        void setRobotType(int type) override { robotType = JUMP; }
        int getRobotType() const override { return JUMP; }
};
#endif
