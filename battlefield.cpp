///*********************************************************   
// Program: Battlefield.cpp   
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

#include "Battlefield.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <random>
using namespace std;



void Battlefield::readFile(string filename) {

  ifstream infile(filename);
  string line;

  //find matrix
  getline(infile, line); //read first line
  size_t pos1 = line.find(":");
  if (pos1 != string::npos){
  string numStr = line.substr(pos1+2);
  stringstream ss(numStr);
  string colstr, rowstr;
  ss >> rowstr >> colstr;
  battlefieldRows_ = stoi(rowstr);
  battlefieldCols_ = stoi(colstr);
  }

battlefield_ = vector<vector<string>>(battlefieldRows_+1, vector<string>(battlefieldCols_+1, "")); //2D vector for rows and columns

  //find total turn
  getline(infile, line); //read second line
  size_t pos2 = line.find(":");
  if (pos2 != string::npos){
  string numStr2 = line.substr(pos2+2);
  totalTurns_ = stoi(numStr2);

  }
  
  //find total robot
  getline(infile, line);// read the third line
  size_t pos3 = line.find(":");
  if (pos3 != string::npos){
  string numStr3 = line.substr(pos3+2);
  numOfRobots_ = stoi(numStr3);
  }

cout << battlefieldCols_ << " " << battlefieldRows_ << " " << totalTurns_ << " " << numOfRobots_ << endl;

  //find robot name and position
for (int i = 0; i < numOfRobots_; i++) {
    getline(infile, line);
    istringstream robotLine(line);
    string name, xStr, yStr;
    int x, y;
    robotLine >> name >> yStr >> xStr;
    if (xStr == "random" && yStr == "random"){
      x = rand() % (battlefieldRows_)+1;
      y = rand() % (battlefieldCols_)+1;
    }else{
      x = stoi(xStr);
      y = stoi(yStr);
    }
//
}

}


/*void Battlefield::placeRobots(){
for(int i=0;i<battlefield_.size(); i++){
for (int j=0; i<battlefield_[i].size(); j++){
  battlefield_[i][j]="";
}
  }
  for (int i=0;i<robots_.size(); i++){
    if(robots_[i].getRobotY()<battlefield_.size() && robots_[i].getRobotX()<battlefield_[0].size()){
      battlefield_[robots_[i].getRobotY()][robots_[i].getRobotX()]=robots_[i].getRobotName();
    }
    else
    {
      cout << "Error message: Invalid location for the robot " << robots_[i].getRobotName() << endl;
      exit(1);
    }
  }
}*/

void Battlefield::displayBattlefield() const{
  cout << "Display Battlefield";
  cout << endl << "    ";
  for (int j=0; j< battlefield_[0].size();j++){
    cout << "   " << right << setfill('0') << setw(2) << j << "";
  }
  cout << endl;
 for (int i=0; i< battlefield_.size();i++){
    cout << "     ";
    for (int j = 0; j < battlefield_[i].size(); j++)
    cout << "+----";
  cout << "+" << endl;
  cout << "   " << right << setfill('0') << setw(2) << i;
  for (int j = 0;j <battlefield_[0].size(); j++)
  {
    if(battlefield_[i][j] == "")
    {
      cout << "|" << "    ";
    }
    else
    {
      cout << "|" << left << setfill(' ') << setw(10) << battlefield_[i][j];
    }
  }
  cout << "|" << endl;
  }
  cout << "     ";
  for (int j = 0;j<battlefield_[0].size();j++)
  cout << "+----";
  cout << "+" << endl;
}

// int main() {
//     cout << "Hello World!" << endl;
//     Battlefield battlefield;
//     battlefield.readFile("inputFile.txt");
//     battlefield.displayBattlefield();
    
//     return 0;
// }




