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
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Battlefield{
    private:
    int battlefieldCols = -1;
    int battlefieldRows = -1;

    int totalTurns = -1;
    int currentTurn = 0;

    int numOfRobots = -1;

    vector<Robot*> robots_;
    queue<Robot*> destroyedRobots_;
    queue<Robot*> waitingRobots_;

    vector <vector<string>> battlefield_; 

    public:
    //Get function 
    int battlefieldCols(){return battlefieldCols;}
    int battlefieldRows(){return battlefieldRows;}
    int turn(){return totalTurns;}
    int numOfRobots(){return numOfRobots;}

// Read file to initialize battleield and robots
void readFile(string filename){

}

void placeRobots()
{
    for(int i=0; i<battlefield_.size();++i){
        for (int j=0;j<battlefield_[i].size();++j){
            battlefield[i][j]=""; //empty string
        }
    }

    for (int i = 0;i<robots_.size();++i){
        if(robots_[i]->y() < battlefield_.size() && robots_[i]->x() < battlefield_[0].size()){
            battlefield_[robots_[i]->y()][robots_[i]->x()]=robots_[i]->id();
        }
        else{
            cout << "Error message: Invalid location for the robot " << robots_[i]->id() << endl;
            exit(1);
        }

    }
}

}