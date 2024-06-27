#pragma once
#include "Robot.h"

class ShootingRobot : virtual public Robot
{
public:
    virtual void fire() = 0;
    virtual ~ShootingRobot();
};