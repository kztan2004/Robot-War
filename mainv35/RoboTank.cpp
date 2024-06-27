#include "RoboTank.h"

RoboTank::RoboTank(int x, int y, string n) : Robot(x, y, n) { type = "RoboTank"; }

RoboTank::RoboTank(const Robot *other) : Robot(other) { type = "RoboTank"; }

void RoboTank::fire()
{
    int kX, kY;
    do
    {
        kX = rand() % Bptr->getROWS();
        kY = rand() % Bptr->getCOLS();
    } while (kX == getX() && kY == getY());
    setTarget(kX, kY);
    cout << "Fire at (" << kX << "," << kY << ")" << endl;
    *outfile << "Fire at (" << kX << "," << kY << ")" << endl;
}

void RoboTank::action()
{
    fire();
}