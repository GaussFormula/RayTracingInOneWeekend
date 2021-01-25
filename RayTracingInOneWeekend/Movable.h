#pragma once

#include "vec3.h"
class Movable
{
public:
    virtual vec3 GetCurrentPositionByTime(const float& currentTime)const = 0;
};