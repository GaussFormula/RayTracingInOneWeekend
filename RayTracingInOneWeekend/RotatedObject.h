#pragma once
#include "Hitable.h"
#include <memory>
class YAxisRotatedObject :public Hitable
{
public:
    YAxisRotatedObject(const std::shared_ptr<Hitable>& p, const float& angle);
    virtual bool Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const override;
    virtual bool BoundingBox(const float& t0, const float& t1, AABB& aabb, const float time = 0.0f)const override
    {
        aabb = (*this).aabb;
        return hasBox;
    }

private:
    vec3 RotateCalculate(const vec3& vec)const
    {
        return vec3(vec[0] * cos_theta + sin_theta * vec[2], vec[1], -sin_theta * vec[0] + cos_theta * vec[2]);
    }

    AABB aabb;
    float sin_theta = 0.0f;
    float cos_theta = 0.0f;
    bool hasBox;
    std::shared_ptr<Hitable> ptr;
};