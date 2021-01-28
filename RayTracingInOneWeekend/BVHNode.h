#pragma once

#include <memory>
#include <vector>

#include "Hitable.h"

class BVHNode :public Hitable
{
public:
    BVHNode(){}

    BVHNode(std::vector<std::shared_ptr<Hitable>>& list,const int&start, const int& n, const float& time0, const float& time1);

    virtual bool Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const override;
    virtual bool BoundingBox(const float& t0, const float& t1, AABB& aabb, const float time = 0.0f)const override;

    BVHNode(const BVHNode& rhs)
    {
        left = rhs.left;
        right = rhs.right;
        box = rhs.box;
    }

    std::shared_ptr<Hitable> left;
    std::shared_ptr<Hitable> right;
    AABB box;
};