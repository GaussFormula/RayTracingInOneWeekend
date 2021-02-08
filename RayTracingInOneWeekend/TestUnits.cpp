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
#include "YZRectangle.h"
#include "XZRectangle.h"
#include "FlipNormals.h"
#include "Box.h"
#include "RotatedObject.h"

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

    std::vector<int> nx(10, 0);
    std::vector<int> ny(10, 0);
    std::vector<int> nn(10, 0);
    std::vector<unsigned char*> tex_data;
    tex_data.resize(10);

    tex_data[0] = stbi_load("soviet_flag.jpg", &nx[0], &ny[0], &nn[0], 0);
    tex_data[1] = stbi_load("poster1.jpg", &nx[1], &ny[1], &nn[1], 0);


    std::shared_ptr<CheckerTexture> checker = std::make_shared<CheckerTexture>(
        std::make_shared<ConstantTexture>(vec3(0.2f, 0.3f, 0.1f) * 255.0f),
        std::make_shared<ConstantTexture>(vec3(0.9f, 0.9f, 0.9f) * 255.0f));

    std::shared_ptr<ImageTexture> image = std::make_shared<ImageTexture>(tex_data[0], nx[0], ny[0]);

    std::shared_ptr<Metal> metal = std::make_shared<Metal>(vec3(1.0f, 1.0f, 1.0f));
    std::shared_ptr<Lambertian> lambertian = std::make_shared<Lambertian>(image);
    std::shared_ptr<Lambertian> lambertian2 = std::make_shared<Lambertian>(checker);
    std::shared_ptr<Dielectric> dielectric = std::make_shared<Dielectric>(1.5f);
    std::shared_ptr<Dielectric> dielectric2 = std::make_shared<Dielectric>(1.51f);
    std::shared_ptr<DiffuseLight> diffuseLight = std::make_shared<DiffuseLight>(
        std::make_shared<ConstantTexture>(vec3(255.0f, 235.0f, 205.0f) * 4.0f));

    std::shared_ptr<DiffuseLight> poster = std::make_shared<DiffuseLight>(
        std::make_shared<ImageTexture>(tex_data[1], nx[1], ny[1]));

    std::shared_ptr<DiffuseLight> diffuse_lambertian 
        = std::make_shared<DiffuseLight>
        (image);
    
    std::shared_ptr<Lambertian> red = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(vec3(0.65f, 0.05f, 0.05f) * 255.0f));
    std::shared_ptr<Lambertian> white = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(vec3(0.73f, 0.73f, 0.73f) * 255.0f));
    std::shared_ptr<Lambertian> white2 = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(vec3(0.83f, 0.83f, 0.83f) * 255.0f));
    std::shared_ptr<Lambertian> green = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(vec3(0.12f, 0.45f, 0.15f) * 255.0f));

    //hitableList->push_back(std::make_shared<Sphere>(vec3(0.0f, 1.0f, 0.0f), 1.0f, lambertian));
    //hitableList->push_back(std::make_shared<Sphere>(vec3(0.0f, 0.48f, 1.52f), 0.5f, lambertian));
    //hitableList->push_back(std::make_shared<Sphere>(vec3(2.0f, 0.0f, 0.0f), 0.5f, diffuseLight));
    //hitableList->push_back(std::make_shared<Sphere>(vec3(0.51f, 0.0f, -1.0f), -0.45f, dielectric));
    //hitableList->push_back(std::make_shared<Sphere>(vec3(0.0f, -100.5f, -1.0f), 100.0f, lambertian2));
    //hitableList->push_back(std::make_shared<XYRectangle>(-2.0f, 3.0f, 0.0f, 1.5f, 1.3f, poster));
    //hitableList->push_back(std::make_shared<XYRectangle>(-2.0f, 3.0f, 0.0f, 1.5f, -1.3f, poster));
    hitableList->push_back(std::make_shared<FlipNormalRectangle>(std::make_shared<XYRectangle>(-2.0f, 2.0f, -2.0f, 2.0f, 2.0f, green)));
    hitableList->push_back(std::make_shared<FlipNormalRectangle>(std::make_shared<XZRectangle>(-2.0f, 2.0f, -2.0f, 2.0f, 2.0f, white)));
    hitableList->push_back(std::make_shared<XZRectangle>(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, white));
    hitableList->push_back(std::make_shared<XYRectangle>(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, red));
    hitableList->push_back(std::make_shared<YZRectangle>(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, white));
    hitableList->push_back(std::make_shared<XZRectangle>(-1.0f, 1.0f, -1.0f, 1.0f, 1.9f, diffuseLight));
    //CreateBox(vec3(-1.0f, -2.0f, -1.5f), vec3(1.0f, 1.0f, 1.0f), hitableList, white2);
    hitableList->push_back(std::make_shared<YAxisRotatedObject>(std::make_shared<Box>(vec3(-1.5f, -2.0f, 0.0f), vec3(0.0f, 0.0f, 1.6f), white2), -18.0f));
    hitableList->push_back(std::make_shared<YAxisRotatedObject>(std::make_shared<Box>(vec3(-1.6f, -2.0f, -1.6f), vec3(1.1f, -0.5f, 0.5f), white2), 45.0f));
    //hitableList->push_back(std::make_shared<Box>(vec3(-1.6f, -2.0f, -1.6f), vec3(1.1f, 1.2f, -0.1f),white2));

    return hitableList;
}

void CreateBox(const vec3& p0, const vec3& p1,const std::shared_ptr<HitableList>& hitableList, const std::shared_ptr<Material>& material)
{
    hitableList->push_back(std::make_shared<XYRectangle>(p0.X(), p1.X(), p0.Y(), p1.Y(), p1.Z(), material));
    hitableList->push_back(std::make_shared<FlipNormalRectangle>(std::make_shared<XYRectangle>(p0.X(), p1.X(), p0.Y(), p0.Y(), p0.Z(), material)));
    hitableList->push_back(std::make_shared<XZRectangle>(p0.X(), p1.X(), p0.Z(), p1.Z(), p0.Y(), material));
    hitableList->push_back(std::make_shared<FlipNormalRectangle>(std::make_shared<XZRectangle>(p0.X(), p1.X(), p0.Z(), p1.Z(), p1.Y(), material)));
    hitableList->push_back(std::make_shared<FlipNormalRectangle>(std::make_shared<YZRectangle>(p0.Y(), p1.Y(), p0.Z(), p1.Z(), p1.X(), material)));
    hitableList->push_back(std::make_shared<FlipNormalRectangle>(std::make_shared<YZRectangle>(p0.Y(), p1.Y(), p0.Z(), p1.Z(), p0.X(), material)));
}