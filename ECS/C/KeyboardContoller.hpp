#pragma once

#include "Game.hpp"
#include "ECS/ECS.hpp"

#include "Components.hpp"
#include "IS/Physics/Vector2.hpp"
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
                    sprite->SetAction("Strike");
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
                    sprite->UnsetAction();
                    break;

                default:
                    break;
                }
            }

            direction.Normalize();
            transform->velocity = direction;
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
        }
};
