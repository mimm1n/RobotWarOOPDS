//*********************************************************   
// Program: TrackBot.h   
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

#ifndef TRACKBOT_H
#define TRACKBOT_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "SeeingRobot.h"
#include "Battlefield.h"
#include "Robot.h"
using namespace std;

class TrackBot : public SeeingRobot {
    private:
        int trackersUsed = 0;
        const int MAX_TRACKERS = 3;
        vector<int> targets {};

    public:
        TrackBot(int x, int y, string name):Robot(x, y, name){}
        void actionLook(Battlefield* battlefield, int x, int y) override;
        vector<int> getTrackedTargets() { return targets; }
        void setRobotType(int type) override { robotType = TRACK; }
        int getRobotType() const override { return TRACK; }
};
#endif