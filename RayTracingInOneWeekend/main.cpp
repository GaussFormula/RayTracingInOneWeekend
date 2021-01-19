#include "PPMFileP3.h"
#include "HitableList.h"
#include "Sphere.h"
#include "Camera.h"

#include <ctime>
#include <cstdlib>

#include <thread>

void Rendering(int startRowNumber, 
    int endRowNumber, 
    int startColumnNumber,
    int endColumnNumber,
    int totalWidth,
    int totalHeight,
    std::string& outputBuffer,
    const HitableList& objectList,
    const Camera& camera)
{
    if (endRowNumber > totalHeight)
    {
        endRowNumber = totalHeight;
    }
    for (int j = endRowNumber - 1; j >= startRowNumber; --j)
    {
        for (int i = startColumnNumber; i < endColumnNumber; ++i)
        {
            vec3 col(0.0f, 0.0f, 0.0f);
            for (int s = 0; s < 4; ++s)
            {
                float u = float(i + rand() * 1.0f / RAND_MAX) / (float)totalWidth;
                float v = float(j + rand() * 1.0f / RAND_MAX) / (float)totalHeight;
                Ray r(camera.GetRay(u, v));
                col += objectList.Hit(r, 0.0f, std::numeric_limits<float>::max());
            }
            col *= 255.99f / 4.0f;

            //col *= 255.99f;
            std::string colorStr;
            for (int i = 0; i < 3; ++i)
            {
                colorStr += std::to_string((int)col[i]) + std::string(" ");
            }
            outputBuffer += colorStr;
        }
        outputBuffer += std::string("\n");
    }
}

int main()
{
    const int width = 1000;
    const int height = width;
    PPMFileP3 picture(width, height);

    Camera camera;

    HitableList objectList;

    objectList.push_back(std::make_shared<Sphere>(vec3(0.0f, 0.0f, -1.0f), 0.5f));
    objectList.push_back(std::make_shared<Sphere>(vec3(0.0f, -100.5f, -1.0f), 100.0f));

    objectList.ReferenceCount();

    srand((unsigned int)time(0));

    std::vector<std::thread> threadArray;
    std::vector<std::string> outputBuffer;
    outputBuffer.resize(8);

    for (int i = 0; i < 8; ++i)
    {
        threadArray.push_back(
            std::thread(
                Rendering, i * (height / 8),
                (i + 1) * (height / 8),
                0,
                width,
                width,
                height,
                std::ref(outputBuffer[i]),
                std::ref(objectList),
                std::ref(camera)
            ));
    }

    for (int i = 0; i < 8; ++i)
    {
        if (threadArray[i].joinable())
        {
            threadArray[i].join();
        }
    }

    for (int i = 7; i >= 0; --i)
    {
        picture.AddPixelsToBuffer(outputBuffer[i]);
    }
    
    picture.OutputAsFile("1.ppm");

    objectList.ReferenceCount();
    return 0;
}