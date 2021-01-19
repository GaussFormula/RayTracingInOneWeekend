#pragma once

#include "Ray.h"
#include "Hitable.h"
#include <memory>

vec3 RayColor(const Ray& r,const std::unique_ptr<Hitable>& object);

vec3 Reflection(const HitRecord& hitRecord);