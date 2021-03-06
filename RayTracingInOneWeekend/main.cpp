#include "PPMFileP3.h"
#include "PPMFileP6.h"
#include "Camera.h"
#include "TestUnits.h"
#include "BVHList.h"
#include "ImageTexture.h"
#include "HelperFunctions.h"
#include "Denoise.h"

#include <ctime>
#include <cstdlib>

#include <thread>
#include <mutex>

std::mutex oneMutex;
int currentFinisedLinesAmount = 0;


void Rendering(int startRowNumber, 
    int endRowNumber, 
    int startColumnNumber,
    int endColumnNumber,
    int totalWidth,
    int totalHeight,
    int myThreadOrderNumber,
    std::string& outputBuffer,
    std::vector<unsigned char>& outputBuffer2,
    const std::shared_ptr<BVHList>& bvhList,
    const Camera& camera)
{
    if (endRowNumber > totalHeight)
    {
        endRowNumber = totalHeight;
    }
    const int sample_times = 12;
    const int bounce_times = 100;
    const float inv_sample_times = 1.0f / sample_times;
    //const int totalRowsCount = endRowNumber - startRowNumber + 1;
    for (int j = endRowNumber-1; j >= startRowNumber; --j)
    {
        for (int i = startColumnNumber; i < endColumnNumber; ++i)
        {
            vec3 col(0.0f, 0.0f, 0.0f);
            for (int s = 0; s < sample_times; ++s)
            {
                float u = float(i + Random01()) / (float)totalWidth;
                float v = float(j + Random01()) / (float)totalHeight;
                Ray r(camera.GetRay(u, v));
                col += bvhList->Hit(r, 0.001f, std::numeric_limits<float>::max(), bounce_times);
            }
            col *= inv_sample_times;
            SelfClamp(col);

            //col *= 255.99f;
            std::string colorStr;
            for (int i = 0; i < 3; ++i)
            {
                colorStr += std::to_string((int)col[i]) + std::string(" ");
                outputBuffer2.push_back((unsigned char)col[i]);
            }
            outputBuffer += colorStr;
        }
        outputBuffer += std::string("\n");
        oneMutex.lock();
        currentFinisedLinesAmount += 1;
        std::cout << "Program has finished "
            << (float)currentFinisedLinesAmount / totalHeight * 100.0f << "%" << "\n";
        std::cout.flush();
        oneMutex.unlock();
    }
    oneMutex.lock();
    std::cout << "Thread " << myThreadOrderNumber << " completed." << "\n";
    std::cout.flush();
    oneMutex.unlock();
}

int main()
{
    const int width = 1500;
    const int height = width;
    const int thread_number = 24;
    PPMFileP3 picture(width, height);
    PPMFileP6 picture2(width, height);

    vec3 lookFrom(4.0f, 0.0f, 0.0f);
    vec3 lookAt(0.0f, 0.0f, 0.0f);
    vec3 up(0.0f, 1.0f, 0.0f);
    float fov = 90.0f;
    float aspect = (float)width / (float)height;
    float dist_to_focus = (lookFrom - lookAt).Length();
    float aperture = 0.005f;

    Camera camera(lookFrom, lookAt, up, fov, aspect, aperture, dist_to_focus, 0.0f, 1.0f);

    //std::shared_ptr<HitableList> objectList = GetRandomScene();
    std::shared_ptr<HitableList> objectList = GetFixedScene();
    

    BVHNode bvh(objectList->GetList(), 0, (int)objectList->size(), 0.0f, 1.0f);
    std::shared_ptr<BVHList> bvhList = std::make_shared<BVHList>(bvh);

    //objectList.ReferenceCount();

    std::vector<std::thread> threadArray;
    std::vector<std::thread> denoiseThreadArray;
    std::vector<std::string> outputBuffer;
    std::vector<std::vector<unsigned char>> outputBuffer2;
    std::vector<unsigned char> denoiseInputBuffer;
    std::vector<unsigned char> denoiseOutputBuffer;
    outputBuffer.resize(thread_number);
    outputBuffer2.resize(thread_number);
    denoiseOutputBuffer.resize(width * height * 3);

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
                i+1,
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
        //picture2.AddPixelsToBuffer(outputBuffer2[i]);
        denoiseInputBuffer.insert(denoiseInputBuffer.end(), outputBuffer2[i].begin(), outputBuffer2[i].end());
    }    
    
    
    real_thread_number = 0;


    for (int i = 0; i < thread_number && i * length < height; ++i, ++real_thread_number)
    {
        denoiseThreadArray.push_back(
            std::thread(BoxFilterDenoising,
                std::ref(denoiseInputBuffer),
                std::ref(denoiseOutputBuffer),
                i * length, (i + 1) * length,
                0, width,
                width, height
            )
        );
    }

    for (int i = 0; i < real_thread_number; ++i)
    {
        if (denoiseThreadArray[i].joinable())
        {
            denoiseThreadArray[i].join();
        }
    }
    picture2.AddPixelsToBuffer(denoiseOutputBuffer);
    
    picture.OutputAsFile("1.ppm");
    picture2.OutputAsFile("2.ppm");

    //objectList.ReferenceCount();
    return 0;
}