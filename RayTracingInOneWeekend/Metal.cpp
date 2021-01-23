#include "Metal.h"
#include "HelperFunctions.h"
bool Metal::Scatter(const Ray& ray, const HitRecord& record, vec3& attenuation, Ray& scattered)const
{
    vec3 ray_direction = ray.GetDirection().GetUnitVector();
    vec3 reflected = Reflection(ray_direction, record.normal);
    scattered = Ray(record.point, reflected);
    attenuation = myAlbedo;
    return scattered.GetDirection() * record.normal > 0;
}