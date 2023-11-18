#include "Vector2.hpp"
#include <math.h>

#define PI 3.14159265f

Vector2::Vector2()
{
    x = 0.0f;
    y = 0.0f;   
}

Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}



float Vector2::angle(bool degrees = false)
{
    if (degrees) {
        return atan2(this->x, this->y) * 180.0f / PI;
    }
    return atan2(this->x, this->y);
}

float Vector2::length()
{
    return sqrt(this->x * this->x + this->y * this->y);
}

bool Vector2::isZero()
{
    return this->x == 0.0f && this->y == 0.0f;
}


Vector2& Vector2::Add(const Vector2& vec)
{
    this->x += vec.x;
    this->y += vec.y;

    return *this;
}

Vector2& Vector2::Sub(const Vector2& vec)
{
    this->x -= vec.x;
    this->y -= vec.y;

    return *this;
}

Vector2& Vector2::Mul(const Vector2& vec)
{
    this->x *= vec.x;
    this->y *= vec.y;

    return *this;
}

Vector2& Vector2::Div(const Vector2& vec)
{
    this->x /= vec.x;
    this->y /= vec.y;

    return *this;
}


Vector2& operator+(Vector2& v1, const Vector2& v2) { return v1.Add(v2); }
Vector2& operator-(Vector2& v1, const Vector2& v2) { return v1.Sub(v2); }
Vector2& operator*(Vector2& v1, const Vector2& v2) { return v1.Mul(v2); }
Vector2& operator/(Vector2& v1, const Vector2& v2) { return v1.Div(v2); }


Vector2& Vector2::operator+=(const Vector2& vec) { return this->Add(vec); }
Vector2& Vector2::operator-=(const Vector2& vec) { return this->Sub(vec); }
Vector2& Vector2::operator*=(const Vector2& vec) { return this->Mul(vec); }
Vector2& Vector2::operator/=(const Vector2& vec) { return this->Div(vec); }

bool Vector2::operator==(const Vector2& vec) { 
    return this->x == vec.x && this->y == vec.y; 
}
bool Vector2::operator!=(const Vector2& vec) { 
    return this->x != vec.x || this->y != vec.y; 
}


Vector2& Vector2::operator*(const int& i)
{
    this->x *= i;
    this->y *= i;

    return *this;
}

Vector2& Vector2::Zero()
{
    this->x = 0;
    this->y = 0;

    return *this;
}

Vector2& Vector2::Normalize()
{
    if (this->x != 0) {
        this->x /= this->length();
    }
    if (this->y != 0) {
        this->y /= this->length();
    }
    return *this;
}

Vector2& Vector2::Round()
{
    this->x = round(this->x);
    this->y = round(this->y);
    return *this;
}



Vector2 Vector2::Copy()
{
    return Vector2(this->x, this->y);
}



// Nice printing
std::ostream& operator<<(std::ostream& stream, const Vector2& vec)
{
    stream << "(" << vec.x << "," << vec.y << ")";
    return stream;
}
