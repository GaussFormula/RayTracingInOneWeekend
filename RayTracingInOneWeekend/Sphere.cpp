#include "Sphere.h"
#include <cmath>
bool Sphere::BeHitByRay(const Ray& ray)const
{
    float B = ray.GetDirection() * (ray.GetOrigin() - myOrigin) * 2;
    float A = ray.GetDirection() * ray.GetDirection();
    float C = (ray.GetOrigin() - myOrigin) * (ray.GetOrigin() - myOrigin) - myRadius * myRadius;

    float discriminant = B * B - 4 * A * C;
    if (discriminant > 0)
    {
        if ((-1 * B - std::sqrt(discriminant)) / (2 * A) > 0)
        {
            return true;
        }
        else if((-1 * B + std::sqrt(discriminant)) / (2 * A) > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (discriminant == 0)
    {
        if (-1 * B / (2 * A) >= 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

}