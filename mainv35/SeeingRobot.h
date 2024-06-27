#pragma once
#include "Robot.h"

class SeeingRobot : virtual public Robot
{
public:
    virtual void look() = 0;
    virtual ~SeeingRobot();
};