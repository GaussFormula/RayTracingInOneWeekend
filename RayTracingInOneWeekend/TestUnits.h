#pragma once
#include "HitableList.h"

#include <memory>

std::shared_ptr<HitableList> GetRandomScene();

std::shared_ptr<HitableList> GetFixedScene();