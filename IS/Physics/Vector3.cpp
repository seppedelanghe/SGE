#include "Vector3.hpp"
#include <math.h>

#define PI 3.14159265f

Vector3::Vector3()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Vector3::Vector3(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float Vector3::length()
{
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}



Vector3& Vector3::Add(const Vector3& vec)
{
    this->x += vec.x;
    this->y += vec.y;
    this->z += vec.z;

    return *this;
}

Vector3& Vector3::Sub(const Vector3& vec)
{
    this->x -= vec.x;
    this->y -= vec.y;
    this->z -= vec.z;

    return *this;
}

Vector3& Vector3::Mul(const Vector3& vec)
{
    this->x *= vec.x;
    this->y *= vec.y;
    this->z *= vec.z;

    return *this;
}

Vector3& Vector3::Div(const Vector3& vec)
{
    this->x /= vec.x;
    this->y /= vec.y;
    this->z /= vec.z;

    return *this;
}



Vector3& operator+(Vector3& v1, const Vector3& v2) { return v1.Add(v2); }
Vector3& operator-(Vector3& v1, const Vector3& v2) { return v1.Sub(v2); }
Vector3& operator*(Vector3& v1, const Vector3& v2) { return v1.Mul(v2); }
Vector3& operator/(Vector3& v1, const Vector3& v2) { return v1.Div(v2); }


Vector3& Vector3::operator+=(const Vector3& vec) { return this->Add(vec); }
Vector3& Vector3::operator-=(const Vector3& vec) { return this->Sub(vec); }
Vector3& Vector3::operator*=(const Vector3& vec) { return this->Mul(vec); }
Vector3& Vector3::operator/=(const Vector3& vec) { return this->Div(vec); }


Vector3& Vector3::operator*(const int& i)
{
    this->x *= i;
    this->y *= i;
    this->z *= i;

    return *this;
}

Vector3& Vector3::Zero()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;

    return *this;
}

Vector3& Vector3::Normalize()
{
    this->x /= this->length();
    this->y /= this->length();
    this->z /= this->length();

    return *this;
}

// Nice printing
std::ostream& operator<<(std::ostream& stream, const Vector3& vec)
{
    stream << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
    return stream;
}
