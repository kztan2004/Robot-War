#pragma once
#include "ShootingRobot.h"
#include "SeeingRobot.h"
#include "SteppingRobot.h"
#include "Controller.h"
using namespace std;

class TerminatorRoboCop : virtual public ShootingRobot, virtual public SeeingRobot, virtual public SteppingRobot
{
public:
    TerminatorRoboCop(int x, int y, string n);
    TerminatorRoboCop(const Robot *other);
    virtual void fire();
    virtual void look();
    virtual void step();
    virtual void action();
};