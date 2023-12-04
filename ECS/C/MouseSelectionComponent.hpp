#include "ECS.hpp"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_mouse.h"

#include "Vector2.hpp"
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <ostream>

#include "C/TransformComponent.hpp"


class MouseSelectionComponent : public Component
{
    private:
        enum selectionStates : std::size_t {
            unselected,
            clicked,
            active
        };

        selectionStates selected = selectionStates::unselected;

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

        void FlipSelection() {
            if (selected == selectionStates::unselected) {
                selected = selectionStates::clicked;
                printf("clicked\n");
            } else if (selected == selectionStates::active) {
                selected = selectionStates::unselected;
                printf("unselected\n");
            }
        }
        
        void CheckSelect(Vector2 clicked) {
            clicked = clicked.Round();

            Vector2 target = transform->position.Clone().Round();
            target += centerAlign;
            target += cameraAdjust();

            Vector2 diff = clicked - target;
            diff /= forgiveness;
            diff = diff.Round();

            if (diff.isZero()) {
                FlipSelection();
            }
        }

    public:
        TransformComponent *transform;

        MouseSelectionComponent() = default;
        MouseSelectionComponent(SDL_Rect *gameCamera) {
            camera = gameCamera;
        }
        MouseSelectionComponent(SDL_Rect *gameCamera, float centerAdjust) {
            camera = gameCamera;
            centerAlign = Vector2(centerAdjust, centerAdjust);
            forgiveness = Vector2(centerAdjust * 2, centerAdjust * 2);
        } 

        void init() override {
            transform = &entity->getComponent<TransformComponent>();
        }

        void update() override {
            // delay => activate after other components updated
            if (selected == selectionStates::clicked) {
                selected = selectionStates::active;
                printf("active\n");
                return;
            }

            if (Game::event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX,&mouseY);
                
                Vector2 clicked {
                    (float)mouseX, (float)mouseY
                };
                CheckSelect(clicked);
            }
        }

        bool IsSelected() {
            return selected == selectionStates::active;
        }
};
