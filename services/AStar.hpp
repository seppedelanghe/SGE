
#include "Vector2.hpp"
#include <vector>


struct Node {
    uint G, H;
    Vector2 coordinates;
    Node* parent;

    Node(Vector2 coords_, Node* parent_ = nullptr);
    uint getScore();
};

using HeuristicFunction = std::function<uint(Vector2, Vector2)>;
using NodeSet = std::vector<Node*>;
using CoordinateList = std::vector<Vector2>;

class AStar
{
    public:
        AStar(HeuristicFunction heuristicFn, uint width, uint height, uint directions = 4);
        void AddWall(Vector2 wall);
        void RemoveWall(Vector2 wall);
        void ClearWalls();
        CoordinateList search(Vector2 origin, Vector2 target);

    private:
        bool isBlocked(Vector2 coord, NodeSet& closed);
        Node* findNode(Vector2 coord, NodeSet& nodes);

        HeuristicFunction heuristic;
        CoordinateList walls;
        uint w, h, directions;

        // no diagonal
        CoordinateList direction = {
            { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 }
        };
};

class Heuristic
{
    static Vector2 getDelta(Vector2 origin, Vector2 target)
    {
        return Vector2(abs(origin.x-target.x), abs(origin.y-target.y));
    };

    public:
        static uint manhattan(Vector2 origin, Vector2 target);
        static uint euclidiean(Vector2 origin, Vector2 target);
        static uint octagonal(Vector2 origin, Vector2 target);
};
