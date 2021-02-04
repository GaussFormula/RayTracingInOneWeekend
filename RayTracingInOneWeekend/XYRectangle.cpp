#include "XYRectangle.h"

bool XYRectangle::BoundingBox(const float& t0, const float& t1, AABB& aabb, const float time /* = 0.0f */)const
{
    aabb = AABB(vec3(x0, y0, k - 0.0001f), vec3(x1, y1, k + 0.0001f));
    return true;
}

bool XYRectangle::Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const
{
    float t = (k - ray.GetOrigin().Z()) / ray.GetDirection().Z();
    if (t<t_min || t>t_max)
    {
        return false;
    }
    float x = ray.GetOrigin().X() + t * ray.GetDirection().X();
    float y = ray.GetOrigin().Y() + t * ray.GetDirection().Y();
    if (x<x0 || x>x1 || y<y0 || y>y1)
    {
        return false;
    }
    hitRecord.u = (x - x0) / (x1 - x0);
    hitRecord.v = 1.0f - (y - y0) / (y1 - y0);
    hitRecord.t = t;
    hitRecord.material = myMaterial;
    hitRecord.point = ray.PointAtParameter(t);
    hitRecord.normal = vec3(0.0f, 0.0f, 1.0f);
    return true;
}