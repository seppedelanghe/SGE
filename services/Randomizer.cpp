

#include <cstdlib>
#include <ctime>
#include "Randomizer.hpp"
#include "IS/Physics/Vector2.hpp"


Randomizer::Randomizer()
{
    seed = time(NULL);
    srand(seed);
}

Randomizer::Randomizer(int s)
{
    seed = s;
}


float Randomizer::Float(const float min, const float max)
{
    return ((float)rand() / max) + min;
}

int Randomizer::Int(const int min, const int max)
{
    return static_cast<int>(Float((float)min, (float)max));
}

Vector2 Randomizer::Vec2(const float min, const float max)
{
    return Vector2(
        Float(min, max),
        Float(min, max)
    );
}
