#include "BVHNode.h"
#include "HelperFunctions.h"
#include <algorithm>
#include <iostream>
bool BVHNode::BoundingBox(const float& t0, const float& t1, AABB& aabb, const float time)const
{
    aabb = box;
    return true;
}

bool BVHNode::Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const
{
    AABB real_box;
    bool isCurrentMovableSphere = false;
    if (left == right)
    {
        if (strcmp("class MovableSphere", typeid(*(left.get())).name()) == 0)
        {
            left->BoundingBox(t_min, t_max, real_box, ray.GetExistTime());
            isCurrentMovableSphere = true;
        }
    }
    if (!isCurrentMovableSphere)
    {
        real_box = box;
    }
    if (real_box.Hit(ray, t_min, t_max))
    {
        HitRecord left_rec, right_rec;
        bool hit_left = left->Hit(ray, t_min, t_max, left_rec);
        bool hit_right = right->Hit(ray, t_min, t_max, right_rec);
        if (hit_left && hit_right)
        {
            if (left_rec.t < right_rec.t)
            {
                hitRecord = left_rec;
            }
            else
            {
                hitRecord = right_rec;
            }
            return true;
        }
        else if(hit_left)
        {
            hitRecord = left_rec;
            return true;
        }
        else if (hit_right)
        {
            hitRecord = right_rec;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

BVHNode::BVHNode(std::vector<std::shared_ptr<Hitable>>& list, const int& start, const int& n, const float& time0, const float& time1)
{
    int axis = int(3 * Random01());
    if (axis == 0)
    {
        std::qsort(&list[start], n, sizeof(std::shared_ptr<Hitable>), 
            [](const void* a, const void* b)->int 
            {
                AABB box_left, box_right;
                std::shared_ptr<Hitable> ah = *(std::shared_ptr<Hitable>*)a;
                std::shared_ptr<Hitable> bh = *(std::shared_ptr<Hitable>*)b;
                if (!ah->BoundingBox(0.0f, 0.0f, box_left) || !bh->BoundingBox(0.0f, 0.0f, box_right))
                {
                    std::cerr << "no bounding box in bvh_node constructor";
                }
                if (box_left.GetMin().X() - box_right.GetMin().X() < 0.0f)
                {
                    return -1;
                }
                else
                {
                    return 1;
                }
            });
    }
    else if (axis == 1)
    {
        std::qsort(&list[start], n, sizeof(std::shared_ptr<Hitable>),
            [](const void* a, const void* b)->int
            {
                AABB box_left, box_right;
                std::shared_ptr<Hitable> ah = *(std::shared_ptr<Hitable>*)a;
                std::shared_ptr<Hitable> bh = *(std::shared_ptr<Hitable>*)b;
                if (!ah->BoundingBox(0.0f, 0.0f, box_left) || !bh->BoundingBox(0.0f, 0.0f, box_right))
                {
                    std::cerr << "no bounding box in bvh_node constructor";
                }
                if (box_left.GetMin().Y() - box_right.GetMin().Y() < 0.0f)
                {
                    return -1;
                }
                else
                {
                    return 1;
                }
            });
    }
    else
    {
        std::qsort(&list[start], n, sizeof(std::shared_ptr<Hitable>),
            [](const void* a, const void* b)->int
            {
                AABB box_left, box_right;
                std::shared_ptr<Hitable> ah = *(std::shared_ptr<Hitable>*)a;
                std::shared_ptr<Hitable> bh = *(std::shared_ptr<Hitable>*)b;
                if (!ah->BoundingBox(0.0f, 0.0f, box_left) || !bh->BoundingBox(0.0f, 0.0f, box_right))
                {
                    std::cerr << "no bounding box in bvh_node constructor";
                }
                if (box_left.GetMin().Z() - box_right.GetMin().Z() < 0.0f)
                {
                    return -1;
                }
                else
                {
                    return 1;
                }
            });
    }
    if (n == 1)
    {
        left = right = list[start];
    }
    else if (n == 2)
    {
        left = list[start];
        right = list[start + 1];
    }
    else
    {
        left = std::make_shared<BVHNode>(list, start, n / 2, time0, time1);
        right = std::make_shared<BVHNode>(list, start + n / 2, n - n / 2, time0, time1);
    }

    AABB box_left, box_right;
    if (!left->BoundingBox(time0, time1, box_left) || !right->BoundingBox(time0, time1, box_right))
    {
        std::cerr << "no bounding box in bvh_node constructor";
    }
    box = AABB::SurroundingBox(box_left, box_right);
}