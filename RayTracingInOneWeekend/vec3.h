#pragma once
#include <assert.h>
class vec3
{
public:
    vec3(const float& n0, const float& n1, const float& n2)
    {
        data[0] = n0;
        data[1] = n1;
        data[2] = n2;
    }

    float& operator[](int index)
    {
        assert(index >= 0 && index <= 2);
        return data[index];
    }

    

private:
    float data[3] = {};
};