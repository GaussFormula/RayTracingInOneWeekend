#include "Denoise.h"
#include "vec3.h"
void BoxFilterDenoising(const std::vector<unsigned char>& src, std::vector<unsigned char>& dst, 
    int startRows, int endRows,
    int startColumns,int endColumns,
    const int& totalWidth,const int& totalHeight)
{
    if (endRows > totalHeight)
    {
        endRows = totalHeight;
    }
    for (int i = endRows - 1; i >= startRows; --i)
    {
        for (int j = startColumns; j < endColumns; ++j)
        {
            int tempCounter = 0;
            int sampleGridsCount = 8;
            bool isUpperEdge = false;
            bool isLowestEdge = false;
            bool isLeftEdge = false;
            bool isRightEdge = false;
            vec3 result;
            if (i - 1 < 0)
            {
                isLowestEdge = true;
                sampleGridsCount -= 3;
                tempCounter += 1;
            }
            else if (i + 1 >= totalHeight)
            {
                isUpperEdge = true;
                sampleGridsCount -= 3;
                tempCounter += 1;
            }
            if (j - 1 < 0)
            {
                isLeftEdge = true;
                sampleGridsCount -= 3;
                tempCounter += 1;
            }
            else if (j + 1 >= totalWidth)
            {
                isRightEdge = true;
                sampleGridsCount -= 3;
                tempCounter += 1;
            }
            if (tempCounter == 2)
            {
                sampleGridsCount += 1;
            }
            if (isUpperEdge)
            {
                //vec3 v0(src[(size_t)i * totalWidth * 3 + j*3], src[(size_t)i * totalWidth * 3 + (j*3) + 1], src[(size_t)i * totalWidth * 3 + (j * 3) + 2]);
                vec3 v7(src[(size_t)(i - 1) * totalWidth * 3 + (j * 3)], src[(size_t)(i - 1) * totalWidth * 3 + (j * 3) + 1], src[(size_t)(i - 1) * totalWidth * 3 + (j * 3) + 2]);
                if (isLeftEdge)
                {
                    vec3 v8(src[(size_t)(i - 1) * totalWidth * 3 + (j + 1) * 3], src[(size_t)(i - 1) * totalWidth * 3 + (j + 1) * 3 + 1], src[(size_t)(i - 1) * totalWidth * 3 + (j + 1) * 3 + 2]);
                    vec3 v5(src[(size_t)i * totalWidth * 3 + (j + 1) * 3], src[(size_t)i * totalWidth * 3 + (j + 1) * 3 + 1], src[(size_t)i * totalWidth * 3 + (j + 1) * 3 + 2]);
                    result = 1.0f / sampleGridsCount * (v7 + v5 + v8);
                }
                else if (isRightEdge)
                {
                    vec3 v6(src[(size_t)(i - 1) * totalWidth * 3 + (j - 1) * 3], src[(size_t)(i - 1) * totalWidth * 3 + (j - 1) * 3 + 1], src[(size_t)(i - 1) * totalWidth * 3 + (j - 1) * 3 + 2]);
                    vec3 v4(src[(size_t)i * totalWidth * 3 + (j - 1) * 3], src[(size_t)i * totalWidth * 3 + (j - 1) * 3 + 1], src[(size_t)i * totalWidth * 3 + (j - 1) * 3 + 2]);
                    result = 1.0f / sampleGridsCount * (v7 + v4 + v6);
                }
                else
                {
                    vec3 v6(src[(size_t)(i - 1) * totalWidth * 3 + (j * 3) - 3], src[(size_t)(i - 1) * totalWidth * 3 + (j * 3) - 2], src[(size_t)(i - 1) * totalWidth * 3 + (j * 3) - 1]);
                    vec3 v4(src[(size_t)i * totalWidth * 3 + (j * 3) - 3], src[(size_t)i * totalWidth * 3 + (j * 3) - 2], src[(size_t)i * totalWidth * 3 + (j * 3) - 1]);
                    vec3 v8(src[(size_t)(i - 1) * totalWidth * 3 + (j + 1) * 3], src[(size_t)(i - 1) * totalWidth * 3 + (j + 1) * 3 + 1], src[(size_t)(i - 1) * totalWidth * 3 + (j + 1) * 3 + 2]);
                    vec3 v5(src[(size_t)i * totalWidth * 3 + (j - 1) * 3], src[(size_t)i * totalWidth * 3 + (j - 1) * 3 + 1], src[(size_t)i * totalWidth * 3 + (j - 1) * 3 + 2]);
                    result = 1.0f / sampleGridsCount * (v4 + v5 + v6 + v7 + v8);
                }
            }
            else if (isLowestEdge)
            {
                //vec3 v0(src[(size_t)i * totalWidth * 3 + (j * 3)], src[(size_t)i * totalWidth * 3 + (j * 3) + 1], src[(size_t)i * totalWidth * 3 + (j * 3) + 2]);
                vec3 v2(src[(size_t)(i + 1) * totalWidth * 3 + (j * 3)], src[(size_t)(i + 1) * totalWidth * 3 + (j * 3) + 1], src[(size_t)(i + 1) * totalWidth * 3 + (j * 3) + 2]);
                if (isLeftEdge)
                {
                    vec3 v3(src[(size_t)(i + 1) * totalWidth * 3 + (j + 1) * 3], src[(size_t)(i + 1) * totalWidth * 3 + (j + 1) * 3 + 1], src[(size_t)(i + 1) * totalWidth * 3 + (j + 1) * 3 + 2]);
                    vec3 v5(src[(size_t)i * totalWidth * 3 + (j + 1) * 3], src[(size_t)i * totalWidth * 3 + (j + 1) * 3 + 1], src[(size_t)i * totalWidth * 3 + (j + 1) * 3 + 2]);
                    result = 1.0f / sampleGridsCount * (v2 + v3 + v5);
                }
                else if (isRightEdge)
                {
                    vec3 v1(src[(size_t)(i + 1) * 3 * totalWidth + (j - 1) * 3], src[(size_t)(i + 1) * 3 * totalWidth + (j - 1) * 3 + 1], src[(size_t)(i + 1) * 3 * totalWidth + (j - 1) * 3 + 2]);
                    vec3 v4(src[(size_t)i * totalWidth * 3 + (j - 1) * 3], src[(size_t)i * totalWidth * 3 + (j - 1) * 3 + 1], src[(size_t)i * totalWidth * 3 + (j - 1) * 3 + 2]);
                    result = 1.0f / sampleGridsCount * (v2 + v1 + v4);
                }
                else
                {
                    vec3 v1(src[(size_t)(i + 1) * 3 * totalWidth + (j - 1) * 3], src[(size_t)(i + 1) * 3 * totalWidth + (j - 1) * 3 + 1], src[(size_t)(i + 1) * 3 * totalWidth + (j - 1) * 3 + 2]);
                    vec3 v4(src[(size_t)i * totalWidth * 3 + (j - 1) * 3], src[(size_t)i * totalWidth * 3 + (j - 1) * 3 + 1], src[(size_t)i * totalWidth * 3 + (j - 1) * 3 + 2]);
                    vec3 v3(src[(size_t)(i + 1) * totalWidth * 3 + (j + 1) * 3], src[(size_t)(i + 1) * totalWidth * 3 + (j + 1) * 3 + 1], src[(size_t)(i + 1) * totalWidth * 3 + (j + 1) * 3 + 2]);
                    vec3 v5(src[(size_t)i * totalWidth * 3 + (j + 1) * 3], src[(size_t)i * totalWidth * 3 + (j + 1) * 3 + 1], src[(size_t)i * totalWidth * 3 + (j + 1) * 3 + 2]);
                    result = 1.0f / sampleGridsCount * (v1 + v2 + v3 + v4 + v5);
                }
            }
            else if (isLeftEdge)
            {
                //vec3 v0(src[(size_t)i * totalWidth * 3 + (j * 3)], src[(size_t)i * totalWidth * 3 + (j * 3) + 1], src[(size_t)i * totalWidth * 3 + (j * 3) + 2]);
                vec3 v2(src[(size_t)(i - 1) * totalWidth * 3 + (j * 3)], src[(size_t)(i - 1) * totalWidth * 3 + (j * 3) + 1], src[(size_t)(i - 1) * totalWidth * 3 + (j * 3) + 2]);
                vec3 v3(src[(size_t)(i - 1) * totalWidth * 3 + (j + 1) * 3], src[(size_t)(i - 1) * totalWidth * 3 + (j + 1) * 3 + 1], src[(size_t)(i - 1) * totalWidth * 3 + (j + 1) * 3 + 2]);
                vec3 v5(src[(size_t)i * totalWidth * 3 + (j + 1) * 3], src[(size_t)i * totalWidth * 3 + (j + 1) * 3 + 1], src[(size_t)i * totalWidth * 3 + (j + 1) * 3 + 2]);
                vec3 v7(src[(size_t)(i + 1) * totalWidth * 3 + (j * 3)], src[(size_t)(i + 1) * totalWidth * 3 + (j * 3) + 1], src[(size_t)(i + 1) * totalWidth * 3 + (j * 3) + 2]);
                vec3 v8(src[(size_t)(i + 1) * totalWidth * 3 + (j * 3) + 3], src[(size_t)(i + 1) * totalWidth * 3 + (j * 3) + 3 + 1], src[(size_t)(i + 1) * totalWidth * 3 + (j * 3) + 3 + 2]);
                result = 1.0f / sampleGridsCount * (v2 + v3 + v5 + v7 + v8);
            }
            else if (isRightEdge)
            {
                //vec3 v0(src[(size_t)i * totalWidth * 3 + (j * 3)], src[(size_t)i * totalWidth * 3 + (j * 3) + 1], src[(size_t)i * totalWidth * 3 + (j * 3) + 2]);
                vec3 v1(src[(size_t)(i - 1) * 3 * totalWidth + (j - 1) * 3], src[(size_t)(i - 1) * 3 * totalWidth + (j - 1) * 3 + 1], src[(size_t)(i - 1) * 3 * totalWidth + (j - 1) * 3 + 2]);
                vec3 v2(src[(size_t)(i - 1) * totalWidth * 3 + (j * 3)], src[(size_t)(i - 1) * totalWidth * 3 + (j * 3) + 1], src[(size_t)(i - 1) * totalWidth * 3 + (j * 3) + 2]);
                vec3 v4(src[(size_t)i * totalWidth * 3 + (j - 1) * 3], src[(size_t)i * totalWidth * 3 + (j - 1) * 3 + 1], src[(size_t)i * totalWidth * 3 + (j - 1) * 3 + 2]);
                vec3 v6(src[(size_t)(i + 1) * totalWidth * 3 + (j - 1) * 3], src[(size_t)(i + 1) * totalWidth * 3 + (j - 1) * 3 + 1], src[(size_t)(i + 1) * totalWidth * 3 + (j - 1) * 3 + 2]);
                vec3 v7(src[(size_t)(i + 1) * totalWidth * 3 + (j * 3)], src[(size_t)(i + 1) * totalWidth * 3 + (j * 3) + 1], src[(size_t)(i + 1) * totalWidth * 3 + (j * 3) + 2]);
                result = 1.0f / sampleGridsCount * (v1 + v2 + v4 + v6 + v7);
            }
            else
            {
                //vec3 v0(src[(size_t)i * totalWidth * 3 + (j * 3)], src[(size_t)i * totalWidth * 3 + (j * 3) + 1], src[(size_t)i * totalWidth * 3 + (j * 3) + 2]);
                vec3 v1(src[(size_t)(i - 1) * 3 * totalWidth + (j - 1) * 3], src[(size_t)(i - 1) * 3 * totalWidth + (j - 1) * 3 + 1], src[(size_t)(i - 1) * 3 * totalWidth + (j - 1) * 3 + 2]);
                vec3 v2(src[(size_t)(i - 1) * totalWidth * 3 + (j * 3)], src[(size_t)(i - 1) * totalWidth * 3 + (j * 3) + 1], src[(size_t)(i - 1) * totalWidth * 3 + (j * 3) + 2]);
                vec3 v3(src[(size_t)(i - 1) * totalWidth * 3 + (j + 1) * 3], src[(size_t)(i - 1) * totalWidth * 3 + (j + 1) * 3 + 1], src[(size_t)(i - 1) * totalWidth * 3 + (j + 1) * 3 + 2]);
                vec3 v4(src[(size_t)i * totalWidth * 3 + (j - 1) * 3], src[(size_t)i * totalWidth * 3 + (j - 1) * 3 + 1], src[(size_t)i * totalWidth * 3 + (j - 1) * 3 + 2]);
                vec3 v5(src[(size_t)i * totalWidth * 3 + (j + 1) * 3], src[(size_t)i * totalWidth * 3 + (j + 1) * 3 + 1], src[(size_t)i * totalWidth * 3 + (j + 1) * 3 + 2]);
                vec3 v6(src[(size_t)(i + 1) * totalWidth * 3 + (j - 1) * 3], src[(size_t)(i + 1) * totalWidth * 3 + (j - 1) * 3 + 1], src[(size_t)(i + 1) * totalWidth * 3 + (j - 1) * 3 + 2]);
                vec3 v7(src[(size_t)(i + 1) * totalWidth * 3 + (j * 3)], src[(size_t)(i + 1) * totalWidth * 3 + (j * 3) + 1], src[(size_t)(i + 1) * totalWidth * 3 + (j * 3) + 2]);
                vec3 v8(src[(size_t)(i + 1) * totalWidth * 3 + (j * 3) + 3], src[(size_t)(i + 1) * totalWidth * 3 + (j * 3) + 3 + 1], src[(size_t)(i + 1) * totalWidth * 3 + (j * 3) + 3 + 2]);
                result = 1.0f / sampleGridsCount * (v1 + v2 + v3 + v4 + v5 + v6 + v7 + v8);
            }
            for (int k = 0; k < 3; ++k)
            {
                dst[(size_t)i * totalWidth * 3 + (size_t)j * 3 + k] = (unsigned char)result[k];
            }
        }
    }
}