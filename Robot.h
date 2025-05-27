//*********************************************************   
// Program: Robot.h   
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

#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

enum RobotType {GENERIC, SCOUT, TRACK, LONGSHOT, SEMIAUTO, THIRTYSHOT, JUMP, HIDE, REFLECTSHOT, HEAL, BOMB};

class Robot{
    private:
        int robotX = -1, robotY = -1; // x and y coordinates of the robot (x,y)
        string robotName = ""; // The name of this robot        
    
    protected:
        int killCount = 0; // Number of robots this robot managed to destroy/kill
        int lives = 3; // Number of lives of this robot (initial is 3)
        int robotId = -1; // The ID of this robot
        int robotType = GENERIC; // This robot's type; Jump, Hide, etc.

    public:
        Robot(int x, int y, string name); // Constructor
        virtual ~Robot(){} // Destructor
        
        // Set and get the x coordinate of this robot
        void setRobotX(int x); 
        int getRobotX() const;

        // Set and get the y coordinate of this robot
        void setRobotY(int y);
        int getRobotY() const;

        // Get the name of this robot(fixed so can't set)
        string getRobotName() const;

        int addLife(); // Adds 1 life to the lives count 
        bool reduceLife(); // Reduces the lives count by 1
        int getLives() const; // Get this robot's lives count
        bool isAlive() const; // Checks if this robot's lives count is more than 0
        
        int getKills() const; // Get this robot's current kill count
        void incrementKills(); // Adds 1 to the kill count

        // Set and get the robot's type
        virtual void setRobotType(int type) = 0;
        virtual int getRobotType() const = 0;
};
#endif