#include "vec3.h"
#include "HelperFunctions.h"

#include <assert.h>
#include <cmath>

void vec3::operator=(const vec3& rhs)
{
    data[0] = rhs[0];
    data[1] = rhs[1];
    data[2] = rhs[2];
}

float& vec3::operator[](int index)
{
    assert(index >= 0 && index <= 2);
    return data[index];
}

float vec3::operator[](int index)const
{
    assert(index >= 0 && index <= 2);
    return data[index];
}

vec3 vec3::operator+(const vec3& rhs)
{
    return vec3(data[0] + rhs.X(), data[1] + rhs.Y(), data[2] + rhs.Z());
}

void vec3::operator+=(const vec3& rhs)
{
    for (int i = 0; i < 3; ++i)
    {
        data[i] += rhs[i];
    }
}

vec3 vec3::operator*(const float& rhs)const
{
    return vec3(data[0] * rhs, data[1] * rhs, data[2] * rhs);
}

vec3 operator*(const float& lhs, const vec3& rhs)
{
    return vec3(rhs[0] * lhs, rhs[1] * lhs, rhs[2] * lhs);
}

vec3 operator+(const vec3& a, const vec3& b)
{
    return vec3(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
}

float vec3::operator*(const vec3& rhs)const
{
    float sum = 0.0f;
    for (int i = 0; i < 3; ++i)
    {
        sum += data[i] * rhs[i];
    }
    return sum;
}

vec3 vec3::operator-(const vec3& rhs)const
{
    return vec3(data[0] - rhs.X(), data[1] - rhs.Y(), data[2] - rhs.Z());
}

void vec3::operator*=(const float& rhs)
{
    *this = *this * rhs;
}

float vec3::Length()const
{
    vec3 temp = (*this);
    return std::sqrt(temp * temp);
}

vec3 vec3::GetUnitVector()const
{
    return vec3(*this) * (1.0f / Length());
}

void vec3::Normalized()
{
    float length = Length();
    for (int i = 0; i < 3; ++i)
    {
        data[i] *= 1.0f / length;
    }
}

vec3 cross(const vec3& a, const vec3& b)
{
    return vec3(a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]);
}

vec3 vec3::GetRandomVecInUnitDisk()
{
    vec3 p;
    do 
    {
        p = 2.0f * vec3(Random01(), Random01(), 0) - vec3(1.0f, 1.0f, 0.0f);
    } while (p * p >= 1.0f);
    return p;
}

vec3 vec3::GetRandomVecInUnitSphere()
{
    vec3 p;
    do
    {
        p = 2.0f * vec3(Random01(), Random01(), Random01()) - vec3(1.0f, 1.0f, 1.0f);
    } while (p * p >= 1.0f);
    return p;
}