#pragma once
#include "Material.h"
#include "Texture.h"
#include <memory>
class DiffuseLight :public Material
{
public:
    DiffuseLight(const std::shared_ptr<Texture>& a)
        :emit(a)
    {}

    virtual bool Scatter(const Ray& ray, const HitRecord& record, vec3& attenuation, Ray& scattered)const override
    {
        return false;
    }

    virtual vec3 Emitted(const float& u, const float& v, const vec3& p)const;

private:
    std::shared_ptr<Texture> emit;
};