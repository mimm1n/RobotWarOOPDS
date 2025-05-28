//*********************************************************   
// Program: Battlefield.h   
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

#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "GenericRobot.h"
using namespace std;

class Battlefield {
    private:
        int battlefieldCols_ = -1; // variable to assign number of columns
        int battlefieldRows_ = -1; // variable to assign number of rows

        int totalTurns_ = -1; // variable to assign total turns
        int currentTurn_ = 1; 
        int currentPlayer = 0;
    

        int numOfRobots_ = -1; // variable to assign number of robots

        vector<GenericRobot *> robots_; 
        queue<GenericRobot *> destroyedRobots_;
        queue<GenericRobot *> waitingRobots_;  
        vector<vector<string>> battlefield_;
        vector <int> allRobotId;
        friend class GenericRobot;
    public:
        // Get function
        int battlefieldCols();
        int battlefieldRows();
        int turns();
        int numOfRobots();
        int currentTurn();
        string getPlayer(int x, int y);
        vector <GenericRobot *> getAllRobots() const;
        vector <int> getAllRobotId() const;
        GenericRobot* getCurrentPlayer() const;
        
        
        void readFile(string filename);
        void placeRobots();
        void displayBattlefield(int x, int y, vector<int> targets = {}) const;
        void respawnRobot(int x);
        void nextTurn();
};
#endif