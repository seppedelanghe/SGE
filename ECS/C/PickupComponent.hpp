#pragma once

#include "Components.hpp"
#include <string>

class PickupComponent : public Component
{
    private:
        std::string name;
        int points;
        int health;

    public:
        PickupComponent(std::string n)
        {
            name = n;
            points = 0;
            health = 0;
        }

        PickupComponent(std::string n, int p)
        {
            name = n;
            points = p;
            health = 0;
        }

        PickupComponent(int h, std::string n)
        {
            name = n;
            health = h;
            points = 0;
        }
        
        PickupComponent(std::string n, int p, int h)
        {
            name = n;
            points = p;
            health = h;
        }

        bool GivesPoints() { return points != 0; }
        bool GivesHealth() { return health != 0; }
        bool Taken() { return points == 0 && health == 0; }
        
        int Health()
        {
            return health;
        }

        int Points()
        {
            return points;
        }
        
        void Take(Entity &e)
        {
            try
            {
                e.getComponent<ScoreComponent>().Increase(points);
                points = 0;
            }
            catch(const std::exception& e)
            {
                std::cerr << "Could not take points" << '\n';
            }

            try
            {
                e.getComponent<HealthComponent>().Increase(health);
                health = 0;
            }
            catch(const std::exception& e)
            {
                std::cerr << "Could not take health" << '\n';
            }

            this->entity->destroy();
        }

};