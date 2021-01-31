#include "ConstantTexture.h"

vec3 ConstantTexture::GetValue(const float& u, const float& v, const vec3& p)const
{
    return myColor;
}