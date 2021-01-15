#pragma once
#include "Ray.h"

struct HitRecord
{
    float t;
    vec3 point;
    vec3 normal;
};

class Hitable
{
public:
    virtual bool Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord) const = 0;
};