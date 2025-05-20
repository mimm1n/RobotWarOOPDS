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
        int killCount = 0; // Number of robots this robot managed to destroy/kill
        int lives = 3; // Number of lives of this robot (initial is 3)
        int robotId = -1; // The ID of this robot
        string robotName = ""; // The name of this robot
        string robotType = ""; // This robot's type; Jump, Hide, etc.

    public:
        Robot(int x, int y, string name, string type); // Constructor
        virtual ~Robot(){} // Destructor
        
        // Set and get the x coordinate of this robot
        void setRobotX(int x); 
        int getRobotX() const;

        // Set and get the y coordinate of this robot
        void setRobotY(int y);
        int getRobotY() const;

        // Get the name of this robot(fixed so can't set)
        string getRobotName() const;

        // Set and get the robot's type
        void setRobotType(string type);
        string getRobotType() const;

        int addLife(); // Adds 1 life to the lives count 
        bool reduceLife(); // Reduces the lives count by 1
        int getLives() const; // Get this robot's lives count
        bool isAlive() const; // Checks if this robot's lives count is more than 0

        int incrementKills(); // Adds 1 to the kill count

        // For child classes to rewrite and set new x and y coordinates
        virtual void setLocation(int x, int y) = 0; 

        //virtual void actions(Battlefield* battlefield) = 0;
};
#endif