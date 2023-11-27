#include "IS/Physics/Vector2.hpp"


class Randomizer
{
    private:
        int seed;

    public:
        Randomizer();
        Randomizer(int seed);
        
        float Float(float min, float max);
        int Int(int min, int max);
        Vector2 Vec2(float min, float max);
};
