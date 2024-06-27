#pragma once
#include <iostream>
#include <fstream>

class Controller;

using namespace std;

class Robot
{
private:
    int robotsPositionX;
    int robotsPositionY;
    string name;

protected:
    int firePos[4][2];
    int tCount;
    int lookRobot[9][2];
    int lCount;
    int lookRect[4];
    int killCount;
    int lives;
    bool active;
    string type;
    static int DIR[9][2];
    Controller *Bptr;
    ofstream *outfile;

public:
    Robot();
    Robot(int x, int y, string n);
    Robot(const Robot *other);

    // Pure virtual methods for derived classes
    virtual void action() = 0;
    // Setters and getters

    void kill();

    void resetTarget();

    void setTarget(int x, int y);

    bool checkTarget(int fireX, int fireY) const;

    void addLook(int posX, int posY);

    void switchActive();

    void addKill();

    void setX(int x);
    void setY(int y);
    void setConnect(Controller *ptr, ofstream *optr);

    int getX() const;
    int getY() const;
    int getLives() const;
    string getType() const;
    string getName() const;
    bool getUpgrade() const;
    bool getStatus() const;
    bool getActive() const;

    // Destructor
    virtual ~Robot();

    // Overloaded operators for comparison
    virtual bool operator!=(const Robot &r) const;
    virtual bool operator==(const Robot &r) const;
};