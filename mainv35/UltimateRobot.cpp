#include "UltimateRobot.h"

UltimateRobot::UltimateRobot(int x, int y, string n) : Robot(x, y, n) { type = "UltimateRobot"; }

UltimateRobot::UltimateRobot(const Robot *other) : Robot(other) { type = "UltimateRobot"; }

void UltimateRobot::fire()
{
    int kX, kY;
    do
    {
        kX = rand() % Bptr->getROWS();
        kY = rand() % Bptr->getCOLS();
    } while (Bptr->validTarget(kX - getX(), kY - getY()));
    setTarget(kX, kY);
    cout << "Fire at (" << kX << "," << getY() + kY << ")" << endl;
    *outfile << "Fire at (" << kX << "," << getY() + kY << ")" << endl;
}

void UltimateRobot::look()
{
    int x = 0;
    int y = 0;
    lookRect[0] = getX() + x - 1;
    lookRect[1] = getX() + x + 1;
    lookRect[2] = getY() + y - 1;
    lookRect[3] = getY() + y + 1;
    Bptr->checkLook();
}

void UltimateRobot::step()
{
    int dir, kX, kY;
    if (lCount > 0)
    {
        dir = rand() % lCount; // random choose to step
        kX = lookRobot[dir][0] - getX();
        kY = lookRobot[dir][1] - getY();
        lCount--;
    }
    else
    {
        do
        {
            dir = rand() % 8;
        } while (Bptr->validTarget(DIR[dir][0], DIR[dir][1]));
        kX = DIR[dir][0];
        kY = DIR[dir][1];
    }
    setX(getX() + kX);
    setY(getY() + kY);
    setTarget(getX(), getY());
    cout << "Step to (" << getX() << "," << getY() << ")" << endl;
    *outfile << "Step to (" << getX() << "," << getY() << ")" << endl;
}

void UltimateRobot::action()
{
    look();
    step();
    fire();
    fire();
    fire();
}