#pragma once

#include "../Game.hpp"
#include "../ECS.hpp"

#include "Components.hpp"
#include "Vector2.hpp"
#include <cstdio>

class KeyboardController : public Component
{
    private:
        SDL_Keycode actionKey = SDLK_AMPERSAND;
        Vector2 direction;

        void updateDirection()
        {
            if (Game::event.type == SDL_KEYDOWN) 
            {                
                switch (Game::event.key.keysym.sym)
                {
                // NOTE: azerty
                case SDLK_z:
                    direction.y = -1;
                    break;
                
                case SDLK_s:
                    direction.y = 1;
                    break;

                case SDLK_q:
                    direction.x = -1;
                    break;
                
                case SDLK_d:
                    direction.x = 1;
                    break;

                case SDLK_SPACE:
                    actionKey = SDLK_SPACE;
                    break;

                case SDLK_ESCAPE:
                    Game::isRunning = false;
                    break;

                default:
                    break;
                }
            }
            
            if (Game::event.type == SDL_KEYUP)
            {
                switch (Game::event.key.keysym.sym)
                {
                // NOTE: azerty
                case SDLK_z:
                    direction.y = 0;
                    break;
                
                case SDLK_s:
                    direction.y = 0;
                    break;

                case SDLK_q:
                    direction.x = 0;
                    break;
                
                case SDLK_d:
                    direction.x = 0;
                    break;

                case SDLK_SPACE:
                    actionKey = SDLK_AMPERSAND;
                    break;

                default:
                    break;
                }
            }

            direction.Normalize();
            transform->velocity = direction;
        }

        void updateAnimation()
        {
            float XvsY = abs(direction.x) - abs(direction.y);
            std::string prefix = "";
            std::string animation = "";

            if (actionKey == SDLK_SPACE) {
                prefix = "Strike";
            }

            if (XvsY > 0) {
                if (direction.x < 0) {
                    animation = "Left";
                } else {
                    animation = "Right";
                }
            } else if (XvsY < 0) {
                if (direction.y < 0) {
                    animation = "Up";
                } else {
                    animation = "Down";
                }
            }

            animation = prefix + animation;
            if (animation.length() != 0) {
                printf("%s\n", animation.c_str());
                sprite->Play(animation.c_str());
            } else {
                sprite->Stop();
            }
        }

    public:
        TransformComponent *transform;
        SpriteComponent *sprite;

        bool IsActive()
        {
            return actionKey != SDLK_AMPERSAND || !direction.isZero();
        }

        void init() override
        {
            transform = &entity->getComponent<TransformComponent>();
            sprite = &entity->getComponent<SpriteComponent>();
        }

        void update() override
        {
            updateDirection();
            updateAnimation();
        }
};
