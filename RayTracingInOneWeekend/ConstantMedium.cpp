#include "ConstantMedium.h"
#include "HelperFunctions.h"
#include <limits>
bool Isotropic::Scatter(const Ray& ray, const HitRecord& record, vec3& attenuation, Ray& scattered)const
{
    scattered = Ray(record.point, vec3::GetRandomVecInUnitSphere());
    attenuation = albedo->GetValue(record.u, record.v, record.point);
    return true;
}

bool ConstantMedium::BoundingBox(const float& t0, const float& t1, AABB& aabb, const float time /* = 0.0f */)const
{
    return boundary->BoundingBox(t0, t1, aabb);
}

bool ConstantMedium::Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const
{
    HitRecord rec1, rec2;
    if (boundary->Hit(ray, std::numeric_limits<float>::lowest(), std::numeric_limits<float>::max(), rec1))
    {
        if (boundary->Hit(ray, rec1.t + 0.00001f, std::numeric_limits<float>::max(), rec2))
        {
            if (rec1.t < t_min)
            {
                rec1.t = t_min;
            }
            if (rec2.t > t_max)
            {
                rec2.t = t_max;
            }
            if (rec1.t >= rec2.t)
            {
                return false;
            }
            if (rec1.t < 0.0f)
            {
                rec1.t = 0.0f;
            }
            float distance_inside_boundary = (rec2.t - rec1.t) * ray.GetDirection().Length();
            float hit_distance = -(1 / density) * log(Random01());
            if (hit_distance < distance_inside_boundary)
            {
                hitRecord.t = rec1.t + hit_distance / ray.GetDirection().Length();
                hitRecord.point = ray.PointAtParameter(hitRecord.t);
                hitRecord.normal = vec3(1.0f, 0.0f, 0.0f);
                hitRecord.material = phaseFunction;
                return true;
            }
        }
    }
    return false;
}