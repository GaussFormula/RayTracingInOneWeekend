#include "HelperFunctions.h"
#include "Sphere.h"
#include <cmath>

//static const Sphere sphere = Sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f);

vec3 RayColor(const Ray& r, const std::unique_ptr<Hitable>& object)
{
    HitRecord record;
    if (object->Hit(r, 0.0f, std::numeric_limits<float>::max(), record))
    {
        return 0.5f * (record.normal + vec3(1.0f, 1.0f, 1.0f));
    }
    else
    {
        vec3 unit_direction = r.GetDirection();
        unit_direction.Normalized();
        float t = 0.5f * (unit_direction.Y() + 1.0f);
        return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
    }
}

vec3 RandomReflection(const HitRecord& hitRecord)
{
    vec3 result;
    do 
    {
        result = 2 * vec3(rand() * 1.0f / RAND_MAX, rand() * 1.0f / RAND_MAX, rand() * 1.0f / RAND_MAX);
        result = result - vec3(1.0f, 1.0f, 1.0f);
    } while (result* hitRecord.normal < 0);
    return result;
}

vec3 Reflection(const vec3& v, const vec3& normal)
{
    return v - 2.0f * (v * normal) * normal;
}

bool Refraction(const vec3& incident, const vec3& normal, const float& ni_over_nt, vec3& refracted)
{
    vec3 normalized_incident = incident.Normalized();
    float i_dot_n = normalized_incident * normal;
    
    float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - i_dot_n * i_dot_n);
    if (discriminant > 0)
    {
        refracted = ni_over_nt * (normalized_incident - i_dot_n * normal) - normal * std::sqrt(discriminant);
        return true;
    }
    else
    {
        return false;
    }
}

float Schlick(const float& cosine, const float& refraction_index)
{
    float r0 = (1.0f - refraction_index) / (1.0f + refraction_index);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow((1.0f - cosine), 5.0f);
}