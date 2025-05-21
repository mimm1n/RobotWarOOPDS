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