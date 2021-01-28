#pragma once
#include "Ray.h"
class AABB
{
public:

    AABB(){}

    AABB(const vec3& a,const vec3& b)
        :myMin(a)
        ,myMax(b)
    {}

    vec3 GetMin()const
    {
        return myMin;
    }

    vec3 GetMax()const
    {
        return myMax;
    }

    void SetMin(const vec3& newMin)
    {
        myMin = newMin;
    }

    void SetMax(const vec3& newMax)
    {
        myMax = newMax;
    }

    bool Hit(const Ray& ray, const float& tmin, const float& tmax)const;

    static AABB SurroundingBox(AABB& box0, AABB& box1);

private:
    vec3 myMin, myMax;
};