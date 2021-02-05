#include "XZRectangle.h"

bool XZRectangle::Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const
{
    float t = (y - ray.GetOrigin().Y()) / ray.GetDirection().Y();
    if (t<t_min || t>t_max)
    {
        return false;
    }
    float x = ray.GetOrigin().X() + t * ray.GetDirection().X();
    float z = ray.GetOrigin().Z() + t * ray.GetDirection().Z();
    if (x<x0 || x>x1 || z<z0 || z>z1)
    {
        return false;
    }
    hitRecord.u = (x - x0) / (x1 - x0);
    hitRecord.v = 1.0f - (z - z0) / (z1 - z0);
    hitRecord.t = t;
    hitRecord.material = myMaterial;
    hitRecord.point = ray.PointAtParameter(t);
    hitRecord.normal = vec3(0.0f, 1.0f, 0.0f);
    return true;
}

bool XZRectangle::BoundingBox(const float& t0, const float& t1, AABB& aabb, const float time /* = 0.0f */)const
{
    aabb = AABB(vec3(x0, y - 0.0001f, z0), vec3(x1, y + 0.0001f, z1));
    return true;
}