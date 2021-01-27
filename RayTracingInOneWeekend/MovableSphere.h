#pragma once

#include "Hitable.h"

class MovableSphere :public Hitable
{
public:
    MovableSphere()
        :myTime0(0.0f)
        ,myTime1(0.0f)
        ,myRadius(0.0f)
    {}

    MovableSphere(const vec3& center0,const vec3& center1,
        const float& time0,const float& time1,const float& radius,const std::shared_ptr<Material>& material)
        :myOrigin0(center0)
        ,myOrigin1(center1)
        ,myTime0(time0)
        ,myTime1(time1)
        ,myRadius(radius)
        ,myMaterial(material)
    {}

    std::shared_ptr<Material> GetMaterial()const
    {
        return myMaterial;
    }

    float GetRadius()const
    {
        return myRadius;
    }

    virtual bool Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const override;

    virtual bool BoundingBox(const float& t0, const float& t1, AABB& aabb, const float time = 0.0f)const override;

    vec3 GetCurrentPositionByTime(const float& currentTime)const;

    AABB GetCurrentAABBByTime(const float& currentTime)const;

private:
    float myTime0, myTime1;
    float myRadius;
    vec3 myOrigin0, myOrigin1;
    std::shared_ptr<Material> myMaterial;
};