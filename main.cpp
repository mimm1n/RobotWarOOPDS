/**********|**********|**********|
Program: main.cpp
Course: OOPDS
Trimester: 2510
Name: Aliyah, Khayrin, Aimi, Amirul
ID: 243UC24665 , 243UC246KQ , 243UC247CJ, 241UC24199
Lecture Section: TC2L
Tutorial Section: TT7L
Email: NOR.ALIYAH.SYAHIRAH@student.mmu.edu.my, KHAYRIN.SOFIYA.JAMEL@student.mmu.edu.my, AIMI.MOHD.FAIZAL@student.mmu.edu.my, AMIRUL.IHTISYAM.IDRUS@student.mmu.edu.my
Phone: 0146202605, 0193320041, 0139071648, 0194090095
**********|**********|**********/

#include <iostream>
#include "Robot.h"
using namespace std;

class ThinkingRobot : public Robot{
    public:
        virtual void actionThink(Battlefield* battlefield) = 0;
};

class SeeingRobot : public Robot{
    public:
        virtual void actionLook(Battlefield* battlefield) = 0;
};

class MovingRobot : public Robot{
    public:
        virtual void actionMove(Battlefield* battlefield) = 0;
};

class ShootingRobot : public Robot{
    public:
        virtual void actionFire(Battlefield* battlefield) = 0;
};

int main() {
    cout << "Hello World!" << endl;
}
