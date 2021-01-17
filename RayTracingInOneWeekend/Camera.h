#pragma once
#include "Ray.h"
class Camera
{
public:
    Camera()
    {
        myLowerLeftPoint = vec3(0.0f, -2.0f, 0.3f);
        myHorizontalAxis = vec3(2.8f, 0.0f, -2.8f);
        myVerticalAxis = vec3(0.0f, 4.0f, 0.0f);
        myOrigin = vec3(1.0f, 0.0f, 1.0f);
    }

    Camera(const vec3& origin,const vec3& lowerLeftPoint,const vec3& horizontalAxis,const vec3& verticalAxis)
        :myOrigin(origin)
        ,myLowerLeftPoint(lowerLeftPoint)
        ,myHorizontalAxis(horizontalAxis)
        ,myVerticalAxis(verticalAxis)
    {}

    vec3 GetOrigin() const
    {
        return myOrigin;
    }

    vec3 GetLowerLeftPoint()const
    {
        return myLowerLeftPoint;
    }

    vec3 GetHorizontalAxis()const
    {
        return myHorizontalAxis;
    }

    vec3 GetVerticalAxis()const
    {
        return myVerticalAxis;
    }

    Ray GetRay(const float& u, const float& v)const;

private:
    vec3 myOrigin;
    vec3 myLowerLeftPoint;
    vec3 myHorizontalAxis;
    vec3 myVerticalAxis;
};