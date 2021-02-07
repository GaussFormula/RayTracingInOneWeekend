#pragma once
#include "HitableList.h"

#include <memory>

std::shared_ptr<HitableList> GetRandomScene();

std::shared_ptr<HitableList> GetFixedScene();

void CreateBox(const vec3& p0, const vec3& p1, const std::shared_ptr<HitableList>& hitableList, const std::shared_ptr<Material>& material);