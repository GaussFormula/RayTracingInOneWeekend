#include "Camera.h"

Ray Camera::GetRay(const float& i, const float& j)const
{
    vec3 rd = myLensRadius * vec3::GetRandomVecInUnitDisk();
    vec3 offset = u * rd.X() + v * rd.Y();
    return Ray(myOrigin + offset, myLowerLeftPoint + i * myHorizontalAxis + j * myVerticalAxis - myOrigin - offset);
}