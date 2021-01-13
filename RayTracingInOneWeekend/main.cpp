#include "PPMFileP3.h"
#include "Ray.h"
#include "HelperFunctions.h"
int main()
{
    const int width = 500;
    const int height = width;
    PPMFileP3 picture(width, height);

    vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
    vec3 horizontal(4.0f, 0.0f, 0.0f);
    vec3 vertical(0.0f, 2.0f, 0.0f);
    vec3 origin(0.0f, 0.0f, 0.0f);

    for (int j = height - 1; j >= 0; --j)
    {
        for (int i = 0; i < width; ++i)
        {
            float u = (float)i / (float)width;
            float v = (float)j / (float)height;
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = RayColor(r);
            col *= 256.0f;
            picture.AddOnePixelToBuffer(col);
        }
        picture.AddLFToBuffer();
    }
    picture.OutputAsFile("1.ppm");
    return 0;
}