#pragma once

#include "SDL.h"
#include <cstdio>
#include <map>
#include <string>

#include "Components.hpp"

#include "ECS/A/Animation.hpp"
#include "ECS/A/TextureManager.hpp"
#include "ECS/A/AssetManager.hpp"
#include "IS/Physics/Vector2.hpp"

class SpriteComponent : public Component
{
    private:
        TransformComponent *transform;
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;

        std::string activeAnimation;

        bool animated = false;
        bool controllable = true;
        bool moving = false;
        
        std::string action;
        Vector2 look;

        void updateAnimation()
        {
            if (!controllable) {
                return;
            }

            if (transform->velocity.isZero()) {
                moving = false;
            } else {
                look = transform->velocity.Clone().Ceil();
                moving = true;
            }

            std::string moveAnimation = "";
            float angle = look.angle(true);
            
            if (-45 < angle && angle <= 45) {
                moveAnimation = "Down";
            } else if (45 < angle && angle < 135) {
                moveAnimation = "Right";
            } else if ((135 < angle && angle <= 180) || (angle <= -135)) {
                moveAnimation = "Up";
            } else {
                moveAnimation = "Left";
            }

            if (!moving && action == "") {
                action = "Idle";
            } else if (moving && action == "Idle") {
                action = "";
            }

            if (action != "") {
                moveAnimation = moveAnimation + action;
            }
            
            Play(moveAnimation);
        }

    public:

        std::map<std::string, Animation> animations;

        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

        SpriteComponent() = default;
        SpriteComponent(std::string tId) {
            setTex(tId);
        }

        SpriteComponent(std::string tId, int nFrames, int mSpeed, int imgIndex) {
            animated = true;
            addAnimation("Idle", imgIndex, nFrames, mSpeed);

            Play("Idle");
            setTex(tId);
        }

        ~SpriteComponent() {}

        void addAnimation(std::string name, int index, int nFrames, int speed) {
            Animation a = Animation(index, nFrames, speed);
            animations.emplace(name, a);
        }

        void setTex(std::string tId) {
            texture = Game::assets->GetTexture(tId);
        }

        void setTexIndex(int x, int y) {
            srcRect.x = x * srcRect.w;
            srcRect.y = y * srcRect.h;
        }

        void init() override {
            transform = &entity->getComponent<TransformComponent>();
            
            srcRect.x = srcRect.y = 0;
            srcRect.w = transform->width;
            srcRect.h = transform->height;
        }

        void update() override {
            Animation *anim = &animations[activeAnimation];

            if (animated) {
                updateAnimation();
                srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / anim->speed) % anim->frames);
                srcRect.y = anim->index * transform->height;
            }

            destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
            destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
            
            destRect.w = static_cast<int>(transform->width * transform->scale);
            destRect.h = static_cast<int>(transform->height * transform->scale);
        }

        void draw() override {
            TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
        }

        void SetAction(std::string name) {
            action = name;
        }

        void UnsetAction() {
            action = "";
        }

        void Play(std::string name) {
            activeAnimation = name;
        }
};
