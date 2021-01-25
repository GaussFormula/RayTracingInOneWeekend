#pragma once
#include "vec3.h"

class Ray
{
public:
    Ray(const vec3& origin,const vec3&direction,const float& time=0.0f)
        :myOrigin(origin)
        ,myDirection(direction)
        ,myExistTime(time)
    {}

    Ray()
    {
        
    }

    Ray(const Ray& ray)
    {
        myDirection = ray.GetDirection();
        myOrigin = ray.GetOrigin();
    }

    vec3 GetOrigin()const
    {
        return myOrigin;
    }

    vec3 GetDirection()const
    {
        return myDirection;
    }

    float GetExistTime()const
    {
        return myExistTime;
    }

    vec3 PointAtParameter(const float& t)const
    {
        return myOrigin + (t * myDirection);
    }

private:
    vec3 myOrigin;
    vec3 myDirection;
    float myExistTime = 0.0f;
};