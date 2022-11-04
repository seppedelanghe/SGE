#pragma once

#include "Components.hpp"
#include "Vector2.hpp"

class ProjectileComponent : public Component
{
    public:
        ProjectileComponent(int rng, int spd, Vector2 vel) : range(rng), speed(spd), velocity(vel)
        {}

        ~ProjectileComponent()
        {}

        void init() override
        {
            transform = &entity->getComponent<TransformComponent>();
            transform->velocity = velocity;
        }

        void update() override
        {
            distance += speed;

            if (distance > range)
            {
                entity->destroy();
                std::cout << "range limit" << std::endl;
            } else if (
                transform->position.x > Game::camera.x + Game::camera.w ||
                transform->position.x < Game::camera.x ||
                transform->position.y > Game::camera.y + Game::camera.h ||
                transform->position.y < Game::camera.y)
            {
                entity->destroy();
                std::cout << "Out of bounds" << std::endl;
            }
        }

    private:
        TransformComponent* transform;

        int range = 0;
        int speed = 0;
        int distance = 0;
        Vector2 velocity;
};