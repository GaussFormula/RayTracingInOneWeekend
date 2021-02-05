#include "ImageTexture.h"

vec3 ImageTexture::GetValue(const float& u, const float& v, const vec3& p)const
{
    int i = int(u * myWidth);
    int j = int(v * myHeight - 0.001f);
    if (i < 0)
    {
        i = 0;
    }
    if (j < 0)
    {
        j = 0;
    }
    if (i > myWidth - 1)
    {
        i = myWidth - 1;
    }
    if (j > myHeight - 1)
    {
        j = myHeight - 1;
    }

    float r = int(data[3 * i + 3 * myWidth * j])*1.0f;
    float g = int(data[3 * i + 3 * myWidth * j + 1])*1.0f;
    float b = int(data[3 * i + 3 * myWidth * j + 2])*1.0f;
    return vec3(r, g, b);
}