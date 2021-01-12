#include "PPMFileP3.h"
int main()
{
    const int width = 500;
    const int height = width;
    PPMFileP3 picture(width, height);
    for (int j = height - 1; j >= 0; --j)
    {
        for (int i = 0; i < width; ++i)
        {
            vec3 col((float)i / (float)width, (float)j / (float)height, 1.0f);
            picture.AddOnePixelToBuffer(col);
        }
        picture.AddLFToBuffer();
    }
    picture.OutputAsFile();
    return 0;
}