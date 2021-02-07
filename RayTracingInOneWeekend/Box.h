#pragma once
#include "Hitable.h"
#include "HitableList.h"
class Box :public Hitable
{
public:
    Box(){}
    Box(const vec3& p0, const vec3& p1, const std::shared_ptr<Material>& material);
    virtual bool Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const override;
    virtual bool BoundingBox(const float& t0, const float& t1, AABB& aabb, const float time = 0.0f)const override
    {
        aabb = AABB(pmin, pmax);
        return true;
    }
private:
    vec3 pmin, pmax;
    std::shared_ptr<HitableList> myList;
};