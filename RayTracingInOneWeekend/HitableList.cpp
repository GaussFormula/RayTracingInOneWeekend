#include "HitableList.h"
#include "HelperFunctions.h"
#include "Material.h"

bool HitableList::Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const
{
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
        hitRecord = temp_rec;
        return true;
    }
    else
    {
        return false;
    }
}

void HitableList::push_back(const std::shared_ptr<Hitable>& object)
{
    myList.push_back(object);
}