#pragma once
#include "Hitable.h"
#include <memory>

class FlipNormalRectangle :public Hitable
{
public:
    FlipNormalRectangle(const std::shared_ptr<Hitable>& p)
        :ptr(p)
    {}
    virtual bool Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const override
    {
        if (ptr->Hit(ray, t_min, t_max, hitRecord))
        {
            hitRecord.normal = -1.0f * hitRecord.normal;
            return true;
        }
        return false;
    }
    virtual bool BoundingBox(const float& t0, const float& t1, AABB& aabb, const float time  = 0.0f )const override
    {
        return ptr->BoundingBox(t0, t1, aabb);
    }
private:
    std::shared_ptr<Hitable> ptr;
};