#include "Joker.h"

Joker::Joker(int x, int y, string n) : Robot(x, y, n) { type = "Joker"; }

Joker::Joker(const Robot *other) : Robot(other) { type = "Joker"; }

void Joker::fire()
{
    int kX, kY, dir, count;
    if (lCount > 0) // if looked Robot, shoot them
    {
        count = (lCount > 4) ? 4 : lCount;
        for (int i = 0; i < count; i++)
        {
            do
            {
                dir = rand() % lCount;
                kX = lookRobot[dir][0] - getX();
                kY = lookRobot[dir][1] - getY();
            } while (Bptr->validTarget(kX, kY));
            setTarget(getX() + kX, getY() + kY);
            cout << "Fire at (" << getX() + kX << "," << getY() + kY << ")" << endl;
            *outfile << "Fire at (" << getX() + kX << "," << getY() + kY << ")" << endl;
        }
    }
}

void Joker::look()
{
    int lX, lY;
    do
    {
        lX = rand() % 20 - 10;
        lY = rand() % 20 - 10;
    } while (Bptr->validTarget(lX, lY));
    cout << "look at (" << getX() + lX << "," << getY() + lY << ")" << endl;
    *outfile << "look at (" << getX() + lX << "," << getY() + lY << ")" << endl;
    lookRect[0] = getX() + lX - 1;
    lookRect[1] = getX() + lX + 1;
    lookRect[2] = getY() + lY - 1;
    lookRect[3] = getY() + lY + 1;
    Bptr->checkLook();
}

void Joker::action()
{
    look();
    fire();
}