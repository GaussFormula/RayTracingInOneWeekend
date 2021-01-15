#pragma once

#include "Hitable.h"
class Sphere :public Hitable
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

    virtual bool Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const;

private:

    float myRadius;
    vec3 myOrigin;
};