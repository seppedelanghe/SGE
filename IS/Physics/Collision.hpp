#pragma once
#include "SDL.h"
#include "Vector2.hpp"

class ColliderComponent;

class Collision
{
    public:
        static Vector2* AABBDirection(const SDL_Rect& a, const SDL_Rect& b);
        static Vector2* AABBDirection(const ColliderComponent& a, const ColliderComponent& b);

        static bool AABB(const SDL_Rect& a, const SDL_Rect& b);
        static bool AABB(const ColliderComponent& a, const ColliderComponent& b);
};
