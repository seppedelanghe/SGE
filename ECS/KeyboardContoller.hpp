#pragma once

#include "../Game.hpp"
#include "ECS.hpp"
#include "Components.hpp"

class KeyboardController : public Component
{
    public:
        TransformComponent *transform;
        SpriteComponent *sprite;

        void init() override
        {
            transform = &entity->getComponent<TransformComponent>();
            sprite = &entity->getComponent<SpriteComponent>();
        }

        void update() override
        {
            if (Game::event.type == SDL_KEYDOWN) 
            {
                switch (Game::event.key.keysym.sym)
                {
                // NOTE: azerty
                case SDLK_z:
                    transform->velocity.y = -1;
                    sprite->Play("Walk");
                    break;
                
                case SDLK_s:
                    transform->velocity.y = 1;
                    sprite->Play("Walk");
                    break;

                case SDLK_q:
                    transform->velocity.x = -1;
                    sprite->Play("Walk");
                    sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                    break;
                
                case SDLK_d:
                    transform->velocity.x = 1;
                    sprite->Play("Walk");
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
                case SDLK_z: // w or z => azerty
                    transform->velocity.y = 0;
                    sprite->Play("Idle");
                    break;
                
                case SDLK_s:
                    transform->velocity.y = 0;
                    sprite->Play("Idle");
                    break;

                case SDLK_q:
                    sprite->Play("Idle");
                    transform->velocity.x = 0;
                    sprite->spriteFlip = SDL_FLIP_NONE;
                    break;
                
                case SDLK_d:
                    transform->velocity.x = 0;
                    sprite->Play("Idle");
                    break;

                default:
                    break;
                }
            }
        }
};