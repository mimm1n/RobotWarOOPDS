//*********************************************************   
// Program: GenericRobot.h   
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

#ifndef GENERICROBOT_H
#define GENERICROBOT_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <random>
#include "ShootingRobot.h"
#include "MovingRobot.h"
#include "SeeingRobot.h"
#include "ThinkingRobot.h"
#include "Battlefield.h"
#include "Robot.h"
#include "BombBot.h"
#include "HealBot.h"
#include "HideBot.h"
#include "JumpBot.h"
#include "LongShotBot.h"
#include "ReflectShotBot.h"
#include "ScoutBot.h"
#include "SemiAutoBot.h"
#include "ThirtyShotBot.h"
#include "TrackBot.h"

using namespace std;


class GenericRobot : public ShootingRobot, public MovingRobot, public SeeingRobot, public ThinkingRobot {
private:
    static int robotIncrement;
    int robotId;
    int upgradeCount = 0;
    const int MAX_UPGRADE = 3;
    Robot* robotUpgraded = nullptr;
    bool upgrade = false;

public:
    GenericRobot(std::string name, int x, int y);

    int getRobotID() const;
    void setRobotType(int type) override;
    int getRobotType() const override;

    void actionFire(Battlefield* battlefield, int x, int y) override;
    void actionMove(Battlefield* battlefield, int x, int y) override;
    void actionLook(Battlefield* battlefield, int x, int y) override;
    void actionThink(Battlefield* battlefield) override;
    void actionRand(Battlefield* battlefield);

    void upgradeRobot(Battlefield* battlefield, int upgradeType);
    bool toUpgrade() const;
    void ToGeneric(int upgradeType);
    int getUpgradeCount() const;
};

#endif
