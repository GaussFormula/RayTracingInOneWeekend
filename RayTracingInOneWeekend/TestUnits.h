#pragma once

#include "Sphere.h"
#include "MovableSphere.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include "HitableList.h"
#include "HelperFunctions.h"

#include <memory>

std::shared_ptr<HitableList> GetRandomScene()
{
    std::shared_ptr<HitableList> hitableList = std::make_shared<HitableList>();
    hitableList->push_back(std::make_shared<Sphere>(vec3(0.0f, -1000.0f, 0.0f), 1000.0f,
        std::make_shared<Lambertian>(vec3(0.5f, 0.5f, 0.5f))));
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
                                vec3(Random01() * Random01(), Random01() * Random01(), Random01() * Random01())
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
    hitableList->push_back(std::make_shared<Sphere>(vec3(-4.0f, 1.0f, 0.0f), 1.0f, std::make_shared<Lambertian>(vec3(0.4f, 0.2f, 0.1f))));
    hitableList->push_back(std::make_shared<Sphere>(vec3(4.0f, 1.0f, 0.0f), 1.0f, std::make_shared<Metal>(vec3(0.7f, 0.6f, 0.5f))));
    return hitableList;
}