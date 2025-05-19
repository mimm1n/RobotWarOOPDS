/**********|**********|**********|
Program: Robot.h
Course: OOPDS
Trimester: 2510
Name: Aliyah, Khayrin, Aimi, Amirul
ID: 243UC24665 , 243UC246KQ , 243UC247CJ, 241UC24199
Lecture Section: TC2L
Tutorial Section: TT7L
Email: NOR.ALIYAH.SYAHIRAH@student.mmu.edu.my, KHAYRIN.SOFIYA.JAMEL@student.mmu.edu.my, AIMI.MOHD.FAIZAL@student.mmu.edu.my, AMIRUL.IHTISYAM.IDRUS@student.mmu.edu.my
Phone: 0146202605, 0193320041, 0139071648, 0194090095
**********|**********|**********/

#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class Robot{
    protected:
        int robotX = -1, robotY = -1; // x and y coordinates of the robot (x,y)
        int killCount = 0;
        int lives = 3;
        int robotId = -1;
        string robotName = "";
        string robotType = "";

    public:
        Robot(int x, int y, string name, string type);
        virtual ~Robot(){}
        
        void setRobotX(int x);
        int getRobotX() const;

        void setRobotY(int y);
        int getRobotY() const;

        string getRobotName() const;

        void setRobotType(string type);
        string getRobotType() const;

        bool addLife();
        bool reduceLife();
        int getLives() const;
        bool isAlive() const;

        bool incrementKills();


        virtual void setLocation(int x, int y) = 0;
        virtual void actions(Battlefield* battlefield) = 0;
};
#endif