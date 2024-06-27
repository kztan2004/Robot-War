#include "Robot.h"

int Robot::DIR[9][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {0, 0}};

Robot::Robot() {}

Robot::Robot(int x, int y, string n = "A") : robotsPositionX(x), robotsPositionY(y), name(n)
{
    lives = 3;
    killCount = 0;
    active = true;
    resetTarget();
}

Robot::Robot(const Robot *other)
{
    robotsPositionX = other->robotsPositionX;
    robotsPositionY = other->robotsPositionY;
    name = other->name;
    lives = other->lives;
    Bptr = other->Bptr;
    outfile = other->outfile;
    killCount = 0;
    resetTarget();
}

void Robot::kill()
{
    lives--;
    active = false;
}

void Robot::resetTarget()
{
    tCount = 0;
    lCount = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 2; j++)
            firePos[i][j] = -1;

    for (int i = 0; i < 4; i++)
        lookRect[i] = -1;

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 2; j++)
            lookRobot[i][j] = -1;
}

void Robot::setTarget(int x, int y)
{
    firePos[tCount][0] = x;
    firePos[tCount][1] = y;
    tCount++;
}

bool Robot::checkTarget(int fireX, int fireY) const
{
    for (int i = 0; i < tCount; i++)
    {
        if (fireX == firePos[i][0] && fireY == firePos[i][1])
            return true;
    }
    return false;
}

void Robot::addLook(int posX, int posY)
{
    lookRobot[lCount][0] = posX;
    lookRobot[lCount][1] = posY;
    lCount++;
}

void Robot::switchActive() { active = true; }

void Robot::addKill() { killCount++; }

void Robot::setX(int x) { robotsPositionX = x; }
void Robot::setY(int y) { robotsPositionY = y; }
void Robot::setConnect(Controller *ptr, ofstream *optr)
{
    Bptr = ptr;
    outfile = optr;
}
int Robot::getX() const { return robotsPositionX; }
int Robot::getY() const { return robotsPositionY; }
int Robot::getLives() const { return lives; }
string Robot::getType() const { return type; }
string Robot::getName() const { return name; }
bool Robot::getUpgrade() const { return killCount >= 3; }
bool Robot::getStatus() const { return lives == 0; }
bool Robot::getActive() const { return active; }

// Destructor
Robot::~Robot(){};

// Overloaded operators for comparison
bool Robot::operator!=(const Robot &r) const
{
    bool result = false;
    for (int i = 0; i < tCount; i++)
        if (firePos[i][0] == r.robotsPositionX && firePos[i][1] == r.robotsPositionY)
            result = true;
    return result;
}
bool Robot::operator==(const Robot &r) const
{
    return (r.robotsPositionX >= lookRect[0] && r.robotsPositionX <= lookRect[1] && r.robotsPositionY >= lookRect[2] && r.robotsPositionY <= lookRect[3]);
}