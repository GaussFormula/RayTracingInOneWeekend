#include <cmath>

#include "Sphere.h"
#include "HitDetection.h"


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

float Sphere::BeHitByRay_V2(const Ray& ray)const
{
    HitDetection detetion(*this, ray);
    if (detetion.GetDiscriminant() >= 0.0f)
    {
        if (detetion.GetRoot1() > 0.0f)
        {
            return detetion.GetRoot1();
        }
        else
        {
            return -1.0f;
        }
    }
    else
    {
        return -1.0f;
    }
}

bool Sphere::Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const
{
    HitDetection detetion(*this, ray);
    if (detetion.GetDiscriminant() >= 0.0f)
    {
        float t = detetion.GetRoot1();
        if (t<t_max && t>t_min)
        {
            hitRecord.t = t;
            hitRecord.point = ray.PointAtParameter(t);
            vec3 temp = (hitRecord.point - myOrigin) * (1.0f / myRadius);
            //temp.Normalized();
            hitRecord.normal = temp;
            hitRecord.material = myMaterial;
            return true;
        }
        t = detetion.GetRoot2();
        if (t<t_max && t>t_min)
        {
            hitRecord.t = t;
            hitRecord.point = ray.PointAtParameter(t);
            vec3 temp = (hitRecord.point - myOrigin) * (1.0f / myRadius);
            //temp.Normalized();
            hitRecord.normal = temp;
            hitRecord.material = myMaterial;
            return true;
        }
        return false;
    }
    else
    {
        return false;
    }
}

bool Sphere::BoundingBox(const float& t0, const float& t1, AABB& aabb, const float time = 0.0f)const
{
    // No need to use time because this object is stationary.
    aabb = AABB(myOrigin - vec3(myRadius, myRadius, myRadius), myOrigin + vec3(myRadius, myRadius, myRadius));
    return true;
}