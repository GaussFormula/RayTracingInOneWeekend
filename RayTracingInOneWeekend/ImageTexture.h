#pragma once
#include "Texture.h"
class ImageTexture :public Texture
{
public:
    ImageTexture(){}
    ImageTexture(unsigned char* _data,const int& width,const int& height)
        :data(_data)
        ,myWidth(width)
        ,myHeight(height)
    {}

    ~ImageTexture()
    {
        if (data != nullptr)
        {
            delete[] data;
        }
    }

    virtual vec3 GetValue(const float& u, const float& v, const vec3& p)const override;

private:
    unsigned char* data = nullptr;
    int myWidth = 0;
    int myHeight = 0;
};