#pragma once
#include "Material.h"

class Metal :public Material
{
public:
    Metal(const vec3&a)
        :myAlbedo(a)
    {}

    vec3 GetAlbedo()const
    {
        return myAlbedo;
    }

    virtual bool Scatter(const Ray& ray, const HitRecord& record, vec3& attenuation, Ray& scattered)const;

private:
    vec3 myAlbedo;
};