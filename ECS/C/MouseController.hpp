#pragma once

#include <cstdio>
#include <ostream>
#include "Components.hpp"
#include "ECS/ECS.hpp"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_mouse.h"

#include "IS/Physics/Vector2.hpp"

class MouseController : public Component 
{
    private:
        Vector2 target;
        SDL_Rect *camera;
        bool requiresSelection = false;

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
            pathFinding->SetTarget(target);
            
            std::cout << "Player target: " << target << std::endl;
            std::cout << "Player position: " << transform->position << std::endl;
        } 

    public:
        TransformComponent *transform;
        PathFindingComponent *pathFinding;
        MouseSelectionComponent *selection = nullptr;

        MouseController() = default;
        MouseController(SDL_Rect *gameCamera) {
            camera = gameCamera;
        }

        MouseController(SDL_Rect *gameCamera, bool selection) {
            camera = gameCamera;
            requiresSelection = selection;
        }

        void init() override {
            transform = &entity->getComponent<TransformComponent>();
            pathFinding = &entity->getComponent<PathFindingComponent>();
        }

        void update() override {
            if (requiresSelection && selection == nullptr) {
                selection = &entity->getComponent<MouseSelectionComponent>();
            }

            if (requiresSelection && !selection->IsSelected()) {
                return;
            }

            if (Game::event.type == SDL_MOUSEBUTTONDOWN) {
                setTarget();
            }

            // Vector2 diff = target.Copy();
            // diff -= transform->position;
            // diff = diff.Round();
            //
            // if (diff.isZero()) {
            //     unset = true;
            //     transform->velocity.Zero();
            //     return;
            // }
            //
            // transform->velocity = diff.Normalize();
        };
};
