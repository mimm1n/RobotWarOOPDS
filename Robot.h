#ifndef ROBOT_H
#define ROBOT_H

class Robot{
    private:
        int robotX = -1, robotY = -1; // x and y coordinates of the robot (x,y)
        // void setRobotName(string name);
        // void setRobotType(string type);
    
    protected:
        int killCount = 0;
        int lives = 3;
        string robotName = "";
        string robotType = "";

    public:
        Robot(int robotX, int robotY, string name, string type);
        virtual ~Robot();
        
        void setRobotX(int x);
        int getRobotX() const;

        void setRobotY(int y);
        int getRobotY() const;

        string getRobotName() const;
        string getRobotType() const;
};
#endif