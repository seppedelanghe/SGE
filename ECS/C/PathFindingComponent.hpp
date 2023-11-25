
#include <algorithm>
#include <cstdio>
#include <vector>

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

        void UpdateOrigin()
        {
            origin = transform->position.Clone();
            origin = origin / normalizer;
            origin = origin.Round();
        }

        void UpdatePath()
        {
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
            
            if (path.size() == 0) {
                UpdatePath(); 
            }
            
            FollowPath();

        };

        void SetNormilizer(int divider)
        {
            normalizer = Vector2(divider, divider);
        }

        void SetNormilizer(int x, int y)
        {
            normalizer = Vector2(x, y);
        }

        void SetTarget(Vector2 coord) 
        {
            target = coord / normalizer;
            target = target.Round();
            active = true;
        }
};
