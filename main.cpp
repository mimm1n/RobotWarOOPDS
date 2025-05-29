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
s
using namespace std;

int main() {
    int option, x, y, choice, numOfKills;
    bool exitGame = false, invalidCoordinates;
    Battlefield* battlefield = new Battlefield();
    vector <int> targets {};
    battlefield->readFile("inputFile.txt");
    battlefield->placeRobots();

    do {
     GenericRobot* currentPlayer = battlefield->getCurrentPlayer();
        
        if(currentPlayer->getRobotType() == TRACK ){
           battlefield->displayBattlefield(-5, -5, targets);
        }else{
           battlefield->displayBattlefield(-5, -5 );
        }

        cout << "Player: " << currentPlayer->getRobotName() << endl; 
        cout << "What would you like to do?" << endl;
        cout << "1. Think" << endl;
        cout << "2. Look (x,y)" << endl;
        cout << "3. Fire (x,y)" << endl;
        cout << "4. Move" << endl;
        if (currentPlayer->getRobotType() != -1){
            if (currentPlayer->getRobotType() == SCOUT)
                cout << "5. Scout (see entire battlefield)" << endl;
            else if (currentPlayer->getRobotType() == TRACK)
                cout << "5. Track (plant tracker on another robot)" << endl;
            else if (currentPlayer->getRobotType() == LONGSHOT)
                cout << "5. Fire a long shot (shoot up to 3 squares away from you)" << endl;
            else if (currentPlayer->getRobotType() == SEMIAUTO)
                cout << "You have the SemiAuto upgrade! Each shot you fire shoots 3 consecutive shots." << endl;
            else if (currentPlayer->getRobotType() == JUMP)
                cout << "5. Jump (x,y)" << endl;
            else if (currentPlayer->getRobotType() == HIDE)
                cout << "5. Hide (can't be seen or shot at by other robots)" << endl;
            else if (currentPlayer->getRobotType() == REFLECTSHOT)
                cout << "You have the ReflectShot upgrade! If a robot shoots at you in the new few turns, it will be reflected back at them! >:) " << endl;
            else if (currentPlayer->getRobotType() == HEAL)
                cout << "You have the Heal upgrade! You have a total of " << currentPlayer->getLives() << " lives left." << endl;
            else if (currentPlayer->getRobotType() == BOMB)
                cout << "5. Bomb (shoot all 8 neighbouring locations)" << endl;
        }
        cout << "To quit the game enter any key other than the above options" << endl;
        cout << "Enter your next move option: ";
        cin >> option;

        switch(option){
            case 1: // Think
                currentPlayer->actionThink(battlefield);
                battlefield->nextTurn();
                break;
            case 2: // Look (x,y)
                cout << "Choose where you want to look" << endl;
                cout << "1. UpLeft\n2. Up\n3. UpRight\n4. Left\n5. Center\n 6. Right\n 7. DownLeft\n 8. Down\n 9. DownRight" << endl;
                cin  >> choice;
                switch(choice){
                    case 1: x = -1; y = 1; break;
                    case 2: x = 0; y = 1; break;
                    case 3: x = 1; y = 1; break;
                    case 4: x = -1; y = 0; break;
                    case 5: x = 0; y = 0; break;
                    case 6: x = 1; y = 0; break;
                    case 7: x = -1; y = -1; break;
                    case 8: x = 0; y = -1; break;
                    case 9: x = 1; y = -1; break;
                    default: x = 0; y = 0; break;
                }
                currentPlayer->actionLook(battlefield, x, y);
                break;
            case 3: // Fire (x,y)
                cout << "Choose where you want to shoot" << endl;
                cout << "1. UpLeft\n2. Up\n3. UpRight\n4. Left\n5. Right\n 6. DownLeft\n 7. Down\n 8. DownRight" << endl;
                cin  >> choice;
                switch(choice){
                    case 1: x = -1; y = 1; break;
                    case 2: x = 0; y = 1; break;
                    case 3: x = 1; y = 1; break;
                    case 4: x = -1; y = 0; break;
                    case 5: x = 1; y = 0; break;
                    case 6: x = -1; y = -1; break;
                    case 7: x = 0; y = -1; break;
                    case 8: x = 1; y = -1; break;
                    default: x = 0; y = 0; break;
                }
                numOfKills = currentPlayer->getKills();
                currentPlayer->actionFire(battlefield, x, y);
                if(numOfKills<currentPlayer->getKills() && currentPlayer->toUpgrade()){
                    cout << "Congratulations! You shoot a robot. Choose your upgrade: " << endl;
                    cout << "1. Scout Bot (see entire battlefield)\n2. Track Bot (plant tracker on another robot) \n3. ";
                    cout << "Long Shot Bot (shoot up to 3 squares away from you)\n4. Semi Auto Bot (each shot you fire shoots 3 consecutive shots)\n";
                    cout << "5. Thirty Shot Bot (get 30 shells but replaces old shells)\n6. Jump Bot (jump to anywhere on battlefield)\n";
                    cout << "7. Hide Bot (can't be seen or shot at by other robots)\n8. Reflect Shot Bot (if a robot shoots at you it will be reflected back at them)\n";
                    cout << "9. Heal Bot (gain 3 more lives)\n8. Bomb Bot (shoot all 8 neighbouring locations)\n";
                    cin >> choice;
                    // switch(choice){
                    //     case 1: currentPlayer->upgradeRobot(battlefield, SCOUT); break;
                    //     case 2: currentPlayer->upgradeRobot(battlefield, TRACK); break;
                    //     case 3: currentPlayer->upgradeRobot(battlefield, LONGSHOT); break;
                    //     case 4: currentPlayer->upgradeRobot(battlefield, SEMIAUTO); break;
                    //     case 5: currentPlayer->upgradeRobot(battlefield, THIRTYSHOT); break;
                    //     case 6: currentPlayer->upgradeRobot(battlefield, JUMP); break;
                    //     case 7: currentPlayer->upgradeRobot(battlefield, HIDE); break;
                    //     case 8: currentPlayer->upgradeRobot(battlefield, REFLECTSHOT); break;
                    //     case 9: currentPlayer->upgradeRobot(battlefield, HEAL); break;
                    //     case 10: currentPlayer->upgradeRobot(battlefield, BOMB); break;
                    // }
                }
                battlefield->nextTurn();
                break;
            case 4: // Move
                cout << "Choose where you want to move" << endl;
                cout << "1. UpLeft\n2. Up\n3. UpRight\n4. Left\n5. Right\n 6. DownLeft\n 7. Down\n 8. DownRight" << endl;
                cin  >> choice;
                switch(choice){
                    case 1: x = -1; y = 1; break;
                    case 2: x = 0; y = 1; break;
                    case 3: x = 1; y = 1; break;
                    case 4: x = -1; y = 0; break;
                    case 5: x = 1; y = 0; break;
                    case 6: x = -1; y = -1; break;
                    case 7: x = 0; y = -1; break;
                    case 8: x = 1; y = -1; break;
                    default: x = 0; y = 0; break;
                }
                currentPlayer->actionMove(battlefield, x, y);
                battlefield->nextTurn();
                break;
            case 5: // Upgrades if upgraded robot, quit game if not 
                if(currentPlayer->getRobotType() != -1){ 
                    if (currentPlayer->getRobotType() == SCOUT){
                        currentPlayer->actionLook(battlefield, -10, -10);
                    } else if (currentPlayer->getRobotType() == TRACK){
                        cout << " who do you want to track ?" << endl;
                        // currentPlayer->actionLook(battlefield, x, y);
                    } else if (currentPlayer->getRobotType() == LONGSHOT){
                        // bool tooLongShot;
                        // do {
                        //     cout << "LongShot Upgrade allows you to shoot up to three squares away from you !" << endl;
                        //     cout << "Enter the x and y coordinate of the location you want to shoot at: (separated by a space)" << endl;
                        //     cin >> x >> y;
                        //     invalidCoordinates = x < 0 || x >= battlefield->battlefieldCols() || y < 0 || y >= battlefield->battlefieldRows();
                        //     tooLongShot = x < (currentPlayer->getRobotX() - 4 ) || x > (currentPlayer->getRobotX() + 4 ) || y < (currentPlayer->getRobotY() - 4 ) || y > (currentPlayer->getRobotY() + 4);
                        //     if (invalidCoordinates || tooLongShot)
                        //         cout << "Invalid location entered!" << endl;
                        // } while (invalidCoordinates || tooLongShot);
                        // numOfKills = currentPlayer->getKills();
                        // currentPlayer->actionFire(battlefield, x, y);
                        // if(numOfKills<currentPlayer->getKills() && currentPlayer->toUpgrade()){
                        //     cout << "Congratulations! You bomb a robot. Choose your upgrade: " << endl;
                        //     cout << "1. ScoutBot (see entire battlefield)\n2. TrackBot (plant tracker on another robot) \n3. ";
                        //     cout << "JumpBot (jump to anywhere on battlefield)\n4. Hide (can't be seen or shot at by other robots)\n" << endl;
                        //     cin >> choice;
                        //     switch(choice){
                        //         case 1: currentPlayer->upgradeRobot(SCOUT); break;
                        //         case 2: currentPlayer->upgradeRobot(TRACK); break;
                        //         case 3: currentPlayer->upgradeRobot(JUMP); break;
                        //         case 4: currentPlayer->upgradeRobot(HIDE); break;
                        //     }
                        // }
                        battlefield->nextTurn();
                    } else if (currentPlayer->getRobotType() == JUMP){
                        do {
                            cout << "Enter the x and y coordinate of the location you want to jump to: (separated by a space)" << endl;
                            cin >> x >> y;
                            invalidCoordinates = x < 0 || x >= battlefield->battlefieldCols() || y < 0 || y >= battlefield->battlefieldRows();
                            if (invalidCoordinates)
                                cout << "Invalid location entered!" << endl;
                        } while (invalidCoordinates);
                        currentPlayer->actionMove(battlefield, x, y);
                        battlefield->nextTurn();
                    } else if (currentPlayer->getRobotType() == HIDE){
                        // how to deploy this?? 
                        currentPlayer->actionMove(battlefield, x, y);
                        battlefield->nextTurn();
                    } else if (currentPlayer->getRobotType() == BOMB){
                        numOfKills = currentPlayer->getKills();
                        currentPlayer->actionFire(battlefield, -5, -5);
                        if(numOfKills<currentPlayer->getKills() && currentPlayer->toUpgrade()){
                            cout << "Congratulations! You bomb a robot. Choose your upgrade: " << endl;
                            cout << "1. ScoutBot (see entire battlefield)\n2. TrackBot (plant tracker on another robot) \n3. ";
                            cout << "JumpBot (jump to anywhere on battlefield)\n4. Hide (can't be seen or shot at by other robots)\n" << endl;
                            cin >> choice;
                            // switch(choice){
                            //     case 1: currentPlayer->upgradeRobot(battlefield, SCOUT); break;
                            //     case 2: currentPlayer->upgradeRobot(battlefield, TRACK); break;
                            //     case 3: currentPlayer->upgradeRobot(battlefield, JUMP); break;
                            //     case 4: currentPlayer->upgradeRobot(battlefield, HIDE); break;
                            // }
                        }
                        battlefield->nextTurn();
                    }
                } else {
                    exitGame = true;
                }
                break;
            default: // Quit game
                exitGame = true;
                break;
        }
    } while(!exitGame && (battlefield->currentTurn() < battlefield->turns()));
    
    return 0;
}



