#include "HitableList.h"

bool HitableList::Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const
{
    HitRecord temp_rec;
    bool hit_anything = false;
    double cloest_so_far = t_max;
    for (int i = 0; i < myList.size(); ++i)
    {
        if (myList[i]->Hit(ray, t_min, cloest_so_far, temp_rec))
        {
            hit_anything = true;
            cloest_so_far = temp_rec.t;
            hitRecord = temp_rec;
        }
    }
    return hit_anything;
}