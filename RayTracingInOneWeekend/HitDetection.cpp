#include "HitDetection.h"
#include <assert.h>
#include <cmath>

HitDetection::HitDetection(const Sphere& sphere, const Ray& ray)
{
    b = ray.GetDirection() * (ray.GetOrigin() - sphere.GetOrigin()) * 2;
    a = ray.GetDirection() * ray.GetDirection();
    c = (ray.GetOrigin() - sphere.GetOrigin()) * (ray.GetOrigin() - sphere.GetOrigin()) 
        - sphere.GetRadius() * sphere.GetRadius();

    discriminant = b * b - 4 * a * c;
}

HitDetection::HitDetection(const MovableSphere& sphere, const Ray& ray)
{
    b = ray.GetDirection() * (ray.GetOrigin() - sphere.GetCurrentPositionByTime(ray.GetExistTime())) * 2;
    a = ray.GetDirection() * ray.GetDirection();
    c = (ray.GetOrigin() - sphere.GetCurrentPositionByTime(ray.GetExistTime())) 
        * (ray.GetOrigin() - sphere.GetCurrentPositionByTime(ray.GetExistTime()))
        - sphere.GetRadius() * sphere.GetRadius();
    discriminant = b * b - 4 * a * c;
}

float HitDetection::GetRoot1()const
{
    assert(discriminant >= 0);
    if (discriminant == 0)
    {
        return -b / (2 * a);
    }
    else
    {
        return (-b - std::sqrt(discriminant)) / (2 * a);
    }
}

float HitDetection::GetRoot2()const
{
    assert(discriminant >= 0);
    if (discriminant == 0)
    {
        return -b / (2 * a);
    }
    else
    {
        return (-b + std::sqrt(discriminant)) / (2 * a);
    }
}