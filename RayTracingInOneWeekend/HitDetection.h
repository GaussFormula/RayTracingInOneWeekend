#pragma once
#include "Sphere.h"
#include "Ray.h"
#include "MovableSphere.h"

// For detecting a hit between sphere and ray
class HitDetection 
{
public:
    HitDetection(float _a,float _b,float _c)
        :a(_a)
        ,b(_b)
        ,c(_c)
        ,discriminant(_b*_b-4*_a*_c)
    {

    }

    HitDetection(const Sphere& sphere, const Ray& ray);

    HitDetection(const MovableSphere& sphere, const Ray& ray);

    float GetDiscriminant()const
    {
        return discriminant;
    }

    float GetRoot1()const;

    float GetRoot2()const;
    

private:
    float a;
    float b;
    float c;
    float discriminant;
};