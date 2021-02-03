#include "DiffuseLight.h"

vec3 DiffuseLight::Emitted(const float& u, const float& v, const vec3& p)const
{
    return emit->GetValue(u, v, p);
}