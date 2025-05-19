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

#include "Robot.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <cstdlib>
#include <string>
using namespace std;


class Battlefield{
    private:
    int battlefieldCols_ = -1; //variable to assign number of columns
    int battlefieldRows_ = -1; //variable to assign number of rows

    int totalTurns_ = -1; //variable to assign total turns
    int currentTurn_ = 0; //??

    int numOfRobots_ = -1; //variable to assign number of robots

    vector<Robot*> robots_;  //dynamic vecot robots_ points to Robot* object
    queue<Robot*> destroyedRobots_;
    queue<Robot*> waitingRobots_;

vector <vector<string>> battlefield_; 

    public:
    //Get function 
    int battlefieldCols(){return battlefieldCols_;}
    int battlefieldRows(){return battlefieldRows_;}
    int turn(){return totalTurns_;}
    int numOfRobots(){return numOfRobots_;}

    void readFile(string filename);
    void placeRobots();

};

// Read file to initialize battleield and robots
void Battlefield::readFile(string filename){

ifstream infile(filename);
string line; 

getline(infile, line); 
istringstream iss(line);
iss >> battlefieldRows_ >> battlefieldCols_; //stores the matrix to columns and rows

battlefield_.resize(battlefieldRows_, vector<string>(battlefieldCols_,""));
getline(infile, line); //read the second line
totalTurns_= stoi(line); //stoi convert string to int
getline(infile, line); //read the third line
numOfRobots_ = stoi(line);

for (int i = 0; i<numOfRobots_;i++){
    getline(infile, line);
    istringstream robotLine(line);
    string name, robotType;
    int x, y;
    robotLine >> robotType >> name >> x >> y;
    robots_.push_back(new Robot(x, y, name, robotType));
    cout << "Robot added: " << name << " at (" << x << "," << y << ")" << endl; //try

}
}

void Battlefield::placeRobots()
{
    for(int i=0; i<battlefield_.size();++i){
        for (int j=0;j<battlefield_[i].size();++j){
            battlefield_[i][j]=""; //empty string
        }
    }

    for (int i = 0;i<robots_.size();++i){
        if(robots_[i]->getRobotY() < battlefield_.size() && robots_[i]->getRobotX() < battlefield_[0].size()){
            battlefield_[robots_[i]->getRobotY()][robots_[i]->getRobotX()]=robots_[i]->getRobotName();
        }
        else{
            cout << "Error message: Invalid location for the robot " << robots_[i]->getRobotName() << endl;
            exit(1);
        }

    }
}

int main() {
    Battlefield battlefield;
    battlefield.readFile("inputFile.txt");

    return 0;
}