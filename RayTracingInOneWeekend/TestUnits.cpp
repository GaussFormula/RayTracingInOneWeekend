#include "TestUnits.h"

#include "Sphere.h"
#include "MovableSphere.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include "DiffuseLight.h"

#include "HelperFunctions.h"
#include "ConstantTexture.h"
#include "CheckerTexture.h"
#include "ImageTexture.h"
#include "XYRectangle.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::shared_ptr<HitableList> GetRandomScene()
{
    std::shared_ptr<HitableList> hitableList = std::make_shared<HitableList>();
    std::shared_ptr<CheckerTexture> checker = std::make_shared<CheckerTexture>(
        std::make_shared<ConstantTexture>(vec3(0.2f, 0.3f, 0.1f)),
        std::make_shared<ConstantTexture>(vec3(0.9f, 0.9f, 0.9f))
        );
    hitableList->push_back(std::make_shared<Sphere>(vec3(0.0f, -1000.0f, 0.0f), 1000.0f,
        std::make_shared<Lambertian>(checker)));
    for (int a = -3; a < 3; ++a)
    {
        for (int b = -3; b < 3; ++b)
        {
            float choose_mat = Random01();
            vec3 center(a + 0.9f * Random01(), 0.2f, b + 0.9f * Random01());
            if ((center - vec3(4.0f, 0.2f, 0.0f)).Length() > 0.9f)
            {
                if (choose_mat < 0.8f)// Diffuse
                {
                    hitableList->push_back
                    (
                        std::make_shared<MovableSphere>
                        (
                            center, center + vec3(0.0f, 0.5f * Random01(), 0.0f),
                            0.0f, 1.0f, 0.2f,
                            std::make_shared<Lambertian>
                            (
                                std::make_shared<ConstantTexture>
                                (vec3(Random01() * Random01(), Random01() * Random01(), Random01() * Random01()))
                                )
                            )
                    );
                }
                else if (choose_mat < 0.95f)// Metal
                {
                    hitableList->push_back(
                        std::make_shared<Sphere>(
                            center, 0.2f, std::make_shared<Metal>(
                                vec3(0.5f * (1.0f + Random01()), 0.5f * (1.0f + Random01()), 0.5f * (1.0f + Random01()))
                                )
                            )
                    );
                }
                else // Glass
                {
                    hitableList->push_back(std::make_shared<Sphere>(center, 0.2f, std::make_shared<Dielectric>(1.5f)));
                }
            }
        }
    }

    hitableList->push_back(std::make_shared<Sphere>(vec3(0.0f, 1.0f, 0.0f), 1.0f, std::make_shared<Dielectric>(0.5f)));
    hitableList->push_back(std::make_shared<Sphere>(vec3(-4.0f, 1.0f, 0.0f), 1.0f, std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(vec3(0.4f, 0.2f, 0.1f)))));
    hitableList->push_back(std::make_shared<Sphere>(vec3(4.0f, 1.0f, 0.0f), 1.0f, std::make_shared<Metal>(vec3(0.7f, 0.6f, 0.5f))));
    return hitableList;
}

std::shared_ptr<HitableList> GetFixedScene()
{
    std::shared_ptr<HitableList> hitableList = std::make_shared<HitableList>();

    int nx, ny, nn;
    unsigned char* tex_data = stbi_load("soviet_flag.jpg", &nx, &ny, &nn, 0);

    std::shared_ptr<CheckerTexture> checker = std::make_shared<CheckerTexture>(
        std::make_shared<ConstantTexture>(vec3(0.2f, 0.3f, 0.1f)),
        std::make_shared<ConstantTexture>(vec3(0.9f, 0.9f, 0.9f)));

    std::shared_ptr<Metal> metal = std::make_shared<Metal>(vec3(0.8f, 0.8f, 0.8f));
    std::shared_ptr<Lambertian> lambertian = std::make_shared<Lambertian>(
        std::make_shared<ImageTexture>(tex_data, nx, ny));
    std::shared_ptr<Lambertian> lambertian2 = std::make_shared<Lambertian>(checker);
    std::shared_ptr<Dielectric> dielectric = std::make_shared<Dielectric>(1.5f);
    std::shared_ptr<Dielectric> dielectric2 = std::make_shared<Dielectric>(1.51f);
    std::shared_ptr<DiffuseLight> diffuseLight = std::make_shared<DiffuseLight>(
        std::make_shared<ConstantTexture>(vec3(255.0f, 255.0f, 255.0f)));
    

    hitableList->push_back(std::make_shared<Sphere>(vec3(0.0f, 1.0f, 0.0f), 1.0f, lambertian));
    //hitableList->push_back(std::make_shared<Sphere>(vec3(0.0f, 0.48f, 1.52f), 0.5f, lambertian));
    //hitableList->push_back(std::make_shared<Sphere>(vec3(0.0f, 1.5f, -1.52f), 0.5f, diffuseLight));
    //objectList.push_back(std::make_shared<Sphere>(vec3(0.51f, 0.0f, -1.0f), -0.45f, dielectric));
    hitableList->push_back(std::make_shared<Sphere>(vec3(0.0f, -100.5f, -1.0f), 100.0f, lambertian2));
    hitableList->push_back(std::make_shared<XYRectangle>(-1.0f, 1.5f, 0.0f, 1.0f, 2.1f, diffuseLight));
    hitableList->push_back(std::make_shared<XYRectangle>(-1.0f, 1.5f, 0.0f, 1.0f, -2.1f, diffuseLight));

    return hitableList;
}