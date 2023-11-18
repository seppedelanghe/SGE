#pragma once

#include "Components.hpp"
#include "ECS.hpp"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_mouse.h"
#include "Vector2.hpp"
#include <cstdio>
#include <ostream>


class MouseController : public Component 
{
    private:
        Vector2 target;
        SDL_Rect *camera;
        bool unset = true;

        Vector2 cameraAdjust() {
            Vector2 adjust;
            if (camera != NULL) {
                adjust.x = (float)camera->x;
                adjust.y = (float)camera->y;
            }
            return adjust;
        }

        void setTarget()
        {
            int mouseX; int mouseY;

            SDL_GetMouseState(&mouseX, &mouseY);
            printf("Mouse: %d, %d\n", mouseX, mouseY);
            target.x = (float)mouseX;
            target.y = (float)mouseY;
            target += cameraAdjust();

            target -= Vector2((float)transform->width / 2, (float)transform->height / 2);

            unset = false;
            
            std::cout << "Player target: " << target << std::endl;
            std::cout << "Player position: " << transform->position << std::endl;
        }

        void setIdle() {
            sprite->Play("Idle");
        }

        void setAnimation(Vector2 diff)
        {
            // go left => -1
            // go right => 1
            //
            // go up => -1
            // go down => 1
            
            float XvsY = abs(diff.x) - abs(diff.y);
            if (XvsY > 0) {
                if (diff.x < 0) {
                    sprite->Play("Left");
                } else {
                    sprite->Play("Right");
                }
            } else if (XvsY < 0) {
                if (diff.y < 0) {
                    sprite->Play("Up");
                } else {
                    sprite->Play("Down");
                }
            } else {
                setIdle();
            }
        }

    public:
        TransformComponent *transform;
        SpriteComponent *sprite;

        MouseController() = default;
        MouseController(SDL_Rect *gameCamera)
        {
            camera = gameCamera;
        }

        void init() override 
        {
            transform = &entity->getComponent<TransformComponent>();
            sprite = &entity->getComponent<SpriteComponent>();
        }

        void update() override
        {
            if (Game::event.type == SDL_MOUSEBUTTONDOWN) {
                setTarget();
            }

            if (unset) { return; }

            Vector2 diff = target.Copy();
            diff -= transform->position;
            diff = diff.Round();

            if (diff.isZero()) {
                unset = true;
                transform->velocity.Zero();
                sprite->Stop();
                return;
            }

            transform->velocity = diff.Normalize();
            setAnimation(diff);
        };
};
