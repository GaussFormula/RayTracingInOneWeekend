#include "Camera.h"

Ray Camera::GetRay(const float& u, const float& v)const
{
    return Ray(myOrigin, myLowerLeftPoint + u * myHorizontalAxis + v * myVerticalAxis - myOrigin);
}