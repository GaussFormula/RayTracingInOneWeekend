#include "Dielectric.h"
#include "HelperFunctions.h"

bool Dielectric::Scatter(const Ray& ray, const HitRecord& record, vec3& attenuation, Ray& scattered)const
{
    vec3 outward_normal;
    vec3 reflected = Reflection(ray.GetDirection(), record.normal);
    float ni_over_nt;
    float reflect_prob = 0.0f;
    attenuation = vec3(1.0f, 1.0f, 1.0f);// Glass surface absorbs nothing.
    vec3 refracted;
    vec3 unit_incident = ray.GetDirection().GetUnitVector();
    float incident_cosine = unit_incident * record.normal;
    if (incident_cosine > 0)
    {
        outward_normal = record.normal * -1.0f;
        ni_over_nt = myRefIndex;
        incident_cosine *= myRefIndex;
    }
    else
    {
        outward_normal = record.normal;
        ni_over_nt = 1.0f / myRefIndex;
        incident_cosine *= -1.0f;
    }
    if (Refraction(unit_incident, outward_normal, ni_over_nt, refracted))
    {
        //scattered = Ray(record.point, refracted);
        reflect_prob = Schlick(incident_cosine, myRefIndex);
    }
    else
    {
        scattered = Ray(record.point, reflected);
        reflect_prob = 1.0f;
    }
    if (0.995f < reflect_prob)
    {
        scattered = Ray(record.point, reflected);
    }
    else
    {
        scattered = Ray(record.point, refracted);
    }
    return true;
}