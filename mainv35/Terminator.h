#pragma once
#include "SeeingRobot.h"
#include "SteppingRobot.h"
#include "Controller.h"

using namespace std;

class Terminator : virtual public SeeingRobot, virtual public SteppingRobot
{
public:
    Terminator(int x, int y, string n);
    Terminator(const Robot *other);
    virtual void step();
    virtual void look();
    virtual void action();
};