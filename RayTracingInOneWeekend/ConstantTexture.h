#pragma once
#include "Texture.h"

class ConstantTexture :public Texture
{
public:
    ConstantTexture(){}
    ConstantTexture(const vec3& c)
        :myColor(c)
    {}

    virtual vec3 GetValue(const float& u, const float& v, const vec3& p)const override;


private:
    vec3 myColor;
};