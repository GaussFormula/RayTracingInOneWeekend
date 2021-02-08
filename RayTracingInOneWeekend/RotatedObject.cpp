#include "RotatedObject.h"
#define _USE_MATH_DEFINES 1
#include <math.h>
#include <cmath>
#include <limits>
YAxisRotatedObject::YAxisRotatedObject(const std::shared_ptr<Hitable>& p, const float& angle)
{
    ptr = p;
    float radius = (M_PI / 180.0f) * angle;
    sin_theta = std::sin(radius);
    cos_theta = std::cos(radius);
    hasBox = ptr->BoundingBox(0.0f, 1.0f, aabb);
    vec3 min(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    vec3 max(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest());
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            for (int k = 0; k < 2; ++k)
            {
                float x = i * aabb.GetMax().X() + (1 - i) * aabb.GetMin().X();
                float y = j * aabb.GetMax().Y() + (1 - j) * aabb.GetMin().Y();
                float z = k * aabb.GetMax().Z() + (1 - k) * aabb.GetMin().Z();
                float newx = cos_theta * x + sin_theta * z;
                float newz = -sin_theta * x + cos_theta * z;
                vec3 tester(newx, y, newz);
                for (int c = 0; c < 3; ++c)
                {
                    if (tester[c] > max[c])
                    {
                        max[c] = tester[c];
                    }
                    if (tester[c] < min[c])
                    {
                        min[c] = tester[c];
                    }
                }
            }
        }
    }
    aabb = AABB(min, max);
}

bool YAxisRotatedObject::Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const
{
    vec3 origin = ray.GetOrigin();
    vec3 direction = ray.GetDirection();
    origin[0] = cos_theta * ray.GetOrigin()[0] + sin_theta * ray.GetOrigin()[2];
    origin[2] = -sin_theta * ray.GetOrigin()[0] + cos_theta * ray.GetOrigin()[2];
    direction[0] = cos_theta * ray.GetDirection()[0] + sin_theta * ray.GetDirection()[2];
    direction[2] = -sin_theta * ray.GetDirection()[0] + cos_theta * ray.GetDirection()[2];
    Ray rotatedRay(origin, direction, ray.GetExistTime());
    if (ptr->Hit(rotatedRay, t_min, t_max, hitRecord))
    {
        vec3 p = hitRecord.point;
        vec3 normal = hitRecord.normal;
        p = RotateCalculate(hitRecord.point);
        normal = RotateCalculate(hitRecord.normal);
        hitRecord.point = p;
        hitRecord.normal = normal;
        return true;
    }
    else
    {
        return false;
    }
}