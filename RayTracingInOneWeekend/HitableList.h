#pragma once
#include "Hitable.h"
#include <vector>
#include <memory>
class HitableList :public Hitable
{
public:
    HitableList(){}
    HitableList(const std::vector<std::unique_ptr<Hitable>>& list)
        :myList(list)
    {}

    virtual bool Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const;

private:
    std::vector<std::unique_ptr<Hitable>> myList;
};