#pragma once

#include "Components.hpp"
#include "../Vector2.hpp"

class TransformComponent : public Component
{
    private:
        int xpos;
        int ypos;

    public:

        Vector2 position;
        Vector2 velocity;

        int height = 32;
        int width = 32;
        int scale = 2;

        int speed = 3;

        TransformComponent()
        {
            position.Zero();
        }

        TransformComponent(int scl)
        {
            position.Zero();
            scale = scl;
        }

        TransformComponent(float x, float y) 
        {
            position.x = x;
            position.y = y;
        }

        TransformComponent(float x, float y, int w, int h, int scl)
        {
            position.x = x;
            position.y = y;
            height = h;
            width = w;
            scale = scl;
        }

        void init() override
        {
            velocity.Zero();
        }

        void update() override
        {
            // Move player
            position.x += velocity.x * speed;
            position.y += velocity.y * speed;
        }
};