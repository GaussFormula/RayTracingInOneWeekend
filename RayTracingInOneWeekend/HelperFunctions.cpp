#include "HelperFunctions.h"
#include "Sphere.h"

static const Sphere sphere = Sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f);

vec3 RayColor(const Ray& r)
{
    float t = sphere.BeHitByRay_V2(r);
    if (t > 0.0f)
    {
        vec3 N = r.PointAtParameter(t) - sphere.GetOrigin();
        N.Normalized();
        return 0.5f * (N + vec3(1.0f, 1.0f, 1.0f));
    }
    vec3 unitDirection = r.GetDirection();
    unitDirection.Normalized();

    t = 0.5f * (unitDirection.Y() + 1.0f);
    return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}