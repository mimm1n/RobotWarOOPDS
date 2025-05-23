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

class ScoutBot : public SeeingRobot {
private:
    int lookCount = 0;
    const int maxLooks = 3;

public:
    void actionLook(Battlefield* battlefield) override {
        if (lookCount < maxLooks) {
            // Logic to scan the entire battlefield
            battlefield->scanEntireField(this);
            lookCount++;
        }
    }
};

class TrackBot : public SeeingRobot {
private:
    int trackersUsed = 0;
    const int maxTrackers = 3;

public:
    void actionLook(Battlefield* battlefield) override {
        if (trackersUsed < maxTrackers) {
            Robot* target = battlefield->selectEnemyToTrack();
            if (target) {
                battlefield->trackEnemy(target, this);
                trackersUsed++;
            }
        }
    }
};
class LongShotBot : public ShootingRobot {
public:
    void actionFire(Battlefield* battlefield) override {
        int targetX, targetY;
        if (battlefield->getTargetWithinRange(this, 3, targetX, targetY)) {
            battlefield->fireAt(targetX, targetY);
        }
    }
};
class SemiAutoBot : public ShootingRobot {
public:
    void actionFire(Battlefield* battlefield) override {
        int targetX, targetY;
        if (battlefield->getTarget(this, targetX, targetY)) {
            for (int i = 0; i < 3; ++i) {
                battlefield->fireAt(targetX, targetY); // 3 shells
            }
        }
    }
};
class ThirtyShotBot : public ShootingRobot {
private:
    int ammo = 0;

public:
    void actionFire(Battlefield* battlefield) override {
        ammo = 30; // Reload
    }
};
class HideBot : public ThinkingRobot {
private:
    int hideTurnsUsed = 0;
    const int maxHideTurns = 3;
    bool isHidden = false;

public:
    void actionThink(Battlefield* battlefield) override {
        if (hideTurnsUsed < maxHideTurns) {
            isHidden = true;
            hideTurnsUsed++;
            battlefield->setHidden(this, true);
        }
    }
};
class JumpBot : public MovingRobot {
private:
    int jumpsUsed = 0;
    const int maxJumps = 3;

public:
    void actionMove(Battlefield* battlefield) override {
        if (jumpsUsed < maxJumps) {
            int newX, newY;
            battlefield->getRandomLocation(newX, newY);
            setLocation(newX, newY);
            jumpsUsed++;
        }
    }
};



int main() {
    cout << "Hello World!" << endl;
    Battlefield battlefield;
    battlefield.readFile("inputFile.txt");
    battlefield.displayBattlefield();
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


