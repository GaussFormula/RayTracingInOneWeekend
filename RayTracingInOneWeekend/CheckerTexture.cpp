#include "CheckerTexture.h"
#include <cmath>
vec3 CheckerTexture::GetValue(const float& u, const float& v, const vec3& p)const
{
    float sine = sin(10.0f * p.X()) * sin(10.0f * p.Y()) * sin(10.0f * p.Z());
    if (sine < 0)
    {
        return myOdd->GetValue(u, v, p);
    }
    else
    {
        return myEven->GetValue(u, v, p);
    }
}