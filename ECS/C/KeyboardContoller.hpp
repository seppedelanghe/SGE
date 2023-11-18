#pragma once

#include "../Game.hpp"
#include "../ECS.hpp"

#include "Components.hpp"

class KeyboardController : public Component
{
    private:
        SDL_Keycode key = SDLK_AMPERSAND;

    public:
        TransformComponent *transform;
        SpriteComponent *sprite;

        bool IsActive()
        {
            return key != SDLK_AMPERSAND;
        }

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
                    transform->velocity.x = 0;
                    sprite->Play("Up");
                    break;
                
                case SDLK_s:
                    transform->velocity.y = 1;
                    transform->velocity.x = 0;
                    sprite->Play("Down");
                    break;

                case SDLK_q:
                    transform->velocity.x = -1;
                    transform->velocity.y = 0;
                    sprite->Play("Left");
                    break;
                
                case SDLK_d:
                    transform->velocity.x = 1;
                    transform->velocity.y = 0;
                    sprite->Play("Right");
                    break;

                case SDLK_SPACE:
                    

                case SDLK_ESCAPE:
                    Game::isRunning = false;
                    break;

                default:
                    break;
                }

                key = Game::event.key.keysym.sym;
            }

            if (Game::event.type == SDL_KEYUP)
            {
                if (Game::event.key.keysym.sym == key)
                {
                    transform->velocity.x = 0;
                    transform->velocity.y = 0;
                    sprite->Stop();
                    SDL_Keycode key = SDLK_AMPERSAND;
                }

            }
        }
};
