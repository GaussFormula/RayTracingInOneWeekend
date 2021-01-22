#pragma once
#include "Ray.h"
#include <cmath>

class Camera
{
public:
    Camera()
    {
        myLowerLeftPoint = vec3(-2.0f, -2.0f, 0.0f);
        myHorizontalAxis = vec3(4.0f, 0.0f, 0.0f);
        myVerticalAxis = vec3(0.0f, 4.0f, 0.0f);
        myOrigin = vec3(0.0f, 0.0f, 1.0f);
    }

    Camera(const vec3& origin,const vec3& lowerLeftPoint,const vec3& horizontalAxis,const vec3& verticalAxis)
        :myOrigin(origin)
        ,myLowerLeftPoint(lowerLeftPoint)
        ,myHorizontalAxis(horizontalAxis)
        ,myVerticalAxis(verticalAxis)
    {}

    Camera(const float& vfov, const float& aspect)
    {
        float radians_theta = vfov * 3.1415926f / 180;
        float half_height = std::tan(radians_theta / 2);
        float half_width = aspect * half_height;
        myLowerLeftPoint = vec3(-half_width, -half_height, -1.0f);
        myHorizontalAxis = vec3(2 * half_width, 0.0f, 0.0f);
        myVerticalAxis = vec3(0.0f, 2 * half_height, 0.0f);
    }

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