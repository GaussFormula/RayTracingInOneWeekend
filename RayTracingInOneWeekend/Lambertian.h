#pragma once
#include "Material.h"
#include "Texture.h"
#include <memory>

class Lambertian :public Material
{
public:
    Lambertian(const std::shared_ptr<Texture>& a)
        :myAlbedo(a)
    {}

    virtual bool Scatter(const Ray& ray, const HitRecord& record, vec3& attenuation, Ray& scattered)const override;
private:
    std::shared_ptr<Texture> myAlbedo;
};