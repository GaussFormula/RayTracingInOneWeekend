#pragma once
#include "Hitable.h"
#include "Material.h"
#include <memory>
class YZRectangle :public Hitable
{
public:
    YZRectangle()
    {
        y0 = y1 = z0 = z1 = x = 0.0f;
    }

    YZRectangle(const float&_y0,const float&_y1,const float&_z0,const float&_z1,const float&_x,const std::shared_ptr<Material>&material)
        :y0(_y0)
        ,y1(_y1)
        ,z0(_z0)
        ,z1(_z1)
        ,x(_x)
        ,myMaterial(material)
    {}

    virtual bool BoundingBox(const float& t0, const float& t1, AABB& aabb, const float time = 0.0f)const override;
    virtual bool Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const override;

    float y0, y1, z0, z1, x;
private:
    std::shared_ptr<Material> myMaterial;
};