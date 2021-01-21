#include "Dielectric.h"
#include "HelperFunctions.h"

bool Dielectric::Scatter(const Ray& ray, const HitRecord& record, vec3& attenuation, Ray& scattered)const
{
    vec3 outward_normal;
    vec3 reflected = Reflection(ray.GetDirection(), record.normal);
    float ni_over_nt;
    attenuation = vec3(1.0f, 1.0f, 1.0f);// Glass surface absorbs nothing.
    vec3 refracted;
    if (ray.GetDirection() * record.normal > 0)
    {
        outward_normal = record.normal * -1;
        ni_over_nt = myRefIndex;
    }
    else
    {
        outward_normal = record.normal;
        ni_over_nt = 1.0f / myRefIndex;
    }
    if (Refraction(ray.GetDirection(), outward_normal, ni_over_nt, refracted))
    {
        scattered = Ray(record.point, refracted);
    }
    else
    {
        scattered = Ray(record.point, reflected);
        return false;
    }
    return true;
}