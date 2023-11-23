
#include "Vector2.hpp"
#include "AStar.hpp"
#include <algorithm>
#include <cstdio>

Node::Node(Vector2 coords_, Node* parent_ )
{
    parent = parent_;
    coordinates = coords_;
    G = H = 0;
};

uint Node::getScore()
{
    return G + H;
};

AStar::AStar(HeuristicFunction heuristicFn, int width, int height)
{
    heuristic = heuristicFn;
    w = width;
    h = height;
};

void AStar::UpdateSize(int width, int height)
{
    w = width;
    h = height;
};

void AStar::AddWall(Vector2 wall)
{
    auto it = std::find(walls.begin(), walls.end(), wall);
    if (it == walls.end()) {
        walls.push_back(wall);
    }
};

void AStar::RemoveWall(Vector2 wall)
{
    auto it = std::find(walls.begin(), walls.end(), wall);
    if (it != walls.end()) {
        walls.erase(it);
    }
};

void AStar::ClearWalls()
{
    walls.clear();
};

CoordinateList AStar::search(Vector2 origin, Vector2 target)
{
    Node* current;
    NodeSet open, closed;
    
    // Memory saving
    uint maxSize = (w * h) - walls.size();
    if (maxSize > 100) {
        maxSize = 100;
    }
    open.reserve(maxSize);
    closed.reserve(maxSize);
    
    // add start point
    open.push_back(new Node(origin));

    // while items in stack of open nodes
    while (!open.empty()) {
        auto current_it = open.begin();
        current = *current_it;

        // for each node stack of open nodes
        for (auto it = open.begin(); it != open.end(); it++) {
            auto node = *it;
            if (node->getScore() <= current->getScore()) {
                current = node;
                current_it = it;
            }
        }

        if (current->coordinates == target) {

            break;
        }

        closed.push_back(current);
        open.erase(current_it);


        for (Vector2 vec : direction) {
            Vector2 newCoordinates = current->coordinates.Copy();
            newCoordinates -= vec;

            if (isBlocked(newCoordinates, closed)) {
                continue;
            }

            uint cost = current->G + 10;
            Node* successor = findNode(newCoordinates, open);
            if (successor == nullptr) {
                successor = new Node(newCoordinates, current);
                successor->G = cost;
                successor->H = heuristic(successor->coordinates, target);
                open.push_back(successor);
            } else if (cost < successor->G) {
                successor->parent = current;
                successor->G = cost;
            }
        }
    }

    CoordinateList path;
    while (current != nullptr) {
        path.push_back(current->coordinates);
        current = current->parent;
    }
    
    // release
    for (auto it = open.begin(); it != open.end();) {
        delete *it;
        it = open.erase(it);
    }
    for (auto it = closed.begin(); it != closed.end();) {
        delete *it;
        it = closed.erase(it);
    }

    return path;    
};

bool AStar::isBlocked(Vector2 coord, NodeSet& closed)
{
    // check if coord is blocked by collision or is in closed nodes
    return (
        coord.x < 0 || coord.x >= w || coord.y < 0 || coord.y >= h ||
        std::find(walls.begin(), walls.end(), coord) != walls.end()
        ) || findNode(coord, closed) != nullptr;
};

Node* AStar::findNode(Vector2 coord, NodeSet& nodes)
{
    for (auto node : nodes) {
        if (node->coordinates == coord) {
            return node;
        }
    }

    return nullptr;
};


// heuristic

uint Heuristic::manhattan(Vector2 origin, Vector2 target)
{
    Vector2 delta = std::move(getDelta(origin, target));
    return static_cast<uint>(10 * (delta.x + delta.y));
}

uint Heuristic::euclidiean(Vector2 origin, Vector2 target)
{
    Vector2 delta = std::move(getDelta(origin, target));
    return static_cast<uint>(10 * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
}

uint Heuristic::octagonal(Vector2 origin, Vector2 target)
{
    Vector2 delta = std::move(getDelta(origin, target));
    return 10 * (delta.x + delta.y) + (-6) * std::min(delta.x, delta.y);
}

