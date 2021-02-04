#include "Lambertian.h"
#include "HelperFunctions.h"
bool Lambertian::Scatter(const Ray& ray, const HitRecord& record, vec3& attenuation, Ray& scattered)const
{
    vec3 target = RandomReflection(record);
    scattered = Ray(record.point, target);
    attenuation = 1.0f / 255.0f * myTexture->GetValue(record.u, record.v, record.point);
    return true;
}