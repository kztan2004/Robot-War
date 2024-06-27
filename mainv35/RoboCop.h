#pragma once
#include "MovingRobot.h"
#include "ShootingRobot.h"
#include "SeeingRobot.h"
#include "Controller.h"

using namespace std;

class RoboCop : virtual public MovingRobot, virtual public ShootingRobot, virtual public SeeingRobot
{
public:
    RoboCop(int x, int y, string n);
    RoboCop(const Robot *other);
    virtual void move();
    virtual void fire();
    virtual void look();
    virtual void action();
};