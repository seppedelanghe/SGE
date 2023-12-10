
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <vector>

#include "SDL_render.h"

#include "ECS/C/TransformComponent.hpp"
#include "ECS.hpp"
#include "IS/Physics/Vector2.hpp"
#include "Services/AStar.hpp"


class PathFindingComponent : public Component
{
    private:
        AStar* finder;
        Vector2 origin;
        Vector2 target;
        Vector2 normalizer = Vector2(1, 1);
        CoordinateList path;
        bool active;

        void FollowPath()
        {
            if (path.size() == 0) {
                active = false;
                std::cout << "deactivate path finding" << std::endl;
                return;
            }
            
            UpdateOrigin();

            Vector2 vec = *(path.begin());
            Vector2 delta = vec.Clone();
            delta -= origin;

            if (delta.isZero()) {
                path.erase(path.begin());
                FollowPath();
            }

            transform->velocity = delta.Normalize();
        };

        void UpdateOrigin() {
            origin = transform->position.Clone();
            origin = origin / normalizer;
            origin = origin.Round();
        }

        void UpdatePath() {
            UpdateOrigin();

            path = finder->search(origin, target);
            std::reverse(path.begin(), path.end());

            for (Vector2 vec : path)
                std::cout << "Path " << vec << std::endl;
        }

    public:
        TransformComponent *transform;

        PathFindingComponent() = default;
        PathFindingComponent(AStar* astar) {
            finder = astar;
            active = false;
        }

        void init() override {
            transform = &entity->getComponent<TransformComponent>();
        };
        
        void update() override {
            if (!active) {
                return;
            }

            if (target.isZero()) {
                return;
            }
            
            if (path.size() == 0) {
                UpdatePath(); 
            }
            
            FollowPath();

        };

        void draw() override {
            if (Game::isDebug && active) {
                Vector2 absTarget = target.Clone();
                absTarget *= normalizer;
                std::cout << "abs t " << absTarget << std::endl;

                SDL_Rect rect;
                rect.x = absTarget.x - static_cast<int>(transform->width / 2);
                rect.y = absTarget.y - static_cast<int>(transform->height / 2);
                rect.w = transform->width;
                rect.h = transform->height;
                
                SDL_SetRenderDrawColor(Game::renderer, 255, 0, 255, 255);
                SDL_RenderDrawRect(Game::renderer, &rect);
            }
        }

        void SetNormilizer(int divider) {
            normalizer = Vector2(divider, divider);
        }

        void SetNormilizer(int x, int y) {
            normalizer = Vector2(x, y);
        }

        void SetTarget(Vector2 coord) {
            target = coord.Clone();
            target.x += static_cast<int>(transform->width / 2);
            target.y += static_cast<int>(transform->height / 2);
            target /= normalizer;
            target = target.Round();
            active = true;
        }
};
