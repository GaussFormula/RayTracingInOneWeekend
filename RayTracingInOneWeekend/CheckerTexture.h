#pragma once
#include "Texture.h"
#include <memory>
class CheckerTexture :public Texture
{
public:
    CheckerTexture(){}
    CheckerTexture(const std::shared_ptr<Texture>& t0, const std::shared_ptr<Texture>&t1)
        :myOdd(t0)
        ,myEven(t1)
    {}

    virtual vec3 GetValue(const float& u, const float& v, const vec3& p)const override;

private:
    std::shared_ptr<Texture> myOdd;
    std::shared_ptr<Texture> myEven;
};