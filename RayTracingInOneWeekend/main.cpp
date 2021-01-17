#include "PPMFileP3.h"
#include "HitableList.h"
#include "Sphere.h"
#include "Camera.h"

#include <ctime>
#include <cstdlib>
int main()
{
    const int width = 500;
    const int height = width;
    PPMFileP3 picture(width, height);

    Camera camera;

    HitableList objectList;

    objectList.push_back(std::make_shared<Sphere>(vec3(0.0f, 0.0f, -1.0f), 0.5f));
    objectList.push_back(std::make_shared<Sphere>(vec3(0.0f, -100.5f, -1.0f), 100.0f));

    objectList.ReferenceCount();

    srand((unsigned int)time(0));

    for (int j = height - 1; j >= 0; --j)
    {
        for (int i = 0; i < width; ++i)
        {
            vec3 col(0.0f, 0.0f, 0.0f);
            for (int s = 0; s < 5; ++s)
            {
                float u = float(i + rand() * 1.0f / RAND_MAX) / (float)width;
                float v = float(j + rand() * 1.0f / RAND_MAX) / (float)height;
                Ray r(camera.GetRay(u, v));
                col += objectList.Hit(r, 0.0f, std::numeric_limits<float>::max());
            }
            col *= 255.99f / 5.0f;

            //col *= 255.99f;
            picture.AddOnePixelToBuffer(col);
        }
        picture.AddLFToBuffer();
    }
    picture.OutputAsFile("1.ppm");

    objectList.ReferenceCount();
    return 0;
}