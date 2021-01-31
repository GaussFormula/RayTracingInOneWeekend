#pragma once

#include "vec3.h"

class Texture
{
public:
    virtual vec3 GetValue(const float& u, const float& v, const vec3& p)const = 0;
};