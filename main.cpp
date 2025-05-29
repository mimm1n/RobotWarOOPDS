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
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <random>
#include "Robot.h"
#include "Battlefield.h"
#include "ThinkingRobot.h"
#include "SeeingRobot.h"
#include "MovingRobot.h"
#include "ShootingRobot.h"
#include "GenericRobot.h"
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

int main() {
    ofstream outFile;
    Battlefield* battlefield = new Battlefield();
    battlefield->readFile("inputFile.txt");
    outFile.open("outputFile.txt");
    battlefield->placeRobots();
    Robot* currentPlayer = nullptr, upgradedRobot = nullptr;
    int move, x, y, kills, upgrade, currentPlayerType;
    string name;
    
    do {
        currentPlayer = battlefield->getCurrentPlayer();
        battlefield->displayBattlefield(-5,-5);
        outFile << battlefield->displayBattlefield(-5,-5);

        random_device rd;
        mt19937 gen(rd()); // for think, look, fire, move
        mt19937 gen2(rd()); // for x coordinate
        mt19937 gen3(rd()); // for y coordinate
        mt19937 gen4(rd()); // for upgrades

        uniform_int_distribution<> (1,4); 
        move = posDistr(gen);
        
        switch(move){
            case 1: // Think
                currentPlayer->actionThink(battlefield);
                break;
            case 2: // Look
                uniform_int_distribution<> dirDistr(-1, 1);
                x = dirDistr(gen2);
                y = dirDistr(gen3);
                currentPlayer->actionLook(battlefield, x, y);
                break;
            case 3: // Fire
                uniform_int_distribution<> dirDistr(-1, 1);
                x = dirDistr(gen2);
                y = dirDistr(gen3);
                kills = currentPlayer->getKills();
                currentPlayer->actionFire(battlefield, x, y);

                //GENERIC, SCOUT, TRACK, LONGSHOT, SEMIAUTO, THIRTYSHOT, JUMP, HIDE, REFLECTSHOT, HEAL, BOMB
                if (kills < currentPlayer->getKills()){ // upgrade 
                    if (!currentPlayer->canUpgrade()) continue;

                    currentPlayerType = currentPlayer->getRobotType();
                    x = currentPlayer->getRobotX();
                    y = currentPlayer->getRobotY();
                    name = currentPlayer->getRobotName();

                    if (currentPlayerType == GENERIC){
                        uniform_int_distribution<> (1,10);
                        upgrade = posDistr(gen4);
                        switch(upgrade){
                            case 1: upgradedRobot = new ScoutBot(x, y, name); break;
                            case 2: upgradedRobot = new TrackBot(x, y, name); break;
                            case 3: upgradedRobot = new LongShotBot(x, y, name); break;
                            case 4: upgradedRobot = new SemiAutoBot(x, y, name); break;
                            case 5: upgradedRobot = new ThirtyShotBot(x, y, name); break;
                            case 6: upgradedRobot = new JumpBot(x, y, name); break;
                            case 7: upgradedRobot = new HideBot(x, y, name); break;
                            case 8: upgradedRobot = new ReflectShotBot(x, y, name); break;
                            case 9: upgradedRobot = new HealBot(x, y, name); break;
                            case 10: upgradedRobot = new BombBot(x, y, name); break;
                        }
                    } else if (currentPlayerType == SCOUT || currentPlayerType == TRACK){
                        uniform_int_distribution<> (1,8);
                        upgrade = posDistr(gen4);
                        switch(upgrade){
                            case 1: upgradedRobot = new LongShotBot(x, y, name); break;
                            case 2: upgradedRobot = new SemiAutoBot(x, y, name); break;
                            case 3: upgradedRobot = new ThirtyShotBot(x, y, name); break;
                            case 4: upgradedRobot = new JumpBot(x, y, name); break;
                            case 5: upgradedRobot = new HideBot(x, y, name); break;
                            case 6: upgradedRobot = new ReflectShotBot(x, y, name); break;
                            case 7: upgradedRobot = new HealBot(x, y, name); break;
                            case 8: upgradedRobot = new BombBot(x, y, name); break;
                        }
                    } else if (currentPlayerType == HIDE || currentPlayerType == JUMP){
                        uniform_int_distribution<> (1,8);
                        upgrade = posDistr(gen4);
                        switch(upgrade){
                            case 1: upgradedRobot = new LongShotBot(x, y, name); break;
                            case 2: upgradedRobot = new SemiAutoBot(x, y, name); break;
                            case 3: upgradedRobot = new ThirtyShotBot(x, y, name); break;
                            case 4: upgradedRobot = new ScoutBot(x, y, name); break;
                            case 5: upgradedRobot = new TrackBot(x, y, name); break;
                            case 6: upgradedRobot = new ReflectShotBot(x, y, name); break;
                            case 7: upgradedRobot = new HealBot(x, y, name); break;
                            case 8: upgradedRobot = new BombBot(x, y, name); break;
                        }
                    } else {
                        uniform_int_distribution<> (1,4);
                        upgrade = posDistr(gen4);
                        switch(upgrade){
                            case 1: upgradedRobot = new ScoutBot(x, y, name); break;
                            case 2: upgradedRobot = new TrackBot(x, y, name); break;
                            case 3: upgradedRobot = new ThirtyShotBot(x, y, name); break;
                            case 4: upgradedRobot = new JumpBot(x, y, name); break;
                            case 5: upgradedRobot = new HideBot(x, y, name); break;
                        }
                    }
                    upgradedRobot->addUpgrade(currentPlayer->upgradeCount);
                    upgradedRobot->setLives(currentPlayer->getLives());
                    upgradedRobot->setKills(currentPlayer->getKills());
                    upgradedRobot->setShells(currentPlayer->getShells());
                    // need to update in Battlefield the robot type 
                }
                break;
            case 4: // Move
                uniform_int_distribution<> dirDistr(-1, 1);
                x = dirDistr(gen2);
                y = dirDistr(gen3);
                currentPlayer->actionMove(battlefield, x, y);
                break;
        }
        battlefield->nextTurn();
    } while(!battlefield->getCurrentPlayer() && (battlefield->currentTurn() < battlefield->turns()));
    
    outFile.close();
    return 0;
}
