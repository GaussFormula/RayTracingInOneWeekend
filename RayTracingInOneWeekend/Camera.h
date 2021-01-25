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

    Camera(const float& vfov, const float& aspect)
    {
        float radians_theta = vfov * 3.1415926f / 180;
        float half_height = std::tan(radians_theta / 2);
        float half_width = aspect * half_height;
        myLowerLeftPoint = vec3(-half_width, -half_height, -1.0f);
        myHorizontalAxis = vec3(2 * half_width, 0.0f, 0.0f);
        myVerticalAxis = vec3(0.0f, 2 * half_height, 0.0f);
    }

    Camera(
        const vec3& lookFrom, 
        const vec3& lookAt, 
        const vec3& vUp, 
        const float& vFov, 
        const float& aspect,
        const float& aperture,
        const float& focus_dist,
        const float& time0,
        const float& time1
    )// New: add time0 and time1
    {
        myTime0 = time0;
        myTime1 = time1;
        float radian_theta = vFov * 3.1415926f / 180;
        float half_height = std::tan(radian_theta / 2);
        float half_width = aspect * half_height;
        myLensRadius = aperture / 2.0f;
        myOrigin = lookFrom;
        w = (lookFrom - lookAt).GetUnitVector();
        u = cross(vUp, w).GetUnitVector();
        v = cross(w, u);
        //myLowerLeftPoint = vec3(-half_width, -half_height, -1.0f);
        myLowerLeftPoint = myOrigin - half_width * u * focus_dist - half_height * v * focus_dist - w * focus_dist;
        myHorizontalAxis = 2 * half_width * u * focus_dist;
        myVerticalAxis = 2 * half_height * v * focus_dist;
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

    Ray GetRay(const float& i, const float& j)const;

private:
    vec3 myOrigin;
    vec3 myLowerLeftPoint;
    vec3 myHorizontalAxis;
    vec3 myVerticalAxis;
    vec3 u, v, w;
    float myLensRadius = 0.0f;
    float myTime0, myTime1;
};