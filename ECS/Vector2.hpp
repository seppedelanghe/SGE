#pragma once

#include <iostream>

class Vector2
{
    public:
        float x;
        float y;

        Vector2();
        Vector2(float x, float y);

        Vector2& Add(const Vector2& vec);
        Vector2& Sub(const Vector2& vec);
        Vector2& Mul(const Vector2& vec);
        Vector2& Div(const Vector2& vec);

        friend Vector2& operator+(Vector2& v1, const Vector2& v2);
        friend Vector2& operator-(Vector2& v1, const Vector2& v2);
        friend Vector2& operator*(Vector2& v1, const Vector2& v2);
        friend Vector2& operator/(Vector2& v1, const Vector2& v2);

        Vector2& operator+=(const Vector2& vec);
        Vector2& operator-=(const Vector2& vec);
        Vector2& operator*=(const Vector2& vec);
        Vector2& operator/=(const Vector2& vec);

        friend std::ostream& operator<<(std::ostream& stream, const Vector2& vec);
};