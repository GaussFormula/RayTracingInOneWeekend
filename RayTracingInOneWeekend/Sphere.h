#pragma once

#include "Hitable.h"
#include <memory>

class Sphere :public Hitable
{
public:
    Sphere(const vec3& origin,const float& radius,const std::shared_ptr<Material>& material)
        :myOrigin(origin)
        ,myRadius(radius)
        ,myMaterial(material)
    {}

    float GetRadius()const
    {
        return myRadius;
    }

    vec3 GetOrigin()const
    {
        return myOrigin;
    }

    std::shared_ptr<Material> GetMaterial()const
    {
        return myMaterial;
    }

    bool BeHitByRay(const Ray& ray)const;

    float BeHitByRay_V2(const Ray& ray)const;

    virtual bool Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const;

    virtual ~Sphere(){}

public:


private:

    float                       myRadius;
    vec3                        myOrigin;
    std::shared_ptr<Material>   myMaterial;
};