#include "AABB.h"
#include <utility>

bool AABB::Hit(const Ray& ray, const float& tmin, const float& tmax)const
{
    for (int i = 0; i < 3; ++i)// i=0 for x; i=1 for y; i=2 for z
    {
        float invD = 1.0f / ray.GetDirection()[i];
        float t0 = (myMin[i] - ray.GetOrigin()[i]) * invD;
        float t1 = (myMax[i] - ray.GetOrigin()[i]) * invD;
        if (invD < 0.0f)
        {
            std::swap(t0, t1);
        }

        float temp_min_tmax = t0 < tmin ? tmin : t0;
        float temp_max_tmin = t1 < tmax ? t1 : tmax;
        if (temp_min_tmax <= temp_max_tmin)
        {
            return false;
        }
    }
    return true;
}