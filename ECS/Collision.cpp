#include "Collision.hpp"
#include "C/ColliderComponent.hpp"

bool Collision::AABB(const SDL_Rect& a, const SDL_Rect& b)
{
    return a.x + a.w >= b.x &&
        b.x + b.w >= a.x &&
        a.y + a.h >= b.y &&
        b.y + b.h >= a.y;
}

bool Collision::AABB(const ColliderComponent& a, const ColliderComponent& b)
{
    if (AABB(a.collider, b.collider))
    {
        return true;
    }

    return false;
}