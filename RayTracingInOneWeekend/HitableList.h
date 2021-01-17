#pragma once
#include "Hitable.h"
#include <vector>
#include <memory>
#include <iostream>
class HitableList
{
public:
    HitableList(){}

    void push_back(const std::shared_ptr<Hitable>& object);

    vec3 Hit(const Ray& ray, const float& t_min, const float& t_max)const;

    size_t size()const
    {
        return myList.size();
    }

    void ReferenceCount()const
    {
        std::cout << myList[1].use_count();
    }

private:
    std::vector<std::shared_ptr<Hitable>> myList;
};