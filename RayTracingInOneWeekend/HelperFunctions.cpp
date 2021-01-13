#include "HelperFunctions.h"

vec3 RayColor(const ray& r)
{
    vec3 unitDirection = r.GetDirection();
    unitDirection.Normalized();

    float t = 0.5f * (unitDirection.Y() + 1.0f);
    return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}