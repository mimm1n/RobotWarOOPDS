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

//GenericRobot
class GenericRobot : public ShootingRobot, public MovingRobot, 
                    public SeeingRobot, public ThinkingRobot{
    private: 
        static int robotIncrement = 0;
        string robotId_;
    public: 
        GenericRobot(string id = "GR0", int x, int y) : ShootingRobot(x, y, id, "Shooting"),
                                                        MovingRobot(x, y, id, "Moving"),
                                                        SeeingRobot(x, y, id, "Seeing"),
                                                        ThinkingRobot(x, y, id, "Thinking"){
            robotId_ = id + to_string(robotIncrement);
            int robotPosX = x; 
            int robotPosY = y; 

            robotIncrement++;
        }

        string getRobotID() const { return robotId_; }

    virtual void actionShoot(Battlefield* battlefield){
        // ShootingRobot::actionShoot(battlefield); 
    }
    virtual void actionMove(Battlefield* battlefield){}
    virtual void actionSee(Battlefield* battlefield){}
    virtual void actionThink(Battlefield* battlefield){}
    void actionRand(Battlefield* battlefield){
        random_device rd; 
        mt19937 gen(rd()); 
        uniform_int_distribution<> distr(0, 10); // define range

        actionThink(battlefield);
        actionSee(battlefield); 

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
};


int main() {
    cout << "Hello World!" << endl;
<<<<<<< HEAD

    ScoutBot scout;
    scout.actionLook(&field);

    TrackBot track;
    track.actionLook(&field);

    LongShotBot longShot;
    longShot.actionFire(&field);

    SemiAutoBot semiAuto;
    semiAuto.actionFire(&field);

    ThirtyShotBot thirtyShot;
    thirtyShot.actionFire(&field);

    HideBot hide;
    hide.actionMove(&field);

    JumpBot jump;
    jump.actionMove(&field);
=======
    Battlefield battlefield;
    battlefield.readFile("inputFile.txt");
    battlefield.displayBattlefield();
    return 0;
>>>>>>> 84607456af756870e2a33bd435898d57e8eac9cf
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

<<<<<<< HEAD
class ScoutBot : public Robot,
                 public SeeingRobot<ScoutBot> {
public:
    void doLook(Battlefield* battlefield) {
        cout << "ScoutBot is scanning the area..." <<endl; // i don't know this is right or wrong
        battlefield->status();
    }
};

class TrackBot : public Robot,
                 public SeeingRobot<TrackBot> {
public:
    void doLook(Battlefield* battlefield) {
        std::cout << "TrackBot is planting a tracker on an enemy robot..." <<endl; // i don't know this is right or wrong
    }
};

class LongShotBot : public Robot,
                    public ShootingRobot<LongShotBot> {
public:
    void doFire(Battlefield* battlefield) {
        cout << "LongShotBot is firing up to three units distance away..." <<endl; // i don't know this is right or wrong
    }
};

class SemiAutoBot : public Robot,
                    public ShootingRobot<SemiAutoBot> {
public:
    void doFire(Battlefield* battlefield) {
        cout << "SemiAutoBot is firing three consecutive shells into one location..." <<endl; // i don't know this is right or wrong
    }
};

class ThirtyShotBot : public Robot,
                      public ShootingRobot<ThirtyShotBot> {
public:
    void doFire(Battlefield* battlefield) {
        cout << "ThirtyShotBot is firing with a fresh load of 30 shells..." <<endl; // i don't know this is right or wrong
    }
};

class HideBot : public Robot,
                public MovingRobot<HideBot> {
public:
    void doMove(Battlefield* battlefield) {
        cout << "HideBot is hiding for three turns..." << endl; // i don't know this is right or wrong
    }
};

class JumpBot : public Robot,
                public MovingRobot<JumpBot> {
public:
    void doMove(Battlefield* battlefield) {
        cout << "JumpBot is jumping to a new location..." <<endl; // i don't know this is right or wrong
    }
};
=======

>>>>>>> 84607456af756870e2a33bd435898d57e8eac9cf
