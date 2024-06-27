#pragma once
#include "ShootingRobot.h"
#include "Controller.h"
using namespace std;

class Madbot : virtual public ShootingRobot
{
public:
    Madbot(int x, int y, string n);
    Madbot(const Robot *other);
    virtual void fire();
    virtual void action();
};