#include "PPMFileP3.h"
#include "HitableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Metal.h"
#include "Lambertian.h"
#include "Dielectric.h"

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
    const int sample_times = 7;
    const int bounce_times = 25;
    for (int j = endRowNumber - 1; j >= startRowNumber; --j)
    {
        for (int i = startColumnNumber; i < endColumnNumber; ++i)
        {
            vec3 col(0.0f, 0.0f, 0.0f);
            for (int s = 0; s < sample_times; ++s)
            {
                float u = float(i + rand() * 1.0f / RAND_MAX) / (float)totalWidth;
                float v = float(j + rand() * 1.0f / RAND_MAX) / (float)totalHeight;
                Ray r(camera.GetRay(u, v));
                col += objectList.Hit(r, 0.001f, std::numeric_limits<float>::max(), bounce_times);
            }
            col *= 255.99f / sample_times;

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
    const int thread_number = 10;
    PPMFileP3 picture(width, height);

    Camera camera;

    HitableList objectList;

    std::shared_ptr<Metal> metal = std::make_shared<Metal>(vec3(0.8f, 0.8f, 0.8f));
    std::shared_ptr<Lambertian> lambertian = std::make_shared<Lambertian>(vec3(0.8f, 0.8f, 0.0f));
    std::shared_ptr<Lambertian> lambertian2 = std::make_shared<Lambertian>(vec3(0.1f, 0.2f, 0.5f));
    std::shared_ptr<Dielectric> dielectric = std::make_shared<Dielectric>(1.5f);
    std::shared_ptr<Dielectric> dielectric2 = std::make_shared<Dielectric>(1.51f);

    objectList.push_back(std::make_shared<Sphere>(vec3(0.51f, 0.0f, 0.0f), 0.5f,
        dielectric));
    objectList.push_back(std::make_shared<Sphere>(vec3(-0.51f, 0.0f, 0.0f), 0.5f, metal));
    objectList.push_back(std::make_shared<Sphere>(vec3(0.51f, 0.0f, 0.0f), -0.45f,
        dielectric));
    objectList.push_back(std::make_shared<Sphere>(vec3(0.0f, -100.5f, -1.0f), 100.0f,
        lambertian));

    objectList.ReferenceCount();

    srand((unsigned int)time(0));

    std::vector<std::thread> threadArray;
    std::vector<std::string> outputBuffer;
    outputBuffer.resize(thread_number);

    for (int i = 0; i < thread_number; ++i)
    {
        threadArray.push_back(
            std::thread(
                Rendering, i * (height / thread_number),
                (i + 1) * (height / thread_number),
                0,
                width,
                width,
                height,
                std::ref(outputBuffer[i]),
                std::ref(objectList),
                std::ref(camera)
            ));
    }

    for (int i = 0; i < thread_number; ++i)
    {
        if (threadArray[i].joinable())
        {
            threadArray[i].join();
        }
    }

    for (int i = thread_number - 1; i >= 0; --i)
    {
        picture.AddPixelsToBuffer(outputBuffer[i]);
    }
    
    picture.OutputAsFile("1.ppm");

    objectList.ReferenceCount();
    return 0;
}