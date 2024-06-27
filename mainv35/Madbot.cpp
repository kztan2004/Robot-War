#include "Madbot.h"

Madbot::Madbot(int x, int y, string n) : Robot(x, y, n) { type = "Madbot"; }

Madbot::Madbot(const Robot *other) : Robot(other) { type = "Madbot"; }

void Madbot::fire()
{
    int dir;
    do
    {
        dir = rand() % 8;
    } while (Bptr->validTarget(DIR[dir][0], DIR[dir][1]));
    setTarget(getX() + DIR[dir][0], getY() + DIR[dir][1]);
    cout << "Fire at (" << getX() + DIR[dir][0] << "," << getY() + DIR[dir][1] << ")" << endl;
    *outfile << "Fire at (" << getX() + DIR[dir][0] << "," << getY() + DIR[dir][1] << ")" << endl;
}

void Madbot::action()
{
    fire();
}