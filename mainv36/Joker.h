#pragma once
#include "ShootingRobot.h"
#include "SeeingRobot.h"
#include "Controller.h"
using namespace std;

class Joker : virtual public ShootingRobot, virtual public SeeingRobot
{
public:
    Joker(int x, int y, string n);
    Joker(const Robot *other);
    virtual void fire();
    virtual void look();
    virtual void action();
};