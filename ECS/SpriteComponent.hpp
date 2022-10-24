#pragma once

#include "Components.hpp"
#include "../TextureManager.hpp"
#include "SDL2/SDL.h"
#include "Animation.hpp"
#include <map>

class SpriteComponent : public Component
{
    private:
        TransformComponent *transform;
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;

        bool animated = false;
        int frames = 0;
        int speed = 100; // delay between frames in ms

    public:
        int animIndex = 0;
        std::map<const char*, Animation> animations;

        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

        SpriteComponent() = default;
        SpriteComponent(const char* path)
        {
            setTex(path);
        }

        SpriteComponent(const char* path, int nFrames, int mSpeed)
        {
            animated = true;
            addAnimation("Idle", 0, nFrames, mSpeed);

            Play("Idle");

            setTex(path);
        }

        ~SpriteComponent()
        {
            SDL_DestroyTexture(texture);
        }

        void addAnimation(const char* name, int index, int nFrames, int speed)
        {
            Animation a = Animation(index, nFrames, speed);
            animations.emplace(name, a);
        }

        void setTex(const char* path)
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
            if (animated)
            {
                srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
            }

            srcRect.y = animIndex * transform->height;

            destRect.x = static_cast<int>(transform->position.x);
            destRect.y = static_cast<int>(transform->position.y);
        }

        void draw() override
        {
            TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
        }

        void Play(const char* name)
        {
            frames = animations[name].frames;
            animIndex = animations[name].index;
            speed = animations[name].speed;
        }
};