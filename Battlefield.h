#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "Robot.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

class Battlefield {
private:
  int battlefieldCols_ = -1; // variable to assign number of columns
  int battlefieldRows_ = -1; // variable to assign number of rows

  int totalTurns_ = -1; // variable to assign total turns
  int currentTurn_ = 0; //??

  int numOfRobots_ = -1; // variable to assign number of robots

  //vector<GenericRobot *> robots_; 
  queue<Robot *> destroyedRobots_;
  queue<Robot *> waitingRobots_;

  vector<vector<string>> battlefield_;

public:
  // Get function
  int battlefieldCols() { return battlefieldCols_; }
  int battlefieldRows() { return battlefieldRows_; }
  int turn() { return totalTurns_; }
  int numOfRobots() { return numOfRobots_; }
  
  void readFile(string filename);
  void placeRobots();
  void displayBattlefield() const;
};
#endif