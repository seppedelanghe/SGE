#pragma once

#include "SDL.h"
#include <cstdio>
#include <map>
#include <string>

#include "Components.hpp"

#include "../A/Animation.hpp"
#include "../A/TextureManager.hpp"
#include "../A/AssetManager.hpp"

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
        SpriteComponent(std::string tId)
        {
            setTex(tId);
        }

        SpriteComponent(std::string tId, int nFrames, int mSpeed, int imgIndex = 0)
        {
            animated = true;
            addAnimation("Idle", imgIndex, nFrames, mSpeed);

            Play("Idle");
            setTex(tId);
        }

        ~SpriteComponent()
        {
        }

        void addAnimation(const char* name, int index, int nFrames, int speed)
        {
            Animation a = Animation(index, nFrames, speed);
            animations.emplace(name, a);
        }

        void setTex(std::string tId)
        {
            texture = Game::assets->GetTexture(tId);
        }

        void init() override
        {
            transform = &entity->getComponent<TransformComponent>();

            srcRect.x = srcRect.y = 0;
            srcRect.w = transform->width;
            srcRect.h = transform->height;
        }

        void update() override
        {
            if (animated)
            {
                srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
            }

            srcRect.y = animIndex * transform->height;

            destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
            destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
            
            destRect.w = static_cast<int>(transform->width * transform->scale);
            destRect.h = static_cast<int>(transform->height * transform->scale);


        }

        void draw() override
        {
            TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
        }

        void Play(const char* name)
        {
            printf("Play: %s\n", name);
            frames = animations[name].frames;
            animIndex = animations[name].index;
            speed = animations[name].speed;
        }

        void Stop()
        {
            frames = 1;
        }
};
