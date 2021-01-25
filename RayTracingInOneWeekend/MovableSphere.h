#pragma once

#include "Hitable.h"
#include "Movable.h"

class MovableSphere :public Hitable,public Movable
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

    virtual bool Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const override;

    virtual vec3 GetCurrentPositionByTime(const float& currentTime)const override;

private:
    float myTime0, myTime1;
    float myRadius;
    vec3 myOrigin0, myOrigin1;
    std::shared_ptr<Material> myMaterial;
};