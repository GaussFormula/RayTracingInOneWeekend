#pragma once
#include "Material.h"

class Lambertian :public Material
{
public:
    Lambertian(const vec3& a)
        :myAlbedo(a)
    {}

    vec3 GetAlbedo()const
    {
        return myAlbedo;
    }

    virtual bool Scatter(const Ray& ray, const HitRecord& record, vec3& attenuation, Ray& scattered)const override;
private:
    vec3 myAlbedo;
};