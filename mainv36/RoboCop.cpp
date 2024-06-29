#include "RoboCop.h"

RoboCop::RoboCop(int x, int y, string n) : Robot(x, y, n) { type = "RoboCop"; }

RoboCop::RoboCop(const Robot *other) : Robot(other) { type = "RoboCop"; }

void RoboCop::move()
{
    int dir;
    bool lookR;
    int mCount = 0;
    do
    {
        lookR = false;
        dir = rand() % 8;
        if (lCount > 0)
        {
            for (int i = 0; i < lCount; i++)
            {
                if (getX() + DIR[dir][0] == lookRobot[i][0] && getY() + DIR[dir][1] == lookRobot[i][1])
                {
                    lookR = true;
                    break;
                }
            }
        }
        mCount++;
        if (mCount > 30)
        {
            dir = 8;
            break;
        }
    } while (Bptr->validTarget(DIR[dir][0], DIR[dir][1]) || lookR);
    setX(getX() + DIR[dir][0]);
    setY(getY() + DIR[dir][1]);
    cout << "Move to (" << getX() << "," << getY() << ")" << endl;
    *outfile << "Move to (" << getX() << "," << getY() << ")" << endl;
}

void RoboCop::fire()
{
    int kX, kY;
    do
    {
        kX = rand() % 20 - 10;
        kY = rand() % 20 - 10;
    } while (Bptr->validTarget(kX, kY) || abs(kX) + abs(kY) > 10);
    setTarget(getX() + kX, getY() + kY);
    cout << "Fire at (" << getX() + kX << "," << getY() + kY << ")" << endl;
    *outfile << "Fire at (" << getX() + kX << "," << getY() + kY << ")" << endl;
}

void RoboCop::look()
{
    int x = 0;
    int y = 0;
    lookRect[0] = getX() + x - 1;
    lookRect[1] = getX() + x + 1;
    lookRect[2] = getY() + y - 1;
    lookRect[3] = getY() + y + 1;
    Bptr->checkLook();
}

void RoboCop::action()
{
    look();
    move();
    fire();
    fire();
    fire();
}