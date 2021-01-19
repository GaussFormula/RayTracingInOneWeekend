#include "HitableList.h"
#include "HelperFunctions.h"
#include "Material.h"

vec3 HitableList::Hit(const Ray& ray, const float& t_min, const float& t_max,const int& reflectionLimit)const
{
    if (reflectionLimit <= 0)
    {
        return vec3();
    }
    HitRecord temp_rec;
    bool hit_anything = false;
    float cloest_so_far = t_max;
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
        Ray scattered;
        vec3 attenuation;
        if (temp_rec.material->Scatter(ray, temp_rec, attenuation, scattered))
        {
            vec3 result = Hit(scattered, t_min, std::numeric_limits<float>::max(), reflectionLimit - 1);
            return vec3(attenuation[0] *result[0],attenuation[1]*result[1],attenuation[2]*result[2]);
        }
        else
        {
            return vec3();
        }
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