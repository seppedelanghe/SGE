#include "Collision.hpp"
#include "C/ColliderComponent.hpp"

Vector2* Collision::AABBDirection(const SDL_Rect& a, const SDL_Rect& b)
{
    if (!Collision::AABB(a, b))
    {
        return nullptr; // no collision
    }

    int axc = a.x + a.w / 2; // a.x center
    int ayc = a.y + a.h / 2; // a.y center
    
    int bxc = b.x + b.w / 2; // a.x center
    int byc = b.y + b.h / 2; // a.x center

    Vector2* cv = new Vector2();

    if (axc < bxc) // a is to the left of b
    {
        cv->x = -1.0f;
    } else if (axc > bxc) { // a is to the right of b
        cv->x = 1.0f;
    }

    if (ayc < byc) { // a is below b 
        cv->y = -1.0f;
    } else if (ayc > byc) {
        cv->y = 1.0f;
    }

    return cv;
}

Vector2* Collision::AABBDirection(const ColliderComponent& a, const ColliderComponent& b)
{
    return AABBDirection(a.collider, b.collider);
}



bool Collision::AABB(const SDL_Rect& a, const SDL_Rect& b)
{
    return a.x + a.w >= b.x &&
        b.x + b.w >= a.x &&
        a.y + a.h >= b.y &&
        b.y + b.h >= a.y;
}

bool Collision::AABB(const ColliderComponent& a, const ColliderComponent& b)
{
    return AABB(a.collider, b.collider);
}
