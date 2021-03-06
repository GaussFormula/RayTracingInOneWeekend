#include "HelperFunctions.h"
#include "Sphere.h"
#define _USE_MATH_DEFINES 1
#include <math.h>
#include <cmath>
#include <random>
#include <time.h>

static std::default_random_engine ourRandomEngine(time(0));
static std::uniform_real_distribution<float> ourDistribution(0, 1);

vec3 RayColor(const Ray& r, const std::unique_ptr<Hitable>& object)
{
    HitRecord record;
    if (object->Hit(r, 0.0f, std::numeric_limits<float>::max(), record))
    {
        return 0.5f * (record.normal + vec3(1.0f, 1.0f, 1.0f));
    }
    else
    {
        vec3 unit_direction = r.GetDirection().GetUnitVector();
        float t = 0.5f * (unit_direction.Y() + 1.0f);
        return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
    }
}

vec3 RandomReflection(const HitRecord& hitRecord)
{
    vec3 result;
    do 
    {
        result = 2 * vec3(Random01(), Random01(), Random01());
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
    vec3 normalized_incident = incident.GetUnitVector();
    float i_dot_n = normalized_incident * normal;
    
    float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - i_dot_n * i_dot_n);
    if (discriminant > 0)
    {
        refracted = ni_over_nt * (incident - i_dot_n * normal) - normal * std::sqrt(discriminant);
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

float Random01()
{
    return ourDistribution(ourRandomEngine);
}

void GetSphereUV(const vec3& hitPoint, const Sphere& sphere, float& u, float& v)
{
    vec3 unit_hitVector = 1.0f / sphere.GetRadius() * (hitPoint - sphere.GetOrigin());
    float phi = atan2(unit_hitVector.Z(), unit_hitVector.X());
    float theta = asin(unit_hitVector.Y());
    // theta is latitude. From -pi/2 to pi/2.
    v = 1 - (theta + M_PI_2) / M_PI;
    u = 1 - (phi + M_PI) / (2 * M_PI);
    // phi from -pi to pi.
}

void SelfClamp(vec3& v)
{
    for (int i = 0; i < 3; ++i)
    {
        if (v[i] < 0.0f)
        {
            v[i] = 0.0f;
        }
        if (v[i] > 255.0f)
        {
            v[i] = 255.0f;
        }
    }
}