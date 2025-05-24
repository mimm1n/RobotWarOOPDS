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
#include <random>
#include "Robot.h"
#include "Battlefield.h"
using namespace std;

/* CLASS DEFINITIONS */
// Robot Actions
class ThinkingRobot : virtual public Robot{
    public:
        ThinkingRobot(){}
        virtual void setLocation(int x, int y);
        virtual void actionThink(Battlefield* battlefield) = 0;
        
};

class SeeingRobot : virtual public Robot{
    public:
        SeeingRobot(){}
        virtual void setLocation(int x, int y);
        virtual void actionLook(Battlefield* battlefield) = 0;
};

class MovingRobot : virtual public Robot{
    public:
        MovingRobot(){}
        virtual void setLocation(int x, int y);
        virtual void actionMove(Battlefield* battlefield) = 0;
};

class ShootingRobot : virtual public Robot{
    private:
        int shells = 10;
    public:
        ShootingRobot(){}
        void setShells(int num);
        int getShells() const;
        virtual void setLocation(int x, int y);
        virtual void actionFire(Battlefield* battlefield) = 0;
};

//GenericRobot
class GenericRobot : public ShootingRobot, public MovingRobot, 
                    public SeeingRobot, public ThinkingRobot{
    private: 
        static int robotIncrement;
        int robotId_;
    public: 
        GenericRobot(string name, int x, int y) {
            robotId_ = robotIncrement; 
            robotIncrement++;
        }

        int getRobotID() const { return robotId_; }

        virtual void actionFire(Battlefield* battlefield) override {
            // ShootingRobot::actionShoot(battlefield); 
        }
        virtual void actionMove(Battlefield* battlefield) override {}
        virtual void actionLook(Battlefield* battlefield) override {}
        virtual void actionThink(Battlefield* battlefield){}
        void actionRand(Battlefield* battlefield){
            random_device rd; 
            mt19937 gen(rd()); 
            uniform_int_distribution<> distr(0, 10); // define range

            actionThink(battlefield);
            actionLook(battlefield); 

            int randomInt = distr(gen);

            if(randomInt % 2 == 0) { 
                actionMove(battlefield);
                actionFire(battlefield); 
            }

            else if(randomInt % 2 == 1){
                actionFire(battlefield);
                actionMove(battlefield); 
            }
        }

    void setLocation(int x, int y) override {
        setRobotX(x);
        setRobotY(y);
    }
};

int GenericRobot::robotIncrement = 0; 

int main() {
    cout << "Hello World!" << endl;
    Battlefield battlefield;
    battlefield.readFile("inputFile.txt");

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

void ShootingRobot::setShells(int num){
    shells = num;
}

int ShootingRobot::getShells() const{
    return shells;
}


