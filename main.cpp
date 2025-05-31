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
#include <queue>
using namespace std;

enum RobotType {GENERIC, SCOUT, TRACK, LONGSHOT, SEMIAUTO, THIRTYSHOT, JUMP, HIDE, REFLECTSHOT, HEAL, BOMB};

string robotTypeName(int robotType);
/**********************************************************************
 * CLASS DEFINITIONS
 *********************************************************************/
class Battlefield;
class GenericRobot;

/**********************************************************************
 * Robot Class
 *********************************************************************/
class Robot{
    private:
        int robotX = -1, robotY = -1; // x and y coordinates of the robot (x,y)
        const int MAX_UPGRADES = 3;
        string robotName = ""; // The name of this robot        
    
    protected:
        int killCount = 0; // Number of robots this robot managed to destroy/kill
        int lives = 3; // Number of lives of this robot (initial is 3)
        int robotId = -1; // The ID of this robot
        int robotType = GENERIC; // This robot's type; Jump, Hide, etc.
        int upgradeCount = 0;
        int shells = 10;

    public:
        Robot(int x, int y, string name); // Constructor
        virtual ~Robot(){} // Destructor

        // Set and get the x coordinate of this robot
        void setRobotID(int id) { robotId = id; }
        int getRobotID() const { return robotId; }
        
        // Set and get the x coordinate of this robot
        void setRobotX(int x) { robotX = x; }
        int getRobotX() const { return robotX; }

        // Set and get the y coordinate of this robot
        void setRobotY(int y) { robotY = y; }
        int getRobotY() const { return robotY; }

        // Set and get the shells of this robot
        void setShells(int num) { shells = num; }
        int getShells() const { return shells; }

        // Get the name of this robot(fixed so can't set)
        string getRobotName() const { return robotName; }

        void addLife() { lives++; } // adds a life to the robot's lives
        void reduceLife();
        int getLives() const { return lives; }  // gets the number of lives 
        void setLives(int live) { lives = live; } // sets the number of lives
        bool isAlive() const; // Checks if this robot's lives count is more than 0
        
        int getKills() const { return killCount; } // gets number of kills 
        void setKills(int kills) { killCount = kills; } // sets number of kills
        void incrementKills() { killCount++; } // increases kill count by 1

        int getUpgradeCount() const { return upgradeCount; } // gets the current upgrade count
        bool canUpgrade() const;
        void addUpgrade(int currentUpgradeCount) { upgradeCount = currentUpgradeCount + 1; } // adds 1 to the upgrade count
        void isUpgrading(int upgrades, int live, int kills, int shells);

        virtual bool isHidden() { return false; } // checks if the robot is hiding
        virtual bool isReflecting() { return false; } // checks if the robot is reflecting shots

        virtual void actions(Battlefield* battlefield, ostream &cout) = 0;

        // Set and get the robot's type
        virtual void setRobotType(int type) = 0;
        virtual int getRobotType() const = 0;
        friend ostream &operator<<(ostream &cout, const Robot &r);
};

/**********************************************************************
 * Robot Action Classes 
 *********************************************************************/
class SeeingRobot : virtual public Robot{
    public:
        virtual ~SeeingRobot(){}
        virtual void actionLook(Battlefield* battlefield, int x, int y, ostream &cout) = 0;
};

class ShootingRobot : virtual public Robot{
    public:
        ShootingRobot(int x, int y, string name):Robot(x, y, name){}
        virtual ~ShootingRobot(){}
        virtual void actionFire(Battlefield* battlefield, int x, int y, ostream &cout) = 0;
};

class ThinkingRobot : virtual public Robot{
    public:
        virtual ~ThinkingRobot(){}
        virtual void actionThink(Battlefield* battlefield, ostream &cout) = 0;
};

class MovingRobot : virtual public Robot{
    public:
        MovingRobot(int x, int y, string name):Robot(x, y, name){}
        virtual ~MovingRobot(){}
        virtual void actionMove(Battlefield* battlefield, int x, int y, ostream &cout) = 0;
};

/**********************************************************************
 * Battlefield Class
 *********************************************************************/
class Battlefield {
    private:
        int battlefieldCols_ = -1; // variable to assign number of columns
        int battlefieldRows_ = -1; // variable to assign number of rows

        int totalTurns_ = -1; // variable to assign total turns
        int currentTurn_ = 1; 
        int currentPlayer = 0;
    

        int numOfRobots_ = -1; // variable to assign number of robots

        vector<Robot *> robots_; 
        vector<Robot *> upgradedRobots_[11];
        queue<Robot *> destroyedRobots_;
        queue<Robot *> waitingRobots_;  
        vector < vector <string> > battlefield_;
        friend class GenericRobot;
        
    public:
        // Get function
        int battlefieldCols() { return battlefieldCols_; }
        int battlefieldRows() { return battlefieldRows_; }
        int turns() { return totalTurns_; }
        int numOfRobots() { return numOfRobots_; }
        int currentTurn() { return currentTurn_; }
        string getPlayer(int x, int y) { return battlefield_[y][x]; }
        vector <Robot *> getAllRobots() const { return robots_; }
        Robot* getCurrentPlayer() const { return waitingRobots_.front(); }
        
        void readFile(string filename);
        void placeRobots();
        void displayBattlefield(int x, int y, ostream &cout) const;
        void respawnRobot(int x);
        void nextTurn();
        RobotType findTargetRobot(GenericRobot* target);
        void robotUpgrade(Robot* upgradeRobot_);
        void robotMove(int robotId, int x, int y);
        friend ostream &operator<<(ostream &cout, const Battlefield &b) ;
};

/**********************************************************************
 * GenericRobot Class
 *********************************************************************/
class GenericRobot : public ShootingRobot, public MovingRobot, public SeeingRobot, public ThinkingRobot {
    private:
        static int robotIncrement;
        // int robotId;
        // int upgradeCount = 0;
        // const int MAX_UPGRADE = 3;
        // Robot* robotUpgraded = nullptr;
        // bool upgrade = false;

    public:
        GenericRobot(string name, int x, int y):Robot(x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){
            robotId = robotIncrement;
            robotIncrement++;
        }

        //int getRobotID() const;
        void setRobotType(int type) override { robotType = type; }
        int getRobotType() const override { return robotType; }

        virtual void actions(Battlefield* battlefield, ostream &cout) override;
        virtual void actionThink(Battlefield* battlefield, ostream &cout) override;
        virtual void actionLook(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionMove(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionFire(Battlefield* battlefield, int x, int y, ostream &cout) override;
        
        void actionRand(Battlefield* battlefield);
        // void upgradeRobot(Battlefield* battlefield, int upgradeType);
        // bool toUpgrade() const;
        // void ToGeneric(int upgradeType);
        //int getUpgradeCount() const;
};

/**********************************************************************
 * Upgraded Robot Classes 
 *********************************************************************/
class HideBot : public MovingRobot,public ShootingRobot, public SeeingRobot, public ThinkingRobot{
    private:
        int hideTurnsUsed = 0;
        const int MAX_HIDE_TURNS = 3;
        bool isHidden_ = true;

    public:
        HideBot(int x, int y, string name):Robot(x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){}
        virtual void actions(Battlefield* battlefield, ostream &cout) override;
        virtual void actionThink(Battlefield* battlefield, ostream &cout) override;
        virtual void actionLook(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionMove(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionFire(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual bool isHidden() override;
        //int hidesLeft() const;
        void setRobotType(int type) override { robotType = HIDE; }
        int getRobotType() const override { return HIDE; }
};

class JumpBot : public MovingRobot,public ShootingRobot, public SeeingRobot, public ThinkingRobot {
    private:
        int jumpsUsed = 0;
        const int MAX_JUMPS = 3;

    public:
        JumpBot(int x, int y, string name):Robot(x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){}
        virtual void actions(Battlefield* battlefield, ostream &cout) override;
        virtual void actionThink(Battlefield* battlefield, ostream &cout) override;
        virtual void actionLook(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionMove(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionFire(Battlefield* battlefield, int x, int y, ostream &cout) override;
        void setRobotType(int type) override { robotType = JUMP; }
        int getRobotType() const override { return JUMP; }
};


class LongShotBot : public ShootingRobot , public MovingRobot, public SeeingRobot, public ThinkingRobot{
    public:
        LongShotBot(int x, int y, string name):Robot( x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){}
        virtual void actions(Battlefield* battlefield, ostream &cout) override;
        virtual void actionThink(Battlefield* battlefield, ostream &cout) override;
        virtual void actionLook(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionMove(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionFire(Battlefield* battlefield, int x, int y, ostream &cout) override;
        void setRobotType(int type) override { robotType = LONGSHOT; }
        int getRobotType() const override { return LONGSHOT;}
};

class SemiAutoBot : public ShootingRobot , public MovingRobot, public SeeingRobot, public ThinkingRobot {
    private:
        int shotsFired = 0;
        const int MAX_SHOTS_FIRED = 3;
    public:
        SemiAutoBot(int x, int y, string name):Robot( x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){}
        virtual void actions(Battlefield* battlefield, ostream &cout) override;
        virtual void actionThink(Battlefield* battlefield, ostream &cout) override;
        virtual void actionLook(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionMove(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionFire(Battlefield* battlefield, int x, int y, ostream &cout) override;
        void setRobotType(int type) override { robotType = SEMIAUTO; }
        int getRobotType() const override { return SEMIAUTO; }
};

class ThirtyShotBot : public ShootingRobot , public MovingRobot, public SeeingRobot, public ThinkingRobot {
    public:
        ThirtyShotBot(int x, int y, string name):Robot( x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){}
        virtual void actions(Battlefield* battlefield, ostream &cout) override;
        virtual void actionThink(Battlefield* battlefield, ostream &cout) override;
        virtual void actionLook(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionMove(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionFire(Battlefield* battlefield, int x, int y, ostream &cout) override;
        void setRobotType(int type) override { robotType = THIRTYSHOT; }
        int getRobotType() const override { return THIRTYSHOT;}
};


class HealBot : public ShootingRobot, public MovingRobot, public SeeingRobot, public ThinkingRobot {
    public:
        HealBot(int x, int y, string name):Robot( x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){}
        virtual void actions(Battlefield* battlefield, ostream &cout) override;
        virtual void actionThink(Battlefield* battlefield, ostream &cout) override;
        virtual void actionLook(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionMove(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionFire(Battlefield* battlefield, int x, int y, ostream &cout) override;
        void setRobotType(int type) override { robotType = HEAL; }
        int getRobotType() const override { return HEAL; }
};

class BombBot : public ShootingRobot, public MovingRobot, public SeeingRobot, public ThinkingRobot {
    private:
        int bombs = 1;
    public:
        BombBot(int x, int y, string name):Robot(x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){}
        virtual void actions(Battlefield* battlefield, ostream &cout) override;
        virtual void actionThink(Battlefield* battlefield, ostream &cout) override;
        virtual void actionLook(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionMove(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionFire(Battlefield* battlefield, int x, int y, ostream &cout) override;
        void setRobotType(int type) override { robotType = BOMB; }
        int getRobotType() const override { return BOMB; }
};

class ReflectShotBot : public ShootingRobot , public MovingRobot, public SeeingRobot, public ThinkingRobot{
    private:
        int reflect = 1;
        bool isReflect_ = true;
    public:
        ReflectShotBot(int x, int y, string name):Robot( x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){}
        virtual void actions(Battlefield* battlefield, ostream &cout) override;
        virtual void actionThink(Battlefield* battlefield, ostream &cout) override;
        virtual void actionLook(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionMove(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionFire(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual bool isReflecting() override;
        void setRobotType(int type) override { robotType = REFLECTSHOT; }
        int getRobotType() const override { return REFLECTSHOT; }
 
};

class ScoutBot : public SeeingRobot , public MovingRobot, public ShootingRobot, public ThinkingRobot{
    private:
        int lookCount = 0;
        const int MAX_LOOKS = 3;

    public:
        ScoutBot(int x, int y, string name):Robot( x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){}
        virtual void actions(Battlefield* battlefield, ostream &cout) override;
        virtual void actionThink(Battlefield* battlefield, ostream &cout) override;
        virtual void actionLook(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionMove(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionFire(Battlefield* battlefield, int x, int y, ostream &cout) override;
        void setRobotType(int type) override { robotType = SCOUT; }
        int getRobotType() const override { return SCOUT; }
};

class TrackBot : public SeeingRobot  , public MovingRobot, public ShootingRobot, public ThinkingRobot {
    private:
        int trackersUsed = 0;
        const int MAX_TRACKERS = 3;
        vector<int> targets;

    public:
        TrackBot(int x, int y, string name):Robot(x, y, name), MovingRobot(x, y, name), ShootingRobot(x, y, name), SeeingRobot(), ThinkingRobot(){}
        virtual void actions(Battlefield* battlefield, ostream &cout) override;
        virtual void actionThink(Battlefield* battlefield, ostream &cout) override;
        virtual void actionLook(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionMove(Battlefield* battlefield, int x, int y, ostream &cout) override;
        virtual void actionFire(Battlefield* battlefield, int x, int y, ostream &cout) override;
        vector<int> getTrackedTargets() { return targets; }
        void setRobotType(int type) override { robotType = TRACK; }
        int getRobotType() const override { return TRACK; }
};

int GenericRobot::robotIncrement = 1;

ostream &operator<<(ostream &cout, const Robot &r){
    
        cout << r.robotName << " GR0" << to_string(r.robotId) << endl;
        cout << setfill(' ') << setw(22) << "Action Log" << endl;
        cout << "----------------------------------" << endl;
        cout <<  "GR0" << to_string(r.robotId) << " at (" << r.robotX << ", " << r.robotY << ")" << endl << endl;
        return cout; 
}

ostream &operator<<(ostream &cout, const Battlefield &b) {
      b.displayBattlefield(-10,-10, cout);
      string inString = to_string(b.currentTurn_);
      cout <<  inString << " " << endl;;
      
      return cout;
}


/**********************************************************************
 * MAIN FUNCTION
 *********************************************************************/
int main() {
    ofstream outFile;
    Battlefield* battlefield = new Battlefield();
    battlefield->readFile("inputFile.txt");
    outFile.open("outputFile.txt");
    battlefield->placeRobots();
    Robot* currentPlayer = new GenericRobot("test", 0,0);
    Robot* upgradedRobot = new GenericRobot("test", 0, 0);
    int move, x, y, kills, upgrade, currentPlayerType;
    string name;
    
    do {
        currentPlayer = battlefield->getCurrentPlayer();
        battlefield->displayBattlefield(-10,-10, cout);
        cout << "Current turn: " << battlefield->currentTurn() << endl;
        cout << robotTypeName(battlefield->getCurrentPlayer()->getRobotType()) << " ";
        cout << "Current Player: " << battlefield->getCurrentPlayer()->getRobotName() << " GR0"<< battlefield->getCurrentPlayer()->getRobotID() << endl;
        //outFile << battlefield->displayBattlefield(-5,-5);
        cout << setfill(' ') << setw(22) << "Action Log" << endl;
        cout << "----------------------------------" << endl;
        // outFile << setw(22) << "Action Log" << endl;
        // outFile << "----------------------------------" << endl;
        currentPlayer->actions(battlefield, cout);
        outFile << *battlefield;
        outFile << *currentPlayer;
        battlefield->nextTurn();
        


    } while(battlefield->getCurrentPlayer() && (battlefield->currentTurn() < battlefield->turns()));
    cout << "End Game." << endl;
    outFile.close();

    return 0;
}

/**********************************************************************
 * FUNCTION DEFINTIONS
 *********************************************************************/
string robotTypeName(int robotType){
    switch(robotType){
        case 0: return "GenericRobot";
        case 1: return "ScoutBot";
        case 2: return "TrackBot";
        case 3: return "LongShotBot";
        case 4: return "SemiAutoBot";
        case 5: return "ThirtyShotBot";
        case 6: return "JumpBot";
        case 7: return "HideBot";
        case 8: return "ReflectShotBot";
        case 9: return "HealBot";
        case 10: return "BombBot";
    }
    return "";
}

/**********************************************************************
 * Robot Functions
 *********************************************************************/
/**********************************************************************
 * Robot (constructor)
 * task: Constructs a robot object by assigning it's x and y 
 *       coordinates, its name, and its type 
 * @param x - x coordinate
 *        y - y coordinate
 *        name - robot's name
 *********************************************************************/
Robot::Robot(int x, int y, string name){
    setRobotX(x);
    setRobotY(y);
    robotName = name;
}

/**********************************************************************
 * reduceLife
 * task: Decreases the lives count by 1 if the robot isAlive
 *********************************************************************/
void Robot::reduceLife(){
    if(isAlive()){
        lives--;
    }
    else{
    lives = 0;}
}

/**********************************************************************
 * isAlive
 * task: Checks if the lives count is greater than 0
 * @return true if the lives count is greater than 0
 *********************************************************************/
bool Robot::isAlive() const{
    if(lives<=0){
        cout << "Robot " << robotName << " is dead!";
        return false;
    }
    return true;
}

/**********************************************************************
 * canUpgrade
 * task: Checks if the upgrade count is lesser than max upgrades
 * @return true if it hasn't reached max upgrades
 *********************************************************************/
bool Robot::canUpgrade() const{
    if(upgradeCount < MAX_UPGRADES){
        return true;
    }
    return false;
}

void Robot::isUpgrading(int upgrades, int live, int kills, int shells){
    setRobotType(0);
    addUpgrade(upgrades);
    setLives(live);
    if (robotType == HEAL){
        addLife();
        addLife();
        addLife();
    }
    setKills(kills);
    setShells(shells);
    if (robotType == THIRTYSHOT)
        setShells(30);
}

/**********************************************************************
 * Battlefield Functions
 *********************************************************************/
/**********************************************************************
 * readFile
 * task: 
 * @param filename - 
 *********************************************************************/
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

    battlefield_ = vector<vector<string>>(battlefieldRows_+ 1, vector<string>(battlefieldCols_+ 1, "")); //2D vector for rows and columns

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
            x = rand() % (battlefieldRows_);
            y = rand() % (battlefieldCols_);
            cout << x << y << endl;
        } else {
            x = stoi(xStr);
            y = stoi(yStr);
        }
        robots_.push_back(new GenericRobot(name,x,y));
    }
}

/**********************************************************************
 * placeRobots
 * task: 
 *********************************************************************/
void Battlefield::placeRobots(){
    for(int i=0;i<battlefield_.size(); i++){
        for (int j=0; j<battlefield_[i].size(); j++){
            battlefield_[i][j]="";
        }
    }

    for (int i=0;i<robots_.size(); i++){
        int y = robots_[i]->getRobotY();
        int x = robots_[i]->getRobotX();

        if(y < battlefield_.size() && x < battlefield_[0].size()){
            battlefield_[y][x]= to_string(robots_[i]->getRobotID());
        } else {
            cout << "Error message: Invalid location for the robot " << robots_[i]->getRobotName() << endl;
            exit(1);
        }
        waitingRobots_.push(robots_[i]);
    }

};

/**********************************************************************
 * displayBattlefield
 * task: Displays the battlefield and any needed players
 * x and y are the center of the nine square grid when looking
 * when x = -10 and y = -10, all robots displayed on field (scoutBot)
 * when x = -5 and y = -5 only current player's position displayed
 * @param x - the x coordinate of the nine square
 *        y - the y coordinate of the nine square
 *********************************************************************/
void Battlefield::displayBattlefield(int x, int y, ostream &cout) const{
    string playerStr;
    int id;
    cout << "Display Battlefield";
    cout << endl << "    ";

    for (int j=0; j< battlefield_[0].size();j++)
        cout << "   " << right << setfill('0') << setw(2) << j << "";
    cout << endl;

    for (int i=0; i< battlefield_.size();i++){
        cout << "     ";
        for (int j = 0; j < battlefield_[i].size(); j++)
            cout << "+----";
        cout << "+" << endl;
        cout << "   " << right << setfill('0') << setw(2) << i;

        for (int j = 0;j <battlefield_[0].size(); j++){
            if(battlefield_[i][j] == ""){
                cout << "|" << "    ";
            } else { //placesRobot
                if(x == -10  && y == -10){ //scout  
                    cout << "|" << "GR";
                    cout << "0";   
                    cout << battlefield_[i][j];
                } else {
                    playerStr = battlefield_[i][j];
                    id = stoi(playerStr);
                    if (playerStr != "" && id == getCurrentPlayer()->getRobotID()){ //general
                        cout << "|" << "GR";
                        cout << "0";   
                        cout << battlefield_[i][j];
                    } else {
                        cout << "|" << "    ";
                    }
                    
                    if (y == i-1 || y == i || y == i+1 || x == j-1 || x == j || x == j+1){ //look
                        cout << "|" << "GR";
                        cout << "0";   
                        cout << battlefield_[i][j];
                    }
                }
            }
        }
        cout << "|" << endl;
    }
    cout << "     ";
    for (int j = 0;j<battlefield_[0].size();j++)
        cout << "+----";
    cout << "+" << endl;
}

/**********************************************************************
 * respawnRobot
 * task: 
 * @param index - 
 *********************************************************************/
void Battlefield::respawnRobot(int robotId){
    Robot* died = nullptr;

    for (Robot* robot : robots_) {
        if (robot->getRobotID() == robotId) {
            died = robot;
            break;
        }
    }

    if (died == nullptr) return;

    int size = waitingRobots_.size();
    for (int i = 0; i < size; i++) {
        Robot* current = waitingRobots_.front();
        waitingRobots_.pop();
        
        if (current->getRobotID() != died->getRobotID()) {
            waitingRobots_.push(current);
        }
    }
 cout << died->getLives() << endl;
    if (!died->isAlive()) {
        destroyedRobots_.push(died);
        return;
    }

    int newX, newY;
    string name = died->getRobotName();
    do {
        newX = rand() % battlefieldRows_;
        newY = rand() % battlefieldCols_;
    } while (!battlefield_[newY][newX].empty());

    GenericRobot* respawn = new GenericRobot(name, newX, newY);

    respawn->isUpgrading(died->getUpgradeCount() - 1, died->getLives(), died->getKills(), died->getShells());
    respawn->setRobotID(robotId);

    // Clear the old battlefield position if valid
    int oldX = died->getRobotX();
    int oldY = died->getRobotY();

    if (oldY >= 0 && oldY < battlefieldRows_ && oldX >= 0 && oldX < battlefieldCols_) {
        battlefield_[oldY][oldX] = "";
    }

    // Update battlefield with new position
    battlefield_[newY][newX] = to_string(respawn->getRobotID());

    // Add the new robot to the queue
    waitingRobots_.push(respawn);
    cout << "Robot " << died->getRobotName() << " has respawned at (" << newX << ", " << newY << ")" << endl;
}

/**********************************************************************
 * nextTurn
 * task: 
 *********************************************************************/
void Battlefield::nextTurn(){
    currentTurn_++;
    Robot* front = waitingRobots_.front();
    cout << "Current Player: " << front->getRobotName() << endl;
    waitingRobots_.push(front);
    waitingRobots_.pop();
    cout << "Next Player: " << waitingRobots_.front()->getRobotName() << endl;
}

RobotType Battlefield::findTargetRobot(GenericRobot* target) {
    for (int i = 0; i <= BOMB; ++i){
        for (Robot* robot : upgradedRobots_[i]){
            if (robot == target)
                return static_cast<RobotType>(i);
        }
    }
    return GENERIC;
}

/**********************************************************************
 * robotUpgrade
 * task: 
 *********************************************************************/
 void Battlefield::robotUpgrade(Robot* upgradeRobot_){
    int size = waitingRobots_.size();

    for(int i = 0; i<size;i++){
        Robot* current = waitingRobots_.front();
    if(current){

       if (current->getRobotID() != upgradeRobot_->getRobotID()){
            waitingRobots_.pop();
            waitingRobots_.push(current);
        } else {
            waitingRobots_.pop();
            waitingRobots_.push(upgradeRobot_);
        }
    }
    }

   for (auto& robot : robots_) {
    if(robot){
        if (robot->getRobotID() == upgradeRobot_->getRobotID()) {
            // delete robot;
            robot = upgradeRobot_;  // Replace pointer
            break;
        }
    }
   }

 }

void Battlefield::robotMove(int robotId, int x, int y) {
    for (int i = 0; i < battlefieldRows_; ++i) {
        for (int j = 0; j < battlefieldCols_; ++j) {
            string& cell = battlefield_[i][j];

            if (!cell.empty()) {
                try {
                    int id = stoi(cell);
                    if (id == robotId) {
                        battlefield_[i][j] = "";
                    }
                } catch (const std::invalid_argument& e) {
                    // Skip non-integer cells
                    cerr << "Non-integer cell value at (" << j << ", " << i << "): '" << cell << "'\n";
                }
            }
        }
    }

    // Assign new position (convert robotId to string)
    battlefield_[y][x] = to_string(robotId);
}


//  void Battlefield::robotMove(int robotId, int x, int y){
//     string playerStr;
//     int id;
//     for(int i = 0; i < battlefieldRows_; i++){
//         for(int j = 0; j < battlefieldCols_; j++){
//             playerStr = battlefield_[i][j];
//             if (playerStr != ""){
//                 id = stoi(playerStr);
//                 if (id == robotId)
//                     battlefield_[i][j] = "";
//             }
//         }
//     }
//     battlefield_[y][x] = robotId;
//  }

/**********************************************************************
 * GenericRobot Functions
 *********************************************************************/
// int GenericRobot::getRobotID() const { return robotId; }

void GenericRobot::actions(Battlefield* battlefield, ostream &cout){
    actionThink(battlefield, cout);
}

void GenericRobot::actionThink(Battlefield* battlefield, ostream &cout) {
    cout << "Robot " << getRobotName() << " is thinking..." << endl;
    actionRand(battlefield);
}

void GenericRobot::actionLook(Battlefield* battlefield, int x, int y, ostream &cout) {
    int currentX = getRobotX();
    int currentY = getRobotY();


    for (int dx = -1; dx <= 1; ++dx) {  //iterate 3x3 grid
        for (int dy = -1; dy <= 1; ++dy) {
            int lookX = currentX + dx; //looks at the neighbouring robots
            int lookY = currentY + dy;

            if (dx==0 && dy ==0) continue;

            bool outOfBounds = lookX < 0 || lookX >= battlefield->battlefieldCols() ||
                            lookY < 0 || lookY >= battlefield->battlefieldRows();
            if (outOfBounds) continue;

            string playerStr = battlefield->getPlayer(lookX, lookY);
            if (!playerStr.empty()) {
                int lookRobotId = stoi(playerStr);
                Robot* robotLooked = nullptr;

                for (Robot* robot : battlefield->getAllRobots()) {
                    if (robot->getRobotID() == lookRobotId) {
                        robotLooked = robot;
                        break;
                    }
                }

                if (robotLooked) {
                    cout << "Robot " << robotLooked->getRobotName() 
                        << " is at position (" << lookX << ", " << lookY 
                        << ") looked by Robot " << getRobotName() << endl;
                }
            }
        }
    }
}

void GenericRobot::actionMove(Battlefield* battlefield, int x, int y, ostream &cout) {

    if (abs(x) > 1 || abs(y) > 1 || (x == 0 && y == 0)) {
    cout << "Invalid move." << endl;
    return;  //check so it doesnt move to its own place or more than allowed
    }

    int currentX = getRobotX();
    int currentY = getRobotY();

    int nextX = currentX + x;
    int nextY = currentY + y;
    // cout << nextX << nextY << endl;
    if (nextX < 0 || nextX >= battlefield->battlefieldCols() || nextY < 0 || nextY >= battlefield->battlefieldRows()) {
        cout << "Out of Bounds!." << endl;
        return;
    }
    if (battlefield->battlefield_[nextY][nextX] != "") {
        cout << "Robot " << getRobotName() << " tried to move to position (" << nextX << ", " << nextY << ") but place taken!" << endl;
        return;
    }
    battlefield->battlefield_[currentY][currentX] = "";
    battlefield->battlefield_[nextY][nextX] = to_string(robotId);

    setRobotX(nextX);
    setRobotY(nextY);

    cout << "Robot " << getRobotName() << " move to position (" << nextX << ", " << nextY << ")" << endl;
}

void GenericRobot::actionFire(Battlefield* battlefield, int x, int y, ostream &cout) {
    cout << "Robot " << getRobotName() << " is firing!" << endl;

    if (getShells() <= 0) {
        cout << "No more shots left! " << getRobotName() << " has fired its maximum shells.\n";
        return;
    }
    setShells(getShells() - 1);

    // int targetX = getRobotX() + x;
    // int targetY = getRobotY() + y;
    int targetX =x;
    int targetY =y;

    bool outOfBounds = targetX < 0 || targetX >= battlefield->battlefieldCols() ||
                    targetY < 0 || targetY >= battlefield->battlefieldRows();
    bool ownSelf = (x == 0 && y == 0);

    if (outOfBounds || ownSelf) {
        if (ownSelf) {
            cout << "Can't shoot own self!" << endl;
        } else {
            cout << "Out of Bounds!" << endl;
        }
        return;
    }
cout << battlefield->getPlayer(targetX, targetY) << endl;
    if (!(battlefield->getPlayer(targetX, targetY)).empty()) {
        Robot* targetRobot = nullptr;
        string playerStr = battlefield->getPlayer(targetX, targetY);
        int targetRobotId = stoi(playerStr);

        for (Robot* robot : battlefield->getAllRobots()) {
            if (robot->getRobotID() == targetRobotId) {
                targetRobot = robot;
                break;
            }
        }

        if (!targetRobot) {
            cout << "Missed!" << endl;
            return;
        }

        if (targetRobot->getRobotType() == HIDE && targetRobot->isHidden()) {
            cout << "Shot missed. Robot is hidden." << endl;
            return;
        }

        if (targetRobot->getRobotType() == REFLECTSHOT && targetRobot->isReflecting()) {
            cout << "Shot reflected." << endl;
            reduceLife();
            battlefield->respawnRobot(getRobotID());
            if (!isAlive())
                cout << "Robot " << getRobotID() << " has been destroyed." << endl;
            return;
        }

        // Hit chance logic
        random_device rd;
        mt19937 gen(rd()), gen2(rd());
        uniform_int_distribution<> hitDist(1, 100);
        int hitChance = hitDist(gen);

        if (hitChance <= 70) {
            targetRobot->reduceLife();
            incrementKills();
            cout << "Robot " << getRobotName() << " killed Robot " << targetRobot->getRobotName() << endl;
            battlefield->respawnRobot(targetRobot->getRobotID());

            if (!canUpgrade()) return;

            // Upgrade
            Robot* upgradedRobot = nullptr;
            string name = getRobotName();
            int curX = getRobotX();
            int curY = getRobotY();

            uniform_int_distribution<> upgradeDist(1, 8);
            int choice = upgradeDist(gen2);

            switch (choice) {
                case 1: upgradedRobot = new LongShotBot(x, y, name); break;
                case 2: upgradedRobot = new SemiAutoBot(x, y, name); break;
                case 3: upgradedRobot = new ThirtyShotBot(x, y, name); break;
                case 4: upgradedRobot = new JumpBot(x, y, name); break;
                case 5: upgradedRobot = new HideBot(x, y, name); break;
                case 6: upgradedRobot = new ReflectShotBot(x, y, name); break;
                case 7: upgradedRobot = new HealBot(x, y, name); break;
                case 8: upgradedRobot = new BombBot(x, y, name); break;
            }

            upgradedRobot->isUpgrading(getUpgradeCount() - 1, getLives(), getKills(), getShells());
            upgradedRobot->setRobotID(getRobotID());
            cout << "Robot " << upgradedRobot->getRobotName() << " has upgraded to " << robotTypeName(upgradedRobot->getRobotType()) << endl;
            battlefield->robotUpgrade(upgradedRobot);
            return;
        }
        cout << "70" << endl;
    }else{
    cout << "Missed completely!" << endl;}
}

void GenericRobot::actionRand(Battlefield* battlefield) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> posDistr(0, 8);

    int directionMove = posDistr(gen);

    int currentX = getRobotX();
    int currentY = getRobotY();

    int moveX = 0, moveY = 0;

    switch (directionMove) {
        case 0: moveX = -1; moveY = -1; break;
        case 1: moveX =  0; moveY = -1; break;
        case 2: moveX =  1; moveY = -1; break;
        case 3: moveX = -1; moveY =  0; break;
        case 4: moveX =  1; moveY =  0; break;
        case 5: moveX = -1; moveY =  1; break;
        case 6: moveX =  0; moveY =  1; break;
        case 7: moveX =  1; moveY =  1; break;
        case 8: moveX =  0; moveY =  0; break;
    }

    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> actionDistr(0, 10);

    actionLook(battlefield, moveX, moveY, cout);

    int randomInt = actionDistr(gen2);

    if (randomInt % 2 == 0) {
        actionMove(battlefield, 0, 0, cout);
        actionFire(battlefield, 7, 2, cout);
    } else {
        actionFire(battlefield, 7, 2, cout);
        actionMove(battlefield, 0, 0, cout);
    }
}

/**********************************************************************
 * HideBot Functions
 *********************************************************************/
void HideBot::actions(Battlefield* battlefield, ostream &cout){
    actionThink(battlefield, cout);
}

void HideBot::actionThink(Battlefield* battlefield, ostream &cout){
    cout << "Robot " << getRobotName() << "  is thinking..." << endl;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> posDistr(0, 8);

    int directionMove = posDistr(gen);

    int currentX = getRobotX();
    int currentY = getRobotY();

    int moveX = 0, moveY = 0;

    switch (directionMove) {
        case 0: moveX = -1; moveY = -1; break;
        case 1: moveX =  0; moveY = -1; break;
        case 2: moveX =  1; moveY = -1; break;
        case 3: moveX = -1; moveY =  0; break;
        case 4: moveX =  1; moveY =  0; break;
        case 5: moveX = -1; moveY =  1; break;
        case 6: moveX =  0; moveY =  1; break;
        case 7: moveX =  1; moveY =  1; break;
        case 8: moveX =  0; moveY =  0; break;
    }

    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> actionDistr(0, 10);

    actionLook(battlefield, moveX, moveY, cout);

    int randomInt = actionDistr(gen2);

    if (randomInt % 2 == 0) {
        actionMove(battlefield, moveX, moveY, cout);
        actionFire(battlefield, moveX, moveY, cout);
    } else {
        actionFire(battlefield, moveX, moveY, cout);
        actionMove(battlefield, moveX, moveY, cout);
    }
}

void HideBot::actionLook(Battlefield* battlefield, int x, int y, ostream &cout){
    int currentX = getRobotX();
    int currentY = getRobotY();

    for (int dx = -1; dx <= 1; ++dx) {  //iterate 3x3 grid
        for (int dy = -1; dy <= 1; ++dy) {
            int lookX = currentX + dx; //looks at the neighbouring robots
            int lookY = currentY + dy;

            if (dx==0 && dy ==0) continue;

            bool outOfBounds = lookX < 0 || lookX >= battlefield->battlefieldCols() ||
                            lookY < 0 || lookY >= battlefield->battlefieldRows();
            if (outOfBounds) continue;

            string playerStr = battlefield->getPlayer(lookX, lookY);
            if (!playerStr.empty()) {
                int lookRobotId = stoi(playerStr);
                Robot* robotLooked = nullptr;

                for (Robot* robot : battlefield->getAllRobots()) {
                    if (robot->getRobotID() == lookRobotId) {
                        robotLooked = robot;
                        break;
                    }
                }

                if (robotLooked) {
                    cout << "Robot " << robotLooked->getRobotName() 
                        << " is at position (" << lookX << ", " << lookY 
                        << ") looked by Robot " << getRobotName() << endl;
                }
            }
        }
    }
}

void HideBot::actionMove(Battlefield* battlefield, int x, int y, ostream &cout){
    
    if (abs(x) > 1 || abs(y) > 1 || (x == 0 && y == 0)) {
    cout << "Invalid move." << endl;
    return;  //check so it doesnt move to its own place or more than allowed
    }

    int currentX = getRobotX();
    int currentY = getRobotY();

    int nextX = currentX + x;
    int nextY = currentY + y;

    if (nextX < 0 || nextX >= battlefield->battlefieldCols() || nextY < 0 || nextY >= battlefield->battlefieldRows()) {
        cout << "Out of Bounds!." << endl;
        return;
    }
    battlefield->robotMove(getRobotID(), nextX, nextY);
    setRobotX(nextX);
    setRobotY(nextY);

    cout << "Robot " << getRobotName() << " move to position (" << nextX << ", " << nextY << ")" << endl;
}

void HideBot::actionFire(Battlefield* battlefield, int x, int y, ostream &cout) {
    cout << "Robot " << getRobotName() << " is Firing!" << endl;

    if (getShells() <= 0) {
        cout << "No more shots left! " << getRobotName() << " has fired its maximum shells.\n";
        return;
    }
    setShells(getShells() - 1);

    int targetX = getRobotX() + x;
    int targetY = getRobotY() + y;

    bool outOfBounds = targetX < 0 || targetX >= battlefield->battlefieldCols() ||
                    targetY < 0 || targetY >= battlefield->battlefieldRows();
    bool ownSelf = (x == getRobotX() && y == getRobotY());

    if (outOfBounds || ownSelf) {
        if (ownSelf) {
            cout << "Can't shoot own self!!" << endl;
        } else {
            cout << "Out of Bounds!" << endl;
        }
        return;
    }

    if (!(battlefield->getPlayer(targetX, targetY)).empty()) {
        Robot* targetRobot = nullptr;
        string playerStr = battlefield->getPlayer(targetX, targetY);
        int targetRobotId = stoi(playerStr);

        for (Robot* robot : battlefield->getAllRobots()) {
            if (robot->getRobotID() == targetRobotId) {
                targetRobot = robot;
                break;
            }
        }

        if (!targetRobot) {
            cout << "Missed!" << endl;
            return;
        }

        if (targetRobot->getRobotType() == HIDE && targetRobot->isHidden()) {
            cout << "Shot missed. Robot is hidden." << endl;
            return;
        }

        if (targetRobot->getRobotType() == REFLECTSHOT && targetRobot->isReflecting()) {
            cout << "Shot reflected." << endl;
            reduceLife();
            battlefield->respawnRobot(getRobotID());
            if (!isAlive())
                cout << "Robot " << getRobotID() << " has been destroyed." << endl;
            return;
        }

        // Hit chance logic
        random_device rd;
        mt19937 gen(rd()), gen2(rd());
        uniform_int_distribution<> hitDist(1, 100);
        int hitChance = hitDist(gen);

        if (hitChance <= 70) {
            targetRobot->reduceLife();
            incrementKills();
            cout << "Robot " << getRobotName() << " killed Robot " << targetRobot->getRobotName() << endl;
            battlefield->respawnRobot(targetRobot->getRobotID());

            if (!canUpgrade()) return;

            // Upgrade
            Robot* upgradedRobot = nullptr;
            string name = getRobotName();
            int curX = getRobotX();
            int curY = getRobotY();

            uniform_int_distribution<> upgradeDist(1, 8);
            // int choice;
            // do {
            //     choice = upgradeDist(gen2);
            // } while (choice == 5);  // 7 HideBot

            int choice = upgradeDist(gen2);

            switch (choice) {
                case 1: upgradedRobot = new LongShotBot(x, y, name); break;
                case 2: upgradedRobot = new SemiAutoBot(x, y, name); break;
                case 3: upgradedRobot = new ThirtyShotBot(x, y, name); break;
                case 4: upgradedRobot = new ScoutBot(x, y, name); break;
                case 5: upgradedRobot = new TrackBot(x, y, name); break;
                case 6: upgradedRobot = new ReflectShotBot(x, y, name); break;
                case 7: upgradedRobot = new HealBot(x, y, name); break;
                case 8: upgradedRobot = new BombBot(x, y, name); break;
            }

            upgradedRobot->isUpgrading(getUpgradeCount() - 1, getLives(), getKills(), getShells());
            upgradedRobot->setRobotID(getRobotID());
            battlefield->robotUpgrade(upgradedRobot);
            return;
        }
    }
    cout << "Missed!" << endl;
}

bool HideBot::isHidden(){
    if (hideTurnsUsed >= MAX_HIDE_TURNS)
        isHidden_ = false;
    hideTurnsUsed++;
    return isHidden_;
}

// int HideBot::hidesLeft() const{ 
//     return MAX_HIDE_TURNS - hideTurnsUsed - 1;
// }

/**********************************************************************
 * JumpBot Functions
 *********************************************************************/
void JumpBot::actions(Battlefield* battlefield, ostream &cout){
    actionThink(battlefield, cout);
}

void JumpBot::actionThink(Battlefield* battlefield, ostream &cout){
    cout << "Robot " << getRobotName() << " is thinking..." << endl;

    // int directionMove = posDistr(gen);

    int battlefieldWidth = battlefield->battlefieldCols();
    int battlefieldHeight = battlefield->battlefieldRows(); 

    int currentX = getRobotX();
    int currentY = getRobotY();

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> xDistr(0, battlefieldWidth-1);
    uniform_int_distribution<> yDistr(0, battlefieldHeight-1);
    
    int moveX = 0, moveY = 0;

    do {
        moveX = xDistr(gen);
        moveY = yDistr(gen);
    } while ((moveX == currentX && moveY == currentY) || battlefield->getPlayer(moveY,moveX) != "");

    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> actionDistr(0, 10);

    actionLook(battlefield, moveX, moveY, cout);

    int randomInt = actionDistr(gen2);

    if (randomInt % 2 == 0) {
        actionMove(battlefield, moveX, moveY, cout);
        actionFire(battlefield, moveX, moveY, cout);
    } else {
        actionFire(battlefield, moveX, moveY, cout);
        actionMove(battlefield, moveX, moveY, cout);
    }
}

void JumpBot::actionLook(Battlefield* battlefield, int x, int y, ostream &cout){
    int currentX = getRobotX();
    int currentY = getRobotY();

    for (int dx = -1; dx <= 1; ++dx) {  //iterate 3x3 grid
        for (int dy = -1; dy <= 1; ++dy) {
            int lookX = currentX + dx; //looks at the neighbouring robots
            int lookY = currentY + dy;

            if (dx==0 && dy ==0) continue;

            bool outOfBounds = lookX < 0 || lookX >= battlefield->battlefieldCols() ||
                            lookY < 0 || lookY >= battlefield->battlefieldRows();
            if (outOfBounds) continue;

            string playerStr = battlefield->getPlayer(lookX, lookY);
            if (!playerStr.empty()) {
                int lookRobotId = stoi(playerStr);
                Robot* robotLooked = nullptr;

                for (Robot* robot : battlefield->getAllRobots()) {
                    if (robot->getRobotID() == lookRobotId) {
                        robotLooked = robot;
                        break;
                    }
                }

                if (robotLooked) {
                    cout << "Robot " << robotLooked->getRobotName() 
                        << " is at position (" << lookX << ", " << lookY 
                        << ") looked by Robot " << getRobotName() << endl;
                }
            }
        }
    }
}

void JumpBot::actionMove(Battlefield* battlefield, int x, int y, ostream &cout){
    if (jumpsUsed < MAX_JUMPS) {
        string targetPosition = battlefield->getPlayer(x, y);
        if (targetPosition.empty()) { //check if theres any robots at the location
            battlefield->robotMove(getRobotID(), x, y);
            setRobotX(x);
            setRobotY(y);
            jumpsUsed++;
        } else {
            cout << "Invalid location! There might be a robot there." << endl;
        }
    }
}

void JumpBot::actionFire(Battlefield* battlefield, int x, int y, ostream &cout){
    cout << "Robot " << getRobotName() << " is Firing!" << endl;

    if (getShells() <= 0) {
        cout << "No more shots left! " << getRobotName() << " has fired its maximum shells.\n";
        return;
    }
    setShells(getShells() - 1);

    int targetX = getRobotX() + x;
    int targetY = getRobotY() + y;

    bool outOfBounds = targetX < 0 || targetX >= battlefield->battlefieldCols() ||
                    targetY < 0 || targetY >= battlefield->battlefieldRows();
    bool ownSelf = (x == getRobotX() && y == getRobotY());

    if (outOfBounds || ownSelf) {
        if (ownSelf) {
            cout << "Can't shoot own self!" << endl;
        } else {
            cout << "Out of Bounds!" << endl;
        }
        return;
    }

    if (!(battlefield->getPlayer(targetX, targetY)).empty()) {
        Robot* targetRobot = nullptr;
        string playerStr = battlefield->getPlayer(targetX, targetY);
        int targetRobotId = stoi(playerStr);

        for (Robot* robot : battlefield->getAllRobots()) {
            if (robot->getRobotID() == targetRobotId) {
                targetRobot = robot;
                break;
            }
        }

        if (!targetRobot) {
            cout << "Missed!" << endl;
            return;
        }

        if (targetRobot->getRobotType() == HIDE && targetRobot->isHidden()) {
            cout << "Shot missed. Robot is hidden." << endl;
            return;
        }

        if (targetRobot->getRobotType() == REFLECTSHOT && targetRobot->isReflecting()) {
            cout << "Shot reflected." << endl;
            reduceLife();
            battlefield->respawnRobot(getRobotID());
            if (!isAlive())
                cout << "Robot " << getRobotID() << " has been destroyed." << endl;
            return;
        }

        // Hit chance logic
        random_device rd;
        mt19937 gen(rd()), gen2(rd());
        uniform_int_distribution<> hitDist(1, 100);
        int hitChance = hitDist(gen);

        if (hitChance <= 70) {
            targetRobot->reduceLife();
            incrementKills();
            cout << "Robot " << getRobotName() << " killed Robot " << targetRobot->getRobotName() << endl;
            battlefield->respawnRobot(targetRobot->getRobotID());

            if (!canUpgrade()) return;

            // Upgrade
            Robot* upgradedRobot = nullptr;
            string name = getRobotName();
            int curX = getRobotX();
            int curY = getRobotY();

            uniform_int_distribution<> upgradeDist(1, 8);
            int choice = upgradeDist(gen2);

            switch (choice) {
                case 1: upgradedRobot = new LongShotBot(x, y, name); break;
                case 2: upgradedRobot = new SemiAutoBot(x, y, name); break;
                case 3: upgradedRobot = new ThirtyShotBot(x, y, name); break;
                case 4: upgradedRobot = new TrackBot(x, y, name); break;
                case 5: upgradedRobot = new ScoutBot(x, y, name); break;
                case 6: upgradedRobot = new ReflectShotBot(x, y, name); break;
                case 7: upgradedRobot = new HealBot(x, y, name); break;
                case 8: upgradedRobot = new BombBot(x, y, name); break;
            }

            upgradedRobot->isUpgrading(getUpgradeCount() - 1, getLives(), getKills(), getShells());
            upgradedRobot->setRobotID(getRobotID());
            battlefield->robotUpgrade(upgradedRobot);
            return;
        }
    }
    cout << "Missed!" << endl;
}

/**********************************************************************
 * LongShotBot Functions
 *********************************************************************/
void LongShotBot::actions(Battlefield* battlefield, ostream &cout){
    actionThink(battlefield, cout);
}

void LongShotBot::actionThink(Battlefield* battlefield, ostream &cout){
    cout << "Robot " << getRobotName() << " is thinking..." << endl;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> posDistr(0, 8);

    int directionMove = posDistr(gen);

    int currentX = getRobotX();
    int currentY = getRobotY();

    int moveX = 0, moveY = 0;

    switch (directionMove) {
        case 0: moveX = -1; moveY = -1; break;
        case 1: moveX =  0; moveY = -1; break;
        case 2: moveX =  1; moveY = -1; break;
        case 3: moveX = -1; moveY =  0; break;
        case 4: moveX =  1; moveY =  0; break;
        case 5: moveX = -1; moveY =  1; break;
        case 6: moveX =  0; moveY =  1; break;
        case 7: moveX =  1; moveY =  1; break;
        case 8: moveX =  0; moveY =  0; break;
    }

    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> actionDistr(0, 10);

    actionLook(battlefield, moveX, moveY, cout);

    int randomInt = actionDistr(gen2);

    if (randomInt % 2 == 0) {
        actionMove(battlefield, moveX, moveY, cout);
        actionFire(battlefield, moveX, moveY, cout);
    } else {
        actionFire(battlefield, moveX, moveY, cout);
        actionMove(battlefield, moveX, moveY, cout);
    }
}

void LongShotBot::actionLook(Battlefield* battlefield, int x, int y, ostream &cout){
    int currentX = getRobotX();
    int currentY = getRobotY();

    for (int dx = -1; dx <= 1; ++dx) {  //iterate 3x3 grid
        for (int dy = -1; dy <= 1; ++dy) {
            int lookX = currentX + dx; //looks at the neighbouring robots
            int lookY = currentY + dy;

            if (dx==0 && dy ==0) continue;

            bool outOfBounds = lookX < 0 || lookX >= battlefield->battlefieldCols() ||
                            lookY < 0 || lookY >= battlefield->battlefieldRows();
            if (outOfBounds) continue;

            string playerStr = battlefield->getPlayer(lookX, lookY);
            if (!playerStr.empty()) {
                int lookRobotId = stoi(playerStr);
                Robot* robotLooked = nullptr;

                for (Robot* robot : battlefield->getAllRobots()) {
                    if (robot->getRobotID() == lookRobotId) {
                        robotLooked = robot;
                        break;
                    }
                }

                if (robotLooked) {
                    cout << "Robot " << robotLooked->getRobotName() 
                        << " is at position (" << lookX << ", " << lookY 
                        << ") looked by Robot " << getRobotName() << endl;
                }
            }
        }
    }
}

void LongShotBot::actionMove(Battlefield* battlefield, int x, int y, ostream &cout){
    
    if (abs(x) > 1 || abs(y) > 1 || (x == 0 && y == 0)) {
    cout << "Invalid move." << endl;
    return;  //check so it doesnt move to its own place or more than allowed
    }

    int currentX = getRobotX();
    int currentY = getRobotY();

    int nextX = currentX + x;
    int nextY = currentY + y;

    if (nextX < 0 || nextX >= battlefield->battlefieldCols() || nextY < 0 || nextY >= battlefield->battlefieldRows()) {
        cout << "Out of Bounds!." << endl;
        return;
    }
    battlefield->robotMove(getRobotID(), nextX, nextY);
    setRobotX(nextX);
    setRobotY(nextY);

    cout << "Robot " << getRobotName() << " move to position (" << nextX << ", " << nextY << ")" << endl;
}

void LongShotBot::actionFire(Battlefield* battlefield, int x, int y, ostream &cout){
    cout << "Robot " << getRobotName() << " is Firing!" << endl;

    if (getShells() <= 0) {
        cout << "No more shots left! " << getRobotName() << " has fired its maximum shells.\n";
        return;
    }
    setShells(getShells() - 1);

    int targetX = getRobotX() + x;
    int targetY = getRobotY() + y;

    bool outOfRange = abs(x) > 4 || abs(y) > 4;
    bool outOfBounds = targetX < 0 || targetX >= battlefield->battlefieldCols() ||
                    targetY < 0 || targetY >= battlefield->battlefieldRows();
    bool ownSelf = (x == getRobotX() && y == getRobotY());

    if (outOfRange || outOfBounds || ownSelf) {
        if (ownSelf) {
            cout << "Can't shoot own self!" << endl;
        } else if (outOfBounds) {
            cout << "Out of Bounds!" << endl;
        } else {
            cout << "Target is out of range" << endl;
        }
        return;
    }

    if (!(battlefield->getPlayer(targetX, targetY)).empty()) {
        Robot* targetRobot = nullptr;
        string playerStr = battlefield->getPlayer(targetX, targetY);
        int targetRobotId = stoi(playerStr);

        for (Robot* robot : battlefield->getAllRobots()) {
            if (robot->getRobotID() == targetRobotId) {
                targetRobot = robot;
                break;
            }
        }

        if (!targetRobot) {
            cout << "Missed!" << endl;
            return;
        }

        if (targetRobot->getRobotType() == HIDE && targetRobot->isHidden()) {
            cout << "Shot missed. Robot is hidden." << endl;
            return;
        }

        if (targetRobot->getRobotType() == REFLECTSHOT && targetRobot->isReflecting()) {
            cout << "Shot reflected." << endl;
            reduceLife();
            battlefield->respawnRobot(getRobotID());
            if (!isAlive())
                cout << "Robot " << getRobotID() << " has been destroyed." << endl;
            return;
        }

        // Hit chance logic
        random_device rd;
        mt19937 gen(rd()), gen2(rd());
        uniform_int_distribution<> hitDist(1, 100);
        int hitChance = hitDist(gen);

        if (hitChance <= 70) {
            targetRobot->reduceLife();
            incrementKills();
            cout << "Robot " << getRobotName() << " killed Robot " << targetRobot->getRobotName() << endl;
            battlefield->respawnRobot(targetRobot->getRobotID());

            if (!canUpgrade()) return;

            // Upgrade
            Robot* upgradedRobot = nullptr;
            string name = getRobotName();
            int curX = getRobotX();
            int curY = getRobotY();

            uniform_int_distribution<> upgradeDist(1, 4);
            int choice = upgradeDist(gen2);

            switch (choice) {
                case 1: upgradedRobot = new ScoutBot(curX, curY, name); break;
                case 2: upgradedRobot = new TrackBot(curX, curY, name); break;
                case 3: upgradedRobot = new JumpBot(curX, curY, name); break;
                case 4: upgradedRobot = new HideBot(curX, curY, name); break;
            }

            upgradedRobot->isUpgrading(getUpgradeCount() - 1, getLives(), getKills(), getShells());
            upgradedRobot->setRobotID(getRobotID());
            battlefield->robotUpgrade(upgradedRobot);
            return;
        }
    }
    cout << "Missed!" << endl;
}

/**********************************************************************
 * SemiAutoBot Functions
 *********************************************************************/
void SemiAutoBot::actions(Battlefield* battlefield, ostream &cout){
    actionThink(battlefield, cout);
}

void SemiAutoBot::actionThink(Battlefield* battlefield, ostream &cout){
    cout << "Robot " << getRobotName() << " is thinking..." << endl;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> posDistr(0, 8);

    int directionMove = posDistr(gen);

    int currentX = getRobotX();
    int currentY = getRobotY();

    int moveX = 0, moveY = 0;

    switch (directionMove) {
        case 0: moveX = -1; moveY = -1; break;
        case 1: moveX =  0; moveY = -1; break;
        case 2: moveX =  1; moveY = -1; break;
        case 3: moveX = -1; moveY =  0; break;
        case 4: moveX =  1; moveY =  0; break;
        case 5: moveX = -1; moveY =  1; break;
        case 6: moveX =  0; moveY =  1; break;
        case 7: moveX =  1; moveY =  1; break;
        case 8: moveX =  0; moveY =  0; break;
    }

    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> actionDistr(0, 10);

    actionLook(battlefield, moveX, moveY, cout);

    int randomInt = actionDistr(gen2);

    if (randomInt % 2 == 0) {
        actionMove(battlefield, moveX, moveY, cout);
        actionFire(battlefield, moveX, moveY, cout);
    } else {
        actionFire(battlefield, moveX, moveY, cout);
        actionMove(battlefield, moveX, moveY, cout);
    }
}

void SemiAutoBot::actionLook(Battlefield* battlefield, int x, int y, ostream &cout){
    int currentX = getRobotX();
    int currentY = getRobotY();

    for (int dx = -1; dx <= 1; ++dx) {  //iterate 3x3 grid
        for (int dy = -1; dy <= 1; ++dy) {
            int lookX = currentX + dx; //looks at the neighbouring robots
            int lookY = currentY + dy;

            if (dx==0 && dy ==0) continue;

            bool outOfBounds = lookX < 0 || lookX >= battlefield->battlefieldCols() ||
                            lookY < 0 || lookY >= battlefield->battlefieldRows();
            if (outOfBounds) continue;

            string playerStr = battlefield->getPlayer(lookX, lookY);
            if (!playerStr.empty()) {
                int lookRobotId = stoi(playerStr);
                Robot* robotLooked = nullptr;

                for (Robot* robot : battlefield->getAllRobots()) {
                    if (robot->getRobotID() == lookRobotId) {
                        robotLooked = robot;
                        break;
                    }
                }

                if (robotLooked) {
                    cout << "Robot " << robotLooked->getRobotName() 
                        << " is at position (" << lookX << ", " << lookY 
                        << ") looked by Robot " << getRobotName() << endl;
                }
            }
        }
    }
}

void SemiAutoBot::actionMove(Battlefield* battlefield, int x, int y, ostream &cout){
    
    if (abs(x) > 1 || abs(y) > 1 || (x == 0 && y == 0)) {
    cout << "Invalid move." << endl;
    return;  //check so it doesnt move to its own place or more than allowed
    }

    int currentX = getRobotX();
    int currentY = getRobotY();

    int nextX = currentX + x;
    int nextY = currentY + y;

    if (nextX < 0 || nextX >= battlefield->battlefieldCols() || nextY < 0 || nextY >= battlefield->battlefieldRows()) {
        cout << "Out of Bounds!." << endl;
        return;
    }
    battlefield->robotMove(getRobotID(), nextX, nextY);
    setRobotX(nextX);
    setRobotY(nextY);

    cout << "Robot " << getRobotName() << " move to position (" << nextX << ", " << nextY << ")" << endl;
}

void SemiAutoBot::actionFire(Battlefield* battlefield, int x, int y, ostream &cout) {
    cout << "Robot " << getRobotName() << " is Firing!" << endl;
    // Hit chance logic
    random_device rd;
    mt19937 gen(rd()), gen2(rd());
    uniform_int_distribution<> hitDist(1, 100);
    int hitChance = hitDist(gen);
    uniform_int_distribution<> upgradeDist(1, 4);
    int choice = upgradeDist(gen2);

    int targetX = getRobotX() + x;
    int targetY = getRobotY() + y;

    bool outOfBounds = targetX < 0 || targetX >= battlefield->battlefieldCols() ||
                    targetY < 0 || targetY >= battlefield->battlefieldRows();
    bool ownSelf = (x == getRobotX() && y == getRobotY());

    if (outOfBounds || ownSelf) {
        if (ownSelf) {
            cout << "Can't shoot own self!" << endl;
        } else{
            cout << "Out of Bounds!" << endl;
        } 
        return;
    }

    if (!(battlefield->getPlayer(targetX, targetY)).empty()) {
        Robot* targetRobot = nullptr;
        string playerStr = battlefield->getPlayer(targetX, targetY);
        int targetRobotId = stoi(playerStr);

        for (Robot* robot : battlefield->getAllRobots()) {
            if (robot->getRobotID() == targetRobotId) {
                targetRobot = robot;
                break;
            }
        }

        if (!targetRobot) {
            cout << "Missed!" << endl;
            return;
        }

        if (targetRobot->getRobotType() == HIDE && targetRobot->isHidden()) {
            cout << "Shot missed. Robot is hidden." << endl;
            return;
        }

        if (targetRobot->getRobotType() == REFLECTSHOT && targetRobot->isReflecting()) {
            cout << "Shot reflected." << endl;
            reduceLife();
            battlefield->respawnRobot(getRobotID());
            if (!isAlive())
                cout << "Robot " << getRobotID() << " has been destroyed." << endl;
            return;
        }

        bool killedARobot = false;
        while (shotsFired < MAX_SHOTS_FIRED){
            if (getShells() <= 0) {
                cout << "No more shots left! " << getRobotName() << " has fired its maximum shells.\n";
                return;
            }

            if (hitChance <= 70) {
                targetRobot->reduceLife();
                incrementKills();
                killedARobot = true;
                cout << "Robot " << getRobotName() << " killed Robot " << targetRobot->getRobotName() << endl;
                battlefield->respawnRobot(targetRobot->getRobotID());
            }
            shotsFired++;
            setShells(getShells()-1);
        }
        if (!canUpgrade() || !killedARobot) return;

        // Upgrade
        Robot* upgradedRobot = nullptr;
        string name = getRobotName();
        int curX = getRobotX();
        int curY = getRobotY();

        switch (choice) {
            case 1: upgradedRobot = new ScoutBot(curX, curY, name); break;
            case 2: upgradedRobot = new TrackBot(curX, curY, name); break;
            case 3: upgradedRobot = new JumpBot(curX, curY, name); break;
            case 4: upgradedRobot = new HideBot(curX, curY, name); break;
        }

        upgradedRobot->isUpgrading(getUpgradeCount() - 1, getLives(), getKills(), getShells());
        upgradedRobot->setRobotID(getRobotID());
        battlefield->robotUpgrade(upgradedRobot);
    } else { 
        cout << "Missed!" << endl;
    }
    shotsFired = 1;
}

/**********************************************************************
 * ThirtyShotBot Functions
 *********************************************************************/
void ThirtyShotBot::actions(Battlefield* battlefield, ostream &cout){
    actionThink(battlefield, cout);
}

void ThirtyShotBot::actionThink(Battlefield* battlefield, ostream &cout){
    cout << "Robot " << getRobotName() << " is thinking..." << endl;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> posDistr(0, 8);

    int directionMove = posDistr(gen);

    int currentX = getRobotX();
    int currentY = getRobotY();

    int moveX = 0, moveY = 0;

    switch (directionMove) {
        case 0: moveX = -1; moveY = -1; break;
        case 1: moveX =  0; moveY = -1; break;
        case 2: moveX =  1; moveY = -1; break;
        case 3: moveX = -1; moveY =  0; break;
        case 4: moveX =  1; moveY =  0; break;
        case 5: moveX = -1; moveY =  1; break;
        case 6: moveX =  0; moveY =  1; break;
        case 7: moveX =  1; moveY =  1; break;
        case 8: moveX =  0; moveY =  0; break;
    }

    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> actionDistr(0, 10);

    actionLook(battlefield, moveX, moveY, cout);

    int randomInt = actionDistr(gen2);

    if (randomInt % 2 == 0) {
        actionMove(battlefield, moveX, moveY, cout);
        actionFire(battlefield, moveX, moveY, cout);
    } else {
        actionFire(battlefield, moveX, moveY, cout);
        actionMove(battlefield, moveX, moveY, cout);
    }
}

void ThirtyShotBot::actionLook(Battlefield* battlefield, int x, int y, ostream &cout){
    int currentX = getRobotX();
    int currentY = getRobotY();

    for (int dx = -1; dx <= 1; ++dx) {  //iterate 3x3 grid
        for (int dy = -1; dy <= 1; ++dy) {
            int lookX = currentX + dx; //looks at the neighbouring robots
            int lookY = currentY + dy;

            if (dx==0 && dy ==0) continue;

            bool outOfBounds = lookX < 0 || lookX >= battlefield->battlefieldCols() ||
                            lookY < 0 || lookY >= battlefield->battlefieldRows();
            if (outOfBounds) continue;

            string playerStr = battlefield->getPlayer(lookX, lookY);
            if (!playerStr.empty()) {
                int lookRobotId = stoi(playerStr);
                Robot* robotLooked = nullptr;

                for (Robot* robot : battlefield->getAllRobots()) {
                    if (robot->getRobotID() == lookRobotId) {
                        robotLooked = robot;
                        break;
                    }
                }

                if (robotLooked) {
                    cout << "Robot " << robotLooked->getRobotName() 
                        << " is at position (" << lookX << ", " << lookY 
                        << ") looked by Robot " << getRobotName() << endl;
                }
            }
        }
    }
}

void ThirtyShotBot::actionMove(Battlefield* battlefield, int x, int y, ostream &cout){
    
    if (abs(x) > 1 || abs(y) > 1 || (x == 0 && y == 0)) {
    cout << "Invalid move." << endl;
    return;  //check so it doesnt move to its own place or more than allowed
    }

    int currentX = getRobotX();
    int currentY = getRobotY();

    int nextX = currentX + x;
    int nextY = currentY + y;

    if (nextX < 0 || nextX >= battlefield->battlefieldCols() || nextY < 0 || nextY >= battlefield->battlefieldRows()) {
        cout << "Out of Bounds!." << endl;
        return;
    }
    battlefield->robotMove(getRobotID(), nextX, nextY);
    setRobotX(nextX);
    setRobotY(nextY);

    cout << "Robot " << getRobotName() << " move to position (" << nextX << ", " << nextY << ")" << endl;
}

void ThirtyShotBot::actionFire(Battlefield* battlefield, int x, int y, ostream &cout) {
    cout << "Robot " << getRobotName() << " is Firing!" << endl;

    if (getShells() <= 0) {
        cout << "No more shots left! " << getRobotName() << " has fired its maximum shells.\n";
        return;
    }
    setShells(getShells() - 1);

    int targetX = getRobotX() + x;
    int targetY = getRobotY() + y;

    bool outOfBounds = targetX < 0 || targetX >= battlefield->battlefieldCols() ||
                    targetY < 0 || targetY >= battlefield->battlefieldRows();
    bool ownSelf = (x == getRobotX() && y == getRobotY());

    if (outOfBounds || ownSelf) {
        if (ownSelf) {
            cout << "Can't shoot own self!" << endl;
        } else {
            cout << "Out of Bounds!" << endl;
        }
        return;
    }

    if (!(battlefield->getPlayer(targetX, targetY)).empty()) {
        Robot* targetRobot = nullptr;
        string playerStr = battlefield->getPlayer(targetX, targetY);
        int targetRobotId = stoi(playerStr);

        for (Robot* robot : battlefield->getAllRobots()) {
            if (robot->getRobotID() == targetRobotId) {
                targetRobot = robot;
                break;
            }
        }

        if (!targetRobot) {
            cout << "Missed!" << endl;
            return;
        }

        if (targetRobot->getRobotType() == HIDE && targetRobot->isHidden()) {
            cout << "Shot missed. Robot is hidden." << endl;
            return;
        }

        if (targetRobot->getRobotType() == REFLECTSHOT && targetRobot->isReflecting()) {
            cout << "Shot reflected." << endl;
            reduceLife();
            battlefield->respawnRobot(getRobotID());
            if (!isAlive())
                cout << "Robot " << getRobotID() << " has been destroyed." << endl;
            return;
        }

        // Hit chance logic
        random_device rd;
        mt19937 gen(rd()), gen2(rd());
        uniform_int_distribution<> hitDist(1, 100);
        int hitChance = hitDist(gen);

        if (hitChance <= 70) {
            targetRobot->reduceLife();
            incrementKills();
            cout << "Robot " << getRobotName() << " killed Robot " << targetRobot->getRobotName() << endl;
            battlefield->respawnRobot(targetRobot->getRobotID());

            if (!canUpgrade()) return;

            // Upgrade
            Robot* upgradedRobot = nullptr;
            string name = getRobotName();
            int curX = getRobotX();
            int curY = getRobotY();

            uniform_int_distribution<> upgradeDist(1, 8);
            int choice = upgradeDist(gen2);

            switch (choice) {
                case 1: upgradedRobot = new HideBot(curX, curY, name); break;
                case 2: upgradedRobot = new JumpBot(curX, curY, name); break;
                case 3: upgradedRobot = new ScoutBot(curX, curY, name); break;
                case 4: upgradedRobot = new TrackBot(curX, curY, name); break;
            }

            upgradedRobot->isUpgrading(getUpgradeCount() - 1, getLives(), getKills(), getShells());
            upgradedRobot->setRobotID(getRobotID());
            battlefield->robotUpgrade(upgradedRobot);
            return;
        }
    }
    cout << "Missed!" << endl;
 }

/**********************************************************************
 * HealBot Functions
 *********************************************************************/
void HealBot::actions(Battlefield* battlefield, ostream &cout){
    actionThink(battlefield, cout);
}

void HealBot::actionThink(Battlefield* battlefield, ostream &cout){
    cout << "Robot " << getRobotName() << " is thinking..." << endl;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> posDistr(0, 8);

    int directionMove = posDistr(gen);

    int currentX = getRobotX();
    int currentY = getRobotY();

    int moveX = 0, moveY = 0;

    switch (directionMove) {
        case 0: moveX = -1; moveY = -1; break;
        case 1: moveX =  0; moveY = -1; break;
        case 2: moveX =  1; moveY = -1; break;
        case 3: moveX = -1; moveY =  0; break;
        case 4: moveX =  1; moveY =  0; break;
        case 5: moveX = -1; moveY =  1; break;
        case 6: moveX =  0; moveY =  1; break;
        case 7: moveX =  1; moveY =  1; break;
        case 8: moveX =  0; moveY =  0; break;
    }

    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> actionDistr(0, 10);

    actionLook(battlefield, moveX, moveY, cout);

    int randomInt = actionDistr(gen2);

    if (randomInt % 2 == 0) {
        actionMove(battlefield, moveX, moveY, cout);
        actionFire(battlefield, moveX, moveY, cout);
    } else {
        actionFire(battlefield, moveX, moveY, cout);
        actionMove(battlefield, moveX, moveY, cout);
    }
}

void HealBot::actionLook(Battlefield* battlefield, int x, int y, ostream &cout){
 
    int currentX = getRobotX();
    int currentY = getRobotY();

    for (int dx = -1; dx <= 1; ++dx) {  //iterate 3x3 grid
        for (int dy = -1; dy <= 1; ++dy) {
            int lookX = currentX + dx; //looks at the neighbouring robots
            int lookY = currentY + dy;

            if (dx==0 && dy ==0) continue;

            bool outOfBounds = lookX < 0 || lookX >= battlefield->battlefieldCols() ||
                            lookY < 0 || lookY >= battlefield->battlefieldRows();
            if (outOfBounds) continue;

            string playerStr = battlefield->getPlayer(lookX, lookY);
            if (!playerStr.empty()) {
                int lookRobotId = stoi(playerStr);
                Robot* robotLooked = nullptr;

                for (Robot* robot : battlefield->getAllRobots()) {
                    if (robot->getRobotID() == lookRobotId) {
                        robotLooked = robot;
                        break;
                    }
                }

                if (robotLooked) {
                    cout << "Robot " << robotLooked->getRobotName() 
                        << " is at position (" << lookX << ", " << lookY 
                        << ") looked by Robot " << getRobotName() << endl;
                }
            }
        }
    }
}

void HealBot::actionMove(Battlefield* battlefield, int x, int y, ostream &cout){
    
    if (abs(x) > 1 || abs(y) > 1 || (x == 0 && y == 0)) {
    cout << "Invalid move." << endl;
    return;  //check so it doesnt move to its own place or more than allowed
    }

    int currentX = getRobotX();
    int currentY = getRobotY();

    int nextX = currentX + x;
    int nextY = currentY + y;

    if (nextX < 0 || nextX >= battlefield->battlefieldCols() || nextY < 0 || nextY >= battlefield->battlefieldRows()) {
        cout << "Out of Bounds!." << endl;
        return;
    }
    battlefield->robotMove(getRobotID(), nextX, nextY);
    setRobotX(nextX);
    setRobotY(nextY);

    cout << "Robot " << getRobotName() << " move to position (" << nextX << ", " << nextY << ")" << endl;
}

void HealBot::actionFire(Battlefield* battlefield, int x, int y, ostream &cout){
    cout << "Robot " << getRobotName() << " is Firing!" << endl;

    if (getShells() <= 0) {
        cout << "No more shots left! " << getRobotName() << " has fired its maximum shells.\n";
        return;
    }
    setShells(getShells() - 1);

    int targetX = getRobotX() + x;
    int targetY = getRobotY() + y;

    bool outOfBounds = targetX < 0 || targetX >= battlefield->battlefieldCols() ||
                    targetY < 0 || targetY >= battlefield->battlefieldRows();
    bool ownSelf = (x == getRobotX() && y == getRobotY());

    if (outOfBounds || ownSelf) {
        if (ownSelf) {
            cout << "Can't shoot own self!" << endl;
        } else {
            cout << "Out of Bounds!" << endl;
        }
        return;
    }

    if (!(battlefield->getPlayer(targetX, targetY)).empty()) {
        Robot* targetRobot = nullptr;
        string playerStr = battlefield->getPlayer(targetX, targetY);
        int targetRobotId = stoi(playerStr);

        for (Robot* robot : battlefield->getAllRobots()) {
            if (robot->getRobotID() == targetRobotId) {
                targetRobot = robot;
                break;
            }
        }

        if (!targetRobot) {
            cout << "Missed!" << endl;
            return;
        }

        if (targetRobot->getRobotType() == HIDE && targetRobot->isHidden()) {
            cout << "Shot missed. Robot is hidden." << endl;
            return;
        }

        if (targetRobot->getRobotType() == REFLECTSHOT && targetRobot->isReflecting()) {
            cout << "Shot reflected." << endl;
            reduceLife();
            battlefield->respawnRobot(getRobotID());
            if (!isAlive())
                cout << "Robot " << getRobotID() << " has been destroyed." << endl;
            return;
        }

        // Hit chance logic
        random_device rd;
        mt19937 gen(rd()), gen2(rd());
        uniform_int_distribution<> hitDist(1, 100);
        int hitChance = hitDist(gen);

        if (hitChance <= 70) {
            targetRobot->reduceLife();
            incrementKills();
            cout << "Robot " << getRobotName() << " killed Robot " << targetRobot->getRobotName() << endl;
            battlefield->respawnRobot(targetRobot->getRobotID());

            if (!canUpgrade()) return;

            // Upgrade
            Robot* upgradedRobot = nullptr;
            string name = getRobotName();
            int curX = getRobotX();
            int curY = getRobotY();

            uniform_int_distribution<> upgradeDist(1, 8);
            int choice = upgradeDist(gen2);

            switch (choice) {
                case 1: upgradedRobot = new HideBot(curX, curY, name); break;
                case 2: upgradedRobot = new JumpBot(curX, curY, name); break;
                case 3: upgradedRobot = new ScoutBot(curX, curY, name); break;
                case 4: upgradedRobot = new TrackBot(curX, curY, name); break;
            }


            upgradedRobot->isUpgrading(getUpgradeCount() - 1, getLives(), getKills(), getShells());
            upgradedRobot->setRobotID(getRobotID());
            battlefield->robotUpgrade(upgradedRobot);
            return;
        }
    }
    cout << "Missed!" << endl;
} 

/**********************************************************************
 * BombBot Functions
 *********************************************************************/
void BombBot::actions(Battlefield* battlefield, ostream &cout){
    actionThink(battlefield, cout);
}

void BombBot::actionThink(Battlefield* battlefield, ostream &cout){
    cout << "Robot " << getRobotName() << " is thinking..." << endl;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> posDistr(0, 8);

    int directionMove = posDistr(gen);

    int currentX = getRobotX();
    int currentY = getRobotY();

    int moveX = 0, moveY = 0;

    switch (directionMove) {
        case 0: moveX = -1; moveY = -1; break;
        case 1: moveX =  0; moveY = -1; break;
        case 2: moveX =  1; moveY = -1; break;
        case 3: moveX = -1; moveY =  0; break;
        case 4: moveX =  1; moveY =  0; break;
        case 5: moveX = -1; moveY =  1; break;
        case 6: moveX =  0; moveY =  1; break;
        case 7: moveX =  1; moveY =  1; break;
        case 8: moveX =  0; moveY =  0; break;
    }

    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> actionDistr(0, 10);

    actionLook(battlefield, moveX, moveY, cout);

    int randomInt = actionDistr(gen2);

    if (randomInt % 2 == 0) {
        actionMove(battlefield, moveX, moveY, cout);
        actionFire(battlefield, 0, 0, cout);
    } else {
        actionFire(battlefield, 0, 0, cout);
        actionMove(battlefield, moveX, moveY, cout);
    }
}

void BombBot::actionLook(Battlefield* battlefield, int x, int y, ostream &cout){

    int currentX = getRobotX();
    int currentY = getRobotY();

    for (int dx = -1; dx <= 1; ++dx) {  //iterate 3x3 grid
        for (int dy = -1; dy <= 1; ++dy) {
            int lookX = currentX + dx; //looks at the neighbouring robots
            int lookY = currentY + dy;

            if (dx==0 && dy ==0) continue;

            bool outOfBounds = lookX < 0 || lookX >= battlefield->battlefieldCols() ||
                            lookY < 0 || lookY >= battlefield->battlefieldRows();
            if (outOfBounds) continue;

            string playerStr = battlefield->getPlayer(lookX, lookY);
            if (!playerStr.empty()) {
                int lookRobotId = stoi(playerStr);
                Robot* robotLooked = nullptr;

                for (Robot* robot : battlefield->getAllRobots()) {
                    if (robot->getRobotID() == lookRobotId) {
                        robotLooked = robot;
                        break;
                    }
                }

                if (robotLooked) {
                    cout << "Robot " << robotLooked->getRobotName() 
                        << " is at position (" << lookX << ", " << lookY 
                        << ") looked by Robot " << getRobotName() << endl;
                }
            }
        }
    }
}

void BombBot::actionMove(Battlefield* battlefield, int x, int y, ostream &cout){
    if (abs(x) > 1 || abs(y) > 1 || (x == 0 && y == 0)) {
    cout << "Invalid move." << endl;
    return;  //check so it doesnt move to its own place or more than allowed
    }

    int currentX = getRobotX();
    int currentY = getRobotY();

    int nextX = currentX + x;
    int nextY = currentY + y;

    if (nextX < 0 || nextX >= battlefield->battlefieldCols() || nextY < 0 || nextY >= battlefield->battlefieldRows()) {
        cout << "Out of Bounds!." << endl;
        return;
    }
    battlefield->robotMove(getRobotID(), nextX, nextY);
    setRobotX(nextX);
    setRobotY(nextY);

    cout << "Robot " << getRobotName() << " move to position (" << nextX << ", " << nextY << ")" << endl;
}

void BombBot::actionFire(Battlefield* battlefield, int x, int y, ostream &cout){
    cout << "Robot " << getRobotName() << " is Firing!" << endl;
    if(bombs){
        int cx = getRobotX();
        int cy = getRobotY();
        int tx, ty, targetRobotId;
        bool invalidCoordinates, isHiding, isReflecting;
        bool killedRobot = false;
        Robot* targetRobot = nullptr;        
        cout << "BombBot bombed surrounding squares!\n";
        
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue; // Skip self
                tx = cx + dx; 
                ty = cy + dy;
                invalidCoordinates = tx < 0 || tx >= battlefield->battlefieldCols() || ty < 0 || ty >= battlefield->battlefieldRows();
                cout << "Explosion at (" << tx << ", " << ty << ")\n";
                if(!invalidCoordinates && battlefield->getPlayer(tx, ty) != ""){
                    Robot* targetRobot = nullptr;
                    string playerStr = battlefield->getPlayer(tx, ty);
                    int targetRobotId = stoi(playerStr);

                    for (Robot* robot : battlefield->getAllRobots()) {
                        if (robot->getRobotID() == targetRobotId) {
                            targetRobot = robot;
                            break;
                        }
                    }
                    isHiding = targetRobot->getRobotType() == HIDE && targetRobot->isHidden();
                    isReflecting = targetRobot->getRobotType() == REFLECTSHOT && targetRobot->isReflecting();
                    if (targetRobot && !isHiding && !isReflecting){
                        targetRobot->reduceLife();
                        incrementKills();
                        cout << "Robot " << getRobotName() << " killed Robot " << targetRobot->getRobotName() << endl;
                        battlefield->respawnRobot(targetRobot->getRobotID());
                        killedRobot = true;
                    }
                
                }
            }
        }
        if (!canUpgrade() || !killedRobot) return;

        // Upgrade
        Robot* upgradedRobot = nullptr;
        string name = getRobotName();
        int curX = getRobotX();
        int curY = getRobotY();
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> upgradeDist(1, 8);
        int choice = upgradeDist(gen);

        switch (choice) {
            case 1: upgradedRobot = new ScoutBot(x, y, name); break;
            case 2: upgradedRobot = new TrackBot(x, y, name); break;
            case 3: upgradedRobot = new JumpBot(x, y, name); break;
            case 4: upgradedRobot = new HideBot(x, y, name); break;
        }

        upgradedRobot->isUpgrading(getUpgradeCount() - 1, getLives(), getKills(), getShells());
        upgradedRobot->setRobotID(getRobotID());
        battlefield->robotUpgrade(upgradedRobot);
    }
    bombs--;
}

/**********************************************************************
 * ReflectShotBot Functions
 *********************************************************************/
void ReflectShotBot::actions(Battlefield* battlefield, ostream &cout){
    actionThink(battlefield, cout);
}

void ReflectShotBot::actionThink(Battlefield* battlefield, ostream &cout){
    cout << "Robot " << getRobotName() << " is thinking..." << endl;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> posDistr(0, 8);

    int directionMove = posDistr(gen);

    int currentX = getRobotX();
    int currentY = getRobotY();

    int moveX = 0, moveY = 0;

    switch (directionMove) {
        case 0: moveX = -1; moveY = -1; break;
        case 1: moveX =  0; moveY = -1; break;
        case 2: moveX =  1; moveY = -1; break;
        case 3: moveX = -1; moveY =  0; break;
        case 4: moveX =  1; moveY =  0; break;
        case 5: moveX = -1; moveY =  1; break;
        case 6: moveX =  0; moveY =  1; break;
        case 7: moveX =  1; moveY =  1; break;
        case 8: moveX =  0; moveY =  0; break;
    }

    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> actionDistr(0, 10);

    actionLook(battlefield, moveX, moveY, cout);

    int randomInt = actionDistr(gen2);

    if (randomInt % 2 == 0) {
        actionMove(battlefield, moveX, moveY, cout);
        actionFire(battlefield, moveX, moveY, cout);
    } else {
        actionFire(battlefield, moveX, moveY, cout);
        actionMove(battlefield, moveX, moveY, cout);
    }
}

void ReflectShotBot::actionLook(Battlefield* battlefield, int x, int y, ostream &cout){

    int currentX = getRobotX();
    int currentY = getRobotY();

    for (int dx = -1; dx <= 1; ++dx) {  //iterate 3x3 grid
        for (int dy = -1; dy <= 1; ++dy) {
            int lookX = currentX + dx; //looks at the neighbouring robots
            int lookY = currentY + dy;

            if (dx==0 && dy ==0) continue;

            bool outOfBounds = lookX < 0 || lookX >= battlefield->battlefieldCols() ||
                            lookY < 0 || lookY >= battlefield->battlefieldRows();
            if (outOfBounds) continue;

            string playerStr = battlefield->getPlayer(lookX, lookY);
            if (!playerStr.empty()) {
                int lookRobotId = stoi(playerStr);
                Robot* robotLooked = nullptr;

                for (Robot* robot : battlefield->getAllRobots()) {
                    if (robot->getRobotID() == lookRobotId) {
                        robotLooked = robot;
                        break;
                    }
                }

                if (robotLooked) {
                    cout << "Robot " << robotLooked->getRobotName() 
                        << " is at position (" << lookX << ", " << lookY 
                        << ") looked by Robot " << getRobotName() << endl;
                }
            }
        }
    }
}

void ReflectShotBot::actionMove(Battlefield* battlefield, int x, int y, ostream &cout){
    
    if (abs(x) > 1 || abs(y) > 1 || (x == 0 && y == 0)) {
    cout << "Invalid move." << endl;
    return;  //check so it doesnt move to its own place or more than allowed
    }

    int currentX = getRobotX();
    int currentY = getRobotY();

    int nextX = currentX + x;
    int nextY = currentY + y;

    if (nextX < 0 || nextX >= battlefield->battlefieldCols() || nextY < 0 || nextY >= battlefield->battlefieldRows()) {
        cout << "Out of Bounds!." << endl;
        return;
    }
    battlefield->robotMove(getRobotID(), nextX, nextY);
    setRobotX(nextX);
    setRobotY(nextY);

    cout << "Robot " << getRobotName() << " move to position (" << nextX << ", " << nextY << ")" << endl;
}

void ReflectShotBot::actionFire(Battlefield* battlefield, int x, int y, ostream &cout){
    cout << "Robot " << getRobotName() << " is Firing!" << endl;

    if (getShells() <= 0) {
        cout << "No more shots left! " << getRobotName() << " has fired its maximum shells.\n";
        return;
    }
    setShells(getShells() - 1);

    int targetX = getRobotX() + x;
    int targetY = getRobotY() + y;

    bool outOfBounds = targetX < 0 || targetX >= battlefield->battlefieldCols() ||
                    targetY < 0 || targetY >= battlefield->battlefieldRows();
    bool ownSelf = (x == getRobotX() && y == getRobotY());

    if (outOfBounds || ownSelf) {
        if (ownSelf) {
            cout << "Can't shoot own self!" << endl;
        } else {
            cout << "Out of Bounds!" << endl;
        }
        return;
    }

    if (!(battlefield->getPlayer(targetX, targetY)).empty()) {
        Robot* targetRobot = nullptr;
        string playerStr = battlefield->getPlayer(targetX, targetY);
        int targetRobotId = stoi(playerStr);

        for (Robot* robot : battlefield->getAllRobots()) {
            if (robot->getRobotID() == targetRobotId) {
                targetRobot = robot;
                break;
            }
        }

        if (!targetRobot) {
            cout << "Missed!" << endl;
            return;
        }

        if (targetRobot->getRobotType() == HIDE && targetRobot->isHidden()) {
            cout << "Shot missed. Robot is hidden." << endl;
            return;
        }

        if (targetRobot->getRobotType() == REFLECTSHOT && targetRobot->isReflecting()) {
            cout << "Shot reflected." << endl;
            reduceLife();
            battlefield->respawnRobot(getRobotID());
            if (!isAlive())
                cout << "Robot " << getRobotID() << " has been destroyed." << endl;
            return;
        }

        // Hit chance logic
        random_device rd;
        mt19937 gen(rd()), gen2(rd());
        uniform_int_distribution<> hitDist(1, 100);
        int hitChance = hitDist(gen);

        if (hitChance <= 70) {
            targetRobot->reduceLife();
            incrementKills();
            cout << "Robot " << getRobotName() << " killed Robot " << targetRobot->getRobotName() << endl;
            battlefield->respawnRobot(targetRobot->getRobotID());

            if (!canUpgrade()) return;

            // Upgrade
            Robot* upgradedRobot = nullptr;
            string name = getRobotName();
            int curX = getRobotX();
            int curY = getRobotY();

            uniform_int_distribution<> upgradeDist(1, 8);
            int choice = upgradeDist(gen2);

            switch (choice) {
                case 1: upgradedRobot = new HideBot(curX, curY, name); break;
                case 2: upgradedRobot = new JumpBot(curX, curY, name); break;
                case 3: upgradedRobot = new ScoutBot(curX, curY, name); break;
                case 4: upgradedRobot = new TrackBot(curX, curY, name); break;
            }

            upgradedRobot->isUpgrading(getUpgradeCount() - 1, getLives(), getKills(), getShells());
            upgradedRobot->setRobotID(getRobotID());
            battlefield->robotUpgrade(upgradedRobot);
            return;
        }
    }
    cout << "Missed!" << endl;
}

bool ReflectShotBot::isReflecting(){
    if (reflect <= 0)
        isReflect_ = false;
    reflect--;
    return isReflect_;
}

/**********************************************************************
 * ScoutBot Functions
 *********************************************************************/
void ScoutBot::actions(Battlefield* battlefield, ostream &cout){
    actionThink(battlefield, cout);
}

void ScoutBot::actionThink(Battlefield* battlefield, ostream &cout){
    cout << "Robot " << getRobotName() << " is thinking..." << endl;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> posDistr(0, 8);

    int directionMove = posDistr(gen);

    int currentX = getRobotX();
    int currentY = getRobotY();

    int moveX = 0, moveY = 0;

    switch (directionMove) {
        case 0: moveX = -1; moveY = -1; break;
        case 1: moveX =  0; moveY = -1; break;
        case 2: moveX =  1; moveY = -1; break;
        case 3: moveX = -1; moveY =  0; break;
        case 4: moveX =  1; moveY =  0; break;
        case 5: moveX = -1; moveY =  1; break;
        case 6: moveX =  0; moveY =  1; break;
        case 7: moveX =  1; moveY =  1; break;
        case 8: moveX =  0; moveY =  0; break;
    }

    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> actionDistr(0, 10);

    actionLook(battlefield, 0, 0, cout);

    int randomInt = actionDistr(gen2);

    if (randomInt % 2 == 0) {
        actionMove(battlefield, moveX, moveY, cout);
        actionFire(battlefield, moveX, moveY, cout);
    } else {
        actionFire(battlefield, moveX, moveY, cout);
        actionMove(battlefield, moveX, moveY, cout);
    }
}

void ScoutBot::actionLook(Battlefield* battlefield, int x, int y, ostream &cout){
    if (lookCount < MAX_LOOKS) {
        cout << "Robot " << getRobotName() << " scouting the whole battlefield and knows everyone's position!" << endl;
        lookCount++;
    }
}

void ScoutBot::actionMove(Battlefield* battlefield, int x, int y, ostream &cout){
    
    if (abs(x) > 1 || abs(y) > 1 || (x == 0 && y == 0)) {
    cout << "Invalid move." << endl;
    return;  //check so it doesnt move to its own place or more than allowed
    }

    int currentX = getRobotX();
    int currentY = getRobotY();

    int nextX = currentX + x;
    int nextY = currentY + y;

    if (nextX < 0 || nextX >= battlefield->battlefieldCols() || nextY < 0 || nextY >= battlefield->battlefieldRows()) {
        cout << "Out of Bounds!." << endl;
        return;
    }
    battlefield->robotMove(getRobotID(), nextX, nextY);
    setRobotX(nextX);
    setRobotY(nextY);

    cout << "Robot " << getRobotName() << " move to position (" << nextX << ", " << nextY << ")" << endl;
}

void ScoutBot::actionFire(Battlefield* battlefield, int x, int y, ostream &cout){
    cout << "Robot " << getRobotName() << " is Firing!" << endl;

    if (getShells() <= 0) {
        cout << "No more shots left! " << getRobotName() << " has fired its maximum shells.\n";
        return;
    }
    setShells(getShells() - 1);

    int targetX = getRobotX() + x;
    int targetY = getRobotY() + y;

    bool outOfBounds = targetX < 0 || targetX >= battlefield->battlefieldCols() ||
                    targetY < 0 || targetY >= battlefield->battlefieldRows();
    bool ownSelf = (x == getRobotX() && y == getRobotY());

    if (outOfBounds || ownSelf) {
        if (ownSelf) {
            cout << "Can't shoot own self!" << endl;
        } else {
            cout << "Out of Bounds!" << endl;
        }
        return;
    }

    if (!(battlefield->getPlayer(targetX, targetY)).empty()) {
        Robot* targetRobot = nullptr;
        string playerStr = battlefield->getPlayer(targetX, targetY);
        int targetRobotId = stoi(playerStr);

        for (Robot* robot : battlefield->getAllRobots()) {
            if (robot->getRobotID() == targetRobotId) {
                targetRobot = robot;
                break;
            }
        }

        if (!targetRobot) {
            cout << "Missed!" << endl;
            return;
        }

        if (targetRobot->getRobotType() == HIDE && targetRobot->isHidden()) {
            cout << "Shot missed. Robot is hidden." << endl;
            return;
        }

        if (targetRobot->getRobotType() == REFLECTSHOT && targetRobot->isReflecting()) {
            cout << "Shot reflected." << endl;
            reduceLife();
            battlefield->respawnRobot(getRobotID());
            if (!isAlive())
                cout << "Robot " << getRobotID() << " has been destroyed." << endl;
            return;
        }

        // Hit chance logic
        random_device rd;
        mt19937 gen(rd()), gen2(rd());
        uniform_int_distribution<> hitDist(1, 100);
        int hitChance = hitDist(gen);

        if (hitChance <= 70) {
            targetRobot->reduceLife();
            incrementKills();
            cout << "Robot " << getRobotName() << " killed Robot " << targetRobot->getRobotName() << endl;
            battlefield->respawnRobot(targetRobot->getRobotID());

            if (!canUpgrade()) return;

            // Upgrade
            Robot* upgradedRobot = nullptr;
            string name = getRobotName();
            int curX = getRobotX();
            int curY = getRobotY();

            uniform_int_distribution<> upgradeDist(1, 8);
            int choice = upgradeDist(gen2);

            switch (choice) {
                case 1: upgradedRobot = new LongShotBot(x, y, name); break;
                case 2: upgradedRobot = new SemiAutoBot(x, y, name); break;
                case 3: upgradedRobot = new ThirtyShotBot(x, y, name); break;
                case 4: upgradedRobot = new JumpBot(x, y, name); break;
                case 5: upgradedRobot = new HideBot(x, y, name); break;
                case 6: upgradedRobot = new ReflectShotBot(x, y, name); break;
                case 7: upgradedRobot = new HealBot(x, y, name); break;
                case 8: upgradedRobot = new BombBot(x, y, name); break;
            }

            upgradedRobot->isUpgrading(getUpgradeCount() - 1, getLives(), getKills(), getShells());
            upgradedRobot->setRobotID(getRobotID());
            battlefield->robotUpgrade(upgradedRobot);
            return;
        }
    }
    cout << "Missed!" << endl;
}

/**********************************************************************
 * TrackBot Functions
 *********************************************************************/
void TrackBot::actions(Battlefield* battlefield, ostream &cout){
    actionThink(battlefield, cout);
}

void TrackBot::actionThink(Battlefield* battlefield, ostream &cout){
    cout << "Robot " << getRobotName() << " is thinking..." << endl;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> posDistr(0, 8);

    int directionMove = posDistr(gen);

    int currentX = getRobotX();
    int currentY = getRobotY();

    int moveX = 0, moveY = 0;

    switch (directionMove) {
        case 0: moveX = -1; moveY = -1; break;
        case 1: moveX =  0; moveY = -1; break;
        case 2: moveX =  1; moveY = -1; break;
        case 3: moveX = -1; moveY =  0; break;
        case 4: moveX =  1; moveY =  0; break;
        case 5: moveX = -1; moveY =  1; break;
        case 6: moveX =  0; moveY =  1; break;
        case 7: moveX =  1; moveY =  1; break;
        case 8: moveX =  0; moveY =  0; break;
    }

    random_device rd2;
    mt19937 gen2(rd2());
    uniform_int_distribution<> actionDistr(0, 10);

    actionLook(battlefield, moveX, moveY, cout);

    int randomInt = actionDistr(gen2);

    if (randomInt % 2 == 0) {
        actionMove(battlefield, moveX, moveY, cout);
        actionFire(battlefield, moveX, moveY, cout);
    } else {
        actionFire(battlefield, moveX, moveY, cout);
        actionMove(battlefield, moveX, moveY, cout);
    }
}

void TrackBot::actionLook(Battlefield* battlefield, int x, int y, ostream &cout){
    int currentX = getRobotX();
    int currentY = getRobotY();


    for (int dx = -1; dx <= 1; ++dx) {  //iterate 3x3 grid
        for (int dy = -1; dy <= 1; ++dy) {
            int lookX = currentX + dx; //looks at the neighbouring robots
            int lookY = currentY + dy;

            if (dx==0 && dy ==0) continue;

            bool outOfBounds = lookX < 0 || lookX >= battlefield->battlefieldCols() ||
                            lookY < 0 || lookY >= battlefield->battlefieldRows();
            if (outOfBounds) continue;

            string playerStr = battlefield->getPlayer(lookX, lookY);
            if (!playerStr.empty()) {
                int lookRobotId = stoi(playerStr);
                Robot* robotLooked = nullptr;

                for (Robot* robot : battlefield->getAllRobots()) {
                    if (robot->getRobotID() == lookRobotId) {
                        robotLooked = robot;
                        break;
                    }
                }

                if (robotLooked) {
                    cout << "Robot " << robotLooked->getRobotName() 
                        << " is at position (" << lookX << ", " << lookY 
                        << ") looked by Robot " << getRobotName() << endl;
                }
            }
        }
    }

    // The tracked bots 
    for (int robotId : targets){
        for (Robot* robot : battlefield->getAllRobots()) {
            if (robot->getRobotID() == robotId) {
                cout << "Robot " << robot->getRobotName() << " is at position (" 
                << robot->getRobotX() << ", " << robot->getRobotY() << ") looked by Robot " << getRobotName() << endl;
            }
        }
    }
}

void TrackBot::actionMove(Battlefield* battlefield, int x, int y, ostream &cout){
    
    if (abs(x) > 1 || abs(y) > 1 || (x == 0 && y == 0)) {
    cout << "Invalid move." << endl;
    return;  //check so it doesnt move to its own place or more than allowed
    }

    int currentX = getRobotX();
    int currentY = getRobotY();

    int nextX = currentX + x;
    int nextY = currentY + y;

    if (nextX < 0 || nextX >= battlefield->battlefieldCols() || nextY < 0 || nextY >= battlefield->battlefieldRows()) {
        cout << "Out of Bounds!." << endl;
        return;
    }
    battlefield->robotMove(getRobotID(), nextX, nextY);
    setRobotX(nextX);
    setRobotY(nextY);

    cout << "Robot " << getRobotName() << " move to position (" << nextX << ", " << nextY << ")" << endl;
}

void TrackBot::actionFire(Battlefield* battlefield, int x, int y, ostream &cout){
    cout << "Robot " << getRobotName() << " is Firing!" << endl;

    if (getShells() <= 0) {
        cout << "No more shots left! " << getRobotName() << " has fired its maximum shells.\n";
        return;
    }
    setShells(getShells() - 1);

    int targetX = getRobotX() + x;
    int targetY = getRobotY() + y;

    bool outOfBounds = targetX < 0 || targetX >= battlefield->battlefieldCols() ||
                    targetY < 0 || targetY >= battlefield->battlefieldRows();
    bool ownSelf = (x == getRobotX() && y == getRobotY());

    if (outOfBounds || ownSelf) {
        if (ownSelf) {
            cout << "Can't shoot own self!" << endl;
        } else {
            cout << "Out of Bounds!" << endl;
        }
        return;
    }

    // Focus on tracked targets if nearby
    bool found = false;
    for (int robotId : targets){
        for (Robot* robot : battlefield->getAllRobots()) {
            if (robot->getRobotID() != robotId) continue;

            int dx = robot->getRobotX() - getRobotX();
            int dy = robot->getRobotY() - getRobotY();

            bool isAdjacent = (abs(dx) <= 1 && abs(dy) <= 1) && !(dx == 0 && dy == 0);
            if (isAdjacent) {
                targetX = robot->getRobotX();
                targetY = robot->getRobotY();
                found = true;
                break; 
            }
        }
        if (found) break; 
    }

    if (!(battlefield->getPlayer(targetX, targetY)).empty()) {
        Robot* targetRobot = nullptr;
        string playerStr = battlefield->getPlayer(targetX, targetY);
        int targetRobotId = stoi(playerStr);

        for (Robot* robot : battlefield->getAllRobots()) {
            if (robot->getRobotID() == targetRobotId) {
                targetRobot = robot;
                break;
            }
        }
        if (!targetRobot) {
            cout << "Missed!" << endl;
            return;
        }

        if (targetRobot->getRobotType() == HIDE && targetRobot->isHidden()) {
            cout << "Shot missed. Robot is hidden." << endl;
            return;
        }

        if (targetRobot->getRobotType() == REFLECTSHOT && targetRobot->isReflecting()) {
            cout << "Shot reflected." << endl;
            reduceLife();
            battlefield->respawnRobot(getRobotID());
            if (!isAlive())
                cout << "Robot " << getRobotID() << " has been destroyed." << endl;
            return;
        }

        // Hit chance logic
        random_device rd;
        mt19937 gen(rd()), gen2(rd());
        uniform_int_distribution<> hitDist(1, 100);
        int hitChance = hitDist(gen);

        if (hitChance <= 70) {
            targetRobot->reduceLife();
            incrementKills();
            cout << "Robot " << getRobotName() << " killed Robot " << targetRobot->getRobotName() << endl;
            battlefield->respawnRobot(targetRobot->getRobotID());

            if (!canUpgrade()) return;

            // Upgrade
            Robot* upgradedRobot = nullptr;
            string name = getRobotName();
            int curX = getRobotX();
            int curY = getRobotY();

            uniform_int_distribution<> upgradeDist(1, 8);
            int choice = upgradeDist(gen2);

            switch (choice) {
                case 1: upgradedRobot = new LongShotBot(x, y, name); break;
                case 2: upgradedRobot = new SemiAutoBot(x, y, name); break;
                case 3: upgradedRobot = new ThirtyShotBot(x, y, name); break;
                case 4: upgradedRobot = new JumpBot(x, y, name); break;
                case 5: upgradedRobot = new HideBot(x, y, name); break;
                case 6: upgradedRobot = new ReflectShotBot(x, y, name); break;
                case 7: upgradedRobot = new HealBot(x, y, name); break;
                case 8: upgradedRobot = new BombBot(x, y, name); break;
            }

            upgradedRobot->isUpgrading(getUpgradeCount() - 1, getLives(), getKills(), getShells());
            upgradedRobot->setRobotID(getRobotID());
            battlefield->robotUpgrade(upgradedRobot);
            return;
        }
    }
    cout << "Missed!" << endl;
}

//khayrin's main
// random_device rd;
        // mt19937 gen(rd()), gen2(rd()), gen3(rd()), gen4(rd());

        // uniform_int_distribution<> moveDistr(1, 4);
        // int move = moveDistr(gen);

        // uniform_int_distribution<> dirDistr(-1, 1);
        // int x = dirDistr(gen2);
        // int y = dirDistr(gen3);
        
        // switch(move){
        //     case 1: // Think
        //         currentPlayer->actionThink(battlefield);
        //         cout << currentPlayer->getRobotName() << " is thinking" << endl;
        //         outFile << currentPlayer->getRobotName() << " is thinking" << endl;
        //         break;
        //     case 2: // Look
        //         currentPlayer->actionLook(battlefield, x, y);
        //         cout << currentPlayer->getRobotName() << " is looking" << endl;
        //         outFile << currentPlayer->getRobotName() << " is looking" << endl;
        //         break;
        //     case 3: // Fire
        //         kills = currentPlayer->getKills();
        //         currentPlayer->actionFire(battlefield, x, y);
        //         cout << currentPlayer->getRobotName() << " is shooting..." << endl;
        //         outFile << currentPlayer->getRobotName() << " is shooting..." << endl;

        //         if (kills < currentPlayer->getKills()){ // upgrade 
        //             cout << currentPlayer->getRobotName() << " killed "; 
        //             cout << battlefield->getPlayer(currentPlayer->getRobotX()+x,currentPlayer->getRobotY()+y) << "!" << endl;
        //             outFile << currentPlayer->getRobotName() << " killed "; 
        //             outFile << battlefield->getPlayer(currentPlayer->getRobotX()+x,currentPlayer->getRobotY()+y) << "!" << endl;

        //             if (!currentPlayer->canUpgrade()) continue;

        //             currentPlayerType = currentPlayer->getRobotType();
        //             x = currentPlayer->getRobotX();
        //             y = currentPlayer->getRobotY();
        //             name = currentPlayer->getRobotName();

        //             if (currentPlayerType == GENERIC){
        //                 uniform_int_distribution<> upgradeDistr(1, 10);
        //                 upgrade = upgradeDistr(gen4);
        //                 switch(upgrade){
        //                     case 1: upgradedRobot = new ScoutBot(x, y, name); break;
        //                     case 2: upgradedRobot = new TrackBot(x, y, name); break;
        //                     case 3: upgradedRobot = new LongShotBot(x, y, name); break;
        //                     case 4: upgradedRobot = new SemiAutoBot(x, y, name); break;
        //                     case 5: upgradedRobot = new ThirtyShotBot(x, y, name); break;
        //                     case 6: upgradedRobot = new JumpBot(x, y, name); break;
        //                     case 7: upgradedRobot = new HideBot(x, y, name); break;
        //                     case 8: upgradedRobot = new ReflectShotBot(x, y, name); break;
        //                     case 9: upgradedRobot = new HealBot(x, y, name); break;
        //                     case 10: upgradedRobot = new BombBot(x, y, name); break;
        //                 }
        //             } else if (currentPlayerType == SCOUT || currentPlayerType == TRACK){
        //                 uniform_int_distribution<> upgradeDistr(1, 8);
        //                 upgrade = upgradeDistr(gen4);
        //                 switch(upgrade){
        //                     case 1: upgradedRobot = new LongShotBot(x, y, name); break;
        //                     case 2: upgradedRobot = new SemiAutoBot(x, y, name); break;
        //                     case 3: upgradedRobot = new ThirtyShotBot(x, y, name); break;
        //                     case 4: upgradedRobot = new JumpBot(x, y, name); break;
        //                     case 5: upgradedRobot = new HideBot(x, y, name); break;
        //                     case 6: upgradedRobot = new ReflectShotBot(x, y, name); break;
        //                     case 7: upgradedRobot = new HealBot(x, y, name); break;
        //                     case 8: upgradedRobot = new BombBot(x, y, name); break;
        //                 }
        //             } else if (currentPlayerType == HIDE || currentPlayerType == JUMP){
        //                 uniform_int_distribution<> upgradeDistr(1, 8);
        //                 upgrade = upgradeDistr(gen4);
        //                 switch(upgrade){
        //                     case 1: upgradedRobot = new LongShotBot(x, y, name); break;
        //                     case 2: upgradedRobot = new SemiAutoBot(x, y, name); break;
        //                     case 3: upgradedRobot = new ThirtyShotBot(x, y, name); break;
        //                     case 4: upgradedRobot = new ScoutBot(x, y, name); break;
        //                     case 5: upgradedRobot = new TrackBot(x, y, name); break;
        //                     case 6: upgradedRobot = new ReflectShotBot(x, y, name); break;
        //                     case 7: upgradedRobot = new HealBot(x, y, name); break;
        //                     case 8: upgradedRobot = new BombBot(x, y, name); break;
        //                 }
        //             } else {
        //                 uniform_int_distribution<> upgradeDistr(1, 4);
        //                 upgrade = upgradeDistr(gen4);
        //                 switch(upgrade){
        //                     case 1: upgradedRobot = new ScoutBot(x, y, name); break;
        //                     case 2: upgradedRobot = new TrackBot(x, y, name); break;
        //                     case 3: upgradedRobot = new JumpBot(x, y, name); break;
        //                     case 4: upgradedRobot = new HideBot(x, y, name); break;
        //                 }
        //             }
        //             upgradedRobot->addUpgrade(currentPlayer->getUpgradeCount());
        //             upgradedRobot->setLives(currentPlayer->getLives());
        //             upgradedRobot->setKills(currentPlayer->getKills());
        //             upgradedRobot->setShells(currentPlayer->getShells());
        //             battlefield->robotUpgrade(upgradedRobot);

        //             cout << currentPlayer->getRobotName() << " upgraded!" << endl;
        //             outFile << currentPlayer->getRobotName() << " upgraded!" << endl;
        //             delete upgradedRobot;
        //             upgradedRobot = nullptr; 
        //         }
        //         break;
        //     case 4: // Move
        //         currentPlayer->actionMove(battlefield, x, y);
        //         break;
        // }

////




// void GenericRobot::upgradeRobot(Battlefield* battlefield, int upgradeType) {
//     if (upgradeCount >= MAX_UPGRADE) {
//         cout << "Max upgrade reached.";
//         return;
//     }

//     Robot* current = battlefield->getCurrentPlayer();
//     if (!current) return;  //prevents dereferencing of nullptr

//     int x = current->getRobotX();
//     int y = current->getRobotY();
//     string name = current->getRobotName();

//     if (robotUpgraded) {
//         delete robotUpgraded;
//         robotUpgraded = nullptr;
//     } //clear memory before new upgrade

//     switch (upgradeType) {
//         case 1: robotUpgraded = new ScoutBot(x, y, name); break;
//         case 5: robotUpgraded = new ThirtyShotBot(x, y, name); break;
//         case 6: robotUpgraded = new JumpBot(x, y, name); break;
//         case 7: robotUpgraded = new HideBot(x, y, name); break;
//         case 8: robotUpgraded = new ReflectShotBot(x, y, name); break;
//         case 9: robotUpgraded = new HealBot(x, y, name); break;
//         case 10: robotUpgraded = new BombBot(x, y, name); break;
//         default: return;
//     }

    
//     upgradeCount++;
//     upgrade = false;
// }


