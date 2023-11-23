#include "../services/AStar.hpp"
#include "C/TransformComponent.hpp"
#include "ECS.hpp"
#include "Vector2.hpp"
#include <algorithm>
#include <cstdio>
#include <vector>


class PathFindingController : public Component
{
    private:
        AStar* finder;
        Vector2 origin;
        Vector2 target;
        CoordinateList path;
        bool active;

        void FollowPath()
        {
            if (path.size() == 0) {
                active = false;
                std::cout << "deactivate path finding" << std::endl;
                return;
            }

            Vector2 vec = *(path.begin());
            vec = vec.Round();

            if (origin == vec) {
                path.erase(path.begin());
                FollowPath();
                return;
            }

            Vector2 delta = vec - origin;
            transform->velocity = delta.Normalize();
        };

    public:
        TransformComponent *transform;

        PathFindingController() = default;
        PathFindingController(AStar* astar) {
            finder = astar;
            active = false;
        }

        void init() override
        {
            transform = &entity->getComponent<TransformComponent>();
        };
        
        void update() override
        {
            if (!active) {
                return;
            }

            if (target.isZero()) {
                return;
            }
            
            origin = Vector2(transform->position.x / transform->width, transform->position.y / transform->height);
            origin = origin.Round();

            if (path.size() > 0) {
                FollowPath();
                return;
            }

            path = finder->search(origin, target);
            std::reverse(path.begin(), path.end());
        };

        void SetTarget(Vector2 coord) {
            
            target = coord;
            active = true;
        }
};
