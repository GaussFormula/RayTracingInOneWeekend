#pragma once

class vec3
{
public:
    vec3(const float& n0, const float& n1, const float& n2)
    {
        data[0] = n0;
        data[1] = n1;
        data[2] = n2;
    }

    vec3(const vec3& v)
    {
        data[0] = v[0];
        data[1] = v[1];
        data[2] = v[2];
    }

    vec3()
    {
        data[0] = 0.0f;
        data[1] = 0.0f;
        data[2] = 0.0f;
    }

    // operator overload
    void operator=(const vec3& rhs);

    float& operator[](int index);

    float operator[](int index) const;

    vec3 operator+(const vec3& rhs);

    vec3 operator*(const float& rhs)const;

    float operator*(const vec3& rhs)const;

    vec3 operator-(const vec3& rhs)const;

    void operator*=(const float& rhs);

    void operator+=(const vec3& rhs);

    inline float X()const
    {
        return data[0];
    }

    inline float Y()const
    {
        return data[1];
    }

    inline float Z()const
    {
        return data[2];
    }
    
    float Length()const;
    
    vec3 GetUnitVector()const;

    void Normalized();

private:
    float data[3] = {};
};

vec3 operator*(const float& a, const vec3& rhs);

vec3 operator+(const vec3& a, const vec3& b);

vec3 cross(const vec3& a, const vec3& b);