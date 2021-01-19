#include "HelperFunctions.h"
#include "Sphere.h"

static const Sphere sphere = Sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f);

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

vec3 Reflection(const HitRecord& hitRecord)
{
    vec3 result;
    do 
    {
        result = 2 * vec3(rand() * 1.0f / RAND_MAX, rand() * 1.0f / RAND_MAX, rand() * 1.0f / RAND_MAX);
        result = result - vec3(1.0f, 1.0f, 1.0f);
    } while (result* hitRecord.normal < 0);
    return result;
}