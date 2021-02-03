#pragma once
#include "Hitable.h"
#include "Material.h"
#include <memory>
class XYRectangle :public Hitable
{
public:
    XYRectangle()
    {
        x0 = x1 = y0 = y1 = k = 0;
    }

    XYRectangle(const float&_x0,const float&_x1,const float&_y0,const float&_y1,const float&_k,const std::shared_ptr<Material>&_mat)
        :x0(_x0)
        ,x1(_x1)
        ,y0(_y0)
        ,y1(_y1)
        ,k(_k)
        ,myMaterial(_mat)
    {}

    virtual bool Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const override;

    virtual bool BoundingBox(const float& t0, const float& t1, AABB& aabb, const float time = 0.0f)const override;

    float x0, x1, y0, y1, k;

private:
    std::shared_ptr<Material> myMaterial;
};