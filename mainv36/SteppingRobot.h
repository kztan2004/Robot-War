#pragma once
#include "Robot.h"

class SteppingRobot : virtual public Robot
{
public:
    virtual void step() = 0;
    virtual ~SteppingRobot();
};