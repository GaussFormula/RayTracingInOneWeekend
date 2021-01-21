#include "Lambertian.h"
#include "HelperFunctions.h"
bool Lambertian::Scatter(const Ray& ray, const HitRecord& record, vec3& attenuation, Ray& scattered)const
{
    vec3 target = RandomReflection(record);
    scattered = Ray(record.point, target);
    attenuation = myAlbedo;
    return true;
}