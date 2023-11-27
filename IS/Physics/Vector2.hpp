#pragma once

#include <iostream>

class Vector2
{
    public:
        float x;
        float y;

        Vector2();
        Vector2(float x, float y);
        
        Vector2 Clone() const {
            return Vector2(x, y);
        }

        float angle(bool degrees);
        float length();
        bool isZero();
        bool isNormalized();

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

        bool operator==(const Vector2& vec);
        bool operator!=(const Vector2& vec);

        Vector2& operator*(const int& i);
        Vector2& Zero();
        Vector2& Normalize();
        Vector2& Round();
        Vector2& Ceil();
        Vector2& Floor();
        
        friend std::ostream& operator<<(std::ostream& stream, const Vector2& vec);
};
