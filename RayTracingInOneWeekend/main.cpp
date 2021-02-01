#include "PPMFileP3.h"
#include "PPMFileP6.h"
#include "Camera.h"
#include "TestUnits.h"
#include "BVHList.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
    std::vector<char>& outputBuffer2,
    const std::shared_ptr<BVHList>& bvhList,
    const Camera& camera)
{
    if (endRowNumber > totalHeight)
    {
        endRowNumber = totalHeight;
    }
    const int sample_times = 8;
    const int bounce_times = 50;
    for (int j = endRowNumber-1; j >= startRowNumber; --j)
    {
        for (int i = startColumnNumber; i < endColumnNumber; ++i)
        {
            vec3 col(0.0f, 0.0f, 0.0f);
            for (int s = 0; s < sample_times; ++s)
            {
                float u = float(i + rand() * 1.0f / RAND_MAX) / (float)totalWidth;
                float v = float(j + rand() * 1.0f / RAND_MAX) / (float)totalHeight;
                Ray r(camera.GetRay(u, v));
                col += bvhList->Hit(r, 0.001f, std::numeric_limits<float>::max(), bounce_times);
            }
            col *= 255.99f / sample_times;

            //col *= 255.99f;
            std::string colorStr;
            for (int i = 0; i < 3; ++i)
            {
                colorStr += std::to_string((int)col[i]) + std::string(" ");
                outputBuffer2.push_back((char)col[i]);
            }
            outputBuffer += colorStr;
        }
        outputBuffer += std::string("\n");
    }
}

int main()
{
    srand((unsigned int)time(0));

    const int width = 1500;
    const int height = width;
    const int thread_number = 24;
    PPMFileP3 picture(width, height);
    PPMFileP6 picture2(width, height);

    vec3 lookFrom(-1.0f, 3.0f, 4.0f);
    vec3 lookAt(0.0f, 0.0f, -1.0f);
    vec3 up(0.0f, 1.0f, 0.0f);
    float fov = 90.0f;
    float aspect = (float)width / (float)height;
    float dist_to_focus = (lookFrom - lookAt).Length();
    float aperture = 0.005f;

    Camera camera(lookFrom, lookAt, up, fov, aspect, aperture, dist_to_focus, 0.0f, 1.0f);



    std::shared_ptr<HitableList> objectList = GetRandomScene();
    //HitableList objectList;
    
    /*std::shared_ptr<Metal> metal = std::make_shared<Metal>(vec3(0.8f, 0.8f, 0.8f));
    std::shared_ptr<Lambertian> lambertian = std::make_shared<Lambertian>(vec3(0.8f, 0.8f, 0.0f));
    std::shared_ptr<Lambertian> lambertian2 = std::make_shared<Lambertian>(vec3(0.1f, 0.2f, 0.5f));
    std::shared_ptr<Dielectric> dielectric = std::make_shared<Dielectric>(1.5f);
    std::shared_ptr<Dielectric> dielectric2 = std::make_shared<Dielectric>(1.51f);*/

    /*objectList.push_back(std::make_shared<Sphere>(vec3(0.51f, 0.0f, -1.0f), 0.5f, lambertian2));
    objectList.push_back(std::make_shared<Sphere>(vec3(-0.51f, 0.0f, -1.0f), 0.5f, metal));
    objectList.push_back(std::make_shared<Sphere>(vec3(0.51f, 0.0f, -1.0f), -0.45f, dielectric));
    objectList.push_back(std::make_shared<Sphere>(vec3(0.0f, -100.5f, -1.0f), 100.0f, lambertian));*/

    BVHNode bvh(objectList->GetList(), 0, objectList->size(), 0.0f, 1.0f);
    std::shared_ptr<BVHList> bvhList = std::make_shared<BVHList>(bvh);

    //objectList.ReferenceCount();

    std::vector<std::thread> threadArray;
    std::vector<std::string> outputBuffer;
    std::vector<std::vector<char>> outputBuffer2;
    outputBuffer.resize(thread_number);
    outputBuffer2.resize(thread_number);

    int length = height / thread_number + 1;
    int real_thread_number = 0;


    for (int i = 0; i < thread_number && i * length < height; ++i,++real_thread_number)
    {
        threadArray.push_back(
            std::thread(
                Rendering, i * length ,
                (i+1)*length,
                0,
                width,
                width,
                height,
                std::ref(outputBuffer[i]),
                std::ref(outputBuffer2[i]),
                std::ref(bvhList),
                std::ref(camera)
            ));
        //std::cout << i * length << " " << (i + 1) * length << std::endl;
    }

    for (int i = 0; i < real_thread_number; ++i)
    {
        if (threadArray[i].joinable())
        {
            threadArray[i].join();
        }
    }

    for (int i = real_thread_number-1; i >= 0; --i)
    {
        picture.AddPixelsToBuffer(outputBuffer[i]);
        picture2.AddPixelsToBuffer(outputBuffer2[i]);
    }
    
    picture.OutputAsFile("1.ppm");
    picture2.OutputAsFile("2.ppm");

    //objectList.ReferenceCount();
    return 0;
}