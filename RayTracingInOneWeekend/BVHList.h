#pragma once
#include "BVHNode.h"
#include <vector>
#include <memory>
#include <iostream>

class BVHList
{
public:
    BVHList(){}

    BVHList(const BVHNode& node)
        :head(node)
    {}

    vec3 Hit(const Ray& ray, const float& t_min, const float& t_max, const int& reflectionLimit)const;

private:
    BVHNode head;
};