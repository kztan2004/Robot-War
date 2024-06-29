#pragma once
#include "Robot.h"

class MovingRobot : virtual public Robot
{
public:
    virtual void move() = 0;
    virtual ~MovingRobot();
};