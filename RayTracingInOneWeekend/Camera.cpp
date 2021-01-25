#include "Camera.h"

// New: add time to construct ray
Ray Camera::GetRay(const float& i, const float& j)const
{
    vec3 rd = myLensRadius * vec3::GetRandomVecInUnitDisk();
    vec3 offset = u * rd.X() + v * rd.Y();
    float time = myTime0 + rand() * 1.0f / RAND_MAX * (myTime1 - myTime0);
    return Ray(myOrigin + offset, myLowerLeftPoint + i * myHorizontalAxis + j * myVerticalAxis - myOrigin - offset, time);
}