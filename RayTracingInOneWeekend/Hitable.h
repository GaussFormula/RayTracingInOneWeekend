#pragma once
#include "Ray.h"
#include "AABB.h"
#include <memory>

class Material;

struct HitRecord
{
    float t = 0.0f;
    vec3 point;
    vec3 normal;
    std::shared_ptr<Material> material;
};

class Hitable
{
public:
    virtual bool Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord) const = 0;
    virtual bool BoundingBox(const float& t0, const float& t1, AABB& aabb, const float time = 0.0f)const = 0;
    virtual ~Hitable(){}
};