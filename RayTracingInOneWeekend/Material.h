#pragma once
#include "Ray.h"
#include "Hitable.h"

class Material
{
public:
    virtual bool Scatter(const Ray& ray, const HitRecord& record, vec3& attenuation, Ray& scattered)const = 0;
    virtual vec3 Emitted(const float& u, const float& v, const vec3& p)const
    {
        return vec3();
    }
};