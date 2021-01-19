#include "HitableList.h"
#include "HelperFunctions.h"

vec3 HitableList::Hit(const Ray& ray, const float& t_min, const float& t_max,const int& RandomReflectionLimit)const
{
    if (RandomReflectionLimit <= 0)
    {
        vec3 unit_direction = ray.GetDirection();
        unit_direction.Normalized();
        float t = 0.5f * (unit_direction.Y() + 1.0f);
        return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
    }
    HitRecord temp_rec;
    bool hit_anything = false;
    double cloest_so_far = t_max;
    int closest_index = 0;
    for (int i = 0; i < myList.size(); ++i)
    {
        if (myList[i]->Hit(ray, t_min, cloest_so_far, temp_rec))
        {
            hit_anything = true;
            cloest_so_far = temp_rec.t;
            closest_index = i;
        }
    }
    if (hit_anything)
    {
        Ray RandomReflection(temp_rec.point, RandomReflection(temp_rec));
        return 0.5f * Hit(RandomReflection, 0, std::numeric_limits<float>::max(), RandomReflectionLimit - 1);
    }
    else
    {
        vec3 unit_direction = ray.GetDirection();
        unit_direction.Normalized();
        float t = 0.5f * (unit_direction.Y() + 1.0f);
        return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
    }
}

void HitableList::push_back(const std::shared_ptr<Hitable>& object)
{
    myList.push_back(object);
}