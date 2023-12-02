#include "ECS.hpp"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_mouse.h"

#include "Vector2.hpp"
#include <cstdio>
#include <iostream>
#include <ostream>

#include "C/TransformComponent.hpp"


class SelectionComponent : public Component
{
    private:
        bool selected = false;
        SDL_Rect* camera;
        Vector2 centerAlign = Vector2(8, 8);
        Vector2 forgiveness = Vector2(16, 16);

        Vector2 cameraAdjust() {
            Vector2 adjust;
            if (camera != NULL) {
                adjust.x = (float)camera->x;
                adjust.y = (float)camera->y;
            }

            return adjust;
        }
        
        void CheckSelect(Vector2 clicked) {
            clicked = clicked.Round();

            Vector2 target = transform->position.Clone().Round();
            target += centerAlign;
            target += cameraAdjust();

            Vector2 diff = clicked - target;
            diff /= forgiveness;
            diff = diff.Round();

            selected = diff.isZero();
            printf("Selected: %x\n", selected);
        }

    public:
        TransformComponent *transform;

        SelectionComponent() = default;
        
        SelectionComponent(SDL_Rect *gameCamera) {
            camera = gameCamera;
        }

        SelectionComponent(SDL_Rect *gameCamera, float centerAdjust) {
            camera = gameCamera;
            centerAlign = Vector2(centerAdjust, centerAdjust);
            forgiveness = Vector2(centerAdjust * 2, centerAdjust * 2);
        } 

        void init() override {
            transform = &entity->getComponent<TransformComponent>();
        }

        void update() override {
            if (Game::event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX,&mouseY);
                
                Vector2 clicked {
                    (float)mouseX, (float)mouseY
                };
                CheckSelect(clicked);
            }
        }
};
