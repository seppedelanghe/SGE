#pragma once

#include "Components.hpp"
#include <string>

class PickupComponent : public Component
{
    private:
        std::string name;
        int points;
        int health;
        int energyRequired = 0;
        int energyLeft = 0;

    public:
        PickupComponent(std::string n) {
            name = n;
            points = 0;
            health = 0;
        }

        PickupComponent(std::string n, int p) {
            name = n;
            points = p;
            health = 0;
        }

        PickupComponent(int h, std::string n) {
            name = n;
            health = h;
            points = 0;
        }
        
        PickupComponent(std::string n, int p, int h) {
            name = n;
            points = p;
            health = h;
        }
    
        PickupComponent(std::string n, int p, int h, int e) {
            name = n;
            points = p;
            health = h;
            energyRequired = e;
            energyLeft = e;
        }


        bool GivesPoints() { return points != 0; }
        bool GivesHealth() { return health != 0; }
        bool Taken() { return points == 0 && health == 0; }
        bool Takeable() { return energyRequired == 0; }
        
        int Health() {
            return health;
        }

        int Points() {
            return points;
        }

        int TotalEnergyRequired() {
            return energyRequired;
        }

        int EnergyLeft() {
            return energyLeft;
        }
    
        void Take(Entity &e) {
            if (energyLeft > 0) {
                return;
            }

            try {
                e.getComponent<ScoreComponent>().Increase(points);
                points = 0;
            }
            catch(const std::exception& e) {
                std::cerr << "Could not take points" << '\n';
            }

            try {
                e.getComponent<HealthComponent>().Increase(health);
                health = 0;
            }
            catch(const std::exception& e) {
                std::cerr << "Could not take health" << '\n';
            }

            this->entity->destroy();
        }

        void Work(Entity &e) {
            // TODO: add work logic
            energyLeft -= 1;
        }

};
