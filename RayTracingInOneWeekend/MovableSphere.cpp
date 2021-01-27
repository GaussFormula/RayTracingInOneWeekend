#include "MovableSphere.h"
#include "HitDetection.h"
bool MovableSphere::Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const
{
    HitDetection detetion(*this, ray);
    if (detetion.GetDiscriminant() >= 0.0f)
    {
        float t = detetion.GetRoot1();
        if (t<t_max && t>t_min)
        {
            hitRecord.t = t;
            hitRecord.point = ray.PointAtParameter(t);
            vec3 temp = (hitRecord.point - GetCurrentPositionByTime(ray.GetExistTime())) * (1.0f / myRadius);
            //temp.Normalized();
            hitRecord.normal = temp;
            hitRecord.material = myMaterial;
            return true;
        }
        t = detetion.GetRoot2();
        if (t<t_max && t>t_min)
        {
            hitRecord.t = t;
            hitRecord.point = ray.PointAtParameter(t);
            vec3 temp = (hitRecord.point - GetCurrentPositionByTime(ray.GetExistTime())) * (1.0f / myRadius);
            //temp.Normalized();
            hitRecord.normal = temp;
            hitRecord.material = myMaterial;
            return true;
        }
        return false;
    }
    else
    {
        return false;
    }
}

vec3 MovableSphere::GetCurrentPositionByTime(const float& currentTime)const
{
    return myOrigin0 + (currentTime - myTime0) / (myTime1 - myTime0) * (myOrigin1 - myOrigin0);
}

bool MovableSphere::BoundingBox(const float& t0, const float& t1, AABB& aabb, const float time = 0.0f)const
{
    aabb = GetCurrentAABBByTime(time);
    return true;
}

AABB MovableSphere::GetCurrentAABBByTime(const float& currentTime)const
{
    vec3 currentPosition = GetCurrentPositionByTime(currentTime);
    return AABB(currentPosition - vec3(myRadius, myRadius, myRadius), currentPosition + vec3(myRadius, myRadius, myRadius));
}