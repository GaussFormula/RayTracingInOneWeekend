#pragma once

#include "Ray.h"
#include "Hitable.h"
#include <memory>

vec3 RayColor(const Ray& r,const std::unique_ptr<Hitable>& object);

vec3 RandomReflection(const HitRecord& hitRecord);

vec3 Reflection(const vec3& v, const vec3& normal);

bool Refraction(const vec3& incident, const vec3& normal, const float& ni_over_nt, vec3& refracted);

float Schlick(const float& cosine, const float& refraction_index);