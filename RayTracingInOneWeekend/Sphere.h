#pragma once

#include "vec3.h"
#include "Ray.h"
class Sphere
{
public:
    Sphere(const vec3& origin,const float& radius)
        :myOrigin(origin)
        ,myRadius(radius)
    {}

    float GetRadius()const
    {
        return myRadius;
    }

    vec3 GetOrigin()const
    {
        return myOrigin;
    }

    bool BeHitByRay(const Ray& ray)const;

    float BeHitByRay_V2(const Ray& ray)const;

private:

    float myRadius;
    vec3 myOrigin;
};