#pragma once
#include "Hitable.h"
#include "Material.h"
#include "Texture.h"

#include <memory>

class Isotropic :public Material
{
public:
    Isotropic(const std::shared_ptr<Texture>& a)
        :albedo(a)
    {}
    virtual bool Scatter(const Ray& ray, const HitRecord& record, vec3& attenuation, Ray& scattered)const override;

    std::shared_ptr<Texture> albedo;
};

class ConstantMedium :public Hitable
{
public:
    ConstantMedium(const std::shared_ptr<Hitable>b, float d, const std::shared_ptr<Texture>& a)
        :boundary(b)
        ,density(d)
    {
        phaseFunction = std::make_shared<Isotropic>(a);
    }

    virtual bool Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const override;

    virtual bool BoundingBox(const float& t0, const float& t1, AABB& aabb, const float time = 0.0f)const override;

public:
    std::shared_ptr<Hitable> boundary;
    float density = 0.0f;
    std::shared_ptr<Isotropic> phaseFunction;
};