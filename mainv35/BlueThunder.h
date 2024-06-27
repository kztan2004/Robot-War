#pragma once
#include "ShootingRobot.h"
#include "Controller.h"
using namespace std;

class BlueThunder : virtual public ShootingRobot
{
private:
    int count;

public:
    BlueThunder(int x, int y, string n);
    BlueThunder(const Robot *other);
    virtual void fire();
    virtual void action();
};