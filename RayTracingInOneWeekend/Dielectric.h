#pragma once

#include "Material.h"

class Dielectric :public Material
{
public:
    Dielectric(const float& ref_index)
        :myRefIndex(ref_index)
    {}

    virtual bool Scatter(const Ray& ray, const HitRecord& record, vec3& attenuation, Ray& scattered)const override;
private:
    float myRefIndex;
};