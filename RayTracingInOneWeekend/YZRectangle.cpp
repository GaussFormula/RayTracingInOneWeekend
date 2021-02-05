#include "YZRectangle.h"
#include <cmath>
bool YZRectangle::Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const
{
    float t = (x - ray.GetOrigin().X()) / ray.GetDirection().X();
    if (t < t_min || t>t_max)
    {
        return false;
    }
    float y = ray.GetOrigin().Y() + t * ray.GetDirection().Y();
    float z = ray.GetOrigin().Z() + t * ray.GetDirection().Z();
    if (y<y0 || y>y1 || z<z0 || z>z1)
    {
        return false;
    }
    hitRecord.t = t;
    hitRecord.point = ray.PointAtParameter(t);
    hitRecord.material = myMaterial;
    hitRecord.u = std::abs(z - z0) / std::abs(z1 - z0);
    hitRecord.v = 1.0f - std::abs(y - y0) / std::abs(y1 - y0);
    hitRecord.normal = vec3(1.0f, 0.0f, 0.0f);
    return true;
}

bool YZRectangle::BoundingBox(const float& t0, const float& t1, AABB& aabb, const float time /* = 0.0f */)const
{
    aabb = AABB(vec3(x - 0.0001f, y0, z0), vec3(x + 0.0001f, y1, z1));
    return true;
}