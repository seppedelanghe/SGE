#pragma once

#include <iostream>

class Vector3
{
    public:
        float x;
        float y;
        float z = 0.0f;

        Vector3();
        Vector3(float x, float y);
        Vector3(float x, float y, float z);

        float length();

        Vector3& Add(const Vector3& vec);
        Vector3& Sub(const Vector3& vec);
        Vector3& Mul(const Vector3& vec);
        Vector3& Div(const Vector3& vec);

        friend Vector3& operator+(Vector3& v1, const Vector3& v2);
        friend Vector3& operator-(Vector3& v1, const Vector3& v2);
        friend Vector3& operator*(Vector3& v1, const Vector3& v2);
        friend Vector3& operator/(Vector3& v1, const Vector3& v2);

        Vector3& operator+=(const Vector3& vec);
        Vector3& operator-=(const Vector3& vec);
        Vector3& operator*=(const Vector3& vec);
        Vector3& operator/=(const Vector3& vec);

        Vector3& operator*(const int& i);
        Vector3& Zero();
        Vector3& Normalize();

        friend std::ostream& operator<<(std::ostream& stream, const Vector3& vec);
};
