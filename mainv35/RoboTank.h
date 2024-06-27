#pragma once
#include "ShootingRobot.h"
#include "Controller.h"
using namespace std;

class RoboTank : virtual public ShootingRobot
{
public:
    RoboTank(int x, int y, string n);
    RoboTank(const Robot *other);
    virtual void fire();
    virtual void action();
};