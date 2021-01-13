#pragma once
#include "vec3.h"

class ray
{
public:
    ray(const vec3& origin,const vec3&direction)
        :myOrigin(origin)
        ,myDirection(direction)
    {}

    vec3 GetOrigin()const
    {
        return myOrigin;
    }

    vec3 GetDirection()const
    {
        return myDirection;
    }

    vec3 PointAtParameter(const float& t)
    {
        return myOrigin + (t * myDirection);
    }

private:
    vec3 myOrigin;
    vec3 myDirection;
};