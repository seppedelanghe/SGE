#pragma once

#include "Components.hpp"
#include <string>
#include <sstream>

class HealthComponent : public Component
{
    private:
        int health;
        int maxHealth;

    public:
        HealthComponent()
        {
            health = 100;
            maxHealth = 100;
        }

        HealthComponent(int maxH)
        {
            maxHealth = maxH;
            health = maxH;
        }
        
        HealthComponent(int maxH, int startH)
        {
            maxHealth = maxH;
            health = startH;
        }

        void Decrease(int value = 1)
        {
            health -= value;
            if (health < 0) { health = 0; }
        }

        void Increase(int value = 1)
        {
            health += value;
            if (health > maxHealth) { health = maxHealth; }
        }

        int Value()
        {
            return health;
        }

        int Max()
        {
            return maxHealth;
        }

        bool Zero()
        {
            return health == 0;
        }

        bool IsMax()
        {
            return health == maxHealth;
        }

        std::string AsString()
        {
            std::stringstream ss;
            ss << "Health: " << health << " / " << maxHealth;
            return ss.str();
        }

        void Reset()
        {
            health = maxHealth;
        }
};