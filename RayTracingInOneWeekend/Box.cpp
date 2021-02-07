#include "Box.h"
#include "XYRectangle.h"
#include "YZRectangle.h"
#include "XZRectangle.h"
#include "FlipNormals.h"
bool Box::Hit(const Ray& ray, const float& t_min, const float& t_max, HitRecord& hitRecord)const
{
    return myList->Hit(ray, t_min, t_max, hitRecord);
}

Box::Box(const vec3& p0, const vec3& p1, const std::shared_ptr<Material>& material)
{
    pmin = p0;
    pmax = p1;
    // vec3(-1.0f, -2.0f, 1.5f), vec3(0.0f, 1.0f, -1.0f)
    myList = std::make_shared<HitableList>();
    myList->push_back(std::make_shared<XYRectangle>(p0.X(), p1.X(), p0.Y(), p1.Y(), p1.Z(), material));
    myList->push_back(std::make_shared<FlipNormalRectangle>(std::make_shared<XYRectangle>(p0.X(), p1.X(), p0.Y(), p0.Y(), p0.Z(), material)));
    myList->push_back(std::make_shared<XZRectangle>(p0.X(), p1.X(), p0.Z(), p1.Z(), p0.Y(), material));
    myList->push_back(std::make_shared<FlipNormalRectangle>(std::make_shared<XZRectangle>(p0.X(), p1.X(), p0.Z(), p1.Z(), p1.Y(), material)));
    myList->push_back(std::make_shared<YZRectangle>(p0.Y(), p1.Y(), p0.Z(), p1.Z(), p1.X(), material));
    myList->push_back(std::make_shared<FlipNormalRectangle>(std::make_shared<YZRectangle>(p0.Y(), p1.Y(), p0.Z(), p1.Z(), p0.X(), material)));
}