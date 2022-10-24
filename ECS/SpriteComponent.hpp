#pragma once

#include "Components.hpp"
#include "../TextureManager.hpp"
#include "SDL2/SDL.h"

class SpriteComponent : public Component
{
    private:
        TransformComponent *transform;
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;

    public:
        SpriteComponent() = default;
        SpriteComponent(const char* path)
        {
            setText(path);
        }

        ~SpriteComponent()
        {
            SDL_DestroyTexture(texture);
        }



        void setText(const char* path)
        {
            texture = TextureManager::LoadTexture(path);
        }

        void init() override
        {
            transform = &entity->getComponent<TransformComponent>();

            srcRect.x = srcRect.y = 0;
            srcRect.w = transform->width;
            srcRect.h = transform->height;

            destRect.w = transform->width * transform->scale;
            destRect.h = transform->height * transform->scale;
        }

        void update() override
        {
            destRect.x = static_cast<int>(transform->position.x);
            destRect.y = static_cast<int>(transform->position.y);
        }

        void draw() override
        {
            TextureManager::Draw(texture, srcRect, destRect);
        }
};