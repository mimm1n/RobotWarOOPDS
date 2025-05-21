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
#include <fstream>
#include <iomanip>
#include <vector>
#include "Robot.h"
using namespace std;

/* CLASS DEFINITIONS */
class ThinkingRobot : public Robot{
    public:
        virtual void setLocation(int x, int y);
        virtual void actionThink(Battlefield* battlefield) = 0;
};

class SeeingRobot : public Robot{
    public:
        virtual void setLocation(int x, int y);
        virtual void actionLook(Battlefield* battlefield) = 0;
};

class MovingRobot : public Robot{
    public:
        virtual void setLocation(int x, int y);
        virtual void actionMove(Battlefield* battlefield) = 0;
};

class ShootingRobot : public Robot{
    public:
        virtual void setLocation(int x, int y);
        virtual void actionFire(Battlefield* battlefield) = 0;
};

int main() {
    cout << "Hello World!" << endl;

    return 0;
}

/* FUNCTION DEFINITIONS */
void ThinkingRobot::setLocation(int x, int y){
    setRobotX(x);
    setRobotY(y);
}

void SeeingRobot::setLocation(int x, int y){
    setRobotX(x);
    setRobotY(y);
}

void MovingRobot::setLocation(int x, int y){
    setRobotX(x);
    setRobotY(y);
}

void ShootingRobot::setLocation(int x, int y){
    setRobotX(x);
    setRobotY(y);
}
