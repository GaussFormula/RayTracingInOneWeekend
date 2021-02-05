#pragma once
#include "Hitable.h"
#include "Material.h"
#include <memory>

class XZRectangle :public Hitable
{
public:
    XZRectangle()
    {
        x0 = x1 = z0 = z1 = y = 0.0f;
    }

    XZRectangle(const float&_x0,const float&_x1,const float&_z0,const float&_z1,const float& _y,const std::shared_ptr<Material>& material)
        :x0(_x0)
        ,x1(_x1)
        ,z0(_z0)
        ,z1(_z1)
        ,y(_y)
        ,myMaterial(material)
    {}

    virtual bool Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const override;
    virtual bool BoundingBox(const float& t0, const float& t1, AABB& aabb, const float time = 0.0f)const override;

    float x0, x1, z0, z1, y;

private:
    std::shared_ptr<Material> myMaterial;
};